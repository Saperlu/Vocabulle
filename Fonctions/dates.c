//
//  dates.c
//  Vocabulle 2.0
//
//  Created by Lulu on 16/07/2018.
//  Copyright © 2018 Lulu. All rights reserved.
//

#include "dates.h"


void InitDatePerso(datePerso * date)
{
    date->unite = malloc(sizeof(time_t));
    date->time = malloc(sizeof(struct tm));
}

void DateActuelle (datePerso aujourdhui)
{
    time(aujourdhui.unite);
    *(aujourdhui.time) = * localtime(aujourdhui.unite);
}

void RemplirDate(datePerso date)
{
    date.time = localtime(date.unite);
}
