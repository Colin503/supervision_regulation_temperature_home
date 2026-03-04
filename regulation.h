#ifndef REGULATION_H
#define REGULATION_H
#define REGUL_TOR 1
#define REGUL_PID 2

typedef struct {
    float integrale;
    float erreur_precedente;
} PidState;

void pid_init(PidState *etat);
float regulation(int regul, float consigne, float temperature, PidState *etat);
float regulationTest(int regul, float consigne, float* tabT, int nT);

#endif