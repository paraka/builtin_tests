/**
 * @file pbit_result.h
 *
 * @brief This file includes data structures and methods to control
 * results of the different pbits in the system. Every result has its
 * associated runner to be able to store and retrieve pbit statistics.
 *
 * @author: Sergio Paracuellos <sergio.paracuellos@gmail.com> 
 */

#ifndef PBIT_RESULT_H_
#define PBIT_RESULT_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief enum pbit_result - possible result value 
 * for the PBIT. 
 */
enum pbit_res
{
    PBIT_FAIL   = 0x0,
    PBIT_OK     = 0x1,
    PBIT_SKIP   = 0x2,
};

/**
 * @brief struct pbit_iface_result - PBIT 
 * relative results
 * @res: pbit result
 * @data: associated data results
 */
struct pbit_results
{
    enum pbit_res res;
    void *data;
};

#define MAX_PBIT_LEN    64
#define MAX_PBITS       32

/**
 * @brief struct pbit_all_results
 * @pbit_name: key for identify the PBIT
 * @results: results for the pbit
 */
struct pbit_all_results
{
    char pbit_name[MAX_PBIT_LEN];
    struct pbit_results results;
};

/**
 * @struct __pbit_result
 *
 * @brief stores global statistics of the execution
 */
struct pbit_result 
{
    unsigned int run_count; /**< number of pbits run */
    unsigned int failure_count; /**< number of pbits failed */
    struct pbit_listener *listener; /**< listener associated with this results */
};

/**
 * @brief HELPER to create a pbit_result 'object'.
 */
#define NEW_PBIT_RESULT(listener) \
    { 0, 0, (struct pbit_listener *)listener }

/**
 * @brief pbit_result_init init result object for the current runner.
 *
 * @param self pointer to itself
 * @param listener associated runner
 */
void pbit_result_init(struct pbit_result *self, struct pbit_listener *listener);


/**
 * @brief pbit_result_start_pbit start results for the pbits.
 *
 * @param self self pointer to itself
 * @param pbit current pbit to start results
 */
void pbit_result_start_pbit(struct pbit_result *self, struct PBIT *pbit);

/**
 * @brief pbit_result_end_pbit end results for the pbits.
 *
 * @param self self pointer to itself
 * @param pbit current pbit to end results
 */
void pbit_result_end_pbit(struct pbit_result *self, struct PBIT *pbit);

/**
 * @brief pbit_result_add_failure increment failures for this run.
 *
 * @param self   self pointer to itself
 * @param pbit   associated pbit which the fail
 * @param msg    associated message for the faile
 * @param line   line where the failure occurred
 * @param file   file where the failure occurred
 */
void pbit_result_add_failure(struct pbit_result *self,
                             struct PBIT *pbit,
                             const char *pbit_name,
                             const char* msg, int line,
                             const char* file,
                             enum pbit_res res,
                             void *data);

/**
 * @brief pbit_result_add_pbit_ok sets run pbit as correct
 *
 * @param self   self pointer to itself
 * @param pbit   associated correct pbit
 * @param msg    associated message for the ok pbit
 * @param line   line where the ok occurred
 * @param file   file where the ok occurred
 */
void pbit_result_add_pbit_ok(struct pbit_result *self,
                             struct PBIT *pbit,
                             const char *pbit_name,
                             const char* msg, int line,
                             const char* file,
                             enum pbit_res res,
                             void *data);

/**
 * @brief pbit_result_update_run_pbits updates run_counter
 *
 * @param self pointer to itself
 */
void pbit_result_update_run_pbits(struct pbit_result *self);

/**
 * @brief pbit_result_statistics show global statistics
 *
 * @param self pointer to itself
 */
void pbit_result_statistics(struct pbit_result *self);

/**
 * @brief pbit_get_result - get result for a desired PBIT
 *
 * @param name name of the pbit to retrieve its info
 *
 * @returns results for the pbit. NULL if no result available.
 */
struct pbit_results *pbit_get_result(const char *name);

/**
 * @brief pbit_get_results - get result for all PBIT
 *
 * @returns pointer to first element of the results array.
 */
struct pbit_all_results *pbit_get_results(void);

/**
 * @brief pbit_get_num_pbits - get number of PBIT results
 *
 * @returns number of PBITS
 */
unsigned int pbit_get_num_pbits(void);

#ifdef  __cplusplus
}
#endif

#endif /* PBIT_RESULT_H_*/
