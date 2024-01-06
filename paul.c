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

  while (pastermine) {
    // ZQSD
    c = getchar();
    if (inversion == 1) {
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
        case HOTBAR2: //bas
          pastermine=0;
          break;
        case HOTBAR3: //bas
          //printf("vous avez écrit %d => %c bas !",c,c);
          pastermine=0;
          break;
        case HOTBAR4: //bas
          //printf("vous avez écrit %d => %c bas !",c,c);
          pastermine=0;
          break;
        case HOTBAR5: //bas
          //printf("vous avez écrit %d => %c bas !",c,c);
          pastermine=0;
          break;
        default:
          break;
      }
    }
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
    case HOTBAR1: //bas
      //printf("vous avez écrit %d => %c bas !",c,c);
      pastermine=0;
      break;
    case HOTBAR2: //bas
      //printf("vous avez écrit %d => %c bas !",c,c);
      pastermine=0;
      break;
    case HOTBAR3: //bas
      //printf("vous avez écrit %d => %c bas !",c,c);
      pastermine=0;
      break;
    case HOTBAR4: //bas
      //printf("vous avez écrit %d => %c bas !",c,c);
      pastermine=0;
      break;
    case HOTBAR5: //bas
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
    if(arbre->type){
        return coords;
    }else{
        for(int nbFils = 0; nbFils < arbre->nbFils; nbFils++){
            coords->suivant = cheminAriane(arbre->fils[nbFils],coords);

        }
        coords->suivant = cheminAriane(arbre->parent,coords);
    }
    return NULL;
}

void filAriane(Jeu* jeu){
    CoordsStack ariane = cheminAriane(jeu->arbreChemin,NULL);
    while(ariane != NULL){
        printf("[%d - %d]\n",ariane->positions[0],ariane->positions[1]);
        printf("[%d - %d]\n",ariane->suivant->positions[0],ariane->suivant->positions[1]);
        // printf("[%d - %d]\n",ariane->positions[0],ariane->positions[1]);

        CoordsStack avantDernier = ariane->suivant;
        ariane = avantDernier;
    }
    sleep(1);
}
