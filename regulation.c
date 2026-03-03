#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

float regulationTest(int regul, float consigne, float* tabT, int nT) {
    float cmd = 0.0;   // puissance de commande à retourner

    if (nT <= 0) {
        return cmd;     // pas de données, retourne 0
    }

    if (regul == 1) {
        // Régulation Tout Ou Rien
        for (int i = 0; i < nT; i++) {
            if (tabT[i] < consigne)
                cmd = 50.0;
            else
                cmd = 0.0;
        }
    }
    else if (regul == 2) {
        // Régulation PID avec gains imposés
        const float Kp = 1.1;
        const float Ki = 0.2;
        const float Kd = 0.15;

        float integral = 0.0;       // somme des erreurs
        float previous_error = 0.0; // erreur à l'étape précédente

        for (int i = 0; i < nT; i++) {
            float error = consigne - tabT[i];

            if (i == 0) {
                // Première itération : seulement le terme proportionnel
                cmd = Kp * error;
                // Initialisation pour les itérations suivantes
                integral = error;               // on commence à accumuler
                previous_error = error;
            } else {
                // Itérations suivantes : les trois termes
                integral += error;               // accumulation de l'erreur
                float derivative = error - previous_error;
                cmd = Kp * error + Ki * integral + Kd * derivative;
                previous_error = error;
            }

            // Saturation de la commande entre 0 et 100 %
            if (cmd < 0.0) cmd = 0.0;
            if (cmd > 100.0) cmd = 100.0;
        }
    }
    else {
        // Type de régulation inconnu
        cmd = 0.0;
    }

    return cmd;
}