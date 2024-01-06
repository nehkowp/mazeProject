#include "gabin.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "clem.h"


    // Choisir une ligne de départ aléatoire dans la première colonne
int setStart( int** maze, int taille ) {
    int random = 0;
    random = 1 + rand() % ( taille - 2 );
    // Vérifier que la case choisie est vide (pas un mur)
    while ( maze[ random ][ 1 ] != SPACE ) {
        random = 1 + rand() % ( taille - 2 );
    }
    // Marquer la case de départ dans la matrice et la retourner
    maze[ random ][ 0 ] = START;
    return random;
}

void setEnd(int*** maze, int taille) {
    int random = 0;    
    // Choisir une ligne de fin aléatoire dans la dernière colonne
    random = 1 + rand() % ( taille - 2 );
    // Vérifier que la case choisie est vide (pas un mur)
    while ( (*maze)[ random ][ taille - 2 ] != SPACE ) {
        random = 1 + rand() % ( taille - 2 );
    }
    // Marquer la case de fin dans la matrice
    (*maze)[ random ][ taille - 1 ] = END;
}



void afficherMatrice1(int** matrice , int n) {
   // Afficher la matrice avec des symboles correspondant aux éléments
   for(int i = 0; i < n; i++){
        for(int j =0; j < n; j++){
            switch (matrice[i][j]) {
                case SPACE:
                    printf("  "); // Espace vide
                    break;
                case WALL:
                    printf("🧱"); // Mur
                    break;
                case PLAYER:
                    printf("👾"); // Joueur
                    break;
                case END:
                    printf("🏁"); //Point d'arrivée
                    break;
                case EVENT:
                    printf("❔");
                    break;
                default:
                    break; 
            }

        }
        printf("\n");
    }
}
void afficherMatrice2(int** matrice , int n) {
   // Afficher la matrice avec des symboles correspondant aux éléments
   for(int i = 0; i < n; i++){
        for(int j =0; j < n; j++){
            switch (matrice[i][j]) {
                case SPACE:
                    printf("  "); // Espace vide
                    break;
                case WALL:
                    printf("%s",affichageMur(matrice,i,j,n-1)); // Mur
                    break;
                case PLAYER:
                    printf("# "); // Joueur
                    break;
                case END:
                    printf("🏁"); //Point d'arrivée
                    break;
                case EVENT:
                    printf("❔");
                    break;
                default:
                    break; 
            }

        }
        printf("\n");
    }
}


void allouerTab1(int** tab, int taille){
    int n = (taille*taille);
    *tab = (int*)malloc(n * sizeof(int));
    for (int i= 0; i < n; i++) {
        (*tab)[i] = 0;  // Initialiser la matrice avec des murs (-1)
        }
    }


void allouerTab2(int*** tab, int taille){
    *tab = (int**)malloc(taille * sizeof(int*));
    for (int ligne = 0; ligne < taille; ligne++) {
        (*tab)[ligne] = (int*)malloc(taille * sizeof(int));
        for (int colonne= 0; colonne < taille; colonne++) {
            (*tab)[ligne][colonne] = WALL;  // Initialiser la matrice avec des murs (-1)
        }
    }
}

void mazeGenerator(int*** maze,int taille) {
    
    int ligne;
    int colonne;
    int index = 0;
    int *indexPtr = &index;
    int* cStack = NULL;
    int* rStack = NULL;
    int direction;
    int cont = 4;
    int maze_dir[ 4 ] = { 0 };
    int values[ DIR ][ VALUES ] = { 0 };
    int x;
    int set = 0;

    allouerTab1(&cStack, taille);
    allouerTab1(&rStack, taille);
    allouerTab2(maze,taille);

    ligne = 3;
    colonne = 5;
    

    (*maze)[ ligne ][ colonne ] = 1;

    ajouter_pile( ligne, colonne, &cStack, &rStack, indexPtr );

    srand( time( NULL ) );
    while(index >= 1) {
        while(cont != 0) {
            while( cont > 0 ) {
                set = 0;
                direction = ( 1 + rand() % DIR ) - 1;
                if ( maze_dir[ direction ] == 0 ) {
                    maze_dir[ direction ] = 1;
                    cont--;

                    setValues( values, ligne, colonne,taille);
                    for ( x = 0; x < DIR; ++x ) {
                        if ( direction == x && (*maze)[values[x][0]][values[x][1]] !=SPACE && (*maze)[values[x][2]][values[x][3]] !=SPACE && (*maze)[values[x][4]][values[x][5]] !=SPACE && (*maze)[values[x][6]][values[x][7]] !=SPACE && (*maze)[values[x][8]][values[x][9]] !=SPACE && (*maze)[values[x][10]][values[x][11]] !=SPACE && (*maze)[values[x][12]][values[x][13]] !=SPACE && (*maze)[values[x][14]][values[x][15]] !=SPACE && (*maze)[values[x][16]][values[x][17]] !=SPACE && values[x][18] ) {
                            ligne = values[ x ][ 0 ];
                            colonne = values[ x ][ 1 ];
                            (*maze)[ ligne ][ colonne ] = SPACE;
                            setValues( values, ligne, colonne,taille);
                            ligne = values[ x ][ 0 ];
                            colonne = values[ x ][ 1 ];
                            (*maze)[ ligne ][ colonne ] = SPACE;
                            ajouter_pile( ligne, colonne, &cStack, &rStack, indexPtr );
                            cont = 4;
                            set = 1;
                            break;
                        }
                    }
                    if ( set == 1 ) {
                        break;
                    }
                }

            }
            maze_dir[ 0 ] = 0;
            maze_dir[ 1 ] = 0;
            maze_dir[ 2 ] = 0;
            maze_dir[ 3 ] = 0;
        }
            retirer_pile( ligne, colonne, &cStack, &rStack, indexPtr );
            ligne = cStack[ index ];
            colonne = rStack[ index ];
            maze_dir[ 0 ] = 0;
            maze_dir[ 1 ] = 0;
            maze_dir[ 2 ] = 0;
            maze_dir[ 3 ] = 0;
            cont = 4;
    }
}

void setValues( int values[][ VALUES ], int ligne, int colonne, int taille) {

    // Initialiser le tableau de valeurs en fonction de la position actuelle
    int Table[ DIR ][ VALUES ] = {  { ligne, colonne + 1, ligne, colonne + 2, ligne, colonne + 3, ligne - 1, colonne + 1, ligne + 1, colonne + 1, ligne + 1, colonne + 2, ligne - 1, colonne + 2, ligne - 1, colonne + 3, ligne + 1, colonne + 3, colonne < ( taille - 2 ) },
                                 { ligne, colonne - 1, ligne, colonne - 2, ligne, colonne - 3, ligne - 1, colonne - 1, ligne - 1, colonne - 2, ligne - 1, colonne - 3, ligne + 1, colonne - 1, ligne + 1, colonne - 2, ligne + 1, colonne - 3, colonne > 1 },
                                 { ligne - 1, colonne, ligne - 2, colonne, ligne - 3, colonne, ligne - 1, colonne + 1, ligne - 2, colonne + 1, ligne - 3, colonne + 1, ligne - 1, colonne - 1, ligne - 2, colonne - 1, ligne - 3, colonne - 1, ligne > 1 },
                                 { ligne + 1, colonne, ligne + 2, colonne, ligne + 3, colonne, ligne + 1, colonne + 1, ligne + 2, colonne + 1, ligne + 3, colonne + 1, ligne + 1, colonne - 1, ligne + 2, colonne - 1, ligne + 3, colonne - 1, ligne < ( taille - 2 ) } };
    int x, y;
    // Copier les valeurs de Table dans values
    for ( x = 0; x < DIR; ++x ) {
        for ( y = 0; y < VALUES; ++y ) {
            if(Table[ x ][ y ] >= 0 && Table[x][y] < taille){
                values[ x ][ y ] = Table[ x ][ y ];
            }else{
                values[ x ][ y ] = 0;
            }
        }
    }
}

void ajouter_pile( const int ligne, const int colonne, int** cStack, int** rStack, int *index ) {
    // Ajouter la position actuelle à la pil
    (*cStack)[ *index ] = ligne;
    (*rStack)[ *index ] = colonne;
    *index += 1;
}

void retirer_pile( const int ligne, const int colonne, int** cStack, int** rStack, int *index ) {
    // Retirer la position actuelle de la pile
    (*cStack)[ *index ] = ligne;
    (*rStack)[ *index ] = colonne;
    *index -= 1;
}
