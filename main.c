#include "paul.h"
#include "etienne.h"
#include "gabin.h"
#include "clem.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// IL VA FALLOIR RENOMMER LES FICHIERS ")

void initJeu(Jeu* jeu){
    jeu->level = 0;
    jeu->sizeMaze = INITIALSIZE;
    jeu->j.pvHealth = 10; 
    jeu->maze = NULL;
    srand(time(NULL));
}

void creerMaze(Jeu* jeu){
    jeu->sizeMaze = jeu->sizeMaze + jeu->level;
    mazeGenerator(&jeu->maze,jeu->sizeMaze); 
    setEnd(&jeu->maze,jeu->sizeMaze);
    int start = setStart(jeu->maze,jeu->sizeMaze);
    jeu->maze[ start ][ 0 ] = PLAYER;
    afficherMatrice(jeu->maze,jeu->sizeMaze);  

    jeu->arbreChemin = creerArbreChemins(NULL, start , 0 , jeu->maze);
    jeu->j.positions[0] = start;
    jeu->j.positions[1] = 0;
}

void placerEvents(Jeu* jeu){
    for(int nbEvents = 0; nbEvents < jeu->level; nbEvents++){
        int lrandom = rand() % jeu->sizeMaze;
        int crandom = rand() % jeu->sizeMaze;
        do{
            lrandom = rand() % jeu->sizeMaze;
            crandom = rand() % jeu->sizeMaze;

        }while(jeu->maze[lrandom][crandom] != SPACE);
        jeu->maze[lrandom][crandom] = EVENT;
    }
}


int main(){
    Jeu jeu;
    //affichage menu #ETIENNE
    initJeu(&jeu);
    while(jeu.level < 30){
        creerMaze(&jeu);
        placerEvents(&jeu);
        while(jeu.arbreChemin->type) {
            system("clear");
            afficherMatrice(jeu.maze,jeu.sizeMaze);
            deplacementMaze(&jeu.arbreChemin,&jeu.maze,jeu.j.positions);

            }
        free(jeu.maze);
        free(jeu.arbreChemin);
        jeu.level = jeu.level+2;
    }
}