#include "paul.h"
#include "etienne.h"
#include "gabin.h"
#include "clem.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    while(1){
    Jeu jeu;
    choixMenu(lireMenu(),&jeu.options);
    initJeu(&jeu);
    jouerJeu(&jeu);
    gameOver(jeu.level,jeu.score,jeu.highScore);
    freeGame(&jeu);
    }
}