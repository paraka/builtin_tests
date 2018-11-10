#include <libpbit.h>
#include "pbit_exec.h"
#include "pbits.h"
#include "pbit1.h"
#include "pbit2.h"
#include "pbit3.h"

static inline const char * const pbit_result_str(enum pbit_res res)
{
    static const char * const res_str[] = {
        "PBIT_FAIL",
        "PBIT_OK",
        "PBIT_SKIP",
    };

    return res_str[res];
}

static void pbit1_debug_results(struct pbit_results *res)
{
    struct pbit1_data *data = (struct pbit1_data *)res->data;

    printk("PBIT1 DATA:\n");
    printk("\t- res: %s\n", pbit_result_str(res->res));
    printk("\t- foo: %d\n", data->foo);
    printk("\t- bar: %d\n", data->bar);
}

static void pbit3_debug_results(struct pbit_results *res)
{
    struct pbit3_data *data = (struct pbit3_data *)res->data;

    printk("PBIT3 DATA:\n");
    printk("\t- res: %s\n", pbit_result_str(res->res));
    printk("\t- str: %s\n", data->str);
    printk("\t- enabled: %d\n", data->enabled);
}

static void pbit_debug_get_all_results(void)
{
    unsigned int num_pbits = pbit_get_num_pbits();
    struct pbit_all_results *all_res = pbit_get_results();
    int i;

    printk("Number of PBITS: %d\n", num_pbits);
    for (i = 0; i < num_pbits; i++) {
        printk("PBIT: %s -> res: %s\n",
               all_res->pbit_name, pbit_result_str(all_res->results.res));
        all_res++;
    }
}

static void cbit_pbit1(void)
{
    PBIT_RUN_TEST(pbit1);
}

int main(void)
{
    launch_pbit_tests();

    printk("\nExample of retrieving individual results:\n");

    struct pbit_results *res = pbit_get_result(PBIT1_NAME);
    if (!res) {
        printk("NULL res\n");
        return -1;
    }

    pbit1_debug_results(res);

    res = pbit_get_result(PBIT3_NAME);
    if (!res) {
        printk("NULL res\n");
        return -1;
    }

    pbit3_debug_results(res);

    printk("\nExample of retrieving all results:\n");

    pbit_debug_get_all_results();

    printk("\nExample of running PBIT code as CBIT:\n");
    cbit_pbit1();

    return 0;
}
