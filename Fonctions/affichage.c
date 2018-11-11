//
//  affichage.c
//  Vocabulle 2.0
//
//  Created by Lulu on 13/07/2018.
//  Copyright © 2018 Lulu. All rights reserved.
//

#include "affichage.h"

void premierMessage(void)
{
    char *V [HAUTEUR_LETTRE] =
    {
        "*       * ",
        " *     *  ",
        "  *   *   ",
        "   * *    ",
        "    *     "
    };
    
    char *O [HAUTEUR_LETTRE] =
    {
        " *****  ",
        "*     * ",
        "*     * ",
        "*     * ",
        " *****  "
    };
    
    char *C [HAUTEUR_LETTRE] =
    {
        " ***** ",
        "*      ",
        "*      ",
        "*      ",
        " ***** "
    };
    
    char *A [HAUTEUR_LETTRE] =
    {
        "    *     ",
        "   * *    ",
        "  *****   ",
        " *     *  ",
        "*       * "
    };
    
    char *B [HAUTEUR_LETTRE] =
    {
        "***   ",
        "*  *  ",
        "****  ",
        "*   * ",
        "****  "
    };
    
    char *U [HAUTEUR_LETTRE] =
    {
        "*    * ",
        "*    * ",
        "*    * ",
        "*    * ",
        " ****  "
    };
    
    char *L [HAUTEUR_LETTRE] =
    {
        "*     ",
        "*     ",
        "*     ",
        "*     ",
        "***** "
    };
    
    char *E [HAUTEUR_LETTRE] =
    {
        "***** ",
        "*     ",
        "***   ",
        "*     ",
        "***** ",
    };
    
    for (int i = 0 ; i < HAUTEUR_LETTRE ; i++)
    {
        printf("\n%s %s %s %s %s %s %s %s %s", V[i], O[i], C[i], A[i], B[i], U[i], L[i], L[i], E[i]);
    }
    printf("\n\n");
}

char MenuPrincipal()
{
    char menu;
    do {
        printf("\nMenu principal: \n-> e : Entrer des mots \n-> a : Apprendre des mots \n-> v : Voir les mots\n-> s : Supprimer un mot\n-> q : Quitter\n");
        menu = getchar();
        while (getchar() != '\n');
    } while (menu != 'e' && menu != 'a' && menu != 'v' && menu != 's' && menu != 'q');
    return menu;
}

void PresentationEntrer (void)
{
    printf("\nENTRER : \nEntrez un nouveau mot de vocabulaire avec le symbole << & >> entre deux synonymes, le symbole << > >> entre deux mots de la même famille, le symbole << = >> entre le mot francais et sa traduction et le mot francais en premier.\nEnrez le symbole << ! >> pour arreter.\n");
}

void EntrerMot(char mot[])
{
    printf("\nNouveau mot:\n");
    fgets(mot, TAILLEMOT, stdin);
}

void presentationApprendre(void)
{
    printf("\nAPPRENDRE : \nQuand un mot français est affiché, entrez n'importe quel caractère pour afficher sa traduction.\nEnsuite, entrez :\n-> o : oui, si vous connaissiez la traduction\n-> n : non, si vous ne connaissiez pas la traduction\n-> q : quitter, pour retourner au menu principal\n");
    
}

void afficherMot (char mot[])
{
    int i;
    printf("\n|");
    
    for (i = 0 ; LETTRE != '=' ; i++) {
        if (LETTRE == '&')
            printf("\n|");
        else printf("%c", LETTRE);
    }
    
    getchar();
    while (getchar() != '\n');
    
    for (; LETTRE != '\n' ; i++) {
        if (LETTRE == '&' || LETTRE == '=')
            printf("\n|");
        else
            printf("%c", LETTRE);
    }
    
    printf("\n");
}

char menuApprendre(void)
{
    char c;
    
    do
    {
        c = getchar();
        while (getchar() != '\n');
    } while (c != 'o' && c != 'n' && 'c' != 'q');
    
    return c;
}

int menuVoir(void)
{
    char choix;
    do {
        printf("Choisissez quelle classe afficher.\nMenu Voir:\n-> 1 : Classe 1\n-> 2 : Classe 2\n-> 3 : Classe 3\n-> 4 : Classe 4\n-> 5 : Classe 5\n-> 6 : Classe 6\n-> 7 : Classe 7\n-> t : Toutes les classes\n");
        choix = getchar();
        while (getchar() != '\n');
    } while (choix != '1' && choix != '2' && choix != '3' && choix != '4' && choix != '5' && choix != '6' && choix != '7' && choix != 't');
    
    switch (choix)
    {
        case '1':
            return 0;
            break;
        case '2':
            return 1;
            break;
        case '3':
            return 2;
            break;
        case '4':
            return 3;
            break;
        case '5':
            return 4;
            break;
        case '6':
            return 5;
            break;
        case '7':
            return 6;
            break;
        case 't':
            return 666;
            break;
        default:
            return (-1);
            break;
    }
}

void afficherClasse(FILE* classe)
{
    char ligne[TAILLEMOT] = "";
    char *mot = NULL;
    int i = 1;
    
    long curseur = ftell(classe);
    fseek(classe, 0, SEEK_SET);
    
    printf("\n");
    while (fgets(ligne, TAILLEMOT, classe)) {
        strtol(ligne, &mot, 0);
        printf("%d.%s", i, mot);
        i++;
    }
    
    printf("\n");
    fseek(classe, curseur, SEEK_SET);
}

void menuSupprimer(int* classe, int* ligne, FILE** tableauFichier)
{
    int numClasse = 0;
    int numLigne = 0;
    
    *classe = 0;
    *ligne = 0;
    
    while (numClasse == 0 || numClasse > NOMBRECLASSES)
    {
        printf("Entrez le numéro de classe du mot à supprimer : ");
        scanf("%d", &numClasse);
        while(getchar() != '\n');
    }
    
    numClasse--;
    *classe = numClasse;
    
    afficherClasse(tableauFichier[numClasse]);
    
    while (numLigne <= 0)
    {
        printf("Entrez le numéro du mot à supprimer : ");
        scanf("%d", &numLigne);
        while(getchar() != '\n');
    }
    
    *ligne = numLigne;
}

long afficherLigne(FILE* classe, int ligne)
{
    char lecture[TAILLEMOT] = "";
    char *mot = NULL;
    
    fseek(classe, 0, SEEK_SET);
    
    for (int i = 0 ; i < ligne ; i++) {
        curDebutLigne = ftell(classe);
        fgets(lecture, TAILLEMOT, classe);
    }
    
    strtol(lecture, &mot, 0);
    printf("%s", mot);
    
    return curDebutLigne;
}

char menuValiderSuppression(void)
{
    char choix = ' ';
    
    do {
        printf("\nConfirmez vous la suppression de ce mot?\n-> o : oui\n-> n : non\n");
        choix = getc(stdin);
        while (getchar() != '\n');
    } while (choix != 'o' && choix != 'n');
    
    return choix;
}



