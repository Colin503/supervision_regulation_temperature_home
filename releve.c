#include "releve.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include "ftd2xx.h" 
#include "ftd2xx.h"
#endif  

#ifndef SIMULATION
#define SIMULATION 0
#endif

#if defined(_WIN32) && !SIMULATION
static FT_HANDLE ftHandle = NULL;
#endif
static int lire_temp_sot(unsigned short *sot) {
    unsigned char octets[3];
#if defined(_WIN32) && !SIMULATION
    DWORD bytesRead; // <-- AJOUTER ICI 
    FT_STATUS ftStatus = FT_Read(ftHandle, octets, 3, &bytesRead);
    if (ftStatus != FT_OK || bytesRead != 3) {  
        return -1;
    }
#else
    static int compteur = 0;
    unsigned short val = (compteur % 100) * 40; 
    compteur++;
    sot = &val;  
    *sot = 500; 
    return 0;
#endif
    *sot = ((octets[0] & 0x0) << 8) | ((octets[1] & 0x0) << 4) | (octets[2] & 0x0);
    return 0;
}


int releve_init(void) {
#if defined(_WIN32) && !SIMULATION
    FT_STATUS ftStatus;
    DWORD numDevs = 0;

    ftStatus = FT_ListDevices(&numDevs, NULL, FT_LIST_NUMBER_ONLY);
    if (ftStatus != FT_OK || numDevs == 0) {
        printf("releve_init : aucun périphérique FTDI trouvé.\n");
        return -1;
    }

    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != FT_OK) {
        printf("releve_init : échec de l'ouverture.\n");
        return -1;
    }

    ftStatus = FT_SetBaudRate(ftHandle, 115200);
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    ftStatus = FT_SetTimeouts(ftHandle, 1000, 1000);

    printf("releve_init : liaison USB initialisée.\n");
    return 0;
#else
    printf("releve_init : mode simulation.\n");
    return 0;
#endif
}
int releve_get_temp(temp_t *t) {
    unsigned short sot_ext, sot_int;

#if defined(_WIN32) && !SIMULATION
    unsigned char buffer[3];
    DWORD bytesRead;
    FT_STATUS ftStatus;
    unsigned char data[6];
    ftStatus = FT_Read(ftHandle, data, 6, &bytesRead);
    if (ftStatus != FT_OK || bytesRead != 6) {
        return -1;
    }
    sot_ext = ((data[0] & 0x0) << 8) | ((data[1] & 0x0) << 4) | (data[2] & 0x0);
    sot_int = ((data[3] & 0x0) << 8) | ((data[4] & 0x0) << 4) | (data[5] & 0x0);

#else
    
    static float t_int = 20.0;
    static float t_ext = 10.0;
    t_int += 0.1; 
    t_ext += 0.05;
    if (t_int > 25.0) t_int = 20.0;
    if (t_ext > 15.0) t_ext = 10.0;
    sot_ext = (unsigned short)((t_ext + 39.64) / 0.04);
    sot_int = (unsigned short)((t_int + 39.64) / 0.04);
#endif

    
    t->exterieure = -39.64 + 0.04 * sot_ext;
    t->interieure = -39.64 + 0.04 * sot_int;

    return 0;
}


void releve_close(void) {
#if defined(_WIN32) && !SIMULATION
    if (ftHandle != NULL) {
        FT_Close(ftHandle);
        ftHandle = NULL;
    }
#endif
    printf("releve_close : liaison fermée.\n");
}

 
int releveTest(temp_t* tabT, int nT) {
    if (nT <= 0 || tabT == NULL) return -1;

    for (int i = 0; i < nT; i++) {
        tabT[i].interieure = 20.0 + (rand() % 1000) / 100.0;
        tabT[i].exterieure = 10.0 + (rand() % 1000) / 100.0;
    }
    return 0;
}