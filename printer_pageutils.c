#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG_TRACE
#include <debug_trace.h>

/* Bitel Standard API header */
#include <BitelStdApi.h>

#include "printer_pageutils.h"

/**
 * @brief	Insert a dot character into string
 *
 * @param	char* in_stream  : [IN]  original character string pointer
 * @param	char* out_stream : [OUT] converted character string pointer
 *
 * @return	void
 */
static void insertdot( char* out_stream, char *in_stream )
{
	int i, j, k;
	char tmpbuf[32], tmpbuf1[32];
	
	j = strlen(in_stream);
	memset(tmpbuf, '\0', sizeof(tmpbuf));
	for ( i = 0 ; i < j ; i++ ) {
		tmpbuf[j-i-1] = in_stream[i];
	}

	memset(tmpbuf1, '\0', sizeof(tmpbuf1));
	for ( i = k = 0 ; i < j ; i++ ) {
		if (i && !(i % 3))
			tmpbuf1[k++] = '.';
		tmpbuf1[k++] = tmpbuf[i];
	}

	memset(tmpbuf, '\0', sizeof(tmpbuf));
	for ( i = 0 ; i < k ; i++ ) {
		tmpbuf[k-i-1] = tmpbuf1[i];
	}
	strcpy(out_stream, tmpbuf);
}

/**
 * @brief	Convert amount(1-digit of floating point) of money to money string format
 *
 * @param	double val : [IN] amount of money
 *
 * @return	char*  str : pointer of string of amount of money
 */
char *strmoney( double val ) 
{
    static char result[64];
    char *pt;
    int n;
    snprintf(result, sizeof(result), "%.1f", val);
    // Point pt at "."
    for (pt = result; *pt && *pt != '.'; pt++) {}
    // Length of fractional part
    n = result + sizeof(result) - pt;
    // Step backwards, inserting spaces
    do {
        pt -= 3; // shift 3 digits
        if (pt > result) {
            memmove(pt + 1, pt, n);
            // memmove allows overlap, unlike memcpy
            *pt = ','; // thousand separator
            n += 4; // 3 digits + separator
        } else
            break;
    } while (1);
    return result;
}

/**
 * @brief	Convert amount(2-digit of floating point) of money to money string format
 *
 * @param	double val : [IN] amount of money
 *
 * @return	char*  str : pointer of string of amount of money
 */
char *strmoney2( double val ) 
{
    static char result[64];
    char *pt;
    int n;
    snprintf(result, sizeof(result), "%.2f", val);
    // Point pt at "."
    for (pt = result; *pt && *pt != '.'; pt++) {}
    // Length of fractional part
    n = result + sizeof(result) - pt;
    // Step backwards, inserting spaces
    do {
        pt -= 3; // shift 3 digits
        if (pt > result) {
            memmove(pt + 1, pt, n);
            // memmove allows overlap, unlike memcpy
            *pt = '.'; // thousand separator
            n += 4; // 3 digits + separator
        } else
            break;
    } while (1);
    return result;
}


/**
 * @brief	add a line of character string to the position on a page with decoration.
 *
 */
int AttrPprintf( int page, int y, int x, char *stream )
{
	int rv = 0;
	int i, imax;
	char*  ppage;
	char*  pattr;
	char*  charptr;
	char*  attrptr;
	int line_num = 0;
	int line_char_num = 0;

	_TRACE( "----> %s()\n", __func__ );
	
	line_num      = BtGetPageMaxLineNum();
	line_char_num = BtGetPageMaxCharNumPerLine();

	// get page address for a page
	ppage = BtGetPageCharAddr( page );
	pattr = BtGetPageAttrAddr( page );

	if( !ppage || !pattr ){
		rv = -1;
		goto out;
	}

	// get a character address for x,y position
	charptr = (char *)( ppage + y*line_char_num + x );
	attrptr = (char *)( pattr + y*line_char_num + x );

	imax = strlen( stream );
	for ( i = 0 ; i < imax ; ) {
		if ( *stream & 0x80 ) {
			*charptr++ = *stream++;
			*attrptr++ = 0x20;		// set attribute for a character
			*charptr++ = *stream++;
			*attrptr++ = 0x20;		// set attribute for a character
			i += 2;
			charptr += 2;
			attrptr += 2;
		} else {
			*charptr++ = *stream++;
			*attrptr++ = 0x20;		// set attribute for a character
			charptr++;
			attrptr++;
			i++;
		}
	}

out:
	_TRACE( "<---- %s()\n", __func__ );
	return rv;
}

/**
 * @brief	print stream of character to printer buffer on left side on paper( CHAR_BUFFER1[page] )
 *
 */
int CenterAlignPrint( int page, int line, const char *stream )
{
	int x, rv = 0;
	char* ppage;
	int line_num;
	int line_char_num;

	_TRACE( "----> %s()\n", __func__ );
	
	line_num      = BtGetPageMaxLineNum();
	line_char_num = BtGetPageMaxCharNumPerLine();

	// get page address for a page
	ppage = BtGetPageCharAddr( page );
	
	if( !ppage ){
		rv = -1;
		goto out;
	}

	x = (line_char_num/2) - (strlen(stream) / 2);
	
	strcpy( ppage+line*line_char_num+x, stream );

out:
	_TRACE( "<---- %s()\n", __func__ );
	return rv;
}

/**
 * @brief	print stream of character to printer buffer on left side on paper( CHAR_BUFFER1[page] )
 *
 */
int Pprintf( int page, int y, int x, char *stream )
{
	int rv;
	char* ppage;
	int line_num;
	int line_char_num;


	_TRACE( "----> %s()\n", __func__ );

	line_num      = BtGetPageMaxLineNum();
	line_char_num = BtGetPageMaxCharNumPerLine();

	// get page address for a page
	ppage = BtGetPageCharAddr( page );
	
	if( !ppage ){
		rv = -1;
		goto out;
	}

	strcpy( ppage+y*line_char_num+x, stream );

out:
	_TRACE( "<---- %s()\n", __func__ );
	return rv;
}


int HeadTitleForm(int page, int y, char *title1, char *title2, char *title3)
{
	int x, len;
	char tmpbuf[32], stream[64];
	int line_num;
	int line_char_num;

	_TRACE( "----> %s()\n", __func__ );

	line_num      = BtGetPageMaxLineNum();
	line_char_num = BtGetPageMaxCharNumPerLine();

	_TRACE( "line num : %d\n", line_num );
	_TRACE( "line char num : %d\n", line_char_num );

	strcpy(stream, "Receipt");
	len = strlen(stream);
	x = (line_char_num / 2) - len;
	AttrPprintf(page, y, x, stream);
	y++;
	strcpy(stream, "BankCompany");
	len = strlen(stream);
	x = (line_char_num / 2) - len;
	AttrPprintf(page, y, x, stream);

	y++;
	CenterAlignPrint(page, y, title1);
	y++;
	if (title2[0]) {
		CenterAlignPrint(page, y, title2);
		y++;
	}
	if (title3[0]) {
		CenterAlignPrint(page, y, title3);
		y++;
	}
	CenterAlignPrint(page, y, "Bitel");
	y++;
	CenterAlignPrint(page, y, "SerialNo. #278");
	y++;
	CenterAlignPrint(page, y, "00000000000011");
	y += 2;

out:
	_TRACE( "<---- %s()\n", __func__ );
	return (y);
}
