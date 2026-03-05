#include <stdio.h>
#include "define.h"
#include "consigne.h"
#include "visualisationT.h"
#include "visualisationC.h"

int main() {
    temp_t maTemp = {15, 25}; // Intérieure 18.5, Extérieure 12.0
    float MaConsigne;

    // Test 1 : Lecture de la consigne
    MaConsigne = consigne(20.0); 
    printf("Consigne lue : %.2f\n", MaConsigne);

    // Test 2 : Envoi des températures vers l'IHM
    visualisationT(maTemp);

    // Test 3 : Envoi du témoin de chauffe (puissance > 0)
    visualisationC(50.0); 

    return 0;
}