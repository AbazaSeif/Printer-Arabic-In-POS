#
# Makefile
#
# [INTERNAL] ===================================================================
#
#
# [/INTERNAL] ==================================================================

# ------------------------------------------------------------------------------
# !!DO NOT MODIFY!!
# ------------------------------------------------------------------------------

MACHPKG	= Macaroni

#
# Directory path info.
#
MainHome	= /home/abaza/Work/POS/Bitel/NewBitel/BT-ADE-v1.06.07.std/IDE/SDK
rootDir        = .
BtOSDir        = $(MainHome)/$(MACHPKG)/BtOS
SoCDir         = $(MainHome)/$(MACHPKG)/SoC
# Bitel OS directory
externalObjDir = $(BtOSDir)/release/objs-btos

# Application Directory
#projectBtOSDir = ../../../Project-BtOS/$(MACHPKG)

# ------------------------------------------------------------------------------
# CONFIGURATION
# ------------------------------------------------------------------------------

# Override with full path if necessary
CROSS_COMPILE = arm-none-eabi-

# ------------------------------------------------------------------------------
# Include APPLICATION Project.mk
# ------------------------------------------------------------------------------
include $(rootDir)/Project.mk
# ------------------------------------------------------------------------------

# ---------------------------------------------
# PROJECT PATHS 

# ---------------------------------------------
## Where to find tools
toolsDir = $(SoCDir)/tools


## This varaible is defined to retrieve lib version only
libDir = $(SoCDir)/lib

## Export directory
exportDir = $(SoCDir)/export

## Where to put init files (startup code)
initDir = $(SoCDir)/init

## Where to find link files (scripts)
linkDir = $(SoCDir)/link


## Where to find libs ( it is related with 'LIBS=xxxxx' below )
## $(rootDir)/lib is included by default in $(toolsDir)/make/vars.mk
##
libDirs += $(BtOSDir)/release/lib
ifeq ($(PROJECT_CONFIG),debug)
libDirs += $(BtOSDir)/release/lib/lib$(PROJECT_CONFIG)
else
libDirs += $(BtOSDir)/release/lib/libdebug
endif
libDirs += $(BtOSDir)/release/lib/lib$(PROJECT_CONFIG)/libEMVL2APP

## What is name for POS device's madatory API library ( upper library is first )
LIBS += BitelStdApi

## What is name for POS device's madatory Low-level library ( upper library is first )
LIBS += rsa
LIBS += emvtl
LIBS += contact
LIBS += contactless
LIBS += miscajc-bitel


## Where to find SoC's framework headers
#
# !!!! caution !!!! ---> DO NOT add new path
#
## Where to find framework headers ( !!!! You can add the new path, if you need !!!! )
includeDirs = $(SoCDir)/include
incDirs += $(includeDirs)
incDirs += $(includeDirs)/$(PLATFORM)


## Where to find headers
#
# !!!! caution !!!! ---> referencing order
#
## Where to find headers for POS device's mandatory Standard API header
incDirs += $(BtOSDir)/release/include/libBitelStdApi
## Where to find headers for POS device's mandatory Low-Level header
incDirs += $(BtOSDir)/release/include
incDirs += $(BtOSDir)/release/include/include-from-linux
incDirs += $(BtOSDir)/release/include/libfreetype
incDirs += $(BtOSDir)/release/include/libfreetype/config
incDirs += $(BtOSDir)/release/include/libfribidi
incDirs += $(BtOSDir)/release/include/libmicrowindows
incDirs += $(BtOSDir)/release/include/libfribidi
incDirs += $(BtOSDir)/release/include/libiso8583ajc
incDirs += $(BtOSDir)/release/include/libnetsio
incDirs += $(BtOSDir)/release/include/libcontact
incDirs += $(BtOSDir)/release/include/libmiscajc-bitel

ifeq ($(TARGET_TYPE), bin)
# Mandatory Objects files for BitelOS
EXOBJS += $(externalObjDir)/bt_util.o
EXOBJS += $(externalObjDir)/cstartup.o
EXOBJS += $(externalObjDir)/fntdata.o
EXOBJS += $(externalObjDir)/wrkutil.o
EXOBJS += $(externalObjDir)/CryptoLib.o
EXOBJS += $(externalObjDir)/ppdrv.o

## Where to find library of target processor's driver
libDirs += $(SoCDir)/release/lib/libdebug
LIBS += drvsoc
endif

## Where to find binary files like picture & data & font & audio
ifneq ($(EXRCS_DAT),)
	EXRCS += $(EXRCS_DAT)
endif
ifneq ($(EXRCS_PNG),)
	EXRCS += $(EXRCS_PNG)
endif
ifneq ($(EXRCS_TTF),)
	EXRCS += $(EXRCS_TTF)
endif
ifneq ($(EXRCS_MP3),)
	EXRCS += $(EXRCS_MP3)
endif

ifneq ($(EXRCS),)
	EXOBJS += -Wl,--format=binary -Wl,$(EXRCS) -Wl,--format=default
endif

# ---------------------------------------------
# OPTIONS
# ---------------------------------------------
## Build directory
#buildDir = $(rootDir)/build/$(PLATFORM)-$(SYSTEM)-$(LAYOUT)-$(PROJECT_CONFIG)
buildDir = $(rootDir)/build/$(PLATFORM)-$(LAYOUT)-$(PROJECT_CONFIG)

# PLATFORM: defines the targeted platform
PLATFORM = core1

# SYSTEM: defines the software architecture
#  - ram -- All is loaded by jtag, only one section for code and data
#  - rom -- All is loaded by jtag, two different sections for code and data
#                  * rom = code and rodata
#                  * ram = data and bss
#  - sla -- Second Level Application
#  - scp_aplt -- SCP Applet
#  - stp_app -- STP Application
#SYSTEM = ram
SYSTEM = sdram0

# LAYOUT: defines the memory layout for the different sections
# - default  -- All executed in rom and sram
# - iram1
# - iram2
# - irom
# - sdram
# - sram
# - framework
#LAYOUT = default
LAYOUT = sdram

# FRAMEWORK: defines what framework is targetted
# - SLA = 3 -- 2nd level application based on FLORA
# - SCP_APLT = 2      -- SCP applet based on FLORA
# - STP_APP = 1       -- STP application based on FLORA
# - NO_FWK = 0    -- FLORA ROM code building
FRAMEWORK = NO_FWK

# CPU: defines the CPU type for the platform
#  - arm926	-- ARM926EJ-S
#  - armM3 	-- ARM CORETEX-M3
CPU = arm926


include $(rootDir)/compilation_flags.mk

## Enable debug flags
DebugEnabled = True

## Enable IRQ
#EnableIRQ = False
EnableIRQ = True
## Enable FIQ
EnableFIQ = False
## Enable MMU
EnableMMU = False
#EnableMMU = True
## Enable DCache => MMU enabled
EnableDCache = False
#EnableDCache = True
## Enable ICache
#EnableICache = False
EnableICache = True
## Implement D-TCM
# If D-TCM is implemented ".dtcm" section will be copied to D-TCM
#ArmHasDTCM = False
ArmHasDTCM = True
## Implement I-TCM
# If I-TCM is implemented ".itcm" section will be copied to D-TCM
ArmHasITCM = True
## Use UART for printf
EnableUart = False
## Use GPIO for status
EnableGpio = False

## Want to use COBRA basic library
UseLibCobra = False
## Want to use Libdev library
UseLibDev = False
## Want to use C Library
UseLibC = True

# ------------------------------------------------------------------------------
# !!DO NOT MODIFY!!
# ------------------------------------------------------------------------------
include $(rootDir)/VERSION.mk
include $(includeDirs)/VERSION.mk
include $(libDir)/VERSION.mk
include $(linkDir)/VERSION.mk
include $(initDir)/VERSION.mk

include $(toolsDir)/make/init.mk

# ------------------------------------------------------------------------------
# Add your custom target here
# ------------------------------------------------------------------------------
