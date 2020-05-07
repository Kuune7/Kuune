#include <unistd.h>
#include "son.h"
#include "perso.h"
#include "saveload.h"
#include "monstre.h"
#include "objet.h"

/**
 * \file roguelike.c
 * \brief Fichier contenant la fonction main de notre programme
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/

/** \brief Permet de savoir si le joueur est dans un menu ou non*/
int inGame = 0;
/** \brief Permet de savoir si le joueur est en partie ou non */
int inMenu = 1;

/** \brief Permet de savoir dans quel menu le joueur se trouve (si il est dans un menu)*/
Menu menuActuel = Principal;

/** \brief Permet de savoir dans quel niveau le joueur se trouve*/
int levelActuel = 1;



/**
 * \brief Permet de gerer tout l'affichage du jeu
*/
void Affichage(SDL_Renderer * rendu, TTF_Font * police, Salle salle[N][M], Player player) {

	AfficherSalle(rendu, salle[player.labY][player.labX], player, levelActuel);

	for (int i = 0 ; i < salle[player.labY][player.labX].nbCoffre ; i++) {
		AfficherCoffre(rendu, salle[player.labY][player.labX].coffre[i]);
	}

	//AfficherPlayerSalle(rendu, player);
	AffichageAnimation(player.An, rendu, player.sp->sens, (int)player.sp->stat, player.sp->x, player.sp->y, 0);
	
	for (int i = 0 ; i < salle[player.labY][player.labX].nbMonstres ; i++) {
		AfficherMobHUD(rendu, salle[player.labY][player.labX].monstre[i]);
		AffichageAnimation(salle[player.labY][player.labX].monstre[i].An, rendu, salle[player.labY][player.labX].monstre[i].sp->sens, (int)salle[player.labY][player.labX].monstre[i].sp->stat, salle[player.labY][player.labX].monstre[i].sp->x, salle[player.labY][player.labX].monstre[i].sp->y, salle[player.labY][player.labX].monstre[i].bossFinal);
	}

	AfficherMinimap(rendu, salle, player);
	AfficherHUD(rendu, salle, player);
}



/**
 * \brief Fonction main du programme
 */
int main(int argc, char ** argv) {

	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window *screen = SDL_CreateWindow("RogueLike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_SWSURFACE);
	SDL_Renderer * rendu = SDL_CreateRenderer(screen, -1, 0);
	SDL_Surface * icon = SDL_LoadBMP("img/Icon.bmp");
	SDL_SetWindowIcon(screen, icon);
	SDL_FreeSurface(icon);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);


	TTF_Font * police = TTF_OpenFont("Font.ttf", 65);

	Salle salle[N][M];

	Input in;
	Player player;
	player.sp = NULL;
	player.An = NULL;

	Labyrinthe labyrinthe;

	VOLUME = MIX_MAX_VOLUME/2;
	ChargerSon();

	//Initialisation nécessaire
	InitEvents(&in);
	InitMatSalle(salle);

	while (!in.quit) {

		//On va lancer la musique du menu en s'assurant de stoper les sons deja present sur le canal
		if (background != NULL) {
			Mix_FreeChunk(background);
			background= NULL;
		}
		background = Mix_LoadWAV("./sounds/mainpage.wav");
		Mix_PlayChannel(-1,background, -1);
		Mix_VolumeMusic(VOLUME);

		//Durant que le joueur est dans les menus principaux du jeu
		while (inMenu && !in.quit) {

			Menu choix = choixMenu(menuActuel);

			switch (choix) {
				case Principal:
					menuActuel = Principal;
					AfficherMenuPrincipal(rendu, police);
					break;
				case New:
					inMenu = 0;
					inGame = 1;
					initLab(&labyrinthe);
					initPlayer(&player, screen, "player.txt", 0, 0, LARGEUR_ECRAN/2 - TAILLE_TILE/2, HAUTEUR_ECRAN/2 - TAILLE_TILE/2);
					initSalle(screen, salle, labyrinthe.mat, player, levelActuel);
					int lX, lY;
					CheminLePlusLong(labyrinthe, &lX, &lY);
					InitialisationBoss(screen, &salle[lY][lX], salle[player.labY][player.labX]);
					levelActuel = 1;
					salle[player.labY][player.labX].explorer = 1;
					AfficherInstructions(rendu);
					break;
				case Load:
					menuActuel = Load;
					AfficherMenuChargerPartie(rendu, police);
					break;
				case Quit:
					in.quit = 1;
					break;
				case Setting:
					menuActuel = Setting;
					AfficherMenuSetting(rendu, police);
					break;
				case Volume:
					menuActuel = Volume;
					AfficherMenuVolume(rendu, police);
					break;
				case Save1:
					inMenu = 0;
					inGame = 1;
					ChargerPartie("./saves/Save1.txt", &labyrinthe, &player, salle, &levelActuel);
					ChargerLab(&labyrinthe);
					ChargerPlayer(screen, &player, "player.txt");
					ChargerMob(screen, salle, levelActuel);
					CheminLePlusLong(labyrinthe, &lX, &lY);
					InitialisationBoss(screen, &salle[lY][lX], salle[player.labY][player.labX]);
					break;
				case Save2:
					inMenu = 0;
					inGame = 1;
					ChargerPartie("./saves/Save2.txt", &labyrinthe, &player, salle, &levelActuel);
					ChargerLab(&labyrinthe);
					ChargerPlayer(screen, &player, "player.txt");
					ChargerMob(screen, salle, levelActuel);
					CheminLePlusLong(labyrinthe, &lX, &lY);
					InitialisationBoss(screen, &salle[lY][lX], salle[player.labY][player.labX]);
					break;
				case Save3:
					inMenu = 0;
					inGame = 1;
					ChargerPartie("./saves/Save3.txt", &labyrinthe, &player, salle, &levelActuel);
					ChargerLab(&labyrinthe);
					ChargerPlayer(screen, &player, "player.txt");
					ChargerMob(screen, salle, levelActuel);
					CheminLePlusLong(labyrinthe, &lX, &lY);
					InitialisationBoss(screen, &salle[lY][lX], salle[player.labY][player.labX]);
					break;
				case Touches:
					menuActuel = Touches;
					AfficherMenuTouches(rendu);
					break;
				case Regle:
					menuActuel = Regle;
					AfficherMenuRegles(rendu);
					break;
				default:
					break;
			}
			SDL_RenderPresent(rendu);
			SDL_Delay(2);
		}

		//On va eteindre la musique du menu si on entre le jeu et elle est encore lancer
		if (background != NULL) {
			Mix_FreeChunk(background);
			background= NULL;
		}
		background = Mix_LoadWAV("./sounds/donjon_salle.wav");
		Mix_PlayChannel(-1,background, -1);

		//Durant que le joueur est en partie
		while (inGame && !in.quit) {
			
			UpdateEvents(&in);

			if (ActionSalle(&in, rendu, police, &player, salle[player.labY][player.labX], &inGame, &inMenu, &levelActuel, &menuActuel, salle, labyrinthe)) { //Si on doit up de lvl		
				if (sound != NULL) {
					Mix_FreeMusic(sound);
					sound = NULL;
				}

				LibererPlayer(&player);
				LibererMonstres(salle);
				
				if (levelActuel <= 4) {
					Player p;
					p = player;
					initPlayer(&player, screen, "player.txt", 0, 0, LARGEUR_ECRAN/2 - TAILLE_TILE/2, HAUTEUR_ECRAN/2 - TAILLE_TILE/2);
					player.damage = p.damage;
					player.def = p.def;
					player.hp_max = player.hp = p.hp_max*levelActuel;

					InitMatSalle(salle);
					initSalle(screen, salle, labyrinthe.mat, player, levelActuel);
					salle[player.labY][player.labX].explorer = 1;
					int lX, lY;
					CheminLePlusLong(labyrinthe, &lX, &lY);
					InitialisationBoss(screen, &salle[lY][lX], salle[player.labY][player.labX]);
				}	
				else {
					SDL_Color couleur = {255, 255, 255};
					SDL_Surface * surface = TTF_RenderText_Solid(police, "Bravo tu as gagner !", couleur);
					SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, surface);
					int texW = 0, texH = 0;
					SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
					SDL_Rect dstrect = {LARGEUR_ECRAN/2 - texW/2, HAUTEUR_ECRAN/2 - texH/2, texW, texH };
					SDL_RenderCopy(rendu, texture, NULL, &dstrect);
					SDL_DestroyTexture(texture);
					SDL_FreeSurface(surface);

					SDL_RenderPresent(rendu);
					sleep(3);

					inGame = 0;
					inMenu = 1;
				}

				initLab(&labyrinthe);
			}

			if (inGame) {
				PassagePorte(salle, &player);

				if (EvolutionMonstres(salle, player, &player)) {
					MortPlayer(&player, rendu, screen, salle, &labyrinthe, police, &levelActuel);
				}

				Affichage(rendu, police, salle, player);

				SDL_RenderPresent(rendu);
				SDL_Delay(2);
			}
		}
		
		LibererPlayer(&player);
		LibererMonstres(salle);
	}
	if (background != NULL){
		Mix_FreeChunk(background);
	}
	if (action != NULL){
		Mix_FreeChunk(action);
	}

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
