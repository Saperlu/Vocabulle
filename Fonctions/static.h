//
//  static.h
//  Vocabulle 2.0
//
//  Created by Lulu on 15/07/2018.
//  Copyright © 2018 Lulu. All rights reserved.
//

#ifndef static_h
#define static_h

#define ERREUR (-1)
#define TAILLEMOT 99

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


#include <errno.h>

 long curDebutLigne;
static const char * cheminsFichiers[NOMBRECLASSES] = {F1, F2, F3, F4, F5, F6, F7};


#endif /* static_h */
