//
//  fichiers.h
//  Vocabulle 2.0
//
//  Created by Lulu on 14/07/2018.
//  Copyright © 2018 Lulu. All rights reserved.
//

#ifndef fichiers_h
#define fichiers_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "static.h"
#include "dates.h"

#define NOMBRECLASSES 7
#define DOSSIER "Ressources/"
#define F1 "Ressources/Classe_1.txt"
#define F2 "Ressources/Classe_2.txt"
#define F3 "Ressources/Classe_3.txt"
#define F4 "Ressources/Classe_4.txt"
#define F5 "Ressources/Classe_5.txt"
#define F6 "Ressources/Classe_6.txt"
#define F7 "Ressources/Classe_7.txt"
#define COPIE "Ressources/copie.txt"

#define NOM1 "Classe_1.txt"
#define NOM2 "Classe_2.txt"
#define NOM3 "Classe_3.txt"
#define NOM4 "Classe_4.txt"
#define NOM5 "Classe_5.txt"
#define NOM6 "Classe_6.txt"
#define NOM7 "Classe_7.txt"

/*
 * Modifie le répertoire courant pour ouvrir les fichiers textes plus simplement.
 * Le répertoire d'installation devient le répertoire courant.
 * Pour cela on prend la chaine <<argv[0]>> et on enlève le nom du programme.
 */
void ChangerRepertoireCourant(const char *argv);

/*
 *Ouvre tous les fichiers contenant le vocabulaire.
 *Renvoit un int valant -1 en cas d'erreur ou 0 sinon.
 */
int OuvrirTousFichiers (FILE * fichier[]);

void EcrireMot(FILE* classe, const char mot[], time_t date);

char* chercherMot(FILE* classe, time_t aujourdhui);

void invaliderLigne (FILE* classe, long curFinLigne);

void purifierClasse (FILE** classe, const int i);

#endif /* fichiers_h */
