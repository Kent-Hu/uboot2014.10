/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <garyj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * Configuation settings for the SAMSUNG SMDK2410 board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARM920T		/* This is an ARM920T Core */
#define CONFIG_S3C24X0		/* in a SAMSUNG S3C24x0-type SoC */
#define CONFIG_S3C2440		/* specifically a SAMSUNG S3C2410 SoC */
#define CONFIG_SMDK2440		/* on a SAMSUNG SMDK2410 Board */

#if 0
#define CONFIG_SYS_TEXT_BASE	0x33f80000
#else
#define CONFIG_SYS_TEXT_BASE    0x0
#endif

#define CONFIG_SYS_ARM_CACHE_WRITETHROUGH

/* input clock of PLL (the SMDK2410 has 12MHz input clock) */
#define CONFIG_SYS_CLK_FREQ	12000000


/*modify by kent:remove tags, and support device tree*/
#if 0
#define CONFIG_CMDLINE_TAG	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#else
#define CONFIG_OF_LIBFDT	     1
#endif


#if 0
#define CONFIG_CS8900		/* we have a CS8900 on-board */
#define CONFIG_CS8900_BASE	0x19000300
#define CONFIG_CS8900_BUS16	/* the Linux driver does accesses as shorts */
#else
#define CONFIG_DRIVER_DM9000
#define CONFIG_DM9000_BASE	0x20000000
#define DM9000_IO           CONFIG_DM9000_BASE
#define DM9000_DATA         (CONFIG_DM9000_BASE+4)
#endif
/*
 * select serial console configuration
 */
#define CONFIG_S3C24X0_SERIAL
#define CONFIG_SERIAL1		1	/* we use SERIAL 1 on SMDK2440 */

/************************************************************
 * USB support (currently only works with D-cache off)
************************************************************/
#if 0
#define CONFIG_USB_OHCI
#define CONFIG_USB_OHCI_S3C24XX
#define CONFIG_USB_KEYBOARD
#define CONFIG_USB_STORAGE
#define CONFIG_DOS_PARTITION
#endif

/************************************************************
 * RTC
 ************************************************************/
#if 0
#define CONFIG_RTC_S3C24X0
#endif


#define CONFIG_BAUDRATE		115200

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_BSP
#define CONFIG_CMD_CACHE

#if 0
#define CONFIG_CMD_DATE
#endif

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ELF
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_REGINFO

#if 0
#define CONFIG_CMD_USB
#endif

#if 0
#define CONFIG_SYS_HUSH_PARSER
#endif

#define CONFIG_CMDLINE_EDITING

/* autoboot */
#define CONFIG_BOOTDELAY	5
#define CONFIG_BOOT_RETRY_TIME	-1
#define CONFIG_RESET_TO_RETRY
#define CONFIG_ZERO_BOOTDELAY_CHECK

#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.1.110
#define CONFIG_SERVERIP		192.168.1.100
#define CONFIG_ETHADDR      08:00:3e:26:0a:5b

#if 0
#define CONFIG_BOOTARGS     "console=ttySAC0 root=/dev/mtdblock3"
#endif

#define CONFIG_BOOTCOMMAND  "nand read 30000000 kernel;nand read 31000000 dts;bootm 30000000 - 31000000"

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200	/* speed to run kgdb serial port */
#endif

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_PROMPT	"SMDK2440 # "
#define CONFIG_SYS_CBSIZE	256
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + \
				sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS	16
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

#define CONFIG_DISPLAY_CPUINFO				/* Display cpu info */

#define CONFIG_SYS_MEMTEST_START	0x30000000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x33F00000	/* 63 MB in DRAM */

#define CONFIG_SYS_LOAD_ADDR		0x30800000

/* support additional compression methods */
#define CONFIG_BZIP2
#define CONFIG_LZO
#define CONFIG_LZMA

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1          /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x30000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB */

#define PHYS_FLASH_1		0x00000000 /* Flash Bank #0 */

#define CONFIG_SYS_FLASH_BASE	PHYS_FLASH_1

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */

#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_FLASH_CFI_LEGACY
#define CONFIG_SYS_FLASH_LEGACY_1024Kx16
#define CONFIG_FLASH_SHOW_PROGRESS	45

#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_FLASH_BANKS_LIST     { CONFIG_SYS_FLASH_BASE }
#define CONFIG_SYS_MAX_FLASH_SECT	(50)

#if 0
#define CONFIG_ENV_ADDR			(CONFIG_SYS_FLASH_BASE + 0x070000)
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_SIZE			0x10000
/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#endif

#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET        0x00040000          /*256k*/
#define CONFIG_ENV_ADDR          CONFIG_ENV_OFFSET
#define CONFIG_ENV_SIZE          0x20000             /*128k*/
#define CONFIG_ENV_RANGE         CONFIG_ENV_SIZE

#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE       /* needed for mtdparts commands */
#define MTDIDS_DEFAULT       "nand0=jz2440-0" /*which partion*/
#define MTDPARTS_DEFAULT     "mtdparts=jz2440-0:256k(u-boot),"\
						     "128k(params),"\
						     "4m(kernel),"  \
							 "128k(dts),"    \
						     "-(rootfs)"
 


#define CONFIG_CMD_NAND_YAFFS


/*
 * Size of malloc() pool
 * BZIP2 / LZO / LZMA need a lot of RAM
 */
#define CONFIG_SYS_MALLOC_LEN	(4 * 1024 * 1024)

#define CONFIG_SYS_MONITOR_LEN	(448 * 1024)
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE

/*
 * NAND configuration
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_NAND_S3C2440
#define CONFIG_SYS_S3C2440_NAND_HWECC
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x4E000000
#endif

/*
 * File system
 */
#if 0
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_YAFFS2
#define CONFIG_RBTREE
#endif

/* additions for new relocation code, must be added to all boards */
#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM_1
#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_SDRAM_BASE + 0x1000 - \
				GENERATED_GBL_DATA_SIZE)

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_SYS_GENERIC_BOARD     /*remove some printf information*/
#endif /* __CONFIG_H */
