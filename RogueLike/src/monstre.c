#include "monstre.h"
#include "const.h"
#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "son.h"


/**
 * \file monstre.c
 * \brief Fichier contenant des fonctions nous permettant de gérer les monstres
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/

/**
 * \brief Fonction permettant d'initialiser le boss (monstre de la derniere salle)
 */
void InitialisationBoss(SDL_Window * screen, Salle * salle, Salle s) {
	salle->nbMonstres = 1;
	salle->nbCoffre = 0;

	InitMob(screen, &salle->monstre[0], s, rand()%300+100, rand()%300+100, rand()%2000+1000, 60, 30, 1);
}


/**
 * \brief Fonction permettant de gerer la barre de vie au dessus du monstre
 */
void AfficherMobHUD(SDL_Renderer * rendu, Monstre mob) {

	float pourcentageVie = (float)mob.hp/mob.hp_max;
	SDL_Rect hpBar = {mob.salleX, mob.salleY-20, mob.tailleX, 10};
	SDL_SetRenderDrawColor (rendu, 0, 0, 0, 255);
	SDL_RenderFillRect(rendu, &hpBar);
	SDL_SetRenderDrawColor (rendu, 255, 0, 0, 255);
	hpBar.w = mob.tailleX * pourcentageVie;
	SDL_RenderFillRect(rendu, &hpBar);
}


/**
 * \brief Fonction permettant de savoir si le lieu de spawn du mob est en regle ou non
 * \return 1 si pas convenable
 * \return 0 sinon
*/
int InitPositionMob(Monstre * mob, Salle salle) {
	if ((salle.matTexture[mob->salleY/TAILLE_TILE][mob->salleX/TAILLE_TILE].mur == 1) || (salle.matTexture[(mob->salleY+mob->tailleY)/TAILLE_TILE][(mob->salleX+mob->tailleX)/TAILLE_TILE].mur == 1)) {
		return 1;
	}
	else if ((mob->salleX < 4*TAILLE_TILE) || (mob->salleX > LARGEUR_ECRAN-5*TAILLE_TILE+mob->tailleX)) {
		return 1;
	}
	else if ((mob->salleY < 4*TAILLE_TILE) || (mob->salleY > HAUTEUR_ECRAN-5*TAILLE_TILE+mob->tailleY)) {
		return 1;
	}
	return 0;
}

/**
 * \brief permet apres une sauvegarde de recreer des monstres pour les salles non explorer
*/
void ChargerMob(SDL_Window * screen, Salle salle[N][M], int level) {
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			if (!salle[i][j].explorer) {
				for (int k = 0 ; k < salle[i][j].nbMonstres ; k++) {
					InitMob(screen, &salle[i][j].monstre[k], salle[i][j], TAILLE_TILE, TAILLE_TILE, 100*level + (level-1)*50, 30*level + (level-1)*10, 5*level + (level-1)*5, 0);
				}
			}
		}
	}
}

/**
 * \brief Fonction permettant d'initialiser un monstre
 */
void InitMob(SDL_Window * screen, Monstre * mob, Salle salle, int tailleX, int tailleY, int hp, int maxDamage, int minDamage, int boss) {
	
	mob->An = ChargerAnimation(screen, "mob1.txt");

	mob->tailleX = (mob->An->largeurChar-40)*2;
	mob->tailleY = (mob->An->hauteurChar-15)*2;

	if (boss) {
		mob->tailleX *= 2;
		mob->tailleY *= 2;
	}

	if (!boss) {
		do {
			mob->salleX = rand()%(TAILLE_SALLE_X*TAILLE_TILE);
			mob->salleY = rand()%(TAILLE_SALLE_Y*TAILLE_TILE);
		} while (InitPositionMob(mob, salle));
	}
	else {
		mob->salleX = LARGEUR_ECRAN/2 - mob->tailleX;
		mob->salleY = HAUTEUR_ECRAN/2 - mob->tailleY;
	}

	mob->sp = InitSprite(mob->An, mob->salleX, mob->salleY);

	mob->hp = mob->hp_max = hp;
	mob->vitesse = 1;

	mob->damages = rand()%maxDamage + minDamage;

	mob->bossFinal = boss;

	ftime(&mob->lastAttack);

}

/**
 * \brief Fonction permetttant de gerer le delay entre 2 attaques d'un monstre (1 seconde de delay)
 */
int TimerMob(Monstre * mob) {

	int delay = 1000;

	struct timeb currentAttack;
	ftime(&currentAttack);
	int secondes = (int) difftime(currentAttack.time, mob->lastAttack.time);
	int ms1 = delay - mob->lastAttack.millitm;
    int ms2 = currentAttack.millitm;

	if ((((ms1+ms2) >= delay) && secondes >= 1) || (secondes >= 2)) {
		ftime(&mob->lastAttack);
		return 1;
	}

	return 0;
}


int erreur = 0;
int xincr, yincr;

/**
 * \brief Fonction permettant de gerer le deplacement du monstre
*/
void DeplacementMonstre(Monstre * mob, Player player) {


	float mobX = mob->salleX+(mob->tailleX/2), mobY = mob->salleY+(mob->tailleY/2);
	float playerX = player.salleX+(player.tailleX/2), playerY = player.salleY+(player.tailleY/2);

	int dY = abs(playerY - mobY);
	int dX = abs(playerX - mobX);

	if (mobX < playerX)
		xincr = mob->vitesse;
	else
		xincr = -mob->vitesse;
	
	if (mobY < playerY) 
		yincr = mob->vitesse;
	else
		yincr = -mob->vitesse;

	if (dX > dY) {
		if (erreur == 0)
			erreur = dX/2;
		mob->salleX += xincr;
		erreur += dY;
		if (erreur > dX) {	
			erreur -= dX;
			mob->salleY += yincr;
		}
	}
	else {
		if (erreur == 0)
			erreur = dY/2;
		mob->salleY += yincr;
		erreur += dX;
		if (erreur > dY) {
			erreur -= dY;
			mob->salleX += xincr;

		}
	}

	mob->sp->stat = marche;
	MouvementSpriteMob(mob->sp, *mob, mob->sp->stat);
	
}

/**
 * \brief Permet de liberer la memoire allouer au monstre d'un labyrinthe
*/
void LibererMonstres(Salle salle[N][M]) {

	for (int i  = 0 ; i < N ; i++) {
		for (int j  = 0 ; j < M ; j++) {
			for (int k = 0 ; k < salle[i][j].nbMonstres ; k++) {
				if (salle[i][j].monstre[k].An != NULL) {
					LibererAnimation(salle[i][j].monstre[k].An);
					salle[i][j].monstre[k].An = NULL;
				}
				if (salle[i][j].monstre[k].sp != NULL) {
					LibererSprite(salle[i][j].monstre[k].sp);
					salle[i][j].monstre[k].sp = NULL;
				}
			}
			salle[i][j].nbMonstres = 0;
		}
	}

}


/**
 * \brief Permet de gerer l'evolution des monstres
 * \return 1 Si le joueur est mort suite a une collision avec un mob
 * \return 0 Sinon
*/
int  EvolutionMonstres (Salle salle[N][M], Player player, Player * p) {
	for (int i = 0 ; i < salle[player.labY][player.labX].nbMonstres ; i++) {
		if (((player.salleX >= (salle[player.labY][player.labX].monstre[i].salleX-salle[player.labY][player.labX].monstre[i].tailleX*7)) && (player.salleX <= (salle[player.labY][player.labX].monstre[i].salleX+salle[player.labY][player.labX].monstre[i].tailleX)+7*salle[player.labY][player.labX].monstre[i].tailleX)) && ((player.salleY >= (salle[player.labY][player.labX].monstre[i].salleY-7*salle[player.labY][player.labX].monstre[i].tailleY)) && (player.salleY <= (salle[player.labY][player.labX].monstre[i].salleY+salle[player.labY][player.labX].monstre[i].tailleY)+7*salle[player.labY][player.labX].monstre[i].tailleX))) {
			if (!CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX+2, salle[player.labY][player.labX].monstre[i].salleY, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) && !CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX-2, salle[player.labY][player.labX].monstre[i].salleY, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) && !CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY+2, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) && !CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY-2, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY)) {
				DeplacementMonstre(&salle[player.labY][player.labX].monstre[i], player);
			}
			else {
				salle[player.labY][player.labX].monstre[i].sp->stat = arret;
			}
		}
		if (CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX+2, salle[player.labY][player.labX].monstre[i].salleY, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) || CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX-2, salle[player.labY][player.labX].monstre[i].salleY, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) || CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY+2, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) || CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY-2, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY)) {
			if (TimerMob(&salle[player.labY][player.labX].monstre[i])) {
				int degats = salle[player.labY][player.labX].monstre[i].damages - p->def/4;
				if (salle[player.labY][player.labX].nbMonstres && !salle[player.labY][player.labX].monstre[0].bossFinal) {
					if (sound != NULL) {
						Mix_FreeMusic(sound);
						sound = NULL;
					}
					sound = Mix_LoadMUS("./sounds/hitted.wav");
					Mix_PlayMusic(sound, 1);
				}

				if (!GOD_MOD) {
					if (degats < 5) {
						p->hp -= 5;
					}
					else {
						p->hp -= degats;
					}
					if (p->hp <= 0) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}