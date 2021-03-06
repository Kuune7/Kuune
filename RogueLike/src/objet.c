#include "objet.h"

/**
 * \file objet.c
 * \brief Fichier contenant des fonctions nous permettant de gérer les objets
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.2
 * \date 24/02/2020
*/

/**
 * \brief Permet d'initier un objet
*/
void InitObjet (int * damage, int * def) {

  int choix = rand()%3;
  switch(choix) {
    case 0:
      (*damage) += rand()%MAX_LOOT_DAMAGE + MIN_LOOT_DAMAGE;
      break;
    case 1:
      (*def) += rand()%MAX_LOOT_ARMOR + MIN_LOOT_ARMOR;
      break;
    case 2:
      (*damage) += rand()%MAX_LOOT_DAMAGE + MIN_LOOT_DAMAGE;
      (*def) += rand()%MAX_LOOT_ARMOR + MIN_LOOT_ARMOR;
      break;
    default:
      break;
  }
}

/**
 * \brief Permet d'initier un objet legendaire
 */
void InitObjet_Legendary (int * damage, int * def) {

  (*damage) += rand()%MAX_LOOT_DAMAGE_LEGENDARY + MIN_LOOT_DAMAGE_LEGENDARY;
  (*def) += rand()%MAX_LOOT_ARMOR_LEGENDARY + MIN_LOOT_ARMOR_LEGENDARY;
}

/**
 * \brief Permet d'initialiser un coffre
 */
void InitCoffre(Coffre * coffre, Salle salle) {

  coffre->ouvert = 0;
  do {
		  coffre->salleX = rand()%(TAILLE_SALLE_X*TAILLE_TILE);
	    coffre->salleY = rand()%(TAILLE_SALLE_Y*TAILLE_TILE);
    } while ((salle.matTexture[coffre->salleY/TAILLE_TILE][coffre->salleX/TAILLE_TILE].mur == 1) || (salle.matTexture[(coffre->salleY+TAILLE_TILE)/TAILLE_TILE][(coffre->salleX+TAILLE_TILE)/TAILLE_TILE].mur == 1));
  coffre->legendary = 0;
}

/**
 * \brief Permet d'afficher un coffre
 */
void AfficherCoffre(SDL_Renderer * rendu, Coffre coffre) {

    SDL_Surface * imageCoffre; 

    if (!coffre.legendary) {
      if (!coffre.ouvert) {
        imageCoffre = IMG_Load("./textures/coffreClose.png");
      }
      else {
        imageCoffre = IMG_Load("./textures/coffreOpen.png");
      }
    }
    else {
      if (!coffre.ouvert) {
        imageCoffre = IMG_Load("./textures/coffreCloseLegendary.png");
      }
      else {
        imageCoffre = IMG_Load("./textures/coffreOpenLegendary.png");
      }
    }

    SDL_Texture * T_imageCoffre = SDL_CreateTextureFromSurface(rendu, imageCoffre);


    SDL_Rect R_imageCoffre = {coffre.salleX,coffre.salleY,TAILLE_TILE,TAILLE_TILE};

    SDL_RenderCopy(rendu, T_imageCoffre, NULL, &R_imageCoffre);

    SDL_DestroyTexture(T_imageCoffre);
    SDL_FreeSurface(imageCoffre);

}

/**
 * \brief Permet de gerer la collision d'un acteur avec un coffre
*/
int CollisionCoffre(int pX, int pY, int cX, int cY) {
    if (((cX+TAILLE_TILE >= (pX-TAILLE_TILE)) && (cX <= (pX+2*TAILLE_TILE))) && ((cY+TAILLE_TILE >= (pY-TAILLE_TILE)) && (cY <= (pY+2*TAILLE_TILE)))){
        return 1;
    }
    return 0;
}