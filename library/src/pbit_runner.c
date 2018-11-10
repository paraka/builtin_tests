#include "libpbit.h"
#include "pbit_listener.h"

static struct pbit_result result_;
static struct PBIT *start_;

/* callbacks from this "object" */

static void pbit_runner_start_pbit(struct pbit_listener *self, struct PBIT *pbit)
{
    printk("\n--> Starting execution of pbit %s ---\n", PBIT_NAME(pbit));
}

static void pbit_runner_end_pbit(struct pbit_listener *self, struct PBIT *pbit)
{
    printk("<-- Ending executing of pbit %s ---\n\n", PBIT_NAME(pbit));
}

static void pbit_runner_add_failure(struct pbit_listener *self, struct PBIT *pbit, char *msg, int line, char *file)
{
    printk("[FAIL] %s.%s - %s (%s:%d)\n", PBIT_NAME(start_), PBIT_NAME(pbit), msg, file, line);
}

static void pbit_runner_add_ok(struct pbit_listener *self, struct PBIT *pbit, char *msg, int line, char *file)
{
    printk("[ OK ] %s.%s - %s\n", PBIT_NAME(start_), PBIT_NAME(pbit), msg);
}

/* object callback methods encapsulate struct */
static const struct pbit_listener_implement pbit_runner_implement =
{
    (pbit_listener_start_pbit_cb)  pbit_runner_start_pbit,
    (pbit_listener_end_pbit_cb)    pbit_runner_end_pbit,
    (pbit_listener_add_failure_cb) pbit_runner_add_failure,
    (pbit_listener_add_failure_cb) pbit_runner_add_ok,
};

/* this is my runner object */
static const struct pbit_listener pbit_runner_ =
{
    (struct pbit_listener_implement *)&pbit_runner_implement,
};

void pbit_runner_start(void)
{
    PBIT_BEGIN();
    /* assign result with this runner */
    pbit_result_init(&result_, (struct pbit_listener *)&pbit_runner_);
}

void pbit_runner_run_pbit(struct PBIT *pbit)
{
    start_ = pbit;
    PBIT_RUN(pbit, &result_);
}

void pbit_runner_end(void)
{
    pbit_result_statistics(&result_);
    PBIT_END();
}
