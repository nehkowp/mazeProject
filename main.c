#include "paul.h"
#include "etienne.h"
#include "gabin.h"
#include "clem.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// IL VA FALLOIR RENOMMER LES FICHIERS ")

int main(){
    Jeu jeu;
    //affichage menu #ETIENNE
    initJeu(&jeu);
    while(jeu.level < 30){
        creerMaze(&jeu);
        placerEvents(&jeu);
        while(jeu.arbreChemin->type && jeu.j.pvHealth > 0) {
            system("clear");
            afficherScore(jeu);
            afficherMatrice1(jeu.maze,jeu.sizeMaze);
            // afficherMatrice2(jeu.maze,jeu.sizeMaze);
            afficherInventaire(jeu);
            if(jeu.typeEvent != NONE && jeu.j.etatDangerJoueur == ETAT_NON_DANGER){
                afficherUseItem(jeu.typeEvent);
                printf("%d",jeu.typeEvent);
                jeu.typeEvent = NONE;
            }
            if(jeu.j.etatTourRestants == 0){
                jeu.j.etatDangerJoueur = ETAT_NORMAL;
            }
            if(jeu.j.etatDangerJoueur != ETAT_NON_DANGER){
                if(jeu.j.etatDangerJoueur == ETAT_POISON){
                    afficherUseItem(POISON);
                    jeu.j.pvHealth--;
                    jeu.j.etatTourRestants--;
                }
                if(jeu.j.etatDangerJoueur == ETAT_FEU){
                    jeu.j.pvHealth--;
                    afficherUseItem(FIRE);
                    jeu.j.etatTourRestants--;
                }
            }

            deplacementMaze(&jeu,&jeu.arbreChemin,&jeu.maze,jeu.j.positions);
            }
        free(jeu.maze);
        free(jeu.arbreChemin);
        jeu.level=jeu.level+2;
    }
}