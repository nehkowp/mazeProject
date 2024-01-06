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
        while(jeu.arbreChemin->type) {
            system("clear");
            afficherScore(jeu);
            afficherMatrice1(jeu.maze,jeu.sizeMaze);
            // afficherMatrice2(jeu.maze,jeu.sizeMaze);
            afficherInventaire(jeu);
            deplacementMaze(&jeu,&jeu.arbreChemin,&jeu.maze,jeu.j.positions);
            }
        free(jeu.maze);
        free(jeu.arbreChemin);
        jeu.level=jeu.level+2;
    }
}