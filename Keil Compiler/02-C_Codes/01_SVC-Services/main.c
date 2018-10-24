#include "TM4C123.h"                    // Device header

int __svc(0x00) svc_service_add(int x, int y);
int __svc(0x01) svc_service_sub(int x, int y);
int __svc(0x02) svc_service_mul(int x, int y);
int __svc(0x03) svc_service_div(int x, int y);

void SVC_Handler_C(unsigned int *svc_args);

int x, y, z;

int main(void)	
{
	
	x = 1;
	y = 5;
	
	z = svc_service_add(x, y);
	z = svc_service_sub(x, y);
	z = svc_service_mul(x, y);
	z = svc_service_div(x, y);
	
	while(1)
	{
		
	}
}

__asm void SVC_Handler(void)
{
	TST LR, #4 			//verify if is in Main Stack
	ITE EQ    		  //Beginne if else structure
	MRSEQ R0, MSP   //If equal copy Main Stack to R0
	MRSNE R0, PSP   //else copy Process Stack to R0
	B  __cpp(SVC_Handler_C)
}

void SVC_Handler_C(unsigned int *svc_args)
{
	unsigned int svc_number;
	svc_number = ((char *)svc_args[6])[-2];  //retrieves value from R12 see Stack Frame
	switch(svc_number)
	{
		case 0:
			svc_args[0] = svc_args[0] + svc_args[1];
		  break;
		
		case 1:
			svc_args[0] = svc_args[0] - svc_args[1];
		  break;
		
		case 2:
			svc_args[0] = svc_args[0] * svc_args[1];
		  break;
		
		case 3:
			svc_args[0] = svc_args[0] / svc_args[1];
		  break;
		
		default:
			break;
	}
}
