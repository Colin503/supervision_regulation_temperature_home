#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

float regulationTest(int regul, float consigne, float* tabT, int nT) {
    float cmd = 0.0;   

    if (nT <= 0) {
        return cmd;     

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

        float integral = 0.0;       
        float previous_error = 0.0; 

        for (int i = 0; i < nT; i++) {
            float error = consigne - tabT[i];

            if (i == 0) {
                cmd = Kp * error;
                integral = error;               
                previous_error = error;
            } else {
                integral += error;               
                float derivative = error - previous_error;
                cmd = Kp * error + Ki * integral + Kd * derivative;
                previous_error = error;
            }

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
}