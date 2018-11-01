	.global main								; makes main acessible from outside this file
	.thumb										; use thumb
	.data                                       ; set memory location to sram
	;put here your variables
	.text										; set memory location to flash
	.align 4									; align on 32-bit boundary

;< Hardware Registers >---------------------------------------------------
GPIO_PORTF_DATA_R			.field 0x40025000,32
GPIO_PORTF_DIR_R            .field 0x40025400,32
GPIO_PORTF_AFSEL_R          .field 0x40025420,32
GPIO_PORTF_PUR_R            .field 0x40025510,32
GPIO_PORTF_DEN_R            .field 0x4002551C,32
GPIO_PORTF_PCTL_R           .field 0x4002552C,32
PF1                         .field 0x40025002,32	;LED RED
PF2                         .field 0x40025004,32	;LED BLUE
PF3                         .field 0x40025008,32	;LED GREEN
SWITCHES					.field 0x40025011,32	;SW1, SW2

SW1_PRESSED					.equ 0x10
SW2_PRESSED                 .equ 0x01
BOTH_PRESSED                .equ 0x00
NO_PRESSED                  .equ 0x11


SYSCTL_RCGCGPIO_R			.field 0x400FE608,32
;SYSCTL_RCGCGPIO_R			.equ 0x400FE608

;< Custom Constants >---------------------------------------------------
CPU_FREQ					.field 8000000,32

;< Program Code >-------------------------------------------------------
	.align 2

main:
	; code goes here
	push {R0-R2, lr}

	;Enable GPIO Port F
	ldr r0, SYSCTL_RCGCGPIO_R
	mov R1, #0x10
	str R1, [R0]
	ldr r2, SYSCTL_RCGCGPIO_R

	nop
	nop
	nop
	nop
	nop

	ldr r0,GPIO_PORTF_DIR_R
	mov r1, #0x0E
	str r1, [R0]
	ldr r2, GPIO_PORTF_DIR_R

	ldr r0, GPIO_PORTF_DEN_R
	mov r1, #0x0E
	str r1, [R0]
	ldr r2, GPIO_PORTF_DEN_R

	ldr r0,GPIO_PORTF_DATA_R

blink:
	orr r1, r1, #0x0E
	str r1, [R0]

	ldr r2, CPU_FREQ

wait1:
	sub r2, r2, #10
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	cmp r2, #0
	bgt wait1

	;turn off the LED
	bic r1, r1, #0x0E
	str r1, [r0]

	ldr r2, CPU_FREQ

wait2:
	sub r2, r2, #10
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	cmp r2, #0
	bgt wait2

	b blink

	pop {r0-r2, lr}
	mov pc, lr

	.end
