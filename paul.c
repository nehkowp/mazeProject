#include "paul.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>

void emptyBuffer() {
  char c;
  while (((c = getchar()) != '\n') && (c != EOF));
}

char deplacementTouche(){
  struct termios tty_opts_backup, tty_opts_raw;
  char c;
  int pastermine=1;//par défaut on le met à vrai

  /* on est obligé d'appuyer sur la touche entrée */
  //c =getchar();


  // Back up current TTY settings
  tcgetattr(STDIN_FILENO, &tty_opts_backup);


  // Change TTY settings mode
  cfmakeraw(&tty_opts_raw);
  tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_raw);

  while (pastermine){
    // ZQSD
     
    c =getchar();
     
    switch(c){
    case HAUT: //haut
      //printf("vous avez écrit %d => %c haut !",c,c);
      pastermine=0;
      break;
    case GAUCHE: //gauche
      //printf("vous avez écrit %d => %c gauche !",c,c);
      pastermine=0;
      break;
    case DROITE: //droite
      //printf("vous avez écrit %d => %c droite !",c,c);;
      pastermine=0;
      break;
    case BAS: //bas
      //printf("vous avez écrit %d => %c bas !",c,c);
      pastermine=0;
      break;
    case 97:
      printf("vous avez tapé la lettre %c pour quitter le programme!",c);
      
  /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
  // Restore previous TTY settings
      //emptyBuffer();
      tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);
      printf("\n");
      exit(0);
    default:
      printf("NON prise en compte\n");
    }
  }


  /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
  // Restore previous TTY settings
  tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);

  return c;

}


