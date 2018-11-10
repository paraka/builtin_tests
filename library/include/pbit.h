/**
 * @file pbit.h
 *
 * @brief This file includes data structures and functions related
 *  to a pbit inside the library. This is the general abstraction
 *  of all of the types of pbit in the system: pbit cases
 *
 * @author: Sergio Paracuellos <sergio.paracuellos@gmail.com> 
 */

#ifndef PBIT_H_
#define PBIT_H_

#ifdef  __cplusplus
extern "C" {
#endif

/* forward declaration */
struct pbit_result;

/**
 * @brief type definition for pbit_name callback method
 */
typedef char *(*pbit_name)(void *self);

/**
 * @brief type definition for pbit_run callback method
 */
typedef void (*pbit_run)(void *self, struct pbit_result *result);

/**
 * @brief type definition for pbit_count_pbit_cases callback method
 */
typedef int (*pbit_count_pbit_cases)(void *self);

/**
 * @struct pbit_implement
 *
 * @brief this is the internal representation of the implementation
 *       of a pbit inside the library. It always have three methods
 *       associated with itself. These will be pointer to functions
 *       that the new pbit type MUST overwrite.
 *
 * @note this struct contains the callbacks that should be overwritten
 *  in derived classes.
 */
struct pbit_implement 
{
    pbit_name name; /**< this will call the name function for the pbit inside the library */
    pbit_run run; /**< this will call the run function for the pbit inside the library */
    pbit_count_pbit_cases count_tcs; /**< this will call the pbit cases'count function fot the pbit inside the library */
};

/**
 * @struct PBIT
 *
 * @brief the 'pbit' abstraction itself to export to derived types.
 *
 * @note real pbit_implement callback method will be accesed from this struct.
 *
 * @see pbit_implement
 */
struct PBIT
{
    struct pbit_implement *impl; /** pointer to the pbit_implement functions. This pointer will be the correct one for the current pbit */
};

/**
 * @brief This macro call the pbit_name callback for the current pbit.
 *
 * @note This will be done accessing impl pointer from the correct struct.
 *
 * @see pbit_name
 * @see pbit_implement
 */
static inline const char *PBIT_NAME(struct PBIT *s)
{
    return s->impl->name(s);
}

/**
 * @brief This function call the pbit_run callback for the current pbit.
 *
 * @note This will be done accessing impl pointer from the correct struct.
 *
 * @see pbit_run
 * @see pbit_implement
 */
static inline void PBIT_RUN(struct PBIT *s, struct pbit_result *r)
{
    s->impl->run(s,r);
}

/**
 * @brief This function call the pbit_count_pbit_cases callback for the current pbit.
 *
 * @note This will be done accessing impl pointer from the correct struct.
 *
 * @see pbit_count_pbit_cases
 * @see pbit_implement
 */
static inline unsigned int PBIT_COUNT_TESCASES(struct PBIT *s)
{
    return s->impl->count_tcs(s);
}

#ifdef  __cplusplus
}
#endif

#endif /* PBIT_H_ */
