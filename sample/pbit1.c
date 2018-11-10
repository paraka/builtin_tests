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
