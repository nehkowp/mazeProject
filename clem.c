#include "clem.h"
#include "gabin.h"
#include "paul.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
    if(jeu->j.pvHealth == 10){
        ajouterItemInventaire(jeu,HEALTH,"Healt Potion");
    }else{
        jeu->j.pvHealth++;
    }
}

void damageTrapEvent(Jeu* jeu){
    jeu->j.pvHealth--;
}

/*
CoordsStack creerCord(int positionL, int positionC){
    CoordsStack nvElt;
    nvElt  = malloc(sizeof(coords)*1);
    nvElt->positions[0] = positionL;
    nvElt->positions[1] = positionC;
    return nvElt;
}

CoordsStack ajouterCoord(CoordsStack p, int positionL, int positionC){
    CoordsStack nvElt;
    nvElt =  creerCord(positionL, positionC);

    if (p==NULL){
        p = nvElt;
    }else{
        nvElt->suivant = p;
        p = nvElt;
    }
    return p;
}

CoordsStack cheminAriane(arbreChemins arbre,CoordsStack coords){
    coords = ajouterCoord(coords,arbre->positions[0],arbre->positions[1]);
    printf("[%d - %d]\n",coords->positions[0],coords->positions[1]);
    if(arbre->type == END){
        return coords;
    }else{
        for(int nbFils = 0; nbFils < arbre->nbFils; nbFils++){
            cheminAriane(arbre->fils[nbFils],coords);
        }
    }
    return NULL;
}

void filAriane(Jeu* jeu){
    CoordsStack ariane = cheminAriane(jeu->arbreChemin,NULL);
    while(ariane != NULL){
        printf("[%d - %d]\n",ariane->positions[0],ariane->positions[1]);
        ariane = ariane->suivant;
    }
    sleep(1);
}
*/


void verifEvent(Jeu* jeu, int*** maze, int positionL, int positionsC){
    if((*maze)[positionL][positionsC] == EVENT){
        int randomEvent = rand() % 3;
        switch (randomEvent) {
            case 0:
                healthPotionEvent(jeu);
                break;
            case 1:
                damageTrapEvent(jeu);
                break;
            case 2:
                // filAriane(jeu);
                break;
            default:
                printf("Error Event Switch Case\n");
                break;
        }
    }
}

char* emoji(int type){
    switch (type) {
        case NONE:
            return " - ";
        case HEALTH:
            return "💊 ";
        default:
            return "Error";
    }
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
    jeu->j.inventaire = malloc(5*sizeof(Item)); //5 items max
    for(int nbItems = 0;nbItems < 5; nbItems++){
        jeu->j.inventaire[nbItems].type = NONE;
        jeu->j.inventaire[nbItems].quantite = 0;
    } 
    jeu->maze = NULL;
    srand(time(NULL));
}

void creerMaze(Jeu* jeu){
    jeu->sizeMaze = jeu->sizeMaze + jeu->level;
    mazeGenerator(&jeu->maze,jeu->sizeMaze); 
    setEnd(&jeu->maze,jeu->sizeMaze);
    int start = setStart(jeu->maze,jeu->sizeMaze);
    jeu->maze[ start ][ 0 ] = PLAYER;
    afficherMatrice1(jeu->maze,jeu->sizeMaze);  
    afficherMatrice2(jeu->maze,jeu->sizeMaze);  

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