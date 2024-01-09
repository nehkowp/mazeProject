#ifndef ETIENNE_H
#define ETIENNE_H

#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000
#define BGRN "\e[1;32m"
#define BRED "\e[1;31m"
#define BWHT "\e[1;37m"
#define BPUR "\e[1;96m"	
#define reset "\e[0m"

char** lireMenu();
void choixMenu(char** menus, Options* options);
void regle(Options* options);

#endif