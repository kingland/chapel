class file {
  var filename : string = "";
  var mode : string = "r";
  var path : string = ".";
  var fp : CFILEPTR = _NULLCFILEPTR;

  function open {
    if (fp == _STDINCFILEPTR or fp == _STDOUTCFILEPTR or  
        fp == _STDERRCFILEPTR) {
      halt("It is not necessary to open \"", filename, "\".");
    }
    if (fp != _NULLCFILEPTR) {
      this.close;
    }

    var fullFilename = path + "/" + filename;
    fp = _fopen(fullFilename, mode);            

    if (fp == _NULLCFILEPTR) {
      halt("Unable to open \"", fullFilename, "\".");
    }
  }

  function isOpen: boolean {
    var openStatus: boolean = false;
    if (fp != _NULLCFILEPTR) {
      openStatus = true;
    }
    return openStatus;
  }

  function close {
    if (fp == _STDINCFILEPTR or fp == _STDOUTCFILEPTR or  
        fp == _STDERRCFILEPTR) {
      halt("You may not close \"", filename, "\".");
    }
    if (fp == _NULLCFILEPTR) {
      var fullFilename = path + "/" + filename;
      halt("Trying to close \"", fullFilename, "\" which isn't open.");
    }

    _fclose(fp);
    fp = _NULLCFILEPTR;
  }
}

const stdin  : file = file("stdin", "r", "/dev", _STDINCFILEPTR);
const stdout : file = file("stdout", "w", "/dev", _STDOUTCFILEPTR);
const stderr : file = file("stderr", "w", "/dev", _STDERRCFILEPTR);

function fopenError(f: file) {
  var fullFilename:string = f.path + "/" + f.filename;
  halt("You must open \"", fullFilename, "\" before writing to it.");    
}


pragma "rename _chpl_fwriteln"
function fwriteln(f: file = stdout) {
  if (f.isOpen) {
    fprintf(f.fp, "%s", "\n");
  } else {
    fopenError(f);
  }
}


pragma "rename _chpl_fwrite_integer"
function fwrite(f: file = stdout, val: integer) {
  if (f.isOpen) {
    fprintf(f.fp, "%lld", val);
  } else {
    fopenError(f);
  }
}


pragma "rename _chpl_fwrite_float"
function fwrite(f: file = stdout, val: float) {
  if (f.isOpen) {
     _chpl_fwrite_float_help(f.fp, val);
  } else {
    fopenError(f);
  }
}


pragma "rename _chpl_fwrite_string"
function fwrite(f: file = stdout, val: string) {
  if (f.isOpen) {
    fprintf(f.fp, "%s", val);
  } else {
    fopenError(f);
  }
}


pragma "rename _chpl_fwrite_boolean"
function fwrite(f: file = stdout, val: boolean) {
  if (f.isOpen) {
    if (val == true) {
      fprintf(f.fp, "%s", "true");
    } else {
      fprintf(f.fp, "%s", "false");
    }
  } else {
    fopenError(f);
  }
}


pragma "rename _chpl_fwrite_complex"
function fwrite(f: file = stdout, val: complex) {
  if (f.isOpen) {
    fprintf(f.fp, "%lg", val.real);
    fprintf(f.fp, "%s", " + ");
    fprintf(f.fp, "%lg", val.imag);
    fprintf(f.fp, "%s", "i");
  } else {
    fopenError(f);
  }
}


pragma "rename _chpl_fwrite_nil" 
function fwrite(f: file = stdout, x : _nilType) : void {
  if (f.isOpen) {
    fprintf(f.fp, "%s", "nil");
  } else {
    fopenError(f);
  }
}


function write() {
  halt("This should never be called.  All write calls should be converted to fwrites.");
}
