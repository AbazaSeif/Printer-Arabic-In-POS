/**
 *
 * @mainpage Introduction
 *				This is example source code to show how to use libApiNfc.a API library
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 *  Make "DEBUG_TRACE" active if you want to print on RS232 serial console terminal
 *  for _TRACE(....)
 */
#define DEBUG_TRACE
#include <debug_trace.h>

/* Bitel Standard API header */

#include <BitelStdApi.h> 


#include "printer_pagebuilder.h"

/**
 *
 * @brief Main function
 *
 *					
 */
int main(int argc, char *argv[]) {
    PRT_RESULT_t result;
    int preference = 15; // default 
    int line_space = 4; // default
    int keyval = 0x0;
    int printer_status = 0, working_status;

    PAGEBUILDER_ARGS prt_argument;
    int prt_page = 0;

#if 1
    /* enable _TRACE(...) console printing log trace for debugging */
    _TRACE_ENABLE();
#else
    /* disable _TRACE(...) console printing log trace for debugging */
    _TRACE_DISABLE();
#endif

    /*-----------------
     * Initialize basic system & heap
     */
    BtInitializeSystem();

#ifdef DEBUG_TRACE
    /*-----------------
     * Open Console stdout is 'COM_0' for Btprintf(*fmt, ...)
     * for console terminal to print debug log.
     */
    BtOpenComPort(COM_0, BPS_115200, D8_NP, STOP_B1);
    /* Set console port to COM_0 for Btprintf(...) / _TRACE(...) */
    BtSetConsolePort(CONSOLE_COM_0);
    BtuDelay(10);
#endif

    /*------------------
     *
     * open Printer
     */
    BtOpenPrinter(preference, line_space);

    /* Set paper form feeding function key for BitelOS ( rolling up paper ) 
     * ( use F4 key to rolling up paper )
     */
    BtSavePrintKey(BTKEY_F4_CODE);

    Btprintf("\n");
    Btprintf("+---------------------------------------+\n");
    Btprintf("| BT-ADE : Printer example app. ( build time : %s - %s )\n", __DATE__, __TIME__);
    Btprintf("+---------------------------------------+\n");

    /*
     * Top level loop
     */
    while (1) {
        //--------------------------------
        /* 
         * running "Non-Blocking" Printer Task 
         */
        result = BtPrinterWorking(&working_status);
        if (result != PRT_SUCCESS) {
            Btprintf("ERROR : BtPrinterWorking Error\n");
            break;
        }
        /* debug log printing */
        if (working_status != printer_status) {
            /* update printer status */
            printer_status = working_status;
            switch (printer_status) {
                case PRT_STATUS_NO_PAPER:
                    _TRACE("Printer status : No pater\n");
                    break;
                case PRT_STATUS_TIMEOUT_ERROR:
                    _TRACE("Printer status : Error - timeout\n");
                    break;
                case PRT_STATUS_NO_PAPER_MARK_DETECTION_SEEK_FINISHED:
                    _TRACE("Printer status : No paper make detection seek finished\n");
                    break;
                case PRT_STATUS_HEAD_SEEK_FINISH:
                    _TRACE("Printer status : Head seek finished\n");
                    break;
                case PRT_STATUS_HEAD_SEEK_ERROR:
                    _TRACE("Printer status : Head seek error\n");
                    break;
                case PRT_STATUS_PRINTING:
                    _TRACE("Printer status : Printing now\n");
                    break;
                case PRT_STATUS_ALL_PAGE_PRINGING_FINISH:
                    _TRACE("Printer status : All page printing finish\n");
                    break;
                case PRT_STATUS_ONE_PAGE_PRINGING_FINISH:
                    _TRACE("Printer status : One page printing finish\n");
                    break;
            }
        }
        if (BtIsPrinterBusy()) {
            _TRACE("Busy\n");
            continue; // printer is busy, goto BtPrinterWorking again
        }
        //--------------------------------


        /* polling key input */
        keyval = (int) BtKeyScan();
        /* service for the key input */
        switch (keyval) {
            case BTKEY_CANCEL_CODE:
                Btprintf("CANCEL key is pressed\n");
                /*
                 * < !!!! CAUTION !!!! >
                 *		At everytime when you stop printer, you should check if printer is idle. 
                 *		If it is not idle, you can not exit loop context.
                 *
                 *		If you ignore this mandatory condition then printer may burn.
                 */
                /* check printer is idle or not */
                if (!BtIsPrinterBusy()) {
                    Btprintf("Printer is idle now\n");
                    goto out;
                } else {
                    Btprintf("Printer is busy\n");
                }
                break;
            case BTKEY_N0_CODE:
            case BTKEY_N1_CODE:
            case BTKEY_N2_CODE:
            case BTKEY_N3_CODE:
            case BTKEY_N4_CODE:
            case BTKEY_N5_CODE:
            case BTKEY_N6_CODE:
            case BTKEY_N7_CODE:
            case BTKEY_N8_CODE:
            case BTKEY_N9_CODE:
                Btprintf("%c\n", '0' + keyval);

                /* initialize arguments for print-builder function */
                memset(&prt_argument, 0x0, sizeof (PAGEBUILDER_ARGS));
                /* clear a page of printer */
                BtClearPage(prt_page);

                prt_argument.key_scancode = keyval;
                prt_argument.key_ch = '0' + keyval;

                /* setup page builder function */
                BtSetPageBuilder(PageBuilderPrintKeyValue, prt_page, &prt_argument);
                /* send start command to BitelOS to print */
                BtStartPrintingPage(prt_page);

                break;
            case BTKEY_STAR_CODE:
                Btprintf("*\n");
                break;
            case BTKEY_POND_CODE:
                Btprintf("#\n");
                break;
            case BTKEY_CLEAR_CODE:
                Btprintf("CLEAR\n");
                break;
            case BTKEY_ENTER_CODE:
                Btprintf("ENTER\n");
                break;
            case BTKEY_F1_CODE:
                Btprintf("F1\n");

                /* initialize arguments for print-builder function */
                memset(&prt_argument, 0x0, sizeof (PAGEBUILDER_ARGS));
                /* clear a page of printer */
                BtClearPage(prt_page);

                sprintf(prt_argument.sub_title, "%s", "F1-KEY");
                sprintf(prt_argument.amount, "%s", strmoney((double) 100000000.1));
                sprintf(prt_argument.count, "%s", "10");
                sprintf(prt_argument.pin, "%s", "****");

                /* setup page builder function */
                BtSetPageBuilder(PageBuilderF1Key, prt_page, &prt_argument);
                /* send start command to BitelOS to print */
                BtStartPrintingPage(prt_page);

                break;
            case BTKEY_F2_CODE:
                Btprintf("F2\n");

                /* initialize arguments for print-builder function */
                memset(&prt_argument, 0x0, sizeof (PAGEBUILDER_ARGS));
                /* clear a page of printer */
                BtClearPage(prt_page);

                sprintf(prt_argument.sub_title, "%s", "F2-KEY");
                sprintf(prt_argument.amount, "%s", strmoney((double) 200000000.2));
                sprintf(prt_argument.count, "%s", "20");
                sprintf(prt_argument.pin, "%s", "****");

                BtSetPageBuilder(PageBuilderF2Key, prt_page, &prt_argument);
                /* send start command to BitelOS to print */
                BtStartPrintingPage(prt_page);

                break;
            case BTKEY_F3_CODE:
                Btprintf("F3\n");
                memset(&prt_argument, 0x0, sizeof (PAGEBUILDER_ARGS));
                BtClearPage(prt_page);
                sprintf(prt_argument.sub_title, "%s", "hgtjhp hgvhfu");
                sprintf(prt_argument.amount, "%s", strmoney((double) 300000000.3));
                sprintf(prt_argument.count, "%s", "30");
                sprintf(prt_argument.pin, "%s", ";,]");
                BtSetPageBuilder(PageBuilderPrintKeyValue, prt_page, &prt_argument);
                BtStartPrintingPage(prt_page);

                break;
        }

    }

out:
    Btprintf("+--------------------------\n");
    Btprintf("| Exit printer example app.\n");
    Btprintf("+--------------------------\n");

    /*------------------
     *
     * close Printer
     */
    BtClosePrinter();

    /*------------------
     *
     * close ComPort
     */
    BtCloseComPort(COM_0);

    return 0;
}
