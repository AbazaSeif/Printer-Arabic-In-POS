

/*******************************************************************************
         	     Reference Table to support Static Library working 
*******************************************************************************/


extern void main(void);

extern int __section_start_text;
extern int __section_end_text;
extern int __section_start_rodata;
extern int __section_end_rodata;
extern int __section_start_data;
extern int __section_end_data;
extern int __section_start_bss;
extern int __section_end_bss;
extern int __section_start_stack;
extern int __section_end_stack;
extern int __section_start_heap;
extern int __region_end_ram;
extern int __reset_vectors;
extern int __section_load_data;
extern int __section_wsize_data;

// Please put Application name in here ( Max : 16byte size )
const char AppStrName[] = { "Application" };

const long REFTABLE[] __attribute__ ((section (".reftable"))); 	
const long REFTABLE[] = {


/*******************************************************************************
         	         Please do not change this part 
*******************************************************************************/


/*-- content of search table -------------------------------------------------*/
	0x50524F47,
	0x52455800,	

/*-- 1. Define full or partial part ------------------------------------------*/
	0x00000000,						// full	 
//	0x66776f79,						// fwoy	 
//	0x6d417070,						// mApp	 
	
/*-- 2. C main function ------------------------------------------------------*/
	(long)&main,

/*******************************************************************************
         	     Multi language display & printing support 
         	   -- Please adjust this part, If necessary -- 
*******************************************************************************/			 

/*--- 3. double or single byte language ----------------------------------------
 Default setup for single or double byte language mode
		0x00000000,
		      ----
                |-> Reserved
            -- 
            |----> 2'nd : printer routine mode   ( 0= 1 byte, NZ = 2 bytes code )
          -- 
		  |------> 1'st : Lcd display mode       ( 0= 1 byte, NZ = 2 bytes code )
       
 ------------------------------------------------------------------------------*/

	0x00000000,      
/*  0x01010000,      */


/*--- 4. C function name for LCD display -------------------------------------*/

//	(long)&GetChinaLCDFONT,				/* 2 bytes code */
	0x00000000,				 			/* 1 byte code  */

/*--- 5. C function name for printing    -------------------------------------*/

//	(long)&GetChinaPRTFONT,				/* 2 bytes code */
	0x00000000,				 			/* 1 byte code  */

/*******************************************************************************
         	         Please do not change this part 
*******************************************************************************/

/*-- 6. Section address ------------------------------------------------------*/


	(long)&__reset_vectors,			// 7,
	(long)&__region_end_ram,		// 8,
	(long)&__section_load_data,		// 9,	For variable initialize value 
	(long)&__section_start_data,	// 10,
	(long)&__section_wsize_data,	// 11,	For variable initialize value 
    (long)&__section_start_bss,		// 12,	For working RAM clear
    (long)&__section_end_bss,		// 13,	
    (long)&__section_start_stack,	// 14,	For stack area clear
    (long)&__section_end_stack,		// 15,	

/*******************************************************************************
         	              Application file name 
*******************************************************************************/
/*--- 16( max :16bytes ) application function name        --------------------*/	

	(long)&AppStrName
		
};


