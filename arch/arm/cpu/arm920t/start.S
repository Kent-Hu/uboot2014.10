/*
 *  armboot - Startup Code for ARM920 CPU-core
 *
 *  Copyright (c) 2001	Marius Gröger <mag@sysgo.de>
 *  Copyright (c) 2002	Alex Züpke <azu@sysgo.de>
 *  Copyright (c) 2002	Gary Jennejohn <garyj@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm-offsets.h>
#include <common.h>
#include <config.h>

/*
 *************************************************************************
 *
 * Startup Code (called from the ARM reset exception vector)
 *
 * do important init only if we don't start from memory!
 * relocate armboot to ram
 * setup stack
 * jump to second stage
 *
 *************************************************************************
 */

	.globl	reset

reset:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr, r0

#if	defined(CONFIG_AT91RM9200DK) || defined(CONFIG_AT91RM9200EK)
	/*
	 * relocate exception table
	 */
	ldr	r0, =_start
	ldr	r1, =0x0
	mov	r2, #16
copyex:
	subs	r2, r2, #1
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	bne	copyex
#endif

#ifdef CONFIG_S3C24X0
	/* turn off the watchdog */

#define pWTCON	    0x53000000
#define INTMSK	    0x4A000008	/* Interrupt-Controller base addresses */
#define INTSUBMSK	0x4A00001C
#define S3C2440_MPLL_400MHZ    ((0x5c<<12)|(0x01<<4)|(0x01))


	ldr	r0, =pWTCON
	mov	r1, #0x0
	str	r1, [r0]

	mov	r1, #0xffffffff
	ldr	r0, =INTMSK
	str	r1, [r0]

	ldr r1, =0x7ff
	ldr r0, =INTSUBMSK
	str r1, [r0]

	/*set CAMDIVN to 0*/
    ldr r0, =0x4c000018
	mov r1, #0
	str r1, [r0]

    /*FCLK:HCLK:PCLK = 1:4:8*/
	ldr	r0, =0x4c000014
	mov	r1, #0x05;
	str	r1, [r0]

	/*if HDIVN is not 0, CPU must set sync mode*/
	mrc p15, 0, r1, c1, c0, 0  
	orr r1, r1, #0xC0000000  
	mcr p15, 0, r1, c1, c0, 0 

    /*set main clock to 400MHz*/
    ldr r0, =0x4C000004  
    ldr r1, =S3C2440_MPLL_400MHZ
    str r1, [r0]  
    
#endif	/* CONFIG_S3C24X0 */

	/*
	 * we do sys-critical inits only at reboot,
	 * not when booting from ram!
	 */
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	bl	cpu_init_crit
#endif

	bl	_main

/*------------------------------------------------------------------------------*/

	.globl	c_runtime_cpu_setup
c_runtime_cpu_setup:

	mov	pc, lr

/*
 *************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************
 */


#ifndef CONFIG_SKIP_LOWLEVEL_INIT
cpu_init_crit:
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002300	@ clear bits 13, 9:8 (--V- --RS)
	bic	r0, r0, #0x00000087	@ clear bits 7, 2:0 (B--- -CAM)
	orr	r0, r0, #0x00000002	@ set bit 2 (A) Align
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-Cache
	mcr	p15, 0, r0, c1, c0, 0

	/*
	 * before relocating, we have to setup RAM timing
	 * because memory timing is board-dependend, you will
	 * find a lowlevel_init.S in your board directory.
	 */
	mov	ip, lr

	bl	lowlevel_init

	mov	lr, ip
	mov	pc, lr
#endif /* CONFIG_SKIP_LOWLEVEL_INIT */
