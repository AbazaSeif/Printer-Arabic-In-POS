#ifndef __PRINTER_PAGEUTILS_H__
#define __PRINTER_PAGEUTILS_H__



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief	Insert a dot character into string
 *
 * @param	char* in_stream  : [IN]  original character string pointer
 * @param	char* out_stream : [OUT] converted character string pointer
 *
 * @return	void
 */
void DotInsertStr(char* out_stream, char *in_stream);

/**
 * @brief	Convert amount(1-digit of floating point) of money to money string format
 *
 * @param	double val : [IN] amount of money
 *
 * @return	char*  str : pointer of string of amount of money
 */
char *strmoney(double val);


/**
 * @brief	Convert amount(2-digit of floating point) of money to money string format
 *
 * @param	double val : [IN] amount of money
 *
 * @return	char*  str : pointer of string of amount of money
 */
char *strmoney2(double val);

int AttrPprintf( int page, int y, int x, char *stream );


int CenterAlignPrint( int page, int line, const char *stream );


int Pprintf( int page, int y, int x, char *stream );

int HeadTitleForm(int page, int y, char *title1, char *title2, char *title3);

#ifdef __cplusplus
}
#endif



#endif
