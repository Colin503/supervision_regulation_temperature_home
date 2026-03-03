#include "consigne.h"

   float consigne(float thermostatPrec_f)
   {
   
      float thermostat_f=0;
      FILE *fptr;

      // Open a file in read mode
      fptr = fopen(".verrouConsigne", "r");
      if (fptr != NULL) {
         printf("Le fichier .verrou existe\n");
         fclose(fptr);
         return thermostatPrec_f;
      }
      else {
         printf("Le fichier .verrou n'existe pas\n");
         fptr = fopen("consigne.txt", "r");
         if (fptr != NULL) {
            fscanf(fptr, "%f", &thermostat_f);
            fclose(fptr);
        }
        return thermostat_f;
    }
}
