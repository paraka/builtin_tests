#include <libpbit.h>
#include "pbit2.h"

static void pbit2_setup(void)
{
    printk("PBIT2 SET UP...\n");
}

static void pbit2_run(void)
{
    printk("PBIT2 RUNNING...\n");
    PBIT_SET_OK(0);
}

static void pbit2_teardown(void)
{
    printk("PBIT2 TEAR DOWN...\n");
}

PBIT_TEST(pbit2)
{
    ADD_PBIT_TEST(tc_pbit2, PBIT2_NAME, pbit2_setup, pbit2_teardown, pbit2_run);
    PBIT_RETURN_TEST_REFERENCE(tc_pbit2);
}
