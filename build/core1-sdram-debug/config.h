/*
 * config.h --
 *
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Maxim Integrated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MAXIM INTEGRATED ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* [INTERNAL] ------------------------------------------------------------------
 * Created on: May 27, 2010
 * Author:
 *
 * ---- Subversion keywords (need to set the keyword property)
 * $Revision:: 2405     $:  Revision of last commit
 * $Author:: seeniraj.n#$:  Author of last commit
 * $Date:: 2012-01-19 1#$:  Date of last commit
 * [/INTERNAL] -------------------------------------------------------------- */
#ifndef CONFIG_H_
#define CONFIG_H_

/** @file config.h Automatically generated file */

/** @defgroup COBRA_CONFIG Configuration file
 * 
 * @ingroup COBRA
 * @{
 */

#define VERSION					"1.2.0--rev110"		//!< Project version string
#define VERSION_MAJOR			1	//!< Project version string
#define VERSION_MINOR			2	//!< Project version string
#define VERSION_PATCH			0	//!< Project version string
#define TOOLS_VERSION			"1.3.0.release"	//!< Tools version string
#define INC_VERSION				"1.3.3.release"	//!< Include version string
#define INIT_VERSION			"1.1.1.release"	//!< Init version string
#define LIB_VERSION				"1.2.0.release"	//!< Library version string
#define LINK_VERSION			"1.2.0.release"	//!< Link version string
#define ENABLE_IRQ				1	//!< IRQ enabled
#define ENABLE_FIQ				0	//!< FIQ enabled
#define ENABLE_DCACHE			0	//!< D-Cache enabled
#define ENABLE_ICACHE			1	//!< I-Cache enabled
#define ARM_HAS_DTCM			1	//!< D-TCM enabled
#define ARM_HAS_ITCM			1	//!< I-TCM enabled
#define USE_HIGH_VECTORS		0	//!< Use High Vectors
#define ENABLE_UART				0	//!< UART enabled
#define ENABLE_GPIO				0	//!< GPIO enabled
#define SIMULATION				0	//!< Simulation configuration
#define USE_ATTRIBUTE_IRQ		0	//!< Use gcc irq attribute
#define ALLOW_DEPRECATED_MACROS 1	//!< Deprecated macros allowed
#define HAVE_ROM_BOOTSTRAP		1 /* FIXME: Make it configurable */


#define STACK_SIZE 	/*256K*/ /*512K*/ 4M
#define HEAP_SIZE  	/*16M */ /*8M  */ 24M

#if ENABLE_DCACHE == 1
#define ENABLE_MMU 1	//!< MMU automatically enabled for D-Cache usage 
#else
#define ENABLE_MMU 0	//!< MMU Enabled
#endif /* ENABLE_DCACHE == 0 */

#include <io.h>
#include <core1/core1.h>
#include <core1/core1_io.h>

#if ALLOW_DEPRECATED_MACROS == 1
#include <core1/deprecated.h>
#endif /* #if ALLOW_DEPRECATED_MACROS == 1 */

#if SIMULATION == 1
#  define __sim_unused__ __attribute__ ((unused))
#else
#  define __sim_unused__
#endif

/** Platform expansion.
 * Use this macro to avoid direct platform references.
 * For example you could use "PFM(GCR_RSTR_OFST)" instead of "LONDA_GCR_RSTR_OFST".
 */
#define PFM(_x_) CORE1_ ## _x_

/** Small case platform expansion.
 * Use this macro to avoid direct platform references.
 * For example you could use "PFM(io)" instead of "londa_io".
 */
#define SPFM(_x_) core1_ ## _x_

#ifdef _DEBUG

/** Debug printf
 * printf enabled when debug is enabled.
 */
#  define DPRINTF(...) do {\
	fflush(0);\
	printf("[DEBUG][%s:%d] ",__FILE__,__LINE__);\
	printf(__VA_ARGS__);\
	printf("\n");\
	fflush(0);\
} while(0)

#else /* _DEBUG */

#  define DPRINTF(...) do {  } while (0)

#endif /* _DEBUG */

#if USE_ATTRIBUTE_IRQ == 1
#  define __irq__ __attribute__ ((interrupt ("IRQ")))
#  define __fiq__ __attribute__ ((interrupt ("FIQ")))
#else /* #ifdef USE_ATTRIBUTE_IRQ */
#  define __irq__
#  define __fiq__
#endif /* #ifdef USE_ATTRIBUTE_IRQ */

#define __section__(name) __attribute__ ((section (#name)))

#if ARM_HAS_ITCM == 1
/** itcm section attribute.
 * Set the section destination to ".itcm".
 */
#define __itcm__ __attribute__ ((section (".itcm")))
#else
#define __itcm__
#endif /* #if ARM_HAS_ITCM == 1 */

#if ARM_HAS_DTCM == 1
/** dtcm section attribute.
 * Set the section destination to ".dtcm".
 */
#define __dtcm__ __attribute__ ((section (".dtcm")))
#else
#define __dtcm__ 
#endif /* #if ARM_HAS_DTCM == 1 */

/** @} */
#endif /* CONFIG_H_ */
