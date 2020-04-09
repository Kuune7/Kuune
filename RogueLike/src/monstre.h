#ifndef __MONSTRE__
#define __MONSTRE__

#include "const.h"
#include "perso.h"


/**
 * \file monstre.h
 * \brief Fichier contenant le prototype des fonctions nous permettant de gérer les monstres
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


void ChargerMob(SDL_Window * screen, Salle salle[N][M], int level);
void InitialisationBoss(SDL_Window * screen, Salle * salle, Salle s);
void LibererMonstres(Salle salle[N][M]);
void AfficherMobHUD(SDL_Renderer * rendu, Monstre mob);
void InitMob(SDL_Window * screen, Monstre * mob, Salle salle, int tailleX, int tailleY, int hp, int maxDamage, int minDamage, int boss);
int TimerMob(Monstre * mob);
void DeplacementMonstre(Monstre * mob, Player player);
int  EvolutionMonstres (Salle salle[N][M], Player player, Player * p);

#endif