use UnitTest;
//verifies that generic single argument functions aren't counted

/* A normal function which takes a generic single argument*/
proc dummy_test(test) throws {
    //This is a dummy test
    writeln("a");
}

/* A test function which takes Test Object as argument*/
proc test_square(test: borrowed Test) throws {
    // This is a test function
    writeln("b");
}

/* A test function which takes Test Object as argument*/
proc test_squared(test: borrowed Test) throws {
    // This is a test function
    writeln("c");
}
var test: owned Test = new owned Test();
var a = __primitive("gather tests", test.borrow());
writeln(a);
var c = __primitive("get test by name","test_squared");
var d = __primitive("get test by index",1);
c(test);
d(test);
