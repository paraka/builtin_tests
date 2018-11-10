/**
 * @file pbit_listener.h
 *
 * @brief This file include data structures and functions related
 *  to a listener inside the library. This is the common abstraction
 *  for a runner. 
 *
 * @author: Sergio Paracuellos <sergio.paracuellos@gmail.com> 
 */

#ifndef PBIT_LISTENER_H_
#define PBIT_LISTENER_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief type definition for pbit_listener_start_pbit method callback
 */
typedef void(*pbit_listener_start_pbit_cb)(void *self, void *pbit);

/**
 * @brief type definition for pbit_listener_end_pbit method callback
 */
typedef void(*pbit_listener_end_pbit_cb)(void *self, void *pbit);

/**
 * @brief type definition for pbit_listener_add_failure method callback
 */
typedef void(*pbit_listener_add_failure_cb)(void *self, void *pbit, const char *msg, int line, const char *file);

/** 
 * @struct pbit_listener_implement
 *
 * @brief this will be the common interface for runners 
 *
 * @note Please note that add_failure and ok pbit have the same signature.
 *
 * @see pbit_listener_start_pbit_cb
 * @see pbit_listener_end_pbit_cb
 * @see pbit_listener_add_failure_cb
 */
struct pbit_listener_implement 
{
    pbit_listener_start_pbit_cb start_pbit; /**< callback method to start a pbit */
    pbit_listener_end_pbit_cb end_pbit; /**< callback method to end a pbit */
    pbit_listener_add_failure_cb add_failure; /**< callback method to set a pbit as failed */
    pbit_listener_add_failure_cb ok_pbit; /**< callback method to set a pbit as passed */
};

/** 
 * @struct pbit_listener
 *
 * @brief export pointer to the derived clases. It is useful for
 *      call the correct operations for the current listener implementer.
 *
 * @see pbit_listener_implement
 */
struct pbit_listener
{
    struct pbit_listener_implement *impl;
};

/**
 * @brief This function will call the start_pbit callback method associated with the current pbit.
 *
 * @note This will be done accessing its internal impl pointer.
 *
 * @see pbit_listener_start_pbit_cb
 */
static inline void PBIT_LISTENER_START_PBIT(struct pbit_listener *s, struct PBIT *t)
{
    s->impl->start_pbit(s, t);
}

/**
 * @brief This function will call the end_pbit callback method associated with the current pbit.
 *
 * @note This will be done accessing its internal impl pointer.
 *
 * @see pbit_listener_end_pbit_cb
 */
static inline void PBIT_LISTENER_END_PBIT(struct pbit_listener *s, struct PBIT *t)
{
    s->impl->end_pbit(s, t);
}

/**
 * @brief This function will call the add_failure callback method associated with the current pbit.
 *
 * @note This will be done accessing its internal impl pointer.
 *
 * @see pbit_listener_add_failure_cb
 */
static inline void PBIT_LISTENER_ADD_FAILURE(struct pbit_listener *s, struct PBIT *t,
                                             const char *m, int l, const char *f)
{
    s->impl->add_failure(s, t, m, l, f);
}

/**
 * @brief This function will call the ok_pbit callback method associated with the current pbit.
 *
 * @note This will be done accessing its internal impl pointer.
 *
 * @see pbit_listener_add_failure_cb
 */
static inline void PBIT_LISTENER_ADD_PBIT_OK(struct pbit_listener *s, struct PBIT *t,
                                             const char *m, int l, const char *f)
{
    s->impl->ok_pbit(s, t, m, l, f);
}

#ifdef  __cplusplus
}
#endif

#endif /* PBIT_LISTENER_H_ */
