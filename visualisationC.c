#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"


   void visualisationC(float puissance_f)
   {
      FILE *fptr;
      float ligne2 = 0;
      float ligne3 = 0;
      char temoin[10];
      char ligne1[10];
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
            fscanf(fptr, "%s", ligne1); 
            fscanf(fptr, "%f", &ligne2);
            fscanf(fptr, "%f", &ligne3);
            fclose(fptr);

            if (puissance_f > 0) strcpy(temoin, "true");
            else strcpy(temoin, "false");

            fptr = fopen("data.txt", "w");
            fprintf(fptr, "%s\n", temoin);
            fprintf(fptr, "%.2f\n", ligne2); 
            fprintf(fptr, "%.2f\n", ligne3);
            fclose(fptr);
         }
      }
   }
