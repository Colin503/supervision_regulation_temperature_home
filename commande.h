#ifndef COMMANDE_H
#define COMMANDE_H

/**
 * @file commande.h
 * @brief Envoi de la commande de chauffage via USB (protocole FTDI)
 */

/**
 * @brief Initialise la liaison USB avec la carte électronique.
 * @return 0 si succès, -1 en cas d'erreur.
 */
int commande_init(void);

/**
 * @brief Envoie une commande de chauffage.
 * @param puissance Puissance en pourcentage (0 à 100).
 * @return 0 si succès, -1 en cas d'erreur.
 */
int commande_envoyer(float puissance);

/**
 * @brief Ferme la liaison USB.
 */
void commande_fermer(void);

#endif