/**
 * @file pbit_runner.h
 *
 * @brief this file includes prototypes to manage
 * runner in the library.
 *
 * @author: Sergio Paracuellos <sergio.paracuellos@gmail.com> 
 */
#ifndef PBIT_RUNNER_H_
#define PBIT_RUNNER_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief pbit_runner_start function to start the runner
 */
void pbit_runner_start(void);

/**
 * @brief pbit_runner_run_pbit function to run the pbit
 *
 * @param pbit pbit to be executed
 */
void pbit_runner_run_pbit(struct PBIT *pbit);

/**
 * @brief pbit_runner_end function to end the runner
 */
void pbit_runner_end(void);

#ifdef  __cplusplus
}
#endif

#endif /* PBIT_RUNNER_H_ */
