#ifndef _tasks_fifo_h_
#define _tasks_fifo_h_

#include <stdint.h>
#include CHPL_THREADS_H


//
// The FIFO implementation of tasking is a least-common-denominator
// version whose purpose is to minimize the work needed to get Chapel
// tasking working on top of some new threading layer.
//
// The threading layer only has to supply a small amount of support in
// the form of supplementary types and callback functions.  The
// complete list is:
//
// For mutexes
//   type(s)
//     threadlayer_mutex_t
//     threadlayer_mutex_p
//   functions
//     threadlayer_mutex_init()
//     threadlayer_mutex_new()
//     threadlayer_mutex_lock()
//     threadlayer_mutex_unlock()
//
// For thread management
//   type(s)
//     <none>
//   functions
//     threadlayer_thread_id()
//     threadlayer_yield()
//
// For task management
//   type(s)
//     <none>
//   functions
//     threadlayer_init()
//     threadlayer_thread_create()
//     threadlayer_get_thread_private_data()
//     threadlayer_set_thread_private_data()
//     threadlayer_call_stack_size()
//     threadlayer_call_stack_size_limit()
//
// The types are declared in the threads-*.h file for each specific
// threading layer, and the callback functions are declared here.  The
// interfaces and requirements for these other types and callback
// functions are described elsewhere in this file.
//
// Although the above list may seem long, in practice many of the
// functions are quite simple, and with luck also easily extrapolated
// from what is done for other threading layers.  For an example of an
// implementation, see "pthreads" threading.
//


//
// Type (and default value) used to communicate task identifiers
// between C code and Chapel code in the runtime.
//
typedef uint64_t chpl_taskID_t;
#define chpl_nullTaskID 0


//
// Thread management
//
threadlayer_threadID_t threadlayer_thread_id(void);
void threadlayer_yield(void);


//
// Sync variables
//
typedef struct {
  volatile chpl_bool is_full;
  threadlayer_mutex_t lock;
} chpl_sync_aux_t;


// Tasks

//
// Handy services for threading layer callback functions.
//
// The FIFO tasking implementation also provides the following service
// routines that can be used by threading layer callback functions.
//

//
// Is the task pool empty?
//
chpl_bool chpl_pool_is_empty(void);


//
// The remaining declarations are all for callback functions to be
// provided by the threading layer.
//

//
// These are called once each, from chpl_task_init() and
// chpl_task_exit().
//
void threadlayer_init(uint64_t callStackSize);
void threadlayer_exit(void);


//
// Mutexes
//
void threadlayer_mutex_init(threadlayer_mutex_p);
threadlayer_mutex_p threadlayer_mutex_new(void);
void threadlayer_mutex_lock(threadlayer_mutex_p);
void threadlayer_mutex_unlock(threadlayer_mutex_p);


//
// Task management
//

//
// Create a new thread.
//
int threadlayer_thread_create(threadlayer_threadID_t*, void*(*)(void*), void*);


//
// Thread private data
//
// These set and get a pointer to thread private data associated with
// each thread.  This is for the use of the FIFO tasking implementation
// itself.  If the threading layer also needs to store some data private
// to each thread, it must make other arrangements to do so.
//
void  threadlayer_set_thread_private_data(void*);
void* threadlayer_get_thread_private_data(void);


//
// Thread stack sizes
//
uint64_t threadlayer_call_stack_size(void);
uint64_t threadlayer_call_stack_size_limit(void);

#endif
