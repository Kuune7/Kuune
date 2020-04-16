#include "const.h"

/**
 * \file const.c
 * \brief Fichier contenant des fonctions qui nous seront utile dans tout les domaines
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/**
 *	\brief Fonction permettant de savoir les coordonnées x et y se trouve bien dans le labyrinthe 
 *	\return Vrai ou Faux
 */
int valide (int x, int y) {
	return ((x >= 0 && x < M) && (y >= 0 && y < N));
}


/**
 *	\brief Fonction permettant de savoir les coordonnées x et y se trouve bien dans la salle 
 *	\return Vrai ou Faux
 */
int valideSalle (int x, int y) {
	return ((x >= 0 && x < LARGEUR_ECRAN-TAILLE_TILE) && (y >= 0 && y < HAUTEUR_ECRAN-TAILLE_TILE));
}


/**
 * \brief Fonction permettant de savoir si les coordonnées x et y se trouve sous la minimap
* \return Vrai ou Faux
*/
int verifMinimap(int x, int y) {
	return (x > TAILLE_SALLE_X*TAILLE_TILE-7*TAILLE_TILE && y < 4*TAILLE_TILE);
}


/**
 * \brief Fonction permettant de savoir si les coordonnées x et y se trouve sous la bar de vie
 * \return Vrai ou Faux
 */
int verifHealthBar(int x, int y) {
	return ((x < 7*TAILLE_TILE) && (y > TAILLE_SALLE_Y*TAILLE_TILE - 4*TAILLE_TILE) && (y < TAILLE_SALLE_Y*TAILLE_TILE));
}


/**
 * \brief Permet d'afficher une immage
 * \details Si w et/ou h == 0 alors on prend la taille de l image d origine
 */
void AfficherImage(SDL_Renderer * rendu, int x, int y, int w, int h, const char nom[50]) {

    SDL_Surface * S_image = IMG_Load(nom);
    SDL_Texture * T_image = SDL_CreateTextureFromSurface(rendu, S_image);
    SDL_Rect R_image = {x,y,w,h};

	int tw, th;
    SDL_QueryTexture(T_image, NULL, NULL, &tw, &th);
	if (!w) {
		R_image.w = tw;
	}
	if (!h) {
		R_image.h = th;
	}
    SDL_RenderCopy(rendu, T_image, NULL, &R_image);

    SDL_FreeSurface(S_image);
    SDL_DestroyTexture(T_image);
	S_image = NULL;
	T_image = NULL;
}

/**
 * \brief Permet d'afficher une zone de texte
 */
void AfficherTexte(SDL_Renderer * rendu, TTF_Font * police, SDL_Color couleur, int x, int y, char texte[128]) {

    SDL_Surface * S_texte = TTF_RenderText_Solid(police, texte, couleur);
    SDL_Texture * T_texte = SDL_CreateTextureFromSurface(rendu, S_texte);
	SDL_Rect R_texte = {x, y, 0, 0};

    SDL_QueryTexture(T_texte, NULL, NULL, &R_texte.w, &R_texte.h);
    SDL_RenderCopy(rendu, T_texte, NULL, &R_texte);

    SDL_DestroyTexture(T_texte);
    SDL_FreeSurface(S_texte);
	T_texte = NULL;
	S_texte = NULL;
}