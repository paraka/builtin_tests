# Description

Builtin tests is used to test some hardware and other critical stuff
to decrease the probably of getting an unexpected critical failure.
This is a simple library to provide a common and general way to write 
simple builtin test at boot (pbit) and also retrieve its results and
rerun on normal system runtime providing for example the continuous bit
(cbit) facility.

# Directory contents

* *library*: contents the main pbit framework main files.  
* *sample*: contents a sample of how to use the library.

# How all of this works

The main code in compiled as a static library *libpbit.a*. All objects
in the library are allocated to const area.

There is a sample included to understand how to write a pbit, bit the
idea is simple:

Create a header for the new pbit defining a name for it and the data
structures are going to be used:

```
$ cat pbit1.h

#define PBIT1_NAME   "PBIT1"

struct pbit1_data
{
    unsigned int foo;
    unsigned int bar;
};
```

Create an implementation file for the pbit and define the pbit test
itself and its related functions using *PBIT_TEST(name)* library helper:

```
PBIT_TEST(pbit1)
{
    ADD_PBIT_TEST(tc_pbit1, PBIT1_NAME, pbit1_setup, pbit1_teardown, pbit1_run);
    PBIT_RETURN_TEST_REFERENCE(tc_pbit1);
}
```

Where:
* *tc_pbit1*: is the pbit const reference inside the library (shall be unique).
* *PBIT1_NAME*: defined name to identify the pbit.
* *pbit1_setup*: setup function for the pbit (if any, set to 0 in any other case).
* *pbit1_teardown*: teardown function for the pbit (if any, set to 0 in any other case).
* *pbit1_run*: performs the pbit.

As you can guess this is always executed in the following order:

```
    ...

    setup();
    run();
    teardown();

    ...
```

Now is time to implement the functions (putting all together and using dummy stuff):

```
#include <libpbit.h>
#include "pbit1.h"

static struct pbit1_data data;

static void pbit1_setup(void)
{
    printk("PBIT1 SET UP...\n");
}

static void pbit1_run(void)
{
    printk("PBIT1 RUNNING...\n");
    data.foo = 4;
    data.bar = 5;
    PBIT_SET_OK(&data);
}

static void pbit1_teardown(void)
{
    printk("PBIT1 TEAR DOWN...\n");
}

PBIT_TEST(pbit1)
{
    ADD_PBIT_TEST(tc_pbit1, PBIT1_NAME, pbit1_setup, pbit1_teardown, pbit1_run);
    PBIT_RETURN_TEST_REFERENCE(tc_pbit1);
}
```

There are two macros to say to the library if we are ok or if something was wrong
(both of them need the data to be passed to store it within the library):
* *PBIT_SET_OK(data)*
* *PBIT_SET_FAIL(data)*

And that's all. For more information please see *sample* directory contents.

# Runtime dependencies to run in other systems

Have been maintained to a very few. These are:
* *printk*: provide a way to print. Simple printf family functions.
* *strncmp*: to secure compare few bytes in strings.
* *memcpy*: To copy data between memory.

Please see file *library/include/arch_os.h* for more information.

# Compile and test

Build system is based in *Makefiles*. A main *Makefile* is included in root directory.
To compile the library and the provided sample just type 'make'. A new *build* directory
will be created and store the new compiled binaries:

```
$ make

make[1]: Entering directory '/home/sergio/Descargas/pbit/builtin_tests/library'
gcc -c -Iinclude -fPIC -O2 -g -Wall -c -o ../build/obj/pbit_test.o  src/pbit_test.c
gcc -c -Iinclude -fPIC -O2 -g -Wall -c -o ../build/obj/pbit_runner.o  src/pbit_runner.c
gcc -c -Iinclude -fPIC -O2 -g -Wall -c -o ../build/obj/pbit_result.o  src/pbit_result.c
ar -r -o ../build/lib/libpbit.a ../build/obj/pbit_test.o ../build/obj/pbit_runner.o ../build/obj/pbit_result.o
make[1]: Leaving directory '/home/sergio/Descargas/pbit/builtin_tests/library'
(cd sample; make)
make[1]: Entering directory '/home/sergio/Descargas/pbit/builtin_tests/sample'
gcc -c -I../library/include -Wall -c -o ../build/obj/pbit2.o  pbit2.c
gcc -c -I../library/include -Wall -c -o ../build/obj/pbit3.o  pbit3.c
gcc -c -I../library/include -Wall -c -o ../build/obj/main.o  main.c
gcc -c -I../library/include -Wall -c -o ../build/obj/pbit_exec.o  pbit_exec.c
gcc -c -I../library/include -Wall -c -o ../build/obj/pbit1.o  pbit1.c
gcc ../build/obj/pbit2.o ../build/obj/pbit3.o ../build/obj/main.o ../build/obj/pbit_exec.o ../build/obj/pbit1.o ../build/lib/libpbit.a -o ../build/bin/pbit_sample
make[1]: Leaving directory '/home/sergio/Descargas/pbit/builtin_tests/sample'
```

The library has been stored inside *lib* subdirectory and the sample binary in *bin*:

```
$ cd build
build $ ls -l *

bin:
total 40
-rwxrwxr-x 1 sergio sergio 39528 Nov 10 12:47 pbit_sample

lib:
total 52
-rw-rw-r-- 1 sergio sergio 49446 Nov 10 12:47 libpbit.a

obj:
total 80
-rw-rw-r-- 1 sergio sergio  4328 Nov 10 12:47 main.o
-rw-rw-r-- 1 sergio sergio  2608 Nov 10 12:47 pbit1.o
-rw-rw-r-- 1 sergio sergio  2472 Nov 10 12:47 pbit2.o
-rw-rw-r-- 1 sergio sergio  2640 Nov 10 12:47 pbit3.o
-rw-rw-r-- 1 sergio sergio  2080 Nov 10 12:47 pbit_exec.o
-rw-rw-r-- 1 sergio sergio 21984 Nov 10 12:47 pbit_result.o
-rw-rw-r-- 1 sergio sergio 17184 Nov 10 12:47 pbit_runner.o
-rw-rw-r-- 1 sergio sergio  9584 Nov 10 12:47 pbit_test.o
```

Execute sample binary:

```
*** BEGIN OF PBIT ***

--> Starting execution of pbit PBIT1 ---
PBIT1 SET UP...
PBIT1 RUNNING...
[ OK ] PBIT1.PBIT1 - PBIT OK
PBIT1 TEAR DOWN...
<-- Ending executing of pbit PBIT1 ---


--> Starting execution of pbit PBIT2 ---
PBIT2 SET UP...
PBIT2 RUNNING...
[ OK ] PBIT2.PBIT2 - PBIT OK
PBIT2 TEAR DOWN...
<-- Ending executing of pbit PBIT2 ---


--> Starting execution of pbit PBIT3 ---
PBIT3 SET UP...
PBIT3 RUNNING...
[FAIL] PBIT3.PBIT3 - PBIT FAIL (pbit3.c:16)
PBIT3 TEAR DOWN...
<-- Ending executing of pbit PBIT3 ---

PBITs OK: 2
PBITs FAILED: 1
Total pbit run: 3
*** END OF PBIT ***

Example of retrieving individual results:
PBIT1 DATA:
	- res: PBIT_OK
	- foo: 4
	- bar: 5
PBIT3 DATA:
	- res: PBIT_FAIL
	- str: FOO BAR
	- enabled: 0

Example of retrieving all results:
Number of PBITS: 3
PBIT: PBIT1 -> res: PBIT_OK
PBIT: PBIT2 -> res: PBIT_OK
PBIT: PBIT3 -> res: PBIT_FAIL

Example of running PBIT code as CBIT:

--> Starting execution of pbit PBIT1 ---
PBIT1 SET UP...
PBIT1 RUNNING...
[ OK ] PBIT1.PBIT1 - PBIT OK
PBIT1 TEAR DOWN...
<-- Ending executing of pbit PBIT1 ---
```

All the generated stuff can be deleted just typing *make clean*:

```
$ make clean

(cd library; make clean)
make[1]: Entering directory '/home/sergio/Descargas/pbit/builtin_tests/library'
rm -rf ../build
make[1]: Leaving directory '/home/sergio/Descargas/pbit/builtin_tests/library'
(cd sample; make clean)
make[1]: Entering directory '/home/sergio/Descargas/pbit/builtin_tests/sample'
rm -rf ../build/obj ../build/bin
make[1]: Leaving directory '/home/sergio/Descargas/pbit/builtin_tests/sample'
rm -f core
```

# References

Some implementation ideas are based in embedded unit framework.
