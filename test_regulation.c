#include <stdio.h>
#include "regulation.h"

int main() {
    // Exemple : régulation TOR (regul=1) avec consigne 20°C
    float tabT[] = {18.5, 19.0, 20.5, 21.0};
    int nT = 4;
    float consigne = 20.0;

    // Test TOR
    float cmd = regulationTest(1, consigne, tabT, nT);
    printf("Régulation TOR : puissance finale = %.2f%%\n", cmd);

    // Test PID
    cmd = regulationTest(2, consigne, tabT, nT);
    printf("Régulation PID : puissance finale = %.2f%%\n", cmd);

    return 0;
}