#include "etienne.h"
#include "paul.h"
#include "clem.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>

char** lireMenu(){
    
    //allocation de la mémoire
    char** menus;
    menus = malloc(3*sizeof(char*));
    for (int i=0; i<3; i++){
        menus[i]=malloc(100*sizeof(char));
    }


    /*
    //ouverture du fichier contenant les différents affichages de menus
    FILE* menuCSV=NULL;
    char ligne [N];
    char* laLigne;
    laLigne = malloc(N*sizeof(char));
    menuCSV = fopen("out/menu.txt", "r");

    if(menuCSV==NULL){
        printf(BRED"/!\\ ERREUR D'OUVERTURE DU FICHIER menu.txt /!\\\n"reset);
    } else {
        int j = 0;
        while ((fgets(ligne,N,menuCSV) != NULL)&& j<3){
            laLigne = strtok(ligne,";");
            printf("ligne %d:\n",j);
            printf("%s", laLigne);
            strcat(menus[j], laLigne);
            printf("%s",menus[j]);
            menus[j] = laLigne;
            j++;
        }
    }
    */
    //pris par le désespoir, je mets de côté la lecture de fichier

    menus[0] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< WCKD >"BGRN"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║ "BWHT"▶ JOUER    ◀ "BGRN"║  ╔════════╣\n║  ╠══╗  ║  ║   OPTIONS    ║  ║  ════  ║\n║     ║  ║  ║   RÈGLES     ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    menus[1] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< WCKD >"BGRN"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   JOUER      ║  ╔════════╣\n║  ╠══╗  ║  ║ "BWHT"▶ OPTIONS  ◀"BGRN" ║  ║  ════  ║\n║     ║  ║  ║   RÈGLES     ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    menus[2] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< WCKD >"BGRN"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   JOUER      ║  ╔════════╣\n║  ╠══╗  ║  ║   OPTIONS    ║  ║  ════  ║\n║     ║  ║  ║ "BWHT"▶ RÈGLES   ◀"BGRN" ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";




    //fclose(menuCSV);
    return menus;
}

//utiliser deplacementTouche(ETAT_MENU)
void choixMenu(char** menus,Options* options){
    printf(BGRN);
    char*** optionsTab = NULL;
    initOptions(&optionsTab,options);

    int numMenu = 0;
    int jeuLancé = 0;
    while (!jeuLancé){
        system("clear");
        printf("%s", menus[numMenu]);
        switch (deplacementTouche(ETAT_MENU)) {
            case HAUT:
                numMenu--;
                if(numMenu==-1){
                    numMenu=2;
                }
                break;
            case BAS:
                numMenu++;
                if(numMenu==3){
                    numMenu=0;
                }
                break;
            case ENTER:
                switch (numMenu) {
                    case 0:
                        jeuLancé = 1;
                        break;
                    case 1:
                        optionChange(options,optionsTab);
                        break;
                    case 2:
                        regle(options);
                        break;
                }
                // jeuLancé=1;
                break;

            default:
                break;
        }        
        //return numMenu;
        //renvoie 0 pour jouer, 1 pour options et 2 pour règles
    }
    printf(reset);
}


// j'ai la flemme de rediger les regles si qlq un est chaud
void regle(Options* options){
    int lecture=0;
    while(!lecture){
        system("clear");
        printf("\e[4;33m""\nLe Labyrinthe :");
        printf("\n\n""\e[0m""\e[1;97m""Le jeu est plutôt simple et facile à comprendre.\nIl suffit de déplacer le robot jusqu'à l'arrivée.\n\n""\e[1;32m""Les déplacements sont réalisés en utilisant :\n - Z pour aller vers le haut\n - Q pour aller vers la gauche\n - S pour aller vers le bas\n - D pour aller vers la droite\n\n Sur votre route, vous aurez la possibilité de récupérer des bonus ou des malus : \n - Maj Gauche + 1/2/3/4/5 pour utiliser l'item\n\n""\e[0;97m""Ce jeu a été realisé par Paul Brechenmacher, Paul Le Blanc, Etienne Massonnet et Gabin Alquier pour un projet de fin de semestre en 2023-2024.\n");
        printf("\n\n Pour quitter et lancer le jeu, appuyez sur 'Entrée'""\e[0m	");
        switch(deplacementTouche(ETAT_ENTER)){
            case ENTER:
                lecture=1;
                break;
        }

    }
    choixMenu(lireMenu(),options);
}

