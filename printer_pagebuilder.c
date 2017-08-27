#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG_TRACE
#include <debug_trace.h>

/* Bitel Standard API header */
#include <BitelStdApi.h> 
#include <DRIVER.H>

#include "printer_pageutils.h"
#include "printer_pagebuilder.h"

char *ToArabic(char* Striem) {

    int i = 0, x = 0, z, test, slen, j;

    char *pos;
    char N_Char = 0, P_Char = 0;
    char *p1, *p2;
    char localarray[20];
    char *localptr = (char *) &localarray;
    //int StrNum = EBE_WC(Striem);
    slen = strlen(Striem);

    const struct {
        int Graph;
        int CharNumber;
        char Alpha1;
        char Alpha2;
        char Alpha3;
        char Alpha4;
    } CharDataBease[] = {
        /*(Key),(Code)(Start)(Mean)(End)(Alone)*/
        {'_', 95, 0, 0, 0, 0},
        {'h', 104, 0xB0, 0xB1, 0xB1, 0xB0}, /*ا*/
        {'H', 104, 0xB0, 0xB1, 0xB1, 0xB0}, /*ا*/
        {'f', 102, 0xB3, 0xB3, 0xB2, 0xB2}, /*ب*/
        {'j', 106, 0xB7, 0xB7, 0xB6, 0xB6}, /*ت*/
        {'e', 101, 0xB9, 0xB9, 0xB8, 0xB8}, /*ث*/
        {'[', 91, 0xBB, 0xBB, 0xBA, 0xBA}, /*ج*/
        {'p', 112, 0xBF, 0xBF, 0xBE, 0xBE}, /*ح*/
        {'o', 111, 0xC1, 0xC1, 0xC0, 0xC0}, /*خ*/
        {']', 93, 0xC2, 0xC2, 0xC2, 0xC2}, /*د*/
        {'`', 96, 0xC3, 0xC3, 0xC3, 0xC3}, /*ذ*/
        {'v', 118, 0xC4, 0xC4, 0xC4, 0xC4}, /*ر*/
        {'.', 46, 0xC5, 0xC5, 0xC5, 0xC5}, /*ز*/
        {'s', 115, 0xC8, 0xC8, 0xC7, 0xC7}, /*س*/
        {'a', 97, 0xCA, 0xCA, 0xC9, 0xC9}, /*ش*/
        {'w', 119, 0xCC, 0xCC, 0xCB, 0xCB}, /*ص*/
        {'q', 113, 0xCE, 0xCE, 0xCD, 0xCD}, /*ض*/
        {'\'', 39, 0xCF, 0xCF, 0xCF, 0xCF}, /*ط*/
        {'/', 47, 0xD0, 0xD0, 0xD0, 0xD0}, /*ظ*/
        {'u', 117, 0xD4, 0xD3, 0xD2, 0xD1}, /*ع*/
        {'y', 121, 0xD8, 0xD7, 0xD6, 0xD5}, /*غ*/
        {'t', 116, 0xDA, 0xDA, 0xD9, 0xD9}, /*ف*/
        {'r', 114, 0xDC, 0xDC, 0xDB, 0xDB}, /*ق*/
        {';', 59, 0xDE, 0xDE, 0xDD, 0xDD}, /*ك*/
        {'g', 103, 0xE3, 0xE3, 0xE1, 0xE1}, /*ل*/
        {'l', 108, 0xE5, 0xE5, 0xE4, 0xE4}, /*م*/
        {'k', 107, 0xE7, 0xE7, 0xE6, 0xE6}, /*ن*/
        {'i', 105, 0xEB, 0xEA, 0xE9, 0xE9}, /*ه*/
        {'m', 109, 0xB7, 0xB7, 0xE9, 0xE9}, /*ة*/
        {',', 44, 0xE8, 0xE8, 0xE8, 0xE8}, /*و*/
        {'d', 100, 0xEE, 0xEE, 0xED, 0xED}, /*ى*/
        {'b', 98, 0xE2, 0xE2, 0xE2, 0xE2}, /*لا*/
        {'x', 120, 0xAF, 0xAF, 0xAF, 0xAF}, /*ء*/
        {'z', 122, 0xAE, 0xAE, 0xED, 0xED}, /*ئـ*/
        {'N', 78, 0xAD, 0xB1, 0xB1, 0xAD}, /*آ*/
        {'n', 110, 0xED, 0xED, 0xED, 0xED}, /*ى*/
        {'J', 74, 0, 0xAB, 0, 0}, /*ـ*/
        {'?', 63, 0xAC, 0xAC, 0xAC, 0xAC}, /*؟*/
        {'!', 33, 0x21, 0x21, 0x21, 0x21}, /*!*/
        {' ', 32, 0x20, 0x20, 0x20, 0x20}, /* Space */
        {'0', 48, 0xA0, 0xA0, 0xA0, 0xA0}, /*0*/
        {'1', 49, 0xA1, 0xA1, 0xA1, 0xA1}, /*1*/
        {'2', 50, 0xA2, 0xA2, 0xA2, 0xA2}, /*2*/
        {'3', 51, 0xA3, 0xA3, 0xA3, 0xA3}, /*3*/
        {'4', 52, 0xA4, 0xA4, 0xA4, 0xA4}, /*4*/
        {'5', 53, 0xA5, 0xA5, 0xA5, 0xA5}, /*5*/
        {'6', 54, 0xA6, 0xA6, 0xA6, 0xA6}, /*6*/
        {'7', 55, 0xA7, 0xA7, 0xA7, 0xA7}, /*7*/
        {'8', 56, 0xA8, 0xA8, 0xA8, 0xA8}, /*8*/
        {'9', 57, 0xA9, 0xA9, 0xA9, 0xA9}, /*9*/
        {'>', 62, 0x2E, 0x2E, 0x2E, 0x2E}, /*.*/
        {0, 0, 0, 0, 0, 0},
    };

    char check_char[] = {120, 93, 96, 46, 118, 44, 104, 98, 0};


    //Reverce String
    for (p1 = Striem, p2 = Striem + slen - 1; p2 > p1; ++p1, --p2) {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    char* BKStrim = Striem;
    //Get Char Number
looping:
    for (i = 0; CharDataBease[i].Graph; i++) {

        if (BKStrim[x] != '\0') {
            if (CharDataBease[i].Graph == BKStrim[x]) {
                test = CharDataBease[i].CharNumber;
                localptr[x] = test;
                x += 1;
                i = 0;
            }
        } else {
            break;
        }

    }
    if (x != slen) {
        goto looping;
    } else {

        localptr[x] = '\0';

    }

    z = x = 0;

    /*
            for (p1 = localptr, p2 = localptr + slen - 1; p2 > p1; ++p1, --p2) {
     *p1 ^= *p2;
     *p2 ^= *p1;
     *p1 ^= *p2;
            }
     */
    //Convert Number To Arabic Char
    for (i = 0; i <= slen; i++) {
Strarting:
        x = 0;
        if (localptr[i - 1] != '\0')
            P_Char = localptr[i - 1];
        else
            P_Char = '\0';

        if (localptr[i + 1] != '\b')
            N_Char = localptr[i + 1];
        else
            N_Char = '\0';

        //EBE_RS_printf("Localarray %s\n\n (Localptr = (%c-0x%x)) \t Next = (%c-0x%x) \t Priv = (%c-0x%x) \n\n",localptr,localptr[i],localptr[i],N_Char,N_Char,P_Char,P_Char);

        if (N_Char == '\0' || N_Char == 0x00) {
            //Yes
AlonArea:
            if (P_Char == '\0' || P_Char == 0x80) {
                //Yes
                for (x; CharDataBease[x].CharNumber; x++) {
                    if (CharDataBease[x].CharNumber == localptr[i]) {
                        if (localptr[i] == 104 && N_Char == 103) {
                            BKStrim[i] = 0xE2;
                            i++;
                        } else {
                            BKStrim[i] = CharDataBease[x].Alpha4; //Alon
                        }
                        x = 0;
                        break;
                    }
                }
            } else {
                //No
StartArea:
                for (x = 0; CharDataBease[x].CharNumber; x++) {
                    if (CharDataBease[x].CharNumber == localptr[i]) {
                        if (localptr[i] == 104 && N_Char == 103) {
                            BKStrim[i] = 0xE2;
                            i++;

                        } else {
                            BKStrim[i] = CharDataBease[x].Alpha1; //Start
                        }
                        x = 0;
                        break;
                    }
                }
            }
        } else {
            //NO
            if (N_Char == 0x20) {
                //Yes
                goto AlonArea;
            } else {
                //No
                // NCC Area
                for (x = 0; x <= strlen(check_char); x++) {
                    if (check_char[x] == N_Char) {
                        // Yes NCC Fund Char
                        for (x = 0; CharDataBease[x].CharNumber; x++) {

                            if (P_Char == '\0' || P_Char == 0x80 || P_Char == 0x20) {
                                //Yes No Previos
                                if (CharDataBease[x].CharNumber == localptr[i]) {
                                    if (localptr[i] == 117 || localptr[i] == 121) {
                                        BKStrim[i] = CharDataBease[x].Alpha4; //Alon
                                    } else {
                                        if (localptr[i] == 104 && N_Char == 103) {
                                            BKStrim[i] = 0xE2;
                                            i++;

                                        } else {
                                            BKStrim[i] = CharDataBease[x].Alpha3; //End
                                        }
                                    }
                                    x = 0;
                                    break;

                                }
                            } else {
                                goto StartArea;
                                // Striem[i] = CharDataBease[x].Alpha1; //Start
                                // x = 0;
                                break;
                            }
                        }

                        i += 1;
                        goto Strarting;
                        break;
                    }
                }
                x = 0;
                //Normal Exit : Not Found NCC Char
                if (P_Char == 0x00 || P_Char == 0x20) {
                    //Yes
EndArea:
                    for (x; CharDataBease[x].CharNumber; x++) {
                        if (CharDataBease[x].CharNumber == localptr[i]) {
                            if (localptr[i] == 120 || localptr[i] == 93 || localptr[i] == 96 || localptr[i] == 46 || localptr[i] == 118 || localptr[i] == 44 || localptr[i] == 104 || localptr[i] == 98) {
                                if (localptr[i] == 104 && N_Char == 103) {
                                    BKStrim[i] = 0xE2;
                                    i++;

                                } else {
                                    BKStrim[i] = CharDataBease[x].Alpha2; //Mean
                                }
                            } else {
                                if (localptr[i] == 104 && N_Char == 103) {
                                    BKStrim[i] = 0xE2;
                                    i++;

                                } else {
                                    BKStrim[i] = CharDataBease[x].Alpha3; //End
                                }
                            }
LocalEnd:
                            x = 0;
                            break;
                        }//End If
                    }//End For
                } else {
                    //No
                    if (P_Char == '\0' || P_Char == 0x80) {
                        //Yesx
                        goto EndArea;
                    } else {
                        //No
                        for (x; CharDataBease[x].CharNumber; x++) {
                            if (CharDataBease[x].CharNumber == localptr[i]) {
                                if (i == 0) {
                                    if (localptr[i] == 104 && N_Char == 103) {
                                        BKStrim[i] = 0xE2;
                                        i++;

                                    } else {
                                        BKStrim[i] = CharDataBease[x].Alpha3; //End
                                    }
                                } else if (i == slen) {
                                    if (localptr[i] == 104 && N_Char == 103) {
                                        BKStrim[i] = 0xE2;
                                        i++;

                                    } else {
                                        BKStrim[i] = CharDataBease[x].Alpha1; //Start
                                    }
                                } else if (i < slen) {
                                    if (N_Char == 'b' || N_Char == 'N' || N_Char == '\0') {
                                        if (localptr[i] == 104 && N_Char == 103) {
                                            BKStrim[i] = 0xE2;
                                            i++;
                                        } else {
                                            BKStrim[i] = CharDataBease[x].Alpha1; //Start
                                        }
                                    } else {
                                        if (localptr[i] == 104 && N_Char == 103) {
                                            BKStrim[i] = 0xE2;
                                            i++;
                                        } else {
                                            BKStrim[i] = CharDataBease[x].Alpha2; //Mean
                                        }
                                    }
                                }
                                x = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    /*
            for (p1 = BKStrim, p2 = BKStrim + slen - 1; p2 > p1; ++p1, --p2) {
     *p1 ^= *p2;
     *p2 ^= *p1;
     *p1 ^= *p2;
            }
     */

    for (i = 0; BKStrim[i] != 0; ++i) {
        while (BKStrim[i] == 'g') {
            j = i;
            while (BKStrim[j] != 0) {
                BKStrim[j] = BKStrim[j + 1];
                ++j;
            }
        }
    }
    return BKStrim;
}

void Arabic_Printer_printf(int y, int x, const char *str, int page) {
    int xx = 32, fx, len, z, i;
    char *New;
    len = strlen(str);
    fx = xx - strlen(str) - x;
    New = ToArabic((char *) str);

    Pprintf(page, y, fx, New);
}

PRT_RESULT_t PageBuilderF1Key(int page, void* parguments) {
    PRT_RESULT_t rv = PRT_ERR_FAIL;
    int x, y, len;
    char stream[64 * 2];
    char sub_title[64 * 2];
    PAGEBUILDER_ARGS* args;
    int line_num_max;
    int line_char_max;

    _TRACE("----> %s()\n", __func__);

    args = (PAGEBUILDER_ARGS*) parguments;
    line_num_max = BtGetPageMaxLineNum();
    line_char_max = BtGetPageMaxCharNumPerLine();

    _TRACE("page( %d ), line_num_max( %d ), line_char_max( %d )\n", page, line_num_max, line_char_max);

    if (args->sub_title[0]) {
        // max character number per line is 32
        sprintf(sub_title, "< %s >", args->sub_title);
    }

#ifdef CONFIG_PRINTER_GRAPHIC
    {
        int line_space = 4;
        unsigned int logo_width;
        unsigned int logo_height;
        /* the height of the line of BitelOS printer driver is 24 pixels 
         * when line space is zero
         */
        int pixel_per_line_height = 24 + line_space;

        /*
         * Please, keep widthxheight header format for LOG byte arrary
         * BitelOS spec. : the first 4bytes are dedicated for resolution to be needed to be printed area 
                        addr[0] = MSB of width
                        addr[1] = LSB of width
                        addr[2] = MSB of height
                        addr[3] = LSB of height
         */
        extern const char BITEL_PRINT_LOGO_128x32[];

        BtAssignGraphic(BITEL_PRINT_LOGO_128x32, 0);

        /* get width & height from BITEL logo bitmap */
        logo_width = (BITEL_PRINT_LOGO_128x32[0]&0xFF) << 8 | (BITEL_PRINT_LOGO_128x32[1]&0xFF);
        logo_height = (BITEL_PRINT_LOGO_128x32[2]&0xFF) << 8 | (BITEL_PRINT_LOGO_128x32[3]&0xFF);
        _TRACE("Logo( %u, %u )\n", logo_width, logo_height);

        // convert pixel height to line
        y = logo_height / pixel_per_line_height;
        // one line more for margin
        y += 1;
    }
#else
    y = 0;
#endif

    y = HeadTitleForm(page, y, "PageBuilder", sub_title, "Test");
    Pprintf(page, y, 0, "--------------------------------");
    y++;

    // max character number per line is 32
    Pprintf(page, y, 0, "################################");
    y++;

    strcpy(stream, "F1-Key");
    len = strlen(stream);
    x = 0;
    AttrPprintf(page, y, x, stream);
    y++;

    if (args->sub_title[0]) {
        // max character number per line is 32
        sprintf(stream, "< %s >", args->sub_title);
        Pprintf(page, y, 0, stream);
        y++;
    }
    // max character number per line is 32
    Pprintf(page, y, 0, "--------------------------------");
    y++;

    if (args->amount[0]) {
        // max character number per line is 32
        sprintf(stream, "Amount : %s", args->amount);
        Pprintf(page, y, 0, stream);
        y++;
    }

    if (args->count[0]) {
        // max character number per line is 32
        sprintf(stream, "Count : %s", args->count);
        Pprintf(page, y, 0, stream);
        y++;
    }

    if (args->pin[0]) {
        // max character number per line is 32
        sprintf(stream, "Pin : %s", args->pin);
        Pprintf(page, y, 0, stream);
        y++;
    }
    if (args->transaction_result[0]) {
        // max character number per line is 32
        sprintf(stream, "Transaction : %s", args->transaction_result);
        Pprintf(page, y, 0, stream);
        y++;
    }

    // scroll up by more 7 lines
    rv = BtSetFormFeed(y + 7);

    _TRACE("<---- %s()\n", __func__);
    return rv;
}

PRT_RESULT_t PageBuilderF2Key(int page, void* parguments) {
    PRT_RESULT_t rv = PRT_ERR_FAIL;
    int x, y, len;
    char stream[64 * 2];
    char sub_title[64 * 2];
    PAGEBUILDER_ARGS* args;
    int line_num_max;
    int line_char_max;

    _TRACE("----> %s()\n", __func__);

    args = (PAGEBUILDER_ARGS*) parguments;
    line_num_max = BtGetPageMaxLineNum();
    line_char_max = BtGetPageMaxCharNumPerLine();

    _TRACE("page( %d ), line_num_max( %d ), line_char_max( %d )\n", page, line_num_max, line_char_max);

    if (args->sub_title[0]) {
        // max character number per line is 32
        sprintf(sub_title, "< %s >", args->sub_title);
    }

#ifdef CONFIG_PRINTER_GRAPHIC
    {
        int line_space = 4;
        unsigned int logo_width;
        unsigned int logo_height;
        /* the height of the line of BitelOS printer driver is 24 pixels 
         * when line space is zero
         */
        int pixel_per_line_height = 24 + line_space;

        /*
         * Please, keep widthxheight header format for LOG byte arrary
         * BitelOS spec. : the first 4bytes are dedicated for resolution to be needed to be printed area 
                        addr[0] = MSB of width
                        addr[1] = LSB of width
                        addr[2] = MSB of height
                        addr[3] = LSB of height
         */
        extern const char BITEL_PRINT_LOGO_128x32[];

        BtAssignGraphic(BITEL_PRINT_LOGO_128x32, 0);

        /* get width & height from BITEL logo bitmap */
        logo_width = (BITEL_PRINT_LOGO_128x32[0]&0xFF) << 8 | (BITEL_PRINT_LOGO_128x32[1]&0xFF);
        logo_height = (BITEL_PRINT_LOGO_128x32[2]&0xFF) << 8 | (BITEL_PRINT_LOGO_128x32[3]&0xFF);
        _TRACE("Logo( %u, %u )\n", logo_width, logo_height);

        // convert pixel height to line
        y = logo_height / pixel_per_line_height;
        // one line more for margin
        y += 1;
    }
#else
    y = 0;
#endif

    y = HeadTitleForm(page, y, "PageBuilder", sub_title, "Test");
    Pprintf(page, y, 0, "--------------------------------");
    y++;

    // max character number per line is 32
    Pprintf(page, y, 0, "################################");
    y++;

    if (args->sub_title[0]) {
        strcpy(stream, args->sub_title);
        strcpy(stream + strlen(stream), " builder");
        len = strlen(stream);
        x = 0;
        AttrPprintf(page, y, x, stream);
        y++;
    }

    if (args->sub_title[0]) {
        // max character number per line is 32
        sprintf(stream, "< %s >", args->sub_title);
        Pprintf(page, y, 0, stream);
        y++;
    }
    // max character number per line is 32
    Pprintf(page, y, 0, "--------------------------------");
    y++;

    if (args->amount[0]) {
        // max character number per line is 32
        sprintf(stream, "Amount : %s", args->amount);
        Pprintf(page, y, 0, stream);
        y++;
    }

    if (args->count[0]) {
        // max character number per line is 32
        sprintf(stream, "Count : %s", args->count);
        Pprintf(page, y, 0, stream);
        y++;
    }

    if (args->pin[0]) {
        // max character number per line is 32
        sprintf(stream, "Pin : %s", args->pin);
        Pprintf(page, y, 0, stream);
        y++;
    }
    if (args->transaction_result[0]) {
        // max character number per line is 32
        sprintf(stream, "Transaction : %s", args->transaction_result);
        Pprintf(page, y, 0, stream);
        y++;
    }

    // scroll up by more 7 lines
    rv = BtSetFormFeed(y + 7);

    _TRACE("<---- %s()\n", __func__);
    return rv;
}

PRT_RESULT_t PageBuilderF3Key(int page, void* parguments) {
    PRT_RESULT_t rv = PRT_ERR_FAIL;
    int x, y, len;
    char stream[64 * 2];
    char sub_title[64 * 2];
    PAGEBUILDER_ARGS* args;
    int line_num_max;
    int line_char_max;

    _TRACE("----> %s()\n", __func__);

    args = (PAGEBUILDER_ARGS*) parguments;
    line_num_max = BtGetPageMaxLineNum();
    line_char_max = BtGetPageMaxCharNumPerLine();

    _TRACE("page( %d ), line_num_max( %d ), line_char_max( %d )\n", page, line_num_max, line_char_max);

    if (args->sub_title[0]) {
        // max character number per line is 32
        sprintf(sub_title, "< %s >", args->sub_title);
    }

#ifdef CONFIG_PRINTER_GRAPHIC
    {
        int line_space = 4;
        unsigned int logo_width;
        unsigned int logo_height;
        /* the height of the line of BitelOS printer driver is 24 pixels 
         * when line space is zero
         */
        int pixel_per_line_height = 24 + line_space;

        /*
         * Please, keep widthxheight header format for LOG byte arrary
         * BitelOS spec. : the first 4bytes are dedicated for resolution to be needed to be printed area 
                        addr[0] = MSB of width
                        addr[1] = LSB of width
                        addr[2] = MSB of height
                        addr[3] = LSB of height
         */
        extern const char BITEL_PRINT_LOGO_128x32[];

        BtAssignGraphic(BITEL_PRINT_LOGO_128x32, 0);

        /* get width & height from BITEL logo bitmap */
        logo_width = (BITEL_PRINT_LOGO_128x32[0]&0xFF) << 8 | (BITEL_PRINT_LOGO_128x32[1]&0xFF);
        logo_height = (BITEL_PRINT_LOGO_128x32[2]&0xFF) << 8 | (BITEL_PRINT_LOGO_128x32[3]&0xFF);
        _TRACE("Logo( %u, %u )\n", logo_width, logo_height);

        // convert pixel height to line
        y = logo_height / pixel_per_line_height;
        // one line more for margin
        y += 1;
    }
#else
    y = 0;
#endif

    y = HeadTitleForm(page, y, "PageBuilder", sub_title, "Test");
    Pprintf(page, y, 0, "--------------------------------");
    y++;

    // max character number per line is 32
    Pprintf(page, y, 0, "################################");
    y++;

    if (args->sub_title[0]) {
        strcpy(stream, args->sub_title);
        strcpy(stream + strlen(stream), " builder");
        len = strlen(stream);
        x = 0;
        AttrPprintf(page, y, x, stream);
        y++;
    }

    if (args->sub_title[0]) {
        // max character number per line is 32
        sprintf(stream, "< %s >", args->sub_title);
        Pprintf(page, y, 0, stream);
        y++;
    }
    // max character number per line is 32
    Pprintf(page, y, 0, "--------------------------------");
    y++;

    if (args->amount[0]) {
        // max character number per line is 32
        sprintf(stream, "Amount : %s", args->amount);
        Pprintf(page, y, 0, stream);
        y++;
    }

    if (args->count[0]) {
        // max character number per line is 32
        sprintf(stream, "Count : %s", args->count);
        Pprintf(page, y, 0, stream);
        y++;
    }

    if (args->pin[0]) {
        // max character number per line is 32
        sprintf(stream, "Pin : %s", args->pin);
        Pprintf(page, y, 0, stream);
        y++;
    }
    if (args->transaction_result[0]) {
        // max character number per line is 32
        sprintf(stream, "Transaction : %s", args->transaction_result);
        Pprintf(page, y, 0, stream);
        y++;
    }

    // scroll up by more 7 lines
    rv = BtSetFormFeed(y + 7);

    _TRACE("<---- %s()\n", __func__);
    return rv;
}

/**
 * @brief	Printer Test Page builder
 *
 */
PRT_RESULT_t PageBuilderPrintKeyValue(int page, void* parguments) {
    PRT_RESULT_t rv = PRT_ERR_FAIL;
    int x, y, len;
    char stream[64 * 2];
    PAGEBUILDER_ARGS* args;
    int line_num_max;
    int line_char_max;

    _TRACE("----> %s()\n", __func__);

    args = (PAGEBUILDER_ARGS*) parguments;
    line_num_max = BtGetPageMaxLineNum();
    line_char_max = BtGetPageMaxCharNumPerLine();

#ifdef CONFIG_PRINTER_GRAPHIC
    {
        int line_space = 4;
        unsigned int logo_width;
        unsigned int logo_height;
        /* the height of the line of BitelOS printer driver is 24 pixels 
         * when line space is zero
         */
        int pixel_per_line_height = 24 + line_space;

        /*
         * Please, keep widthxheight header format for LOG byte arrary
         * BitelOS spec. : the first 4bytes are dedicated for resolution to be needed to be printed area 
                        addr[0] = MSB of width
                        addr[1] = LSB of width
                        addr[2] = MSB of height
                        addr[3] = LSB of height
         */
        extern const char BITEL_PRINT_LOGO_128x32[];

        BtAssignGraphic(BITEL_PRINT_LOGO_128x32, 0);

        /* get width & height from BITEL logo bitmap */
        logo_width = (BITEL_PRINT_LOGO_128x32[0]&0xFF) << 8 | (BITEL_PRINT_LOGO_128x32[1]&0xFF);
        logo_height = (BITEL_PRINT_LOGO_128x32[2]&0xFF) << 8 | (BITEL_PRINT_LOGO_128x32[3]&0xFF);
        _TRACE("Logo( %u, %u )\n", logo_width, logo_height);

        // convert pixel height to line
        y = logo_height / pixel_per_line_height;
        // one line more for margin
        y += 1;
    }
#else
    y = 0;
#endif
    USE_PRTFONT(PrtArabic,1);
    
    strcpy(stream, "hgsghl ugd;l , vplm hggi");
    len = strlen(stream);
    x = 0;
    Arabic_Printer_printf(y, x, stream, page);
    y++;
    strcpy(stream, "hgsghl ugd;l , vplm hggi");
    len = strlen(stream);
    x = 0;
    Arabic_Printer_printf(y, x, stream, page);
    y++;
    strcpy(stream, "hgsghl ugd;l , vplm hggi");
    len = strlen(stream);
    x = 0;
    Arabic_Printer_printf(y, x, stream, page);
    y++;
    Pprintf(page, y, 0, "--------------------------------");
    y++;
    Pprintf(page, y, 0, "--------------------------------");
    y++;
    Pprintf(page, y, 0, "--------------------------------");
    y++;
    // scroll up by more 1 lines
    y++;
    rv = BtSetFormFeed(y);

    _TRACE("<---- %s()\n", __func__);
    return rv;
}

PRT_RESULT_t ArabicPrinter(int page) {
    PRT_RESULT_t rv = PRT_ERR_FAIL;
    int line_num_max;
    int line_char_max;
    int y = 0, x = 0;

    line_num_max = BtGetPageMaxLineNum();
    line_char_max = BtGetPageMaxCharNumPerLine();
    Pprintf(page, y, 0, "Test 1");
    y++;
    Pprintf(page, y, 0, "Test 2");
    y++;
    y++;

    Arabic_Printer_printf(y, x, "hgsghl ugd;l , vplm hggi", page);
    y++;
    Arabic_Printer_printf(y, x, "Yojfhv hggym hguvfdm", page);
    y++;
    Arabic_Printer_printf(y, x, "hgd,l i, 8-6-2017", page);
    y++;
    Arabic_Printer_printf(y, x, "jlj ,/dtm hggym hguvfdm", page);
    y++;
    Pprintf(page, y, 0, "--------------------------------");
    y++;
    rv = BtSetFormFeed(y + 7);
    return rv;
}
