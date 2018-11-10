#include "pbit.h"
#include "pbit_listener.h"
#include "pbit_result.h"
#include "buffer_pbit_io.h"

static struct pbit_all_results p_results[MAX_PBITS];
static unsigned int result_index = 0;

void pbit_result_init(struct pbit_result *self, struct pbit_listener *listener)
{
    self->run_count = 0;
    self->failure_count = 0;
    self->listener = listener;
}

void pbit_result_start_pbit(struct pbit_result *self, struct PBIT *pbit)
{
    if (self->listener) 
        PBIT_LISTENER_START_PBIT(self->listener, pbit);
}

void pbit_result_end_pbit(struct pbit_result *self, struct PBIT *pbit)
{
    if (self->listener) 
        PBIT_LISTENER_END_PBIT(self->listener, pbit);
}

static int pbit_result_exists_for_pbit(const char *name)
{
    int i = 0;

    for (i = 0; i < result_index; i++)
        if (strncmp(p_results[i].pbit_name, name, MAX_PBIT_LEN) == 0)
            return i;

    return -1;
}

static void pbit_set_results(struct PBIT *pbit, const char *name, enum pbit_res res, void *data)
{
    unsigned int result_backup;
    int index = pbit_result_exists_for_pbit(name);

    /*
     * if there was a previous pbit
     * overwrite its value
     */
    if (index != -1) {
        result_backup = result_index;
        result_index = index;
    }

    if (result_index >= MAX_PBITS)
        result_index = 0;

    memcpy(p_results[result_index].pbit_name, name, strlen(name)); 
    p_results[result_index].results.res = res;
    p_results[result_index].results.data = data;

    /* restore values */
    if (index != -1)
        result_index = result_backup;
    else
        result_index++;
}

void pbit_result_add_failure(struct pbit_result *self, 
                             struct PBIT *pbit,
                             const char *name,
                             const char *msg, int line,
                             const char* file,
                             enum pbit_res res,
                             void *data)
{
    self->failure_count++;
    if (self->listener) {
        PBIT_LISTENER_ADD_FAILURE(self->listener, pbit, msg, line, file);
        pbit_set_results(pbit, name, res, data);
    }
}

void pbit_result_add_pbit_ok(struct pbit_result *self,
                             struct PBIT *pbit,
                             const char *name,
                             const char *msg, int line,
                             const char* file,
                             enum pbit_res res,
                             void *data)
{
    if (self->listener) {
        PBIT_LISTENER_ADD_PBIT_OK(self->listener, pbit, msg, line, file);
        pbit_set_results(pbit, name, res, data);
    }
}

void pbit_result_update_run_pbits(struct pbit_result *self)
{
    self->run_count++;
}

void pbit_result_statistics(struct pbit_result *self)
{
    printk("PBITs OK: %d\n", self->run_count - self->failure_count);
    printk("PBITs FAILED: %d\n", self->failure_count);
    printk("Total pbit run: %d\n", self->run_count);
}

struct pbit_results *pbit_get_result(const char *name)
{
    int i = 0;

    for (i = 0; i < result_index; i++)
        if (strncmp(p_results[i].pbit_name, name, MAX_PBIT_LEN) == 0)
            return &p_results[i].results;

    return NULL;
}

struct pbit_all_results *pbit_get_results(void)
{
    return &p_results[0];
}

unsigned int pbit_get_num_pbits(void)
{
    return result_index;
}
