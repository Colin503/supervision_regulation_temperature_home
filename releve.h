#ifndef RELEVE_H
#define RELEVE_H

#include "define.h"   // pour temp_t

int releve_init(void);
int releve_get_temp(temp_t *t);
void releve_close(void);
int releveTest(temp_t* tabT, int nT);

#endif