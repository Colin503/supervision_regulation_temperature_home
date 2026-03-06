#include <stdio.h>
#include <stdlib.h>

// Inclusion pour la fonction de pause (selon votre système)
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Inclusion de tous vos modules
#include "define.h"
#include "commande.h"
#include "consigne.h"
#include "regulation.h"
#include "releve.h"
#include "visualisationT.h"
#include "visualisationC.h"
#include "simulateur.h" // Si vous avez un simulateur pour tester sans matériel

// Décommentez ces lignes si votre prof vous a fourni ces fichiers :
// #include "simulateur.h"
// #include "visualisationT.h"
// #include "visualisationC.h"

int main(void) {
    // 1. Initialisation des variables
    float consigne_act = 19.0;    // Consigne de départ
    float temp_mesuree = 15.0;    // Température de la pièce au démarrage
    float puissance_cmd = 0.0;
    temp_t temperatures = {15.0, 10.0}; // Structure pour stocker les températures int/ext
    
    PidState etat_pid;
    pid_init(&etat_pid);

    printf("=== DEMARRAGE DU THERMOSTAT ===\n");

    // 2. Initialisation de la carte (ou mode simulation)
    commande_init(); 
    releve_init(); // Initialisation du capteur
    struct simParam_s* mon_simulateur = simConstruct(temperatures);

    // 3. Boucle infinie du régulateur
    while (1) {
        printf("\n--- Nouveau cycle de 10s ---\n");

        // A. Lire la consigne envoyée par l'IHM (lit le fichier consigne.txt)
        consigne_act = consigne(consigne_act);
        printf("Consigne demandee : %.2f °C\n", consigne_act);

        // B. Lire la température de la pièce (via le simulateur ou la carte)
        temperatures = simCalc(puissance_cmd, mon_simulateur);
        temp_mesuree = temperatures.interieure; 
        temp_mesuree = temperatures.interieure; // Met à jour la variable float utilisée par le PID
        printf("Temperature lue   : %.2f °C\n", temp_mesuree);

        // C. Calculer la puissance de chauffe (On teste le PID ici)
        puissance_cmd = regulation(REGUL_PID, consigne_act, temp_mesuree, &etat_pid, i);
        printf("Puissance chauffe : %.2f %%\n", puissance_cmd);

        // D. Envoyer l'ordre de chauffe
        commande_envoyer(puissance_cmd);

        // E. Envoyer les données à l'IHM pour qu'elle trace les courbes
        visualisationT(temperatures); // Envoie la structure complète (int + ext)
        visualisationC(puissance_cmd);

       
       
        temp_mesuree += (puissance_cmd / 100.0) * 0.8 - 0.2; 
    }

    commande_fermer();
    releve_close(); // Fermeture propre du capteur
    return 0;
}