#include "menu.h"
#include "saveload.h"
#include <unistd.h>

/**
 * \file menu.c
 * \brief Fichier contenant des fonctions nous permettant de gérer la création et l'affichage des différents menus
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/**
 * \brief Permet d'afficher les informations sur l'HUD avant de lancer une nouvelle partie
 */
void AfficherInstructions(SDL_Renderer * rendu) {
    AfficherImage(rendu, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN, "./img/instruction.png");
    SDL_RenderPresent(rendu);
    sleep(10);
}

/**
 * \brief Permet d'afficher le menu affichants les différentes règles du jeu
*/
void AfficherMenuRegles (SDL_Renderer * rendu) {
    
    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    AfficherImage(rendu, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN, "./img/fondecran.jpg");
    AfficherImage(rendu, LARGEUR_ECRAN/2 - 738/2, ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-78/2, 0, 0, "./img/ROGUELIKE.png");

    SDL_Rect R_Cadre = {0,240,LARGEUR_ECRAN,350};
    SDL_SetRenderDrawColor (rendu, 0, 0, 0, 255);
    SDL_RenderFillRect(rendu, &R_Cadre);


    /************************************************************************************/
    TTF_Font * police = TTF_OpenFont("Font.ttf", 30);
    SDL_Color couleur = {255, 255, 255};

    AfficherTexte(rendu, police, couleur, 10, 250, "Bienvenu dans The Forgotten !");
    AfficherTexte(rendu, police, couleur, 10, 310, "The Forgotten est un jeu original developpe en langage C a ");
    AfficherTexte(rendu, police, couleur, 10, 340, "l aide de la bibliotheque SDL2. C est un jeu de type Roguelike ou ");
    AfficherTexte(rendu, police, couleur, 10, 370, "vous incarnez Lazar, un jeune chevalier perdu dans un donjon ");
    AfficherTexte(rendu, police, couleur, 10, 400, "rempli de dangereux ennemis. Le but est de progresser a travers ");
    AfficherTexte(rendu, police, couleur, 10, 430, "les differents etages du donjon, recolter les coffres afin de ");
    AfficherTexte(rendu, police, couleur, 10, 460, "devenir plus puissant et eliminer tous les ennemis !");
    AfficherTexte(rendu, police, couleur, 10, 490, "Ce projet est realise dans le cadre de la licence 2 ");
    AfficherTexte(rendu, police, couleur, 10, 550, "Informatique de l Universite du Mans.");

    TTF_CloseFont(police);
    police = NULL;

    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    AfficherImage(rendu, LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 0, 0, "./img/return.png");
}


/**
	\brief Permet d'afficher le menu Principal
*/
void AfficherMenuPrincipal(SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    AfficherImage(rendu, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN, "./img/fondecran.jpg");
    AfficherImage(rendu, LARGEUR_ECRAN/2 - 738/2, ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-78/2, 0, 0, "./img/ROGUELIKE.png");

    /************************************************************************************/

    int ecartCase = TAILLE_BUTTON_MENU_PRINCIPAL_Y + 55;

    SDL_Rect rect = {0, 0, TAILLE_BUTTON_MENU_PRINCIPAL_X, TAILLE_BUTTON_MENU_PRINCIPAL_Y};

    rect.x = LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2;
    rect.y = (HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100;

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor (rendu, 100, 100, 100, 200);

    for (int i = 0 ; i < NB_BUTTON_MENU_PRINCIPAL ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += ecartCase;
    }


    SDL_Color couleur = {255, 255, 255};

    int x = rect.x + 55;
    int y = HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 15 + 100;
    AfficherTexte(rendu, police, couleur, x, y, "Nouvelle Partie");
    y += ecartCase;
    AfficherTexte(rendu, police, couleur, x, y, "Charger Partie");
    y += ecartCase;
    x += 125;
    AfficherTexte(rendu, police, couleur, x, y, "Quitter");

    TTF_Font * createurs = TTF_OpenFont("Font.ttf", 30);
    AfficherTexte(rendu, createurs, couleur, 10, HAUTEUR_ECRAN - 50, "Cree par Henry Allan, Ster Maxime, Zheng Haoran, Gaisne Maxime");
    TTF_CloseFont(createurs);

    /******************** AFFICHE LE BOUTON SETTING EN BAS A DROITE ***************************/
    
    AfficherImage(rendu, LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 0, 0, "./img/setting.png");

}


/**
	\brief Permet d'afficher le menu Charger Partie
*/
void AfficherMenuChargerPartie(SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    FILE * fichier;

    AfficherImage(rendu, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN, "./img/fondecran.jpg");
    AfficherImage(rendu, LARGEUR_ECRAN/2 - 738/2, ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-78/2, 0, 0, "./img/ROGUELIKE.png");

    /************************************************************************************/

    int ecartCase = TAILLE_BUTTON_MENU_PRINCIPAL_Y + 55;

    //Rectangle plein
    // {posX, posY, TAILLE_X, TAILLE_Y}
    SDL_Rect rect = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2, (HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100, TAILLE_BUTTON_MENU_PRINCIPAL_X, TAILLE_BUTTON_MENU_PRINCIPAL_Y};

    SDL_SetRenderDrawColor (rendu, 100, 100, 100, 200);

    for (int i = 0 ; i < NB_BUTTON_MENU_PRINCIPAL ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += ecartCase;
    }

    SDL_Color couleur = {255, 255, 255};

    int x = rect.x + 75;
    int y = HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 15 + 100;
    AfficherTexte(rendu, police, couleur, x, y, "Sauvegarde 1");
    y += ecartCase;
    AfficherTexte(rendu, police, couleur, x, y, "Sauvegarde 2");
    y += ecartCase;
    AfficherTexte(rendu, police, couleur, x, y, "Sauvegarde 3");

    SDL_SetRenderDrawColor (rendu, 20, 20, 20, 100);

    //On va assombrir les boutons si aucune sauvegarde n°x est trouver
    rect.y = (HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100;
    rect.x = LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2;
    rect.w = TAILLE_BUTTON_MENU_PRINCIPAL_X;
    rect.h = TAILLE_BUTTON_MENU_PRINCIPAL_Y;
    fichier = fopen("./saves/Save1.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }

    rect.y += ecartCase;
    fichier = fopen("./saves/Save2.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }

    rect.y += ecartCase;
    fichier = fopen("./saves/Save3.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }


    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    AfficherImage(rendu, LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 0, 0, "./img/return.png");

}

/**
 * \brief Permet d'afficher le menu du volume
 */
void AfficherMenuVolume (SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/
    
    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    AfficherImage(rendu, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN, "./img/fondecran.jpg");
    AfficherImage(rendu, LARGEUR_ECRAN/2 - 738/2, ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-78/2, 0, 0, "./img/ROGUELIKE.png");

    /************************************************************************************/


    SDL_SetRenderDrawColor (rendu, 20, 20, 20, 100);
    SDL_Rect sliderVolume = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2, HAUTEUR_ECRAN/2 - 13, TAILLE_BUTTON_MENU_PRINCIPAL_X, 26};
    SDL_RenderFillRect(rendu, &sliderVolume);

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    float pourcentageVie = (float)VOLUME/MIX_MAX_VOLUME;
    sliderVolume.w = TAILLE_BUTTON_MENU_PRINCIPAL_X * pourcentageVie;
    SDL_RenderFillRect(rendu, &sliderVolume);


    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    AfficherImage(rendu, LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 0, 0, "./img/return.png");
}


/**
	\brief Permet d'afficher le menu option
*/
void AfficherMenuSetting(SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    AfficherImage(rendu, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN, "./img/fondecran.jpg");
    AfficherImage(rendu, LARGEUR_ECRAN/2 - 738/2, ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-78/2, 0, 0, "./img/ROGUELIKE.png");

    /************************************************************************************/

    int ecartCase = TAILLE_BUTTON_MENU_PRINCIPAL_Y + 55;

    SDL_Rect rect = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2, (HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100, TAILLE_BUTTON_MENU_PRINCIPAL_X, TAILLE_BUTTON_MENU_PRINCIPAL_Y};

    SDL_SetRenderDrawColor (rendu, 100, 100, 100, 200);

    for (int i = 0 ; i < NB_BUTTON_MENU_PRINCIPAL ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += ecartCase;
    }

    SDL_Color couleur = {255, 255, 255};

    int x = rect.x + 150;
    int y = HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 115;
    AfficherTexte(rendu, police, couleur, x, y, "Touches");
    y += ecartCase;
    x += 30;
    AfficherTexte(rendu, police, couleur, x, y, "Volume");
    y += ecartCase;
    x += 5;
    AfficherTexte(rendu, police, couleur, x, y, "Regles");


    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    AfficherImage(rendu, LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 0, 0, "./img/return.png");

}

/**
 * \brief Fonction permettant de gerer l'affiche du menu des touches
 */
void AfficherMenuTouches(SDL_Renderer * rendu) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/
    
    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    AfficherImage(rendu, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN, "./img/fondecran.jpg");
    AfficherImage(rendu, LARGEUR_ECRAN/2 - 738/2, ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-78/2, 0, 0, "./img/ROGUELIKE.png");

    /************************************************************************************/

    SDL_SetRenderDrawColor (rendu, 100, 100, 100, 200);

    SDL_Rect R_Cadre = {0,240,LARGEUR_ECRAN,350};
    SDL_SetRenderDrawColor (rendu, 0, 0, 0, 255);
    SDL_RenderFillRect(rendu, &R_Cadre);

    TTF_Font * police = TTF_OpenFont("Font.ttf", 30);
    SDL_Color couleur = {255, 255, 255};
    int x = 50, y = 250, ecartTouches = 50;
    AfficherTexte(rendu, police, couleur, x, y, "Haut");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Bas");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Gauche");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Droite");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Menu");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Attaquer");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Ouvrir coffre");

    x = LARGEUR_ECRAN/2;
    y = 250;
    AfficherTexte(rendu, police, couleur, x, y, "Z");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "S");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Q");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "D");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Echap");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "Clique Souri Gauche");
    y += ecartTouches;
    AfficherTexte(rendu, police, couleur, x, y, "F");

    TTF_CloseFont(police);
    police = NULL;

    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    AfficherImage(rendu, LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 0, 0, "./img/return.png");
}


/**
    \brief Permet, dans le menu choisi, de séléctionner une intéraction en cliquant sur un des boutons
*/
Menu choixMenu (Menu menuActuel) {

    
	SDL_Event event;
	SDL_PollEvent(&event);

	//Menu principal #1
	if (menuActuel == Principal) {
		switch (event.type) {
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:		
						if ((event.button.y >= 250 && event.button.y <= 350) && (event.button.x >= 200 && event.button.x <= 800)) { //Bouton 1
							return New;
						}
						else if ((event.button.y >= 410 && event.button.y <= 510) && (event.button.x >= 200 && event.button.x <= 800)) { //Bouton 2
							return Load;
						}
						else if ((event.button.y >= 565 && event.button.y <= 660) && (event.button.x >= 200 && event.button.x <= 800)) { //Bouton 3
							return Quit;
						}
                        else if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton Setting
                            return Setting;
                        }
						break;
					default:
						break;
				}
				break;
			case SDL_QUIT:
				return Quit;
			default:
				return Principal;
		}
	}
    else if (menuActuel == Load) {
        FILE * fichier;
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                    	if ((event.button.y >= 250 && event.button.y <= 350) && (event.button.x >= 200 && event.button.x <= 800)) { //Save 1
                            fichier = fopen("./saves/Save1.txt", "r");
                            if (fichier != NULL) {
                                fclose(fichier);
                                return Save1; 
                            }
						}
						else if ((event.button.y >= 410 && event.button.y <= 510) && (event.button.x >= 200 && event.button.x <= 800)) { //Save 2
							fichier = fopen("./saves/Save2.txt", "r");
                            if (fichier != NULL) {
                                fclose(fichier);
                                return Save2; 
                            }
						}
						else if ((event.button.y >= 560 && event.button.y <= 660) && (event.button.x >= 200 && event.button.x <= 800)) { //Save 3
							fichier = fopen("./saves/Save3.txt", "r");
                            if (fichier != NULL) {
                                fclose(fichier);
                                return Save3; 
                            }
						}
                        else if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Principal;
                        }
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Load;
                break;
        }
    }
    else if (menuActuel == Setting) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                    	if ((event.button.y >= 250 && event.button.y <= 350) && (event.button.x >= 200 && event.button.x <= 800)) { //Touches
                            return Touches;
						}
						else if ((event.button.y >= 410 && event.button.y <= 510) && (event.button.x >= 200 && event.button.x <= 800)) { //Volume
							return Volume;
						}
						else if ((event.button.y >= 560 && event.button.y <= 660) && (event.button.x >= 200 && event.button.x <= 800)) { //Save 3
							return Regle;
						}
                        else if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Principal;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Setting;
                break;
        }
    }
    else if (menuActuel == Volume) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if (event.button.x >= 200 && event.button.x <= 800 && event.button.y > 367 && event.button.y < 393) {
                            int choix = event.button.x - 200;
                            VOLUME = (choix * MIX_MAX_VOLUME)/TAILLE_BUTTON_MENU_PRINCIPAL_X;
                            Mix_VolumeMusic(VOLUME);
                            SauvegarderSon();
                        }
                        else if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Setting;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Volume; 
                break;
        }
    }
    else if (menuActuel == Touches) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Setting;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Touches;
        }
    }
    else if (menuActuel == Regle) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Setting;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Regle;
        }
    }

	return Aucun;
}








/******************** IN GAME ********************/


/** \brief Nous permet d'afficher le menu de sauvegarde en jeu*/
void AfficherMenuSauvegardeIG (SDL_Renderer * rendu, TTF_Font * police) {

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_Color couleur = {255, 255, 255};
    SDL_Rect rect = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_IG_X/2, (HAUTEUR_ECRAN/NB_BUTTON_MENU_IG) - TAILLE_BUTTON_MENU_PRINCIPAL_Y, TAILLE_BUTTON_MENU_IG_X, TAILLE_BUTTON_MENU_IG_Y};

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 200);

    for (int i = 0 ; i < 3 ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += 150;
    }

    int x = rect.x + 10;
    int y = (HAUTEUR_ECRAN/NB_BUTTON_MENU_IG) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 15;
    AfficherTexte(rendu, police, couleur, x, y, "Sauvegarde 1");
    y += 150;
    AfficherTexte(rendu, police, couleur, x, y, "Sauvegarde 2");
    y += 150;
    AfficherTexte(rendu, police, couleur, x, y, "Sauvegarde 3");



    SDL_SetRenderDrawColor (rendu, 20, 20, 20, 100);
    FILE * fichier = NULL;

    rect.y = (HAUTEUR_ECRAN/NB_BUTTON_MENU_IG) - TAILLE_BUTTON_MENU_IG_Y;
    rect.w = TAILLE_BUTTON_MENU_IG_X;
    rect.h = TAILLE_BUTTON_MENU_IG_Y;
    fichier = fopen("./saves/Save1.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }

    rect.y += 150;
    fichier = fopen("./saves/Save2.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }

    rect.y += 150;
    fichier = fopen("./saves/Save3.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }


    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 200);

    SDL_Rect rectReturn = {LARGEUR_ECRAN - 300, HAUTEUR_ECRAN - 150, rect.w/2, rect.h} ;
    SDL_RenderFillRect(rendu, &rectReturn);

    AfficherTexte(rendu, police, couleur, rectReturn.x + 5, rectReturn.y + 15, "Retour");

    SDL_RenderPresent(rendu);
}




/**
    \brief Affichage du menu en jeu
*/
void AfficherMenuIG(SDL_Renderer * rendu, TTF_Font * police) {

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_Color couleur = {255, 255, 255};
    SDL_Rect rect = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_IG_X/2, (HAUTEUR_ECRAN/NB_BUTTON_MENU_IG) - TAILLE_BUTTON_MENU_PRINCIPAL_Y, TAILLE_BUTTON_MENU_IG_X, TAILLE_BUTTON_MENU_IG_Y};

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 200);

    for (int i = 0 ; i < 3 ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += 150;
    }

    int x = rect.x + 55;
    int y = (HAUTEUR_ECRAN/NB_BUTTON_MENU_IG) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 15;
    AfficherTexte(rendu, police, couleur, x, y, "Reprendre");
    y += 150;
    x -= 40;
    AfficherTexte(rendu, police, couleur, x, y, "Sauvegarder");
    y += 150;
    x += 90;
    AfficherTexte(rendu, police, couleur, x, y, "Quitter");

    SDL_RenderPresent(rendu);
}


/**
 * \brief Permet de gerer les actions dans le menu du jeu en partie
 * \return Le menu actuel 
*/
MenuIG choixMenuIG (SDL_Renderer * rendu, TTF_Font * police, MenuIG menuActuel) {

    SDL_Event event;

    //On ne change rien au jeu tant que le joueur reste dans le menu
    SDL_PollEvent(&event);

    if (menuActuel == Premier) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if (event.button.y >= 150 && event.button.y <= 250 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton resume
                            return Resume;
                        }
                        else if (event.button.y >= 320 && event.button.y <= 420 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton save
                           return Sauvegarde;
                        }
                        else if (event.button.y >= 490 && event.button.y <= 590 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton quit
                            return ReturnMenu;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN: //Si le joueur appuie sur ECHAP alors le jeu reprend
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return Resume;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quitter;
            default:
                break;
        }
    } 
    else if (menuActuel == Sauvegarde) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if (event.button.y >= 150 && event.button.y <= 250 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton save1
                            return Sauvegarde1;
                        }
                        else if (event.button.y >= 320 && event.button.y <= 420 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton save2
                            return Sauvegarde2;
                        }
                        else if (event.button.y >= 490 && event.button.y <= 590 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton save3
                            return Sauvegarde3;
                        }
                        else if (event.button.y >= 600 && event.button.y <= 700 && event.button.x >= 705 && event.button.x <= 925) { //Si clic sur bouton return
                            return Premier;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN: //Si le joueur appuie sur ECHAP alors le jeu reprend
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return Resume;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quitter;
                break;
            default:
                break;
        }
    }

    return 0;
}