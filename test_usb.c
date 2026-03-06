#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "regulation.h"
#include "visualisationT.h"
#include "visualisationC.h"
#include "simulateur.h"
#include "consigne.h"
#include "define.h"
#include "releve.h"
#include "commande.h"

int main(void) {
    temp_t temperature;
    temperature.interieure = 10.0f;
    temperature.exterieure = 8.0f;
    float cons = 20.0f;
    float cmd = 0.0f; // commande de chauffage
    PidState pid;

    /* initialisation des interfaces USB / simulation */
    if (commande_init() != 0) {
        fprintf(stderr, "Erreur initialisation commande USB.\n");
        return EXIT_FAILURE;
    }
    if (releve_init() != 0) {
        fprintf(stderr, "Erreur initialisation relev\u00e9e de temp\u00e9rature.\n");
        commande_fermer();
        return EXIT_FAILURE;
    }

    pid_init(&pid);

    /* boucle de supervision */
    while (cons > 5.0f) {
        if (releve_get_temp(&temperature) != 0) {
            fprintf(stderr, "Erreur lecture temp\u00e9rature.\n");
            break;
        }

        visualisationT(temperature);
        printf("Ext %f, Int %f\n", temperature.exterieure, temperature.interieure);

        /* régulation en PID (ou TOR si modifié) */
        cmd = regulation(REGUL_PID, cons, temperature.interieure, &pid);

        cons = consigne(cons);

        visualisationC(cmd);

        if (commande_envoyer(cmd) != 0) {
            fprintf(stderr, "Erreur d'envoi de commande USB.\n");
            break;
        }

        usleep(40000);
    }

    /* arrêt et nettoyage */
    commande_envoyer(0.0f);
    releve_close();
    commande_fermer();

    return EXIT_SUCCESS;
}