#include <libpbit.h>
#include "pbits.h"
#include "pbit_exec.h"

void launch_pbit_tests(void)
{
    PBIT_TEST_RUNNER_START();

    PBIT_RUN_TEST(pbit1);
    PBIT_RUN_TEST(pbit2);
    PBIT_RUN_TEST(pbit3);

    PBIT_TEST_RUNNER_FINISH();
}
