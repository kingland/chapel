_extern def chpl_malloc(number, size, description, lineno = -1, filename = ""): opaque;

while (1) {
  var i = 1000000;
  chpl_malloc(i, numBytes(int(64)), "malloc test", 5, "mallocOutOfMemory.chpl");
}
