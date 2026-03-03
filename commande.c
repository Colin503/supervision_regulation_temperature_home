#include "commande.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include "ftd2xx.h"
#endif

#if defined(_WIN32) && !defined(SIMULATION)
static FT_HANDLE ftHandle = NULL;
#endif


int commande_init(void) {
#if defined(_WIN32) && !defined(SIMULATION)
    FT_STATUS ftStatus;
    DWORD numDevs = 0;

    ftStatus = FT_ListDevices(&numDevs, NULL, FT_LIST_NUMBER_ONLY);
    if (ftStatus != FT_OK || numDevs == 0) {
        printf("commande_init : aucun périphérique FTDI trouvé.\n");
        return -1;
    }

    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != FT_OK) {
        printf("commande_init : échec de l'ouverture du périphérique.\n");
        return -1;
    }

    ftStatus = FT_SetBaudRate(ftHandle, 115200);
    if (ftStatus != FT_OK) {
        printf("commande_init : erreur de configuration du baudrate.\n");
        FT_Close(ftHandle);
        return -1;
    }

    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    if (ftStatus != FT_OK) {
        printf("commande_init : erreur de configuration des données.\n");
        FT_Close(ftHandle);
        return -1;
    }

    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    if (ftStatus != FT_OK) {
        printf("commande_init : erreur de configuration du contrôle de flux.\n");
        FT_Close(ftHandle);
        return -1;
    }

    ftStatus = FT_SetTimeouts(ftHandle, 1000, 1000);
    if (ftStatus != FT_OK) {
        printf("commande_init : erreur de configuration des timeouts.\n");
        FT_Close(ftHandle);
        return -1;
    }

    printf("commande_init : liaison USB initialisée avec succès.\n");
    return 0;
#else
    printf("commande_init : mode simulation.\n");
    return 0;
#endif
}


int commande_envoyer(float puissance) {
    if (puissance < 0.0) puissance = 0.0;
    if (puissance > 100.0) puissance = 100.0;

    unsigned char puish = (unsigned char)((puissance * 127.0 / 100.0) + 0.5);
    unsigned char commande = puish & 0x7F;

#if defined(_WIN32) && !defined(SIMULATION)
    if (ftHandle == NULL) {
        printf("commande_envoyer : liaison USB non initialisée.\n");
        return -1;
    }
    DWORD bytesWritten;
    FT_STATUS ftStatus = FT_Write(ftHandle, &commande, 1, &bytesWritten);
    if (ftStatus != FT_OK || bytesWritten != 1) {
        printf("commande_envoyer : erreur d'écriture USB.\n");
        return -1;
    }
#else
    printf("commande_envoyer : puissance = %.1f%%, octet = 0x%02X\n", puissance, commande);
#endif
    return 0;
}

void commande_fermer(void) {
#if defined(_WIN32) && !defined(SIMULATION)
    if (ftHandle != NULL) {
        FT_Close(ftHandle);
        ftHandle = NULL;
        printf("commande_fermer : liaison USB fermée.\n");
    }
#else
    printf("commande_fermer : simulation.\n");
#endif
}