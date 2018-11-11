//
//  dates.h
//  Vocabulle 2.0
//
//  Created by Lulu on 16/07/2018.
//  Copyright © 2018 Lulu. All rights reserved.
//

#ifndef dates_h
#define dates_h

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define joursEnSecondes(jours) 86400*jours

typedef struct datePerso datePerso;

void InitDatePerso(datePerso * date);

struct datePerso {
    time_t * unite;
    struct tm * time;
};

void DateActuelle (datePerso aujourdhui);

void RemplirDate(datePerso date);

#endif /* dates_h */
