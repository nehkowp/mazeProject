#include "paul.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include "structure.h"

int inversion = 0;

void emptyBuffer() {
  char c;
  while (((c = getchar()) != '\n') && (c != EOF));
}

char deplacementTouche(int etatJoueur){
  struct termios tty_opts_backup, tty_opts_raw;
  char c;
  int pastermine=1;//par défaut on le met à vrai


  // Back up current TTY settings
  tcgetattr(STDIN_FILENO, &tty_opts_backup);

  // Change TTY settings mode
  cfmakeraw(&tty_opts_raw);
  tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_raw);

  while (pastermine) {


    c = getchar();

    if (etatJoueur == ETAT_ENTER){
      switch(c){
        case ENTER:
          pastermine =0;
          break;
        default:
          break;
      }
    }

    if (etatJoueur == ETAT_OPTION) {
      switch (c) {
        case HAUT:
          pastermine = 0;
          break;
        case BAS:
          pastermine = 0;
          break;
        case ENTER:
          pastermine = 0;
          break;
        case DROITE:
          pastermine = 0;
          break;
        case GAUCHE:
          pastermine = 0;
          break;

        default:
          break;
      }
    }


    if (etatJoueur == ETAT_MENU) {
      switch (c) {
        case HAUT:
          pastermine = 0;
          break;
        case BAS:
          pastermine = 0;
          break;
        case ENTER:
          pastermine = 0;
          break;

        default:
          break;
      }
    }
    
    if (etatJoueur == ETAT_DRUNK) {
      switch (c) {
        case HAUT:
          c = BAS;
          pastermine = 0;
          break;
        case GAUCHE:
          c = DROITE;
          pastermine = 0;
          break;
        case DROITE:
          c = GAUCHE;
          pastermine = 0;
          break;
        case BAS:
          c = HAUT;
          pastermine = 0;
          break;
        case HOTBAR1: 
          pastermine=0;
          break;
        case HOTBAR2:
          pastermine=0;
          break;
        case HOTBAR3:
          pastermine=0;
          break;
        case HOTBAR4:
          pastermine=0;
          break;
        case HOTBAR5:
          pastermine=0;
          break;
        default:
          break;
      }
    }
    
    switch(c){
      case HAUT:
        pastermine=0;
        break;
      case GAUCHE:
        pastermine=0;
        break;
      case DROITE:
        pastermine=0;
        break;
      case BAS:
        pastermine=0;
        break;
      case HOTBAR1:
        pastermine=0;
        break;
      case HOTBAR2:
        pastermine=0;
        break;
      case HOTBAR3:
        pastermine=0;
        break;
      case HOTBAR4:
        pastermine=0;
        break;
      case HOTBAR5:
        pastermine=0;
        break;
      case 97:
        printf("\n Vous avez tapé la lettre %c qui permet de quitter le programme!",c);
      
        /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
        // Restore previous TTY settings
        tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);
        printf("\n");
        exit(0);
      default:
        printf("NON prise en compte\r\n");
        break;
    }
  }


  /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
  // Restore previous TTY settings
  tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);

  return c;

}


void mazeCSV(Maze* maze) {
    FILE *fichier = fopen("out/maze.csv", "w");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier");
    }
    for(int i=0;i<(maze->sizeMaze);i++){
      for(int j=0;j<(maze->sizeMaze);j++){
        fprintf(fichier,"%d ",maze->tabMaze[i][j]);
      }
      fprintf(fichier, "\n");
    }

    fclose(fichier);
}


void mazebigCSV(Maze* maze, int i, int j) {
    char fichiers[40];
    snprintf(fichiers, sizeof(fichiers), "./out/megaMazeCSV/maze%d%d.csv",i,j);
    FILE *fichier = fopen(fichiers, "w");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier");
    }
    for(int i=0;i<maze->sizeMaze;i++){
      for(int j=0;j<maze->sizeMaze;j++){
        fprintf(fichier,"%d ",maze->tabMaze[i][j]);
      }
      fprintf(fichier, "\n");
    }

    fclose(fichier);
} 