#include "regulation.h"
#include <stdio.h>

/**
 * Simule nT appels à la fonction de régulation et retourne la dernière puissance calculée.
 * @param regul    Type de régulation : 1 = Tout Ou Rien, 2 = PID
 * @param consigne Consigne de température (°C)
 * @param tabT     Tableau des températures intérieures successives (°C)
 * @param nT       Nombre de valeurs dans tabT
 * @return         Puissance de chauffage (en %) après le dernier appel
 */
float regulationTest(int regul, float consigne, float* tabT, int nT) {
    if (nT <= 0) return 0.0f;   // Aucune itération

    float puissance = 0.0f;

    if (regul == 1) {
        // Régulation Tout Ou Rien
        for (int i = 0; i < nT; i++) {
            if (tabT[i] < consigne)
                puissance = 50.0f;   // Chauffage à 50 %
            else
                puissance = 0.0f;     // Chauffage éteint
        }
    }
    else if (regul == 2) {
        // Régulation PID avec gains imposés
        const float Kp = 1.1f;
        const float Ki = 0.2f;
        const float Kd = 0.15f;

        float integral = 0.0f;        // Somme des erreurs
        float previous_error = 0.0f;   // Erreur à l'itération précédente

        for (int i = 0; i < nT; i++) {
            float error = consigne - tabT[i];

            if (i == 0) {
                // Première itération : on n'utilise que le terme proportionnel
                puissance = Kp * error;
                // On initialise l'intégrale et l'erreur précédente pour la prochaine fois
                integral = error;           // On pourrait aussi laisser à 0, mais l'intégrale commencera à s'accumuler dès la seconde itération
                previous_error = error;
            } else {
                // Itérations suivantes : on calcule les trois termes
                integral += error;                   // Accumulation de l'erreur (pas de temps = 1)
                float derivative = error - previous_error;
                puissance = Kp * error + Ki * integral + Kd * derivative;

                // Mise à jour pour l'itération suivante
                previous_error = error;
            }

            // Saturation de la puissance entre 0 et 100 % (loi linéaire)
            if (puissance < 0.0f) puissance = 0.0f;
            if (puissance > 100.0f) puissance = 100.0f;
        }
    }

    return puissance;
}