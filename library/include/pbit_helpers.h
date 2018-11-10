/**
 * @file pbit_helpers.h
 *
 * @brief This file contains macros to do the life easier to the
 *  pbit developer. It clearly hide all implementation levels of
 *  the library exposing a easy framework to pbit real code.
 *
 * @author: Sergio Paracuellos <sergio.paracuellos@gmail.com> 
 */

#ifndef PBIT_HELPERS_H_
#define PBIT_HELPERS_H_

/**
 * @brief this macros hide the details of the use of the library to
 *  the pbit developer making a really straighforward way for do
 *  a PBIT
 */

/* implemented in test_pbit.c */
extern void add_pbit_ok(const char *msg, int line, const char *file, enum pbit_res res, void *data);
extern void add_pbit_failure(const char *msg, int line, const char *file, enum pbit_res res, void *data);

/**
 * @brief PBIT_SET_OK Set PBIT result as ok.
 */
#define PBIT_SET_OK(data) \
    add_pbit_ok("PBIT OK", __LINE__, __FILE__, PBIT_OK, data);

/**
 * @brief PBIT_SET_OK Set PBIT result as fail.
 */
#define PBIT_SET_FAIL(data) \
    add_pbit_failure("PBIT FAIL", __LINE__, __FILE__, PBIT_FAIL, data);

/**
 * @brief this macro makes a new pbit_test for the specified data
 *
 * @see pbit_case
 * @see NEW_PBIT_CASE 
 */
#define ADD_PBIT_TEST(ca, name, sup, tdw, run) \
    static const struct pbit_test ca = NEW_PBIT_TEST(name, sup, tdw, run)

/**
 * @brief this macro defines a PBIT test. All test must have this signature.
 */
#define PBIT_TEST(pbit_name) \
    struct PBIT *pbit_name(void)

/**
 * @brief this macro defines reference for the new created pbit
 *
 * @see PBIT_TEST
 */
#define PBIT_RETURN_TEST_REFERENCE(var) \
    return (struct PBIT *)&var;

/**
 * @brief this function starts execution of a runner.
 *
 * @note this must be called before doing anything.
 *
 * @see pbit_runner_start
 */
static inline void PBIT_TEST_RUNNER_START(void)
{
    pbit_runner_start();
}

/**
 * @brief this macro says the runner to run a pbit.
 *
 * @note specified pbit_name must have the signature specified by PBIT_TEST macro.
 *
 * @see PBIT_TEST
 * @see pbit_runner_run_pbit
 */
static inline void PBIT_RUN_TEST(struct PBIT *(*pbit_name)(void))
{
    pbit_runner_run_pbit(pbit_name());
}

/**
 * @brief this function stop the execution of running runner.
 *
 * @note this must be called after all pbits execution.
 *
 * @see pbit_runner_end
 */
static inline void PBIT_TEST_RUNNER_FINISH(void)
{
    pbit_runner_end();
}

#endif /* TEST_HELPERS_H_ */
