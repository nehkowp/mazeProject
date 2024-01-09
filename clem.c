#include "clem.h"
#include "etienne.h"
#include "gabin.h"
#include "paul.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            if(maze[a->positions[0]][a->positions[1]] == CHECKPOINT){
                a->type = 2;
            }else{
                a->type = 1;

            }
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
    printf("[%d - %d] --> %d\n",a->positions[0],a->positions[1],a->type);
    for(int n = 0; n < a->nbFils; n++){
        afficherArbreChemins(a->fils[n],maze);
    }
}


int deplacementValide(int positionL, int positionC, arbreChemins* a,Joueur j,int** maze,int taille){
    int val = 0;
    
    if(positionL > -1 && positionC > -1 && positionC < taille && positionL < taille){
        if(maze[positionL][positionC] == END){
            if(!j.findKeys){
                return 0;
            }
        }
    }

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

void neverGonnaGiveUP(){
    system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ &");
    system("sleep 2");  system("clear");     
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


void milkPotionEvent(Jeu* jeu){
    if(jeu->j.etatSobreJoueur){
        jeu->j.etatSobreJoueur=0;
    }else{
        ajouterItemInventaire(jeu,MILK,"Milk Potion");
    }

}


void verifEvent(Jeu* jeu, int*** maze, int positionL, int positionC){
    if((*maze)[positionL][positionC] == EVENT){
        jeu->score = jeu->score + 25;
        int precEvent =-1;
        int randomEvent;
        usleep(5000);
        // pas remettre l'inversion clavier si on l'a pas enlever avant
        do{
            randomEvent = (rand() % 8)+1; // entre random entre 1 et 8
        }while (precEvent==randomEvent);
        precEvent = randomEvent;
        switch (randomEvent) {
            case HEALTH:
                healthPotionEvent(jeu);
                break;
            case DAMAGE:
                damageTrapEvent(jeu);
                break;
            case FIRE:
                jeu->j.etatDangerJoueur = ETAT_FEU;
                jeu->j.etatTourRestants = jeu->j.etatTourRestants + (jeu->level/4)+1;
                //neverGonnaGiveUP();
                break;
            case DRUNK:
                jeu->j.etatSobreJoueur=ETAT_DRUNK;
                precEvent=1;
                break;
            case MILK:
                milkPotionEvent(jeu);
                break;
            case ARIANE:
                // filAriane(jeu);
                break;
            case POISON:
                jeu->j.etatDangerJoueur = ETAT_POISON;
                jeu->j.etatTourRestants = jeu->j.etatTourRestants + (jeu->level/4)+2;
                break;
            case SCORE:
                jeu->score = jeu->score + 500;
            case FUN:

                break;

            default:
                printf("Error Event Switch Case\n");
                break;
        }
        jeu->typeEvent = randomEvent;
    }
    if((*maze)[positionL][positionC] == KEY){
        jeu->j.findKeys = 1;
        jeu->score = jeu->score + 100;
    }
}

char* emoji(int type){
    switch (type) {
        case NONE:
            return " - ";
        case HEALTH:
            return "💊 ";
        case DAMAGE:
            return "🤕 ";
        case FIRE:
            return "🔥 ";
        case DRUNK:
            return "🍾 ";
        case MILK:
            return "🥛 ";
        case ARIANE:
            return "🧶 ";
        case POISON: 
            return "🧪 ";
        case SCORE:
            return "🪙 ";

        case FUN: 
            return "🎷 ";
        default:
            return "Error";
    }
}

void afficherUseItem(int type){
    printf("╔═══════════════════════╗\n");
    printf("║ Vous avez utilisé %s ║\n",emoji(type));
    printf("╚═══════════════════════╝\n");
}



void verifPoisonFeu(Joueur* j){
    if(j->etatDangerJoueur != ETAT_NON_DANGER){
            if(j->etatDangerJoueur == ETAT_POISON){
                afficherUseItem(POISON);
                j->pvHealth--;
                j->etatTourRestants--;
            }
            if(j->etatDangerJoueur == ETAT_FEU){
                j->pvHealth--;
                afficherUseItem(FIRE);
                j->etatTourRestants--;
            }
        }
}
void verifEtatEvent(Joueur* j,int* typeEvent){
    if(*typeEvent != NONE && j->etatDangerJoueur == ETAT_NON_DANGER){
                afficherUseItem(*typeEvent);
                *typeEvent = NONE;
    }
    if(j->etatTourRestants == 0){
        j->etatDangerJoueur = ETAT_NORMAL;
    }
}

void eventJoueur(int* typeEvent,Joueur* j,int** maze){
    verifEtatEvent(j,typeEvent);
    verifPoisonFeu(j);
}


int lenInt(int score){
    int len = 0;
    if (score == 0){
        len = 1;
    }
    while(score != 0){
        score = score/10;
        len++;
    }
    return len;
}

void scorePrint(int scoreLen){
    while(scoreLen < 5){
        printf(" ");
        scoreLen++;
    }
    printf("    ║\n");
}
void afficherScore(int level,int score){
printf("\e[1;97m");
printf("╔══════════════╗    ╔══════════════╗\n");
printf("║   ""\e[1;92m""Niveau %d""\e[1;97m""   ║    ║  ""\e[1;33m""%d 🪙""\e[1;97m",(level/2)+1,score);
scorePrint(lenInt(score));
printf("╚══════════════╝    ╚══════════════╝\n");
printf(reset);
}

void afficherInventaire(Jeu jeu){
printf("\e[1;97m");
printf("╔═1═╦═2═╦═3═╦═4═╦═5═╗\n");
printf("║%s║%s║%s║%s║%s║  %d❤️\n",emoji(jeu.j.inventaire[0].type),emoji(jeu.j.inventaire[1].type),emoji(jeu.j.inventaire[2].type),emoji(jeu.j.inventaire[3].type),emoji(jeu.j.inventaire[4].type),jeu.j.pvHealth);
printf("╚═══╩═══╩═══╩═══╩═══╝\n");
printf(reset);
}

void useItem(Jeu* jeu, int typeInput){
    switch (jeu->j.inventaire[typeInput].type){
        case HEALTH:
            jeu->j.pvHealth++;
            break;
        case MILK:
            jeu->j.etatSobreJoueur = ETAT_NORMAL;
            jeu->j.etatDangerJoueur = ETAT_NON_DANGER;
            break;
        default:
            break;
    }
    jeu->j.inventaire[typeInput].type = NONE;
}

void modeHealth(int* pvHealth, int typeMode){
    switch (typeMode) {
        case 0:
            *pvHealth = 10;
            break;
        case 1:
            *pvHealth = 1;
            break;
        case 2:
            *pvHealth = 20;
            break;
        default:
            printf("Erreur Vie");
            break;
    
    }
}


void initJeu(Jeu* jeu){
    
    jeu->maze.typeMaze = 1;
    jeu->posMaze[0] = 1;
    jeu->posMaze[1] = 0;
    jeu->level = 0;
    jeu->score = 0;
    jeu->maze.sizeMaze = INITIALSIZE;
    modeHealth(&jeu->j.pvHealth,jeu->options.typeMode);
    jeu->j.findKeys = 1;
    jeu->j.etatCheckPoint = 1;
    jeu->typeEvent = NONE;
    jeu->j.inventaire = malloc(5*sizeof(Item)); //5 items max
    for(int nbItems = 0;nbItems < 5; nbItems++){
        jeu->j.inventaire[nbItems].type = NONE;
        jeu->j.inventaire[nbItems].quantite = 0;
    } 
    jeu->maze.tabMaze = NULL;
    getScoreCSV(jeu);
    srand(time(NULL));
}

void jouerMaze(Jeu* jeu){
    system("clear");
    afficherScore(jeu->level,jeu->score);
    afficherMatrice1(jeu->maze.tabMaze,jeu->maze.sizeMaze,jeu->options.typeEmoji);
    afficherInventaire(*jeu);
    eventJoueur(&jeu->typeEvent,&jeu->j,jeu->maze.tabMaze);
    deplacementMaze(jeu,&jeu->maze.arbreChemin,&jeu->maze.tabMaze,jeu->j.positions);

}

void mazePlacementSimple(int*** maze,int taille,Joueur* j){
    int randPlacement = rand() % 4; // 0 1 2 3

    setEnd(maze,taille,randPlacement);
    setStart(maze,taille,randPlacement,j);

}

void setCheck( int*** maze, int taille , int randPlacement) {
    int random = 0;
    random = 1 + rand() % ( taille - 2 );
    // Vérifier que la case choisie est vide (pas un mur)
    // Marquer la case de départ dans la matrice et la retourner
    switch (randPlacement) {
        case 2:
                while ( (*maze)[ random ][ 1 ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ random ][ 0 ] = CHECKPOINT;
             
            break;
        case 3:
            while ( (*maze)[ taille - 2  ][ random ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ taille - 1 ][ random ] = CHECKPOINT;

            break;
        case 0:
                while ( (*maze)[ random ][ taille - 2 ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ random ][ taille - 1 ] = CHECKPOINT;   
            break;
        case 1:
            while ( (*maze)[ 1 ][ random ] != SPACE ) {
                    random = 1 + rand() % ( taille - 2 );
                }
                // Marquer la case de fin dans la matrice
                (*maze)[ 0 ][ random ] = CHECKPOINT;
            break;
        default:
            break;
    
    }
}

void mazePlacementComplexe(int*** maze, int taille, Joueur*j, int posMazeL,int posMazeC){
    if(!(posMazeC%2 || posMazeL%2)){
        // 0 / 0 --> 3 0
        // 2 / 2 --> 2 1
        // 0 / 2 --> 3 2
        // 2 / 0 --> 1 0
        switch (posMazeC+posMazeL) {
            case 0:
                setCheck(maze,taille,3);
                setCheck(maze,taille,0);
                break;
            case 2:
                if(posMazeL == 2){
                    setCheck(maze,taille,1);
                    setCheck(maze,taille,0);;

                }else{
                    setCheck(maze,taille,3);
                    setCheck(maze,taille,2);
                }
                break;
            case 4:
                setCheck(maze,taille,2);
                setCheck(maze,taille,1);
                break;
        }
 

    }else{
        if(posMazeL%2 && posMazeC%2){ //no 3
            for(int i=0;i<4;i++){
                setCheck(maze,taille,i);
            }
        }else{
            if(posMazeC == 2){
            setEnd(maze,taille,2);
            setCheck(maze,taille,1);
            setCheck(maze,taille,3);
            setCheck(maze,taille,2);
            }
            if(posMazeC == 0){
                setCheck(maze,taille,1);
                setCheck(maze,taille,3);
                setCheck(maze,taille,0);
                setStart(maze,taille,2,j);
            }
            if(posMazeC == 1){
                if(posMazeL == 2){
                    setCheck(maze,taille,1);
                    setCheck(maze,taille,0);
                    setCheck(maze,taille,2);
                }else{

                    setCheck(maze,taille,3);
                    setCheck(maze,taille,0);
                    setCheck(maze,taille,2);
                }
    
            
            }
        }
        
    }
}


void creerMegaMaze(Jeu* jeu){
    jeu->maze.sizeMaze = INITIALSIZE+(jeu->level);
    jeu->posMaze[0] = 1;
    jeu->posMaze[1] = 0;

    int size = 3;
    jeu->megamaze = (Maze**)malloc(size * sizeof(Maze*));
    for (int ligne = 0; ligne <  size; ligne++) {
        jeu->megamaze[ligne] = (Maze*)malloc(size * sizeof(Maze));
        for (int colonne= 0; colonne < size; colonne++) {
            mazeGenerator(&jeu->maze.tabMaze,jeu->maze.sizeMaze);
            mazePlacementComplexe(&jeu->maze.tabMaze,jeu->maze.sizeMaze,&jeu->j,ligne,colonne);
            jeu->megamaze[ligne][colonne] = jeu->maze;  // Initialiser la matrice avec des murs (-1)
        }
    }
}


void creerMaze(Jeu* jeu){
    jeu->maze.sizeMaze = jeu->maze.sizeMaze + jeu->level;
    mazeGenerator(&jeu->maze.tabMaze,jeu->maze.sizeMaze);
    mazePlacementSimple(&jeu->maze.tabMaze,jeu->maze.sizeMaze,&jeu->j);
    jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);

}

void placerEvents(Maze* maze,int level){
    for(int nbEvents = 0; nbEvents < level; nbEvents++){
        int lrandom = rand() % maze->sizeMaze;
        int crandom = rand() % maze->sizeMaze;
        do{
            lrandom = rand() % maze->sizeMaze;
            crandom = rand() % maze->sizeMaze;

        }while(maze->tabMaze[lrandom][crandom] != SPACE);
        maze->tabMaze[lrandom][crandom] = EVENT;
    }
}

void placerKeys(Maze* maze, Joueur* j){
        j->findKeys = 0;
        int lrandom = rand() % maze->sizeMaze;
        int crandom = rand() % maze->sizeMaze;
        do{
            lrandom = rand() % maze->sizeMaze;
            crandom = rand() % maze->sizeMaze;

        }while(maze->tabMaze[lrandom][crandom] != SPACE);
            maze->tabMaze[lrandom][crandom] = KEY;
}

void findCheck(Jeu* jeu,int positionInverse,int mode){
    int i = 1;
    // mode 1 --> recherche ligne sinon  0 --> recherche colonne
    afficherMatrice1(jeu->maze.tabMaze,jeu->maze.sizeMaze,jeu->options.typeEmoji);
    if(mode){
        while(jeu->maze.tabMaze[i][positionInverse] != CHECKPOINT && i < jeu->maze.sizeMaze){
            i++;
        }
        jeu->j.positions[0] = i;
        jeu->j.positions[1] = positionInverse;
    }else{
        while(jeu->maze.tabMaze[positionInverse][i] != CHECKPOINT && i < jeu->maze.sizeMaze){
            i++;
        }
        jeu->j.positions[0] = positionInverse;
        jeu->j.positions[1] = i;
    }
}

void verifCheck(Jeu* jeu, int** maze, int positionL, int positionC){
    if(positionL > -1 && positionC > -1 && positionC < jeu->maze.sizeMaze && positionL < jeu->maze.sizeMaze){
        if((maze[positionL][positionC]) == CHECKPOINT){
            jeu->j.etatCheckPoint = 0;
            jeu->maze.tabMaze[jeu->j.positions[0]][jeu->j.positions[1]] = SPACE; 
            if(positionC == 0){
                jeu->maze = jeu->megamaze[jeu->posMaze[0]][jeu->posMaze[1]-1];
                jeu->posMaze[1]--;
                findCheck(jeu,jeu->maze.sizeMaze-1,1);
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
            }
            if(positionL == 0){
                jeu->maze = jeu->megamaze[jeu->posMaze[0]-1][jeu->posMaze[1]];
                jeu->posMaze[0]--;

                findCheck(jeu,jeu->maze.sizeMaze-1,0);
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
            }
            if(positionC == (jeu->maze.sizeMaze-1)){
                jeu->maze = jeu->megamaze[jeu->posMaze[0]][jeu->posMaze[1]+1];
                jeu->posMaze[1]++;
                afficherMatrice1(jeu->maze.tabMaze,jeu->maze.sizeMaze,jeu->options.typeEmoji);

                findCheck(jeu,0,1);
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
            
            }
            if(positionL == (jeu->maze.sizeMaze-1)){
                jeu->maze = jeu->megamaze[jeu->posMaze[0]+1][jeu->posMaze[1]];
                jeu->posMaze[0]++;

                findCheck(jeu,0,0);
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
            
            }
        }
    }
}

void deplacementMaze(Jeu* jeu,arbreChemins* a,int*** maze,int positions[2]){
    switch (deplacementTouche(jeu->j.etatSobreJoueur)) {
                case HAUT:
                    if(deplacementValide(positions[0]-1,positions[1],a,jeu->j,*maze,jeu->maze.sizeMaze)){
                        verifCheck(jeu,*maze,positions[0]-1,positions[1]);
                        if(jeu->j.etatCheckPoint){
                            verifEvent(jeu,maze,positions[0]-1,positions[1]);
                            (*maze)[positions[0]-1][positions[1]] = PLAYER;
                            (*maze)[positions[0]][positions[1]] = SPACE;
                            if(jeu->j.etatCheckPoint == 2){
                                (*maze)[positions[0]][positions[1]] = CHECKPOINT;
                                jeu->j.etatCheckPoint = 1;
                            }
                            positions[0]--;

                        }else{
                            (*maze)[jeu->j.positions[0]][jeu->j.positions[1]] = PLAYER;
                            jeu->j.etatCheckPoint = 2;
                        }
                    }
                    break;
                case DROITE:
                    if(deplacementValide(positions[0],positions[1]+1,a,jeu->j,*maze,jeu->maze.sizeMaze)){
                        verifCheck(jeu,*maze,positions[0],positions[1]+1);
                        if(jeu->j.etatCheckPoint){
                            verifEvent(jeu,maze,positions[0],positions[1]+1);
                            (*maze)[positions[0]][positions[1]+1] = PLAYER;
                            (*maze)[positions[0]][positions[1]] = SPACE;
                            if(jeu->j.etatCheckPoint == 2){
                                (*maze)[positions[0]][positions[1]] = CHECKPOINT;
                                jeu->j.etatCheckPoint = 1;
                            }
                            positions[1]++;
                            
                        }else{
                            (*maze)[jeu->j.positions[0]][jeu->j.positions[1]] = PLAYER;
                            jeu->j.etatCheckPoint = 2;
                        }
                    } 
                    break;
                case GAUCHE:
                    if(deplacementValide(positions[0],positions[1]-1,a,jeu->j,*maze,jeu->maze.sizeMaze)){
                        verifCheck(jeu,*maze,positions[0],positions[1]-1);
                        if(jeu->j.etatCheckPoint){
                            verifEvent(jeu,maze,positions[0],positions[1]-1);
                            (*maze)[positions[0]][positions[1]-1] = PLAYER;
                            (*maze)[positions[0]][positions[1]] = SPACE;
                            if(jeu->j.etatCheckPoint == 2){
                                (*maze)[positions[0]][positions[1]] = CHECKPOINT;
                                jeu->j.etatCheckPoint = 1;
                            }
                            positions[1]--;
                            
                        }else{
                            (*maze)[jeu->j.positions[0]][jeu->j.positions[1]] = PLAYER;
                            jeu->j.etatCheckPoint = 2;
                        }
                    }
                    break;
                case BAS:
                    if(deplacementValide(positions[0]+1,positions[1],a,jeu->j,*maze,jeu->maze.sizeMaze)){
                        verifCheck(jeu,*maze,positions[0]+1,positions[1]);
                        if(jeu->j.etatCheckPoint){
                            verifEvent(jeu,maze,positions[0]+1,positions[1]);
                            (*maze)[positions[0]+1][positions[1]] = PLAYER;
                            (*maze)[positions[0]][positions[1]] = SPACE;
                            if(jeu->j.etatCheckPoint == 2){
                                (*maze)[positions[0]][positions[1]] = CHECKPOINT;
                                jeu->j.etatCheckPoint = 1;
                            }
                            positions[0]++;
                            
                        }else{
                            (*maze)[jeu->j.positions[0]][jeu->j.positions[1]] = PLAYER;
                            jeu->j.etatCheckPoint = 2;
                        }
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

void playMazeSimple(Jeu* jeu){
        creerMaze(jeu);
            mazeCSV(&jeu->maze);
            placerEvents(&jeu->maze,jeu->level);
            while(jeu->maze.arbreChemin->type && jeu->j.pvHealth > 0){
                jouerMaze(jeu);
            }
}
void playMegaMaze(Jeu* jeu){
    creerMegaMaze(jeu);
                jeu->maze = jeu->megamaze[jeu->posMaze[0]][jeu->posMaze[1]];
                jeu->maze.arbreChemin = creerArbreChemins(NULL, jeu->j.positions[0] , jeu->j.positions[1] , jeu->maze.tabMaze,jeu->maze.sizeMaze);
                for(int i = 0; i < 3 ;i++){
                    for(int j = 0; j < 3;j++){
                        /// paul ici
                        placerEvents(&jeu->megamaze[i][j],jeu->level/2);
                        mazebigCSV(&jeu->megamaze[i][j],i,j);
                        }
                    }
                placerKeys(&jeu->megamaze[rand() % 3][rand() % 3],&jeu->j);
                while((!jeu->j.findKeys || jeu->maze.arbreChemin->type) && jeu->j.pvHealth > 0){
                    jouerMaze(jeu);
                }
    }

void jouerJeu(Jeu* jeu){
    while(jeu->level < 30 && jeu->j.pvHealth > 0){
        if(jeu->level > ((jeu->options.typeLevel+2)*4)-1){ // 0 --> 4 --> 8 --> 7 / 1 --> 6 / 2 --> 8
            jeu->maze.typeMaze = 0;
        }

        if (jeu->maze.typeMaze){
            playMazeSimple(jeu);
        }else{
            playMegaMaze(jeu);
        }
        
        if(jeu->j.pvHealth > 0){
            free(jeu->maze.tabMaze);
            free(jeu->maze.arbreChemin);
            jeu->level=jeu->level+2;
            jeu->score= jeu->score + (25*jeu->level);
        }
    }
}


void gameOver(int level, int score,int highScore){    
    system("clear");
    saveHighScoreCSV(highScore,score);
    afficherScore(level,score);
    printf("\e[1;92m""⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⠀⠀⢀⣴⣿⡶⠀⣾⣿⣿⡿⠟⠛⠁\n");
    printf("⠀⠀⠀⠀⠀⠀⣀⣀⣄⣀⠀⠀⠀⠀⣶⣶⣦⠀⠀⠀⠀⣼⣿⣿⡇⠀⣠⣿⣿⣿⠇⣸⣿⣿⣧⣤⠀⠀⠀\n");
    printf("⠀⠀⢀⣴⣾⣿⡿⠿⠿⠿⠇⠀⠀⣸⣿⣿⣿⡆⠀⠀⢰⣿⣿⣿⣷⣼⣿⣿⣿⡿⢀⣿⣿⡿⠟⠛⠁⠀⠀\n");
    printf("⠀⣴⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⣹⣿⣿⣿⣿⣿⣿⡏⢻⣿⣿⢿⣿⣿⠃⣼⣿⣯⣤⣴⣶⣿⡤⠀\n");
    printf("⣼⣿⠏⠀⣀⣠⣤⣶⣾⣷⠄⣰⣿⣿⡿⠿⠻⣿⣯⣸⣿⡿⠀⠀⠀⠁⣾⣿⡏⢠⣿⣿⠿⠛⠋⠉⠀⠀⠀\n");
    printf("⣿⣿⠲⢿⣿⣿⣿⣿⡿⠋⢰⣿⣿⠋⠀⠀⠀⢻⣿⣿⣿⠇⠀⠀⠀⠀⠙⠛⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠹⢿⣷⣶⣿⣿⠿⠋⠀⠀⠈⠙⠃⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣴⣶⣦⣤⡀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡇⢰⣶⣶⣾⡿⠷⣿⣿⣿⡟⠛⣉⣿⣿⣿⠆\n");
    printf("⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⡎⣿⣿⣦⠀⠀⠀⢀⣤⣾⠟⢀⣿⣿⡟⣁⠀⠀⣸⣿⣿⣤⣾⣿⡿⠛⠁⠀\n");
    printf("⠀⠀⠀⠀⣠⣾⣿⡿⠛⠉⢿⣦⠘⣿⣿⡆⠀⢠⣾⣿⠋⠀⣼⣿⣿⣿⠿⠷⢠⣿⣿⣿⠿⢻⣿⣧⠀⠀⠀\n");
    printf("⠀⠀⠀⣴⣿⣿⠋⠀⠀⠀⢸⣿⣇⢹⣿⣷⣰⣿⣿⠃⠀⢠⣿⣿⢃⣀⣤⣤⣾⣿⡟⠀⠀⠀⢻⣿⣆⠀⠀\n");
    printf("⠀⠀⠀⣿⣿⡇⠀⠀⢀⣴⣿⣿⡟⠀⣿⣿⣿⣿⠃⠀⠀⣾⣿⣿⡿⠿⠛⢛⣿⡟⠀⠀⠀⠀⠀⠻⠿⠀⠀\n");
    printf("⠀⠀⠀⠹⣿⣿⣶⣾⣿⣿⣿⠟⠁⠀⠸⢿⣿⠇⠀⠀⠀⠛⠛⠁⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠈⠙⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n""\e[0m");
    sleep(5);
}

void getScoreCSV(Jeu* jeu){
    FILE* scoreFile = NULL;
    int highScore; 
    char ligne[20];
    scoreFile = fopen("./out/score.csv", "r");
    if (scoreFile == NULL) {
        highScore = 0;
        printf("Erreur ouverture fichier \n");
    }else{
        highScore = atoi(fgets(ligne,20,scoreFile));
        fclose(scoreFile);
    }
    jeu->highScore = highScore;
}

void saveHighScoreCSV(int highScore,int score){
    FILE* scoreFile = NULL;
    scoreFile = fopen("./out/score.csv", "w");
    if (scoreFile == NULL) {
        printf("Erreur ouverture fichier \n");
    }else{
        if(score > highScore){
            fprintf(scoreFile,"%d",score);
        }else{
            fprintf(scoreFile,"%d",highScore);
        }
        fclose(scoreFile);
    }
}

void initOptions(char**** optionsTab,Options* options){
    options->typeEmoji = 0;
    options->typeLevel = 1;
    options->typeMode = 0;

    (*optionsTab) = malloc(3*sizeof(char**));
    for (int i=0; i<3; i++){
        (*optionsTab)[i]=malloc(3*sizeof(char*));
        for (int j=0; j<3; j++){
        (*optionsTab)[i][j]=malloc(100*sizeof(char));
    }
    }
    (*optionsTab)[0][0] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣    "BWHT"◀ 👾 ▶"BPUR"    ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[0][1] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣    "BWHT"◀ 🤡 ▶"BPUR"    ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[0][2] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BWHT"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣    "BWHT"◀ 💎 ▶"BPUR"    ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    
    
    
    
    (*optionsTab)[1][0] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BWHT"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║  "BWHT"◀ NORMAL ▶"BPUR"  ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[1][1] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BWHT"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║   "BWHT"◀ HARD ▶"BPUR"   ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[1][2] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BWHT"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║   "BWHT"◀ EASY ▶"BPUR"   ║  ║  ════  ║\n║     ║  ║  ║  "BPUR"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║              ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    
    (*optionsTab)[2][0] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BWHT"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║     "BWHT"◀ 4 ▶"BPUR"    ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[2][1] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BWHT"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║     "BWHT"◀ 6 ▶"BPUR"    ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";
    (*optionsTab)[2][2] = "╔═════╦═══════════════╦════════════════╗\n║  ║  ║  ═══╗  ════╗  ╚═══════  ══╦══  ║\n║  ╚══╩═══  ╠══════╩═══════╦══════╩══  ║\n║  ╔════════╣   "BPUR"< SKIN >"BPUR"   ╠════════╗  ║\n║  ║  ╔═════╣              ╠═══  ═══╝  ║\n║  ║  ╚══╗  ║   "BPUR"< MODE >"BPUR"   ║  ╔════════╣\n║  ╠══╗  ║  ║              ║  ║  ════  ║\n║     ║  ║  ║  "BWHT"< NIVEAU >"BPUR"  ║  ╚═════╗  ║\n╠══╣  ║  ║  ║     "BWHT"◀ 8 ▶"BPUR"    ║  ╔═════╝  ║\n║  ╚══╝  ║  ╚══════════════╝  ║  ║  ║  ║\n╚════════════════════════════════╩══╩══╝\n";

}

void saveOptions(Options* options,int numOptions,int numTest){
    switch (numOptions) {
        case 0:
            options->typeEmoji = numTest;
            break;
        case 1:
            options->typeMode = numTest;
            break;
        case 2:
            options->typeLevel = numTest;
            break;
    }
}

int getOptions(Options* options,int numOptions){
    switch (numOptions) {
        case 0:
            return options->typeEmoji;
        case 1:
            return options->typeMode;
        case 2:
            return options->typeLevel;
        default:
            return 0;
    } 
}

void optionChange(Options* options,char*** optionsTab){
    int lecture=0;
    int numOptions = 0;
    int numTest = 0;

    while(!lecture){
        printf(reset);
        system("clear");
        // printf("\e[4;33m""\nOptions\n");
        printf(BPUR);
        printf("%s",optionsTab[numOptions][numTest]);
        saveOptions(options,numOptions,numTest);
        switch (deplacementTouche(ETAT_OPTION)) {
            case HAUT:
                numOptions--;
                if(numOptions==-1){
                    numOptions=2;
                }
                numTest = getOptions(options,numOptions);
                break;
            case BAS:
                numOptions++;
                if(numOptions==3){
                    numOptions=0;
                }
                numTest = getOptions(options,numOptions);
                break;
            case DROITE:
                numTest++;
                if(numTest==3){
                    numTest=0;
                }
                break;
            case GAUCHE:
                numTest--;
                if(numTest==-1){
                    numTest=2;
                }
                break;
            case ENTER:
                lecture=1;
                break;
        }
        printf(BGRN);
        // choixMenu(lireMenu());
}
}


void freeGame(Jeu* jeu){
    free(jeu->maze.tabMaze);
    free(jeu->maze.arbreChemin);
    free(jeu->megamaze);
    free(jeu->j.inventaire);
    jeu->j.etatDangerJoueur = ETAT_NON_DANGER;
    jeu->j.etatSobreJoueur = ETAT_NORMAL;
    jeu->j.etatTourRestants = 0;
}


