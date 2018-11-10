/**
 * @file pbit_test.h
 *
 * @brief This file includes data structures and functions related
 * to a pbit test inside the library.
 *
 * @author: Sergio Paracuellos <sergio.paracuellos@gmail.com> 
 */

#ifndef PBIT_TEST_H_
#define PBIT_TEST_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @struct pbit_test
 *
 * @brief representation for a pbit test within this library
 */
struct pbit_test 
{
    struct pbit_implement *impl; /**< correct implementation pointer to functions */
    char *name; /**< name of the test case */
    void (*set_up_cb)(void);
    void (*tear_down_cb)(void);
    void (*run_pbit_cb)(void);
};

/**
 * @brief this is the REAL implementation for this type 'pbit_test'
 * It will be defined inside the source code. It will contain real pointers
 * to its functions overwritten for the 'pbit' abstraction. The impl for this
 * will be pbit_pbit_implement type so the functions that will be called will
 * be the correct ones.
 */
extern const struct pbit_implement pbit_pbit_implement;

/**
 * @brief helper to create a new pbit case
 *
 * @note here we set the real impl pointer to call the correct callbacks for the 
 *  current running object. This will point to pbit_pbit_implement address.
 *
 * @see pbit_pbit_implement
 */
#define NEW_PBIT_TEST(name, set_up, tear_down, run_pbit) \
{ \
    (struct pbit_implement *)&pbit_pbit_implement, \
    name, \
    set_up, \
    tear_down, \
    run_pbit, \
}

#ifdef  __cplusplus
}
#endif

#endif /* PBIT_TEST_H */
