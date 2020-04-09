#ifndef __ANIMATION__
#define __ANIMATION__

#include "const.h"

/**
 * \file animation.h
 * \brief Fichier contenant le prototype des fonctions qui nous seront utile dans pour le chargement, l'affichage et la suppression d'animation
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 11/03/2020
*/

void AffichageAnimation(Animation* An, SDL_Renderer * rendu, int sens, int stat, int x, int y, int boss);
Animation * ChargerAnimation(SDL_Window * window, const char* fichier);
void LibererAnimation(Animation* An);

#endif