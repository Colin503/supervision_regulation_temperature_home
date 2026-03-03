#include "visualisationT.h"

void visualisationT(temp_t myTemp)
{
    FILE *fptr;
    char verrouData[10];
    fptr = fopen(".verrouData", "r");
    if (fptr != NULL) {
        printf("Le fichier .verrouData existe\n");
        fclose(fptr);
        return;
    }
    else {
        printf("Le fichier .verrouData n'existe pas\n");
        fptr = fopen("data.txt", "r");
        if (fptr != NULL) {
            fscanf(fptr,"%s",verrouData);
            fclose(fptr);
            fptr = fopen("data.txt", "w");
            fprintf(fptr, "%s\n", verrouData);
            fprintf(fptr, "%.2f\n", myTemp.interieure);
            fprintf(fptr, "%.2f\n", myTemp.exterieure);
            fclose(fptr);
        }
    }
}
