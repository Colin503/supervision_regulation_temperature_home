#include "consigne.h"

float consigne(float thermostatPrec_f) {
    float thermostat_f = thermostatPrec_f; // On garde l'ancienne valeur par défaut
    FILE *fptr;

    // Vérification du verrou
    fptr = fopen(".verrouConsigne", "r");
    if (fptr != NULL) {
        fclose(fptr);
        return thermostatPrec_f; // Verrou présent, on ne touche à rien
    }

    // Lecture de la consigne
    fptr = fopen("consigne.txt", "r");
    if (fptr != NULL) {
        if (fscanf(fptr, "%f", &thermostat_f) != 1) {
            thermostat_f = thermostatPrec_f; // Si fichier vide/mal formé
        }
        fclose(fptr);
    }
    return thermostat_f;
}