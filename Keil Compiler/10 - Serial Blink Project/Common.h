#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "TM4C123.h"                    // Device header

#define SHIFT(x) (1 << (x))							//Shift number

#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))  // IRQ 0 to 31 Set Enable Register
#define NVIC_PRI7_R             (*((volatile unsigned long *)0xE000E41C))  // IRQ 28 to 31 Priority Register


#endif /* _COMMON_H */
