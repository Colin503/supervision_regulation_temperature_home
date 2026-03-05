#include "regulation.h"

static const float KP = 2.0;
static const float KI = 0.5;
static const float KD = 1.0;
static const float DT = 10.0; //cste de temps , 10 -> 10s

void pid_init(PidState *etat)
{
    etat->integrale = 0.0;
    etat->erreur_precedente = 0.0;
}

float regulation(int regul, float consigne, float temperature, PidState *etat)
{
    float commande = 0.0;

    if (regul == REGUL_TOR)
    {
        if (temperature < consigne)
            commande = 50.0;
        else
            commande = 0.0;
    }
    else if (regul == REGUL_PID)
    {
        float erreur = consigne - temperature;
        float derivee = 0.0;
        if (etat->erreur_precedente == 0.0 && etat->integrale == 0.0) derivee = 0.0;
        else {
            // integrale
            etat->integrale += ((erreur + etat->erreur_precedente) / 2.0) * DT;

            // dérivéee
            derivee = (erreur - etat->erreur_precedente) / DT;
        }
        // commande
        commande = (KP * erreur) + (KI * etat->integrale) + (KD * derivee);

        //nouvelle erreur
        etat->erreur_precedente = erreur;

        if (commande < 0.0)
            commande = 0.0;
        if (commande > 100.0)
            commande = 100.0;
    }

    return commande;
}

float regulationTest(int regul, float consigne, float* tabT, int nT)
{
    if (nT <= 0)
        return 0.0;

    PidState etat;
    pid_init(&etat);

    float commande = 0.0;

    for (int i = 0; i < nT; i++)
    {
        commande = regulation(regul, consigne, tabT[i], &etat);
        // On garde la dernière commande calculée (comme spécifié)
    }

    return commande;
}