//
//  affichage.h
//  Vocabulle 2.0
//
//  Created by Lulu on 13/07/2018.
//  Copyright © 2018 Lulu. All rights reserved.
//

#ifndef affichage_h
#define affichage_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "static.h"

#define LETTRE mot[i]
#define HAUTEUR_LETTRE 5

void premierMessage(void);

char MenuPrincipal(void);

void PresentationEntrer (void);

void EntrerMot(char mot[]);

void presentationApprendre(void);

void afficherMot (char mot[]);

char menuApprendre(void);

int menuVoir(void);

void afficherClasse(FILE* classe);

void menuSupprimer(int* classe, int* ligne, FILE** tableauFichier);

long afficherLigne(FILE* classe, int ligne);

char menuValiderSuppression(void);



#endif /* affichage_h */
