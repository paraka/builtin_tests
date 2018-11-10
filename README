# Description

Builtin tests is being used to test some hardware and other critical
stuff to decrease the probably of get a unexpected critical failure.
This library is a simple library to provide a common and general way
to write simple builtin test at boot and also retrieve its results and
rerun on normal system runtime providing for example the continuous bit
facility.

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
itself and its related fnctions using PBIT_TEST(name) library helper:

```
PBIT_TEST(pbit1)
{
    ADD_PBIT_TEST(tc_pbit1, PBIT1_NAME, pbit1_setup, pbit1_teardown, pbit1_run);
    PBIT_RETURN_TEST_REFERENCE(tc_pbit1);
}
```

Where:
    - tc_pbit1 is the pbit const reference inside the library (shall be unique).
    - PBIT1_NAME: defined name to identify the pbit.
    - pbit1_setup: setup function for the pbit (if any, set to 0 in any other case).
    - pbit1_teardown: teardown function for the pbit (if any, set to 0 in any other case).
    - pbit1_run: performs the pbit.

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

There are two macros to say the library we are ok or something was wrong (both of them
need the data to be passed to store it within the library):
    * PBIT_SET_OK(data)
    * PBIT_SET_FAIL(data)

And that's all. For more information see *sample* directory.

# Runtime dependencies to run in other systems

Have been maintain to a very few. These are:
* printk: provide a way to print. Simple printf family functions.
* strncmp: to secure compare few bytes in strings.
* memcpy: To copy memory.

Please see file *library/include/arch_os.h* for more information.

# References

Some implementation ideas are based in embedded unit framework.
