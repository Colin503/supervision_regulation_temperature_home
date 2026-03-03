#include <stdio.h>
#include "commande.h"

int main() {
    printf("Test du module commande\n");

    if (commande_init() != 0) {
        printf("Erreur : échec de l'initialisation\n");
        return 1;
    }

    float puissances[] = {0.0, 25.0, 50.0, 75.0, 100.0, -10.0f, 120.0f};
    int nb = sizeof(puissances) / sizeof(puissances[0]);

    for (int i = 0; i < nb; i++) {
        printf("Envoi puissance = %.1f%%\n", puissances[i]);
        if (commande_envoyer(puissances[i]) != 0) {
            printf("   -> Erreur lors de l'envoi\n");
        }
    }

    commande_fermer();

    return 0;
}