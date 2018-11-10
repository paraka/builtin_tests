#include "pbit.h"
#include "pbit_test.h"
#include "pbit_result.h"

static struct pbit_result *result_;
static struct pbit_test *self_;

char *pbit_case_name(struct pbit_test *self)
{
    return self->name;
}

void pbit_case_run(struct pbit_test *self, struct pbit_result *result)
{
    pbit_result_start_pbit(result, (struct PBIT *)self);

    /* execute set up function */
    if (self->set_up_cb) 
        self->set_up_cb();

    /* run the pbit */
    if (self->run_pbit_cb) 
    {
        /* assign values */
        struct pbit_result *wr = result_;
        struct pbit_test *ws = self_;
        result_ = result;
        self_ = self;
        self->run_pbit_cb();
        pbit_result_update_run_pbits(result);
        result_ = wr;
        self_ = ws;
    }

    /* execute tear down function */
    if (self->tear_down_cb) 
        self->tear_down_cb();

    pbit_result_end_pbit(result, (struct PBIT *)self);
}

int pbit_case_count_tcs(struct pbit_test *self)
{
    return 1;
}

const struct pbit_implement pbit_pbit_implement = {
    (pbit_name)             pbit_case_name,
    (pbit_run)              pbit_case_run,
    (pbit_count_pbit_cases) pbit_case_count_tcs,
};

void add_pbit_failure(const char *msg, int line, const char *file, enum pbit_res res, void *data)
{
    pbit_result_add_failure(result_, (struct PBIT *)self_,
                            self_->name, msg, line, file, res, data);
}

void add_pbit_ok(const char *msg, int line, const char *file, enum pbit_res res, void *data)
{
    pbit_result_add_pbit_ok(result_, (struct PBIT *)self_,
                            self_->name, msg, line, file, res, data);
}
