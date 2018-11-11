//
//  fichiers.c
//  Vocabulle 2.0
//
//  Created by Lulu on 14/07/2018.
//  Copyright © 2018 Lulu. All rights reserved.
//

#include "fichiers.h"

void ChangerRepertoireCourant(const char argv[])// argv est ici le chemin absolu du programme.
{
    char *chemin;
    int i;
    
    for (i = (int) strlen(argv) ; argv[i] != '/' ; i--); // On remonte au dernier / pour savoir où, dans la chaine, se trouve le nom de l app à emputer.
    chemin = malloc(sizeof(char) * (i+2)); // (i+1) pour laisser la place du '\0'
    strncpy(chemin, argv, i);
    chemin[i] = '/';
    chemin[i+1] = '\0';
    if (chdir(chemin) < 0)
        perror("\nERREUR : chdir dans ChangerRepertoireCourant\nCHEMIN : %s\n");
    free(chemin);

}

int OuvrirTousFichiers (FILE * fichier[])
{
    int erreur = 0;
    //mkdir(DOSSIER, S_IRWXU); // Crée le dossier au cas où.
    
    for (int i = 0 ; i<NOMBRECLASSES ; i++)
    {
        if ((fichier[i] = fopen(cheminsFichiers[i], "r+")) == NULL)
        {
            perror("\nERREUR : probleme ouverture fichier\n");
            erreur = 1;
        }
    }
    if(erreur)
        return ERREUR;
    else
        return 0;
}

void EcrireMot(FILE* classe, const char mot[], time_t date)
{
    if (classe == NULL)
        perror("\nERREUR : Fichier inexistant dans EcrireMot\n");
    fseek(classe, 0, SEEK_END);
    if (fprintf(classe, "%ld %s", date, mot) < 0)
        perror("\nERREUR : fputs dans EcrireMot\n");
}

char* chercherMot(FILE* classe, time_t aujourdhui)
{
    int continuer = 1;
    time_t date;
    while (fgetc(classe) != EOF && continuer)
    {
        fseek(classe, -1, SEEK_CUR);
        curDebutLigne = ftell(classe);
        
        char * ligne = malloc(120 * sizeof(char));
        char * mot = malloc(120 * sizeof(char));
        
        fgets(ligne, 120, classe);
        
        if (ligne[0] != '-')
        {
            errno = 0;
            date = strtol(ligne, &mot, 0);
            
            if (errno == ERANGE)
            {
                perror("ERREUR : strtol dans chercher mot : ERANGE\n");
            }
            else if (mot == ligne)
            {
                perror("ERREUR : strtol dans chercher mot : aucun nombre trouvé\n");
            }
            else if (date <= aujourdhui)
                return mot;
        }
    }
    return NULL;
}


void invaliderLigne (FILE* classe, long curFinLigne)
{
    printf("\nCur : %ld\n", curDebutLigne);
    fseek(classe, curDebutLigne, SEEK_SET);
    fputc('-', classe);
    fseek(classe, curFinLigne, SEEK_SET);
}

void purifierClasse (FILE** classe, const int i)
{
    char ligne[256] = "";
    FILE * copie;
    fseek(*classe, 0, SEEK_SET);
    
    if ((copie = fopen(COPIE, "w+")) == NULL)
    {
        fclose(*classe);
        perror("fopen dans purifierClasse");
    }
    
    while (fgets(ligne, 256, *classe))
    {
        if (ligne[0] != '-')
            fputs(ligne, copie);
    }
    
    fclose(*classe);
    fclose(copie);
    
    if (remove(cheminsFichiers[i])) //supprime le fichier impure
        perror("\nERREUR : remove dans purifierClasse");
    if (rename(COPIE, cheminsFichiers[i])) // la copie purifiée prend la place du fichier detruit
        perror("\nERREUR : rename dans purifierFichier");
    
    if ((*classe = fopen(cheminsFichiers[i], "r+")) == NULL) // le pointeur sur le fichier devient celui sur la copie ayant pris la place et le nom du fichier
        perror("ERREUR : nouveau fopen dans purifierClasse");
}

