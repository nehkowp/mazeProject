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
    while(jeu.level < 30 && jeu.j.pvHealth > 0){
        creerMaze(&jeu);
        placerEvents(&jeu);
        while(jeu.arbreChemin->type && jeu.j.pvHealth > 0) {
            system("clear");
            afficherScore(jeu.level,jeu.score);
            afficherMatrice1(jeu.maze,jeu.sizeMaze);
            afficherInventaire(jeu);
            eventJoueur(&jeu.typeEvent,&jeu.j);
            deplacementMaze(&jeu,&jeu.arbreChemin,&jeu.maze,jeu.j.positions);
            }
        if(jeu.j.pvHealth > 0){
            free(jeu.maze);
            free(jeu.arbreChemin);
            jeu.level=jeu.level+2;
            jeu.score= jeu.score + (25*jeu.level);
        }
    }
    gameOver(jeu.level,jeu.score);
    free(jeu.maze);
    free(jeu.arbreChemin);
}