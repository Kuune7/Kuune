#ifndef __SPRITE__
#define __SPRITE__

/**
 * \file sprite.h
 * \brief Fichier contenant les prototypes des fonctions concernant les sprites
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 20/03/2020
*/

#include "animation.h"


Sprite * InitSprite(Animation * An, int x, int y);
void MouvementSpritePlayer(Sprite * sp, Player player, Status stat);
void MouvementSpriteMob(Sprite * sp, Monstre mob, Status stat);
void LibererSprite (Sprite * sp);

#endif