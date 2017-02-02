/*
 * retarget.h
 *
 *  Created on: 17/01/2017
 *      Author: helio
 */

#ifndef RETARGET_H_
#define RETARGET_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include <sys/stat.h>

/*
int _fstat (int fd, struct stat *pStat)
int _close(int)
int _write (int fd, char *pBuffer, int size)
int _isatty (int fd)
int _lseek(int, int, int)
int _read (int fd, char *pBuffer, int size)
*/

/*
void RetargetInit(UART_HandleTypeDef *huart);
int _isatty(int fd);
int _write(int fd, char* ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char* ptr, int len);
int _fstat(int fd, struct stat* st);
 */

#ifdef __cplusplus
}
#endif

#endif /* RETARGET_H_ */
