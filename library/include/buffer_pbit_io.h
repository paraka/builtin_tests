/**
 * @file buffer_test_io.h
 *
 * @brief this include file includes macros to manage
 * tests application outputs. It is all based in the OS print function.
 *
 * @author: Sergio Paracuellos <sergio.paracuellos@gmail.com> 
 */

#ifndef BUFFER_TEST_IO_H_
#define BUFFER_TEST_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "arch_os.h"

static inline void PBIT_BEGIN(void)
{
    printk("*** BEGIN OF PBIT ***\n");
}

static inline void PBIT_END(void)
{
    printk("*** END OF PBIT ***\n");
}

#ifdef __cplusplus
};
#endif

#endif /*BUFFER_TEST_IO_H_ */
