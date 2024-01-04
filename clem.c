#include "clem.h"
#include "gabin.h"
#include "paul.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void testClem(){
    printf("Bonjour c'est la fonction de Clem : ) \n");
}

arbreChemins creerArbreChemins(arbreChemins a, int positionL, int positionC,  int** maze){
    arbreChemins a_parent;
    a_parent = malloc(sizeof(node));
    a_parent->nbFils = 1;
    a_parent->positions[0] = positionL;
    a_parent->positions[1] = positionC;
    return creerArbreCheminsCache(a,positionL,positionC,maze,a_parent);
}


arbreChemins creerArbreCheminsCache(arbreChemins a, int positionL, int positionC,  int** maze,arbreChemins a_parent){
        a = malloc(sizeof(node));
        a->fils = malloc(1 * sizeof(node*));
        a->positions[0] = positionL;
        a->positions[1] = positionC;
        a->parent = a_parent;
        a->nbFils = 0;
        //afficherMatrice(maze, SIZE);
        if(maze[a->positions[0]][a->positions[1]] == END){
            a->type = 0;
        }else{
            a->type = 1;
        }

        if(maze[a->positions[0]][a->positions[1]+1] >= SPACE && (a->positions[0] != a->parent->positions[0] || a->positions[1]+1 != a->parent->positions[1])){ //DROITE
            a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL, positionC+1,maze,a);
            a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
            a->nbFils++;

        }
        if(maze[a->positions[0]+1][a->positions[1]] >= SPACE && (a->positions[0]+1 != a->parent->positions[0] || a->positions[1] != a->parent->positions[1])){ // BAS
            a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL+1, positionC,maze,a);
            a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
            a->nbFils++;
            
        }


        if(maze[a->positions[0]-1][a->positions[1]] >= SPACE && (a->positions[0]-1 != a->parent->positions[0] || a->positions[1] != a->parent->positions[1])){ //HAUT
            a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL-1, positionC,maze,a);
            a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
            a->nbFils++;

        }

        if(positionC != 0){
            if(maze[a->positions[0]][a->positions[1]-1] >= SPACE && (a->positions[0] != a->parent->positions[0] || a->positions[1]-1 != a->parent->positions[1])){ //GAUCHE
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL, positionC-1,maze,a);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;
                return a;
            }
            return a;


        }
        
        return a;
    }
    int usleep(useconds_t usec);


void afficherArbreChemins(arbreChemins a, int** maze){

    for(int n = 0; n < a->nbFils; n++){
        afficherArbreChemins(a->fils[n],maze);
    }
   
    // system("clear");
    // maze[a->positions[0]][a->positions[1]] = PLAYER;
    // afficherMatrice(maze,SIZE);
    // usleep(100000);
    // for(int n = 0; n < a->nbFils; n++){
    //     afficherArbreChemins(a->fils[n],maze);
    // }
    // printf("\n");
}


int deplacementValide(int positionL, int positionC, arbreChemins* a){
    int val = 0;
    
    for(int n = 0; n < (*a)->nbFils; n++){
        if((*a)->fils[n]->positions[0] == positionL && (*a)->fils[n]->positions[1] == positionC){
            *a = (*a)->fils[n];
            val = 1;
            
        }
    }
    if((*a)->parent->positions[0] == positionL && (*a)->parent->positions[1] == positionC){
            *a = (*a)->parent;
            val =  1;
        }
    
    return val;
}


void verifEvent(int*** maze, int positionL, int positionsC){
    if((*maze)[positionL][positionsC] == EVENT){
        int randomEvent = rand() % 2;
        switch (randomEvent) {
            case 0:
                sleep(1);
                printf("Event 0\n");
                break;
            case 1:
                sleep(1);
                printf("Event 1\n");
                break;
            case 2:
                sleep(1);
                printf("Event 2\n");
                break;
            default:
                printf("Error Event Switch Case\n");
                break;
        }
    }
}


void deplacementMaze(arbreChemins* a,int*** maze,int positions[2]){
    switch (deplacementTouche()) {

                case HAUT:
                    if(deplacementValide(positions[0]-1,positions[1],a)){
                        verifEvent(maze,positions[0]-1,positions[1]);
                        (*maze)[positions[0]-1][positions[1]] = PLAYER;
                        (*maze)[positions[0]][positions[1]] = SPACE;
                        positions[0]--;
                    }
                    break;
                case DROITE:
                    if(deplacementValide(positions[0],positions[1]+1,a)){
                        verifEvent(maze,positions[0],positions[1]+1);
                        (*maze)[positions[0]][positions[1]+1] = PLAYER;
                        (*maze)[positions[0]][positions[1]] = SPACE;
                        positions[1]++;
                    }   
                    break;
                case GAUCHE:
                    if(deplacementValide(positions[0],positions[1]-1,a)){
                        verifEvent(maze,positions[0],positions[1]-1);
                        (*maze)[positions[0]][positions[1]-1] = PLAYER;
                        (*maze)[positions[0]][positions[1]] = SPACE;
                        positions[1]--;
                    }
                    break;
                case BAS:
                    if(deplacementValide(positions[0]+1,positions[1],a)){
                        verifEvent(maze,positions[0]+1,positions[1]);
                        (*maze)[positions[0]+1][positions[1]] = PLAYER;
                        (*maze)[positions[0]][positions[1]] = SPACE;
                        positions[0]++;
                    }
                    break;
                default:
                printf("Invalid direction\n");
                    break;

            }
}