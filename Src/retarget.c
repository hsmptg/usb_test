#include "retarget.h"

#define USB_RETARGET

#if !defined(OS_USE_SEMIHOSTING)

#if defined(USB_RETARGET)

#include<sys/stat.h>
#include "vcp.h"

int _fstat (int fd, struct stat *pStat)
{
		pStat->st_mode = S_IFCHR;
	 return 0;
}

int _close(int fd)
{
	 return -1;
}

int _write (int fd, char *pBuffer, int size)
{
	 return VCP_write(pBuffer, size);
}

int _isatty (int fd)
{
	 return 1;
}

int _lseek(int fd, int ptr, int dir)
{
	 return -1;
}

int _read (int fd, char *pBuffer, int size)
{
	uint32_t len = size;

	for (;;) {
		int done = (int) VCP_read((uint8_t*) pBuffer, &len);
		if (done)
			return done;
	}
	return 1;
}

#endif //

#if defined(USART_RETARGET)

#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <limits.h>
#include <signal.h>
#include <stdint.h>

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

UART_HandleTypeDef *gHuart;

void RetargetInit(UART_HandleTypeDef *huart) {
  gHuart = huart;

  // Disable I/O buffering for STDOUT stream, so that
  // chars are sent out as soon as they are printed.
  setvbuf(stdout, NULL, _IONBF, 0);
}

/*
 *
 */
int _isatty(int fd) {
  if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    return 1;

  errno = EBADF;
  return 0;
}

int _write(int fd, char* ptr, int len) {
  HAL_StatusTypeDef hstatus;

  if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
    hstatus = HAL_UART_Transmit(gHuart, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    if (hstatus == HAL_OK)
      return len;
    else
      return EIO;
  }
  errno = EBADF;
  return -1;
}

int _close(int fd) {
  if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    return 0;

  errno = EBADF;
  return -1;
}

int _lseek(int fd, int ptr, int dir) {
  (void) fd;
  (void) ptr;
  (void) dir;

  errno = EBADF;
  return -1;
}

int _read(int fd, char* ptr, int len) {
  HAL_StatusTypeDef hstatus;

  if (fd == STDIN_FILENO) {
    hstatus = HAL_UART_Receive(gHuart, (uint8_t *) ptr, 1, HAL_MAX_DELAY);
    if (hstatus == HAL_OK)
      return 1;
    else
      return EIO;
  }
  errno = EBADF;
  return -1;
}

int _fstat(int fd, struct stat* st) {
  if (fd >= STDIN_FILENO && fd <= STDERR_FILENO) {
    st->st_mode = S_IFCHR;
    return 0;
  }

  errno = EBADF;
  return 0;
}

#endif //#if defined(USART_RETARGET)

#endif //#if !defined(OS_USE_SEMIHOSTING)
