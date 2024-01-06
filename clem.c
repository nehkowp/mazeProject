#include "clem.h"
#include "gabin.h"
#include "paul.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


arbreChemins creerArbreChemins(arbreChemins a, int positionL, int positionC,  int** maze,int taille){
    arbreChemins a_parent;
    a_parent = malloc(sizeof(node));
    a_parent->nbFils = 1;
    a_parent->positions[0] = positionL;
    a_parent->positions[1] = positionC;
    return creerArbreCheminsCache(a,positionL,positionC,maze,a_parent,taille);
}


arbreChemins creerArbreCheminsCache(arbreChemins a, int positionL, int positionC,  int** maze,arbreChemins a_parent,int taille){
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
        
        if(positionC != taille-1){
            if(maze[a->positions[0]][a->positions[1]+1] >= SPACE && (a->positions[0] != a->parent->positions[0] || a->positions[1]+1 != a->parent->positions[1])){ //DROITE
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL, positionC+1,maze,a,taille);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;
            }

        }
        if(positionL != taille-1){
            if(maze[a->positions[0]+1][a->positions[1]] >= SPACE && (a->positions[0]+1 != a->parent->positions[0] || a->positions[1] != a->parent->positions[1])){ // BAS
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL+1, positionC,maze,a,taille);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;
            
            }
        }

        if(positionL != 0){
            if(maze[a->positions[0]-1][a->positions[1]] >= SPACE && (a->positions[0]-1 != a->parent->positions[0] || a->positions[1] != a->parent->positions[1])){ //HAUT
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL-1, positionC,maze,a,taille);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;

            }
        }

        if(positionC != 0){
            if(maze[a->positions[0]][a->positions[1]-1] >= SPACE && (a->positions[0] != a->parent->positions[0] || a->positions[1]-1 != a->parent->positions[1])){ //GAUCHE
                a->fils[a->nbFils] = creerArbreCheminsCache(a->fils[a->nbFils],positionL, positionC-1,maze,a,taille);
                a->fils = realloc(a->fils,(a->nbFils+1) * sizeof(node*));
                a->nbFils++;
                return a;
            }
            return a;


        }
        
        return a;
    }
    //int usleep(useconds_t usec);


void afficherArbreChemins(arbreChemins a, int** maze){

    for(int n = 0; n < a->nbFils; n++){
        afficherArbreChemins(a->fils[n],maze);
    }
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

void ajouterItemInventaire(Jeu* jeu, int type, char* name){
    int nbItems = 0;
    while(jeu->j.inventaire[nbItems].type != NONE){
        nbItems++;
    }
    jeu->j.inventaire[nbItems].quantite++;
    jeu->j.inventaire[nbItems].type = type;
    jeu->j.inventaire[nbItems].name = name;
}

void healthPotionEvent(Jeu* jeu){
    if(jeu->j.pvHealth > 9){
        ajouterItemInventaire(jeu,HEALTH,"Health Potion");
    }else{
        jeu->j.pvHealth++;
    }
}

void damageTrapEvent(Jeu* jeu){
    jeu->j.pvHealth--;
}

void neverGonnaGiveUP(){
    system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ &");
    system("sleep 2");
    system("clear");     
}


void verifEvent(Jeu* jeu, int*** maze, int positionL, int positionsC){
    if((*maze)[positionL][positionsC] == EVENT){
        int precEvent =-1;
        int randomEvent;
        // pas remettre l'inversion clavier si on l'a pas enlever avant
        do{
            randomEvent = (rand() % 5)+1; // entre random entre 1 et 6
        }while (precEvent==randomEvent);
        precEvent = randomEvent;
        switch (randomEvent) {
            case HEALTH:
                healthPotionEvent(jeu);
                break;
            case DAMAGE:
                damageTrapEvent(jeu);
                break;
            case FUN:
                //neverGonnaGiveUP();
                break;
            case DRUNK:
                inversion=1;
                precEvent=1;
                break;
            case MILK:
                inversion=0;
                break;
            case ARIANE:
                // filAriane(jeu);
                break;
            default:
                printf("Error Event Switch Case\n");
                break;
        }
        jeu->typeLastEvent = randomEvent;
    }
}

char* emoji(int type){
    switch (type) {
        case NONE:
            return " - ";
        case HEALTH:
            return "💊 ";
        case DAMAGE:
            return "💔 ";
        case FUN:
            return "🔥 ";
        case DRUNK:
            return "🍾 ";
        case MILK:
            return "🥛 ";
        default:
            return "Error";
    }
}

void afficherUseItem(int type){
    printf("╔═══════════════════════╗\n");
    printf("║ Labyrinthe utilise %s║\n",emoji(type));
    printf("║ (c'est très efficace) ║\n");
    printf("╚═══════════════════════╝\n");
}


void afficherScore(Jeu jeu){
   // int vraiLvl = 1;
   //if(jeu.level!=0){
    //   vraiLvl=vraiLvl+(jeu.level/2);
    //}
printf("\e[1;97m");
printf("╔═══════════════════╗\n");
printf("║   Niveau lvl: %d   ║\n",(jeu.level/2)+1);
printf("╚═══════════════════╝\n");
printf("\e[0m");
}

void afficherInventaire(Jeu jeu){
printf("\e[1;97m");
printf("╔═1═╦═2═╦═3═╦═4═╦═5═╗\n");
printf("║%s║%s║%s║%s║%s║  %d❤️\n",emoji(jeu.j.inventaire[0].type),emoji(jeu.j.inventaire[1].type),emoji(jeu.j.inventaire[2].type),emoji(jeu.j.inventaire[3].type),emoji(jeu.j.inventaire[4].type),jeu.j.pvHealth);
printf("╚═══╩═══╩═══╩═══╩═══╝\n");
printf("\e[0m");
}

void useItem(Jeu* jeu, int typeInput){
    switch (jeu->j.inventaire[typeInput].type){
        case HEALTH:
            jeu->j.pvHealth++;
            break;
        default:
            break;
    }
    jeu->j.inventaire[typeInput].type = NONE;
}

void initJeu(Jeu* jeu){
    jeu->level = 0;
    jeu->sizeMaze = INITIALSIZE;
    jeu->j.pvHealth = 10;
    jeu->typeLastEvent = NONE;
    jeu->j.inventaire = malloc(5*sizeof(Item)); //5 items max
    for(int nbItems = 0;nbItems < 5; nbItems++){
        jeu->j.inventaire[nbItems].type = NONE;
        jeu->j.inventaire[nbItems].quantite = 0;
    } 
    jeu->maze = NULL;
    srand(time(NULL));
}

void mazePlacement(int*** maze,int taille,Joueur* j){
    int randPlacement = rand() % 4; // 0 1 2 3

    setEnd(maze,taille,randPlacement);
    setStart(maze,taille,randPlacement,j);

}

void creerMaze(Jeu* jeu){
    jeu->sizeMaze = jeu->sizeMaze + jeu->level;
    mazeGenerator(&jeu->maze,jeu->sizeMaze);
    mazePlacement(&jeu->maze,jeu->sizeMaze,&jeu->j); 

    //afficherMatrice1(jeu->maze,jeu->sizeMaze);  
    // afficherMatrice2(jeu->maze,jeu->sizeMaze);  

    jeu->arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze,jeu->sizeMaze);

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

void deplacementMaze(Jeu* jeu,arbreChemins* a,int*** maze,int positions[2]){
    switch (deplacementTouche()) {
                case HAUT:
                    if(deplacementValide(positions[0]-1,positions[1],a)){
                        verifEvent(jeu,maze,positions[0]-1,positions[1]);
                        (*maze)[positions[0]-1][positions[1]] = PLAYER;
                        (*maze)[positions[0]][positions[1]] = SPACE;
                        positions[0]--;
                    }
                    break;
                case DROITE:
                    if(deplacementValide(positions[0],positions[1]+1,a)){
                        verifEvent(jeu,maze,positions[0],positions[1]+1);
                        (*maze)[positions[0]][positions[1]+1] = PLAYER;
                        (*maze)[positions[0]][positions[1]] = SPACE;
                        positions[1]++;
                    }   
                    break;
                case GAUCHE:
                    if(deplacementValide(positions[0],positions[1]-1,a)){
                        verifEvent(jeu,maze,positions[0],positions[1]-1);
                        (*maze)[positions[0]][positions[1]-1] = PLAYER;
                        (*maze)[positions[0]][positions[1]] = SPACE;
                        positions[1]--;
                    }
                    break;
                case BAS:
                    if(deplacementValide(positions[0]+1,positions[1],a)){
                        verifEvent(jeu,maze,positions[0]+1,positions[1]);
                        (*maze)[positions[0]+1][positions[1]] = PLAYER;
                        (*maze)[positions[0]][positions[1]] = SPACE;
                        positions[0]++;
                    }
                    break;
                case HOTBAR1:
                    useItem(jeu,0);
                    break;
                case HOTBAR2:
                    useItem(jeu,1);
                    break;
                case HOTBAR3:
                    useItem(jeu,2);
                    break;
                case HOTBAR4:
                    useItem(jeu,3);
                    break;
                case HOTBAR5:
                    useItem(jeu,4);
                    break;

                default:
                printf("Invalid direction\n");
                    break;

            }
}


char* affichageMur(int** maze, int ligne, int colonne,int taille){
    if(ligne == 0){
        if(colonne == 0){
            return "╔═";
        }else{
            if(colonne == taille){
                return "═╗";
            }else{
                if(maze[ligne+1][colonne] == WALL){
                    return "╦═";
                }else{
                    return "══";
                }
            }
        }
    }
    if(colonne == 0){
        if(ligne == 0){
            return "╔═";
        }else{
            if(ligne == taille){
                return "╚═";
            }else{
                if(maze[ligne][colonne+1] == WALL){
                    return "╠═";
                }else{
                return "║";
                }
            }
        }
    }
    if(ligne == taille){
        if(colonne == 0){
            return "╚═";
        }else{
            if(colonne == taille){
                return "═╝";
            }else{
                if(maze[ligne-1][colonne] == WALL){
                    return "╩═";
                }else{
                    return "══";
                }
            }
        }
    }
    if(colonne == taille){
        if(ligne == 0){
            return "═╗";
        }else{
            if(ligne == taille){
                return "═╝";
            }else{
                if(maze[ligne][colonne-1] == WALL){
                    return "═╣";
                }else{
                return " ║";
                }
            }
        }
    }
    if(maze[ligne-1][colonne] == WALL && maze[ligne+1][colonne] == WALL && maze[ligne][colonne+1] == WALL && maze[ligne][colonne-1] == WALL){
        return "╬═";
    }
    if(maze[ligne-1][colonne] == WALL && maze[ligne][colonne-1] == WALL && maze[ligne+1][colonne] == WALL){
        return "═╣";
    }
    if(maze[ligne+1][colonne] == WALL && maze[ligne][colonne-1] == WALL && maze[ligne][colonne+1] == WALL){
        return "╦═";
    }
    if(maze[ligne-1][colonne] == WALL && maze[ligne][colonne-1] == WALL && maze[ligne][colonne+1] == WALL){
        return "╩═";
    }
    if(maze[ligne-1][colonne] == WALL && maze[ligne][colonne+1] == WALL && maze[ligne+1][colonne] == WALL){
        return "╠═";
    }
    if(maze[ligne+1][colonne] == WALL && maze[ligne][colonne-1] == WALL){
        return "═╗";
    }
    if(maze[ligne+1][colonne] == WALL && maze[ligne][colonne+1] == WALL){
        return "╔═";
    }
    if(maze[ligne-1][colonne] == WALL && maze[ligne][colonne-1] == WALL){
        return "═╝";
    }
    if(maze[ligne-1][colonne] == WALL && maze[ligne][colonne+1] == WALL){
        return "╚═";
    }
    if(maze[ligne][colonne+1] == WALL && maze[ligne][colonne-1] == WALL){
        return "══";
    }
    if(maze[ligne-1][colonne] == WALL && maze[ligne+1][colonne] == WALL){
        return " ║";
    }
    if(maze[ligne+1][colonne] == WALL){
        return " ║";
    }
    if(maze[ligne-1][colonne] == WALL){
        return " ║";
    }

    if(maze[ligne][colonne+1] == WALL){
        return "══";
    }

    if(maze[ligne][colonne-1] == WALL){
        return "══";
    }
    return "🟩";
}