/**
 * @file arch_os.h
 *
 * @brief Arch and OS dependant includes and definitions are here
 *
 * @author: Sergio Paracuellos <sergio.paracuellos@gmail.com> 
 */

#ifndef ARCH_OS_H_
#define ARCH_OS_H_

#ifdef __cplusplus
extern "C" {
#endif

#if __linux__
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #define printk printf
#endif

#ifdef __cplusplus
};
#endif

#endif /* ARCH_OS_H_ */
