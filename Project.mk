#
# Project Makefile
#

# ------------------------------------------------------------------------------
# CONFIGURABLE PART
# ------------------------------------------------------------------------------

# Project Name
PROJECT = exam-BtApiPrinter-app

# PROJECT_CONFIG: just to complete the target name (optional)
PROJECT_CONFIG = debug

# final target will be:
#   - lib$(TARGET_NAME).a if TARGET_TYPE = archive  -- Library
#   - $(TARGET_NAME).elf if TARGET_TYPE = bin       -- Binary for JTAG
#   - $(TARGET_NAME).hex if TARGET_TYPE = sim       -- Binary for Simulation
TARGET_NAME = $(PROJECT)
TARGET_TYPE = bin
#TARGET_TYPE = archive

## Where to find libs ( it is related with 'LIBS'; ex) LIBS=-lnano-X.... )
libDirs = 
LIBS	= 

## Where to find sources (you must includes sub-directories)
## $(rootDir) is directory path where Project.mk file is
srcDirs += .

## Where to find headers
incDirs += .

## Set Compiler options
CEFLAGS   +=	-Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers \
				-fno-exceptions -fsigned-char -Wno-switch

## Enable Graphic Logo printing on the paper
CEFLAGS   +=	-DCONFIG_PRINTER_GRAPHIC

## Where to fine binary data files (Picture & Audio & font & etc )
EXRCS_DAT =  $(wildcard $(rootDir)/exrcs/*.dat)
EXRCS_PNG =  $(wildcard $(rootDir)/exrcs/*.png)
EXRCS_TTF =  $(wildcard $(rootDir)/exrcs/*.TTF)
EXRCS_MP3 =  $(wildcard $(rootDir)/exrcs/*.MP3)


