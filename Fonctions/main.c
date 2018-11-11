//
//  main.c
//  Vocabulle 2.0
//
//  Created by Lulu on 13/07/2018.
//  Copyright © 2018 Lulu. All rights reserved.
//

#include <stdio.h>
#include "affichage.h"
#include "fichiers.h"
#include "dates.h"
#include "static.h"

static datePerso aujourdhui;

//teeeest

int main(int argc, const char * argv[])
{
    premierMessage();
    
    //Déclarations des variables
    char menu, menuSecondaire = ' ';
    int autreMenu = -1, menuClasse = 0, menuLigne = 0;
    char * mot = NULL;
    int continuer = 1;
    int i;
    long curseur;
    
    InitDatePerso(&aujourdhui);
    DateActuelle(aujourdhui);
    time_t datesFutures[7] = {joursEnSecondes(1) + *(aujourdhui.unite), joursEnSecondes(2) + *(aujourdhui.unite),joursEnSecondes(3) + *(aujourdhui.unite), joursEnSecondes(5) + *(aujourdhui.unite),joursEnSecondes(8) + *(aujourdhui.unite), joursEnSecondes(13) + *(aujourdhui.unite),joursEnSecondes(21) + *(aujourdhui.unite)};
    
    
    FILE * fichier[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    if (argc >= 1)
        ChangerRepertoireCourant(argv[0]);
    else
        perror("pas de argv");
    if (OuvrirTousFichiers(fichier))
        perror("\nERREUR : ouverture des fichiers.");
    
    
/*********************************************
 * Menu principal :  -entrer des mots        *
 *                   -devinner des mots      *
 *                   -quitter le programme   *
 *********************************************/
    do // boucle monde
    {
        menu = MenuPrincipal();
        
        if (menu == 'e')
        {
            //entrer
            PresentationEntrer();
            continuer = 1;
            
            do {
                mot = malloc(TAILLEMOT+1 * sizeof(char));
                EntrerMot(mot);
                if (mot[0] == '!')
                    continuer = 0;
                else
                    EcrireMot(fichier[0], mot, datesFutures[0]);
                free(mot);
            } while (continuer);
        }
        else if (menu == 'a')
        {
            // apprendre
            presentationApprendre();
            i = 0;
            
            for (; i < NOMBRECLASSES && menuSecondaire != 'q' ; i++) {
               
                continuer = 1;
                curseur = 0;
                curDebutLigne = 0;
                printf("\nCLASSE %d\n", i+1);
                
                while (continuer)
                {
                    mot = malloc(TAILLEMOT+1 * sizeof(char));
                    if (mot == NULL)
                        perror("\nERREUR : malloc de mot dans apprendre");
                    //chercher un mot
                    if ((mot = chercherMot(fichier[i], *(aujourdhui.unite))) != NULL) {
                        curseur = ftell(fichier[i]);
                        
                        //afficher le mot et attendre son menu
                        afficherMot(mot);
                        menuSecondaire = menuApprendre();
                        
                        //ecrire classe
                        if (menuSecondaire == 'o') {
                            EcrireMot(fichier[i+1], mot, datesFutures[i+1]);
                            fseek(fichier[i+1], 0, SEEK_SET);
                        }
                        else if (menuSecondaire == 'n') {
                            EcrireMot(fichier[0], mot, datesFutures[0]);
                            if (i == 0)
                                fseek(fichier[i], curseur, SEEK_SET);
                        }
                        
                        if (menuSecondaire == 'q')
                            continuer = 0;
                        else
                            invaliderLigne(fichier[i], curseur);
                        
                        if (!(strcmp(mot, "")))
                            free(mot);// libere le mot pour eviter les fuites de memoire
                        
                    }// fin de traitement d un mot
                    else // si rechercherMot renvoit NULL, donc si on a atteint la fin du fichier
                    {
                        continuer = 0;
                    }
                } // fin de while (=fin de lecture d un fichier)
                purifierClasse(&(fichier[i]), i);

                if (menuSecondaire == 'q') // if (arreter d apprendre)
                    i = NOMBRECLASSES;
            } //fin de for
        }// fin apprendre
        else if (menu == 'v') {
            autreMenu = menuVoir();
            if (autreMenu == -1) {
                perror("ERREUR  : menuVoir");
            }
            else if (autreMenu == 666) {
                //Toutes les classes
                for (int j = 0 ; j < NOMBRECLASSES ; j++) {
                    printf("\nCLASSE %d:", j+1);
                    afficherClasse(fichier[j]);
                }
            }
            else {
                //une seule classe
                printf("\nCLASSE %d:", autreMenu+1);
                afficherClasse(fichier[autreMenu]);
            }
        }
        else if (menu == 's') {
            menuSupprimer(&menuClasse, &menuLigne, fichier);
            curDebutLigne = afficherLigne(fichier[menuClasse], menuLigne);
            menuSecondaire = menuValiderSuppression();
            
            if (menuSecondaire == 'o') {
                printf("\n CURSEUR : %ld", curDebutLigne);
                invaliderLigne(fichier[menuClasse], 0);
                purifierClasse(&(fichier[menuClasse]), menuClasse);
                printf("Suppression accomplie.\n");
            }
        }// fin supprimer
        
    }while (menu != 'q');
    
    //fin du grand programme

    
    return 0;
}
