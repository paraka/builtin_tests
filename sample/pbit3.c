#include <libpbit.h>
#include "pbit3.h"

static struct pbit3_data data;

static void pbit3_setup(void)
{
    printk("PBIT3 SET UP...\n");
}

static void pbit3_run(void)
{
    printk("PBIT3 RUNNING...\n");
    data.str = "FOO BAR";
    data.enabled = false;
    PBIT_SET_FAIL(&data);
}

static void pbit3_teardown(void)
{
    printk("PBIT3 TEAR DOWN...\n");
}

PBIT_TEST(pbit3)
{
    ADD_PBIT_TEST(tc_pbit3, PBIT3_NAME, pbit3_setup, pbit3_teardown, pbit3_run);
    PBIT_RETURN_TEST_REFERENCE(tc_pbit3);
}
