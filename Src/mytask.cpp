#include "mytask.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "myclass.h"
//#include "usbd_cdc_if.h"

/*
 * To use classes the source must be of .cpp type
 * since the freertos.c should maintain the type (because of CubeMX)
 * we place the task in a .cpp file
 */

void StartPrintTask(void const * argument)
{
	int n = 0;
	MyClass xxx;

//	osDelay(2000);
//	while (!g_VCPInitialized) {}

/*
	int val = 0;
	printf("Enter a number: ");
	scanf("%d", &val);
	printf("%d = 0x%x\r\n", val, val);
*/
	char name[20];
	printf("What's your name?\r\n");
	scanf("%s", name);
	printf("Hello %s!\r\n", name);

  for(;;)
  {
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
  	printf("%d\r\n", n);
  	n = xxx.incby(n, 2);
    osDelay(1000);
  }
}
