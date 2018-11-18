#include <nds.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <list>

#include "map.h"

#include "hmap.h"
#include "Engine.hpp"
#include "rogueLike.h"
#include "ColliderMap.hpp"
#include "Collider.hpp"
#include "SpriteSheet.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "TBackground.hpp"
#include "BColliderMap.hpp"
#include "BMap.hpp"
#include "pixel_tiles.h"
#include "spaceinvaders.h"

#include "pal.h"
#include "img.h"

#include "Mode.hpp"


bool init_step(int);

SpriteSheet	spaceinvadersSheet((unsigned int *)spaceinvadersTiles, spaceinvadersTilesLen,
	pal, palLen,
	96, 160);
//global for game
TBackground	*bg;
TBackground	*bg2;
TBackground *bgs;
TBackground *bgs2;
Sprite		*a;
BColliderMap	*CMap;
BMap		*bMap;
bool    miss = false;
bool    jump = false;
int	    dt = 0;
float		v = 2.;
int		  sx = 0;
int     sxx = 0;
int		  bgx = 0;
vec2f		g_v = {2, 0};

int current_step = 1;
int vilain_dec = 0;
bool vilain_dir = false;
int missil_tour_tir = 0;
int life = 4;
bool mode_pause = false;
bool menu_screen = true;
int menu_time = 0;
bool bool_clignotement = true;

Sprite *monster1;
Sprite *monster2;
Sprite *monster3;

std::list<Sprite *> list_missil;
std::list<Sprite *> list_vilain;
std::list<Sprite *> list_blocks;
std::list<Sprite *> list_vilain_missil;
std::list<Sprite *> list_life;
std::list<Sprite *> list_menu;

//MAP

const u16	O = 1;
const u16	M = 12;

u16   mapV[] =
{
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
};

u16		mapA[] =
{
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, M, O, O, M, O, O, M, O, O, M, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
};

u16		mapB[] =
{
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, M, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, M, O, O, O, M, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, M, O, M, O, M, O, M, O, M, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
};

u16		mapC[] =
{
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, M, M, M, O, O, M, M, O, O, M, M, M, O, O,
	O, O, M, M, M, O, O, M, M, O, O, M, M, M, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
	O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
};

constexpr static int	nbMap = 3;

u16		*maps[nbMap] =
{
	&mapA[0],
	&mapB[0],
	&mapC[0],
};

bool		engineInit()
{
	bg = new TBackground(TBackground::MAIN, BgSize_T_512x256, &spaceinvadersSheet, TileLayer1, 16, 16, 1);
	bg2 = new TBackground(TBackground::MAIN, BgSize_T_512x256, &spaceinvadersSheet, TileLayer1, 16, 16, 0);
	bgs = new TBackground(TBackground::SUB, BgSize_T_512x256, &spaceinvadersSheet, TileLayer1, 16, 16, 1);
	bgs2 = new TBackground(TBackground::SUB, BgSize_T_512x256, &spaceinvadersSheet, TileLayer1, 16, 16, 0);

	BMap	mapBG({16, 16}, {2, 1}, true);

	bMap = new BMap({16, 16}, {2, 1}, true);
	CMap = new BColliderMap(bMap, {16, 16}, {M});

	mapBG.init(1);

	bMap->init(0);
	bMap->setMap(0, mapC);
	bMap->setMap(1, mapC);

	bg->addInMapT16(mapV, 16, 16, 0);
	bg->addInMapT16(mapV, 16, 16, 1);
	bg2->addInMapT16(mapBG.getData(), 16, 16, 0);
	bg2->addInMapT16(mapBG.getData(), 16, 16, 1);

	bgs->addInMapT16(mapV, 16, 16, 0);
	bgs->addInMapT16(mapV, 16, 16, 1);
	bgs2->addInMapT16(mapBG.getData(), 16, 16, 0);
	bgs2->addInMapT16(mapBG.getData(), 16, 16, 1);

	Sprite *monster1 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 2, Sprite::ABSOLUTE);
	monster1->setPos(128, 80);
	Sprite *monster2 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 3, Sprite::ABSOLUTE);
	monster2->setPos(128, 120);
	Sprite *monster3 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 5, Sprite::ABSOLUTE);
	monster3->setPos(128, 160);

	list_menu.push_back(monster1);
	list_menu.push_back(monster2);
	list_menu.push_back(monster3);

	//init_step(current_step++);


	return (true);
}


bool init_step(int step)
{
	int x = 0;
	int xx = 0;
	int y = 0;
	int imax = 0;
	int jmax = 0;
	int decx = 0;
	int decy = 0;
	int enemy = 0;

 //   //CHANGE BG MAIN
	if (step == 1) {
		bgs->addInMapT16(mapA, 16, 16, 0);
		bgs->addInMapT16(mapA, 16, 16, 1);
	} else if (step == 2) {
		bgs->addInMapT16(mapB, 16, 16, 0);
		bgs->addInMapT16(mapB, 16, 16, 1);
	} else if (step == 3) {
		bgs->addInMapT16(mapC, 16, 16, 0);
		bgs->addInMapT16(mapC, 16, 16, 1);
	}

//RESET LISTE MISSILES
	for (auto it=list_missil.begin(); it != list_missil.end();) {
		(*it)->destroy();
		it = list_missil.erase(it);
	}
//RESET POSITION JOUEUR   
	a->setPos(128, 180);
  //RESET LISTE ENEMIS
	for (auto it=list_vilain.begin(); it != list_vilain.end();) {
		(*it)->destroy();
		it = list_vilain.erase(it);
	}
//INITIALISATION DES POSITIONS ENEMIS EN FCT DU STEP
	if (step == 1) {
		jmax = 1;
		imax = 5;
		decx = 40;
		decy = 17;
		xx = 40;
		y = 51;
		enemy = 2;
	} else if (step == 2) {
		jmax = 2;
		imax = 7;
		decx = 35;
		decy = 17;
		xx = 15;
		y = 34;
		enemy = 3;
	} else if (step == 3) {
		jmax = 3;
		imax = 10;
		decx = 20;
		decy = 17;
		xx = 30;
		y = 17;
		enemy = 5;
	}

//CREATION ET PLACEMENT DES ENEMIS
	for (int j = 0; j < jmax; j++) {
		x = xx;
		for (int i = 0; i < imax; i++) {
			Sprite *vilain = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, enemy, Sprite::ABSOLUTE);
			vilain->setPos(x, y);
			list_vilain.push_back(vilain);
			x += decx;
		}
		y += decy;
	}

	return (true);
}

bool		enginePreUpdate()
{
	if (menu_screen == true) {
		if (menu_time == 25) {
			menu_time = 0;
			std::list<Sprite *>::iterator it = list_menu.begin();
			if (bool_clignotement == true) {
				if (current_step == 1) {
					(*it)->destroy();
					list_menu.erase(it);
				} else if (current_step == 2) {
					it++;
					(*it)->destroy();
					list_menu.erase(it);
				} else {
					it++; it++;
					(*it)->destroy();
					list_menu.erase(it);
				}
				bool_clignotement = false;
			} else {
				if (current_step == 1) {
					monster1 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 2, Sprite::ABSOLUTE);
					monster1->setPos(128, 80);
					list_menu.insert(it, monster1);
				} else if (current_step == 2) {
					it++;
					monster2 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 3, Sprite::ABSOLUTE);
					monster2->setPos(128, 120);
					list_menu.insert(it, monster2);
				} else {
					it++;it++;
					monster3 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 5, Sprite::ABSOLUTE);
					monster3->setPos(128, 160);
					list_menu.insert(it, monster3);
				}
				bool_clignotement = true;
			}
		} else 
		menu_time++;
	} else if (mode_pause == false) {

	//g_v = {v, 0};  
//DEPLACEMENTS ENEMIS
      int incr = 0; // VALEUR DE DEPLACEMENT DES SPRITES
      int decmax = 15; //VALEUR MAX DE DEPLACEMENT DROITE/GAUCHE (15 = VALEUR GENERIQUE)

      //BLOC POUR DEFINIR LE DECALAGE MAXIMUM EN FONCTION DE LA LARGEUR DU GROUPE DE MOSNTRES (A COMMENTER POUR USE VALEUR GENERIQUE)
      if (current_step == 2)
      	decmax = 25;
      else if (current_step == 3)
      	decmax = 15;
      else if (current_step == 4)
      	decmax = 20;


      if (vilain_dir == false) { //FALSE  = DEPLACEMENT VERS LA DROITE
        incr = 1; // VALEUR A AJOUTER A LA POS ENEMI SUR AXE X
        vilain_dec++; //VALEUR DU DECALAGE COURANT
      } else { // TRUE = DEPLACEMENT VERS LA GAUCHE
      	incr = -1;
      	vilain_dec--;
      }

      if (vilain_dec == decmax) { // SI VALEUR DU DECALAGE COURANT ATTEINT VALEUR MAX (BUTEE A DROITE)
        vilain_dir = true; //INVERSION DU SENS DE DEPLACEMENT
      } else if (vilain_dec == -decmax) { // SI VALEUR DU DECALAGE COURANT ATTEINT VALEUR MIN (BUTEE A GAUCHE)
        vilain_dir = false;// INVERSION DU SENS DE DEPLACEMENT
    }
  //MODIFICATION DES POSITIONS AVEC INCR SUR L'AXE X
    for (auto it=list_vilain.begin(); it != list_vilain.end(); ++it) {
    	(*it)->setPos((*it)->getPos().x + incr, (*it)->getPos().y);
    }
  //CREATION DES MISSILES ENEMIS
    if (missil_tour_tir == 100) {
    	missil_tour_tir = 0;
    	for (auto it=list_vilain.begin(); it != list_vilain.end(); ++it) {
    		if ((rand() % 10 + 0) > 5) {
    			Sprite *vilain_missil = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 0, Sprite::ABSOLUTE);
    			vilain_missil->setPos((*it)->getPos().x, (*it)->getPos().y + 16);
    			list_vilain_missil.push_back(vilain_missil);
    		}
    	}

    } else {
    	missil_tour_tir++;
    }

//DEPLACEMENTS MISSILES VILAINS
    for (auto it=list_vilain_missil.begin(); it != list_vilain_missil.end(); ++it) {
        if ((*it)->getPos().y < 186) // SI LE MISSILE EST ENTIEREMENT DANS L'ECRAN
           (*it)->setPos((*it)->getPos().x, (*it)->getPos().y + 2); // ON LE FAIT DESCENDRE (y + 2)
       else { 
           if ((*it)->getType() == "MAIN") { // SI IL ETAIT SUR L'ECRAN DU MAIN
             Sprite *vilain_missil = new Sprite(Sprite::SUB, SpriteSize_16x16, &spaceinvadersSheet, 0, Sprite::ABSOLUTE); //ON EN CREE UN NOUVEAU SUR L'ECRAN DU BAS
         vilain_missil->setPos((*it)->getPos().x, 0); 
             (*it)->destroy(); // oN SUPPRIME L'ANCIEN MISSILE
             (*it) = vilain_missil; //ON REMPLACE DANS LA LISTE PAR LE NOUVEAU 
         } else { // SI IL ETAIT SUR L'ECRAN DU BAS
             (*it)->destroy(); // ON LE DETRUIT
             it = list_vilain_missil.erase(it); //ON LE SUPPRIME DE LA LISTE
         }
     }
 }

//DEPLACEMENTS MISSILES
 for (auto it=list_missil.begin(); it != list_missil.end(); ++it) {
        if ((*it)->getPos().y > 0) // SI LE MISSILE EST ENTIEREMENT DANS L'ECRAN
           (*it)->setPos((*it)->getPos().x, (*it)->getPos().y - 2); // ON LE FAIT MONTER (y -2)
       else { 
           if ((*it)->getType() == "SUB") { // SI IL ETAIT SUR L'ECRAN DU BAS
             Sprite *missil = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 7, Sprite::ABSOLUTE); //ON EN CREE UN NOUVEAU SUR L'ECRAN DU HAUT
         missil->setPos((*it)->getPos().x, (*it)->getPos().y + 180); 
             (*it)->destroy(); // oN SUPPRIME L'ANCIEN MISSILE
             (*it) = missil; //ON REMPLACE DANS LA LISTE PAR LE NOUVEAU 
         } else { // SI IL ETAIT SUR L'ECRAN DU HAUT
             (*it)->destroy(); // ON LE DETRUIT
             it = list_missil.erase(it); //ON LE SUPPRIME DE LA LISTE
         }
     }
 }

}
return (true);
}
bool		engineUpdate()
{
	
  // static int	bmap = 0;
  // static bool	b = false;
	return (true);
}

void		keyUUp()
{
	if (menu_screen == true) {
		current_step -= 1;
		if (current_step < 1)
			current_step = 1;
		for (auto it=list_menu.begin(); it != list_menu.end();) {
			(*it)->destroy();
			it = list_menu.erase(it);
		}
		menu_time = 0;
		bool_clignotement = true;		
		Sprite *monster1 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 2, Sprite::ABSOLUTE);
		monster1->setPos(128, 80);
		Sprite *monster2 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 3, Sprite::ABSOLUTE);
		monster2->setPos(128, 120);
		Sprite *monster3 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 5, Sprite::ABSOLUTE);
		monster3->setPos(128, 160);

		list_menu.push_back(monster1);
		list_menu.push_back(monster2);
		list_menu.push_back(monster3);
	}
}

void    	keyUDown()
{
	if (menu_screen == true) {
		current_step += 1;
		if (current_step > 3)
			current_step = 3;
		for (auto it=list_menu.begin(); it != list_menu.end();) {
			(*it)->destroy();
			it = list_menu.erase(it);
		}
		menu_time = 0;
		bool_clignotement = true;		
		Sprite *monster1 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 2, Sprite::ABSOLUTE);
		monster1->setPos(128, 80);
		Sprite *monster2 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 3, Sprite::ABSOLUTE);
		monster2->setPos(128, 120);
		Sprite *monster3 = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 5, Sprite::ABSOLUTE);
		monster3->setPos(128, 160);

		list_menu.push_back(monster1);
		list_menu.push_back(monster2);
		list_menu.push_back(monster3);
	}
}

void    	keyUA()
{
	if (mode_pause == false) {
		Sprite *missil = new Sprite(Sprite::SUB, SpriteSize_16x16, &spaceinvadersSheet, 7, Sprite::ABSOLUTE);
		missil->setPos(a->getPos().x, a->getPos().y - 16);
		missil->addCollider({1, 1}, {14, 14}, CMap);
		list_missil.push_back(missil);
	}
}

void    	keyUStart()
{
	mode_pause = !(mode_pause);
}

void keyUX() 
{	
	if (menu_screen == true) {
		menu_screen = false;
		a = new Sprite(Sprite::SUB, SpriteSize_16x16, &spaceinvadersSheet, 4, Sprite::ABSOLUTE);
		a->setPos(128, 180);
		a->addCollider({1, 1}, {14, 14}, CMap);

		int x = 240;

		for (int i = 1; i <= life; i++) {
			Sprite *heart = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 13, Sprite::ABSOLUTE);
			heart->setPos(x, 1);
			list_life.push_back(heart);
			x -= 17;
		}

		for (auto it=list_menu.begin(); it != list_menu.end();) {
			(*it)->destroy();
			it = list_menu.erase(it);
		}
		init_step(current_step);
	}
}




void    keyUY()
{
	//GESTION DES POINTS DE VIES (AFFICHAGE DES COEURS)
	life--;
	for (auto it=list_life.begin(); it != list_life.end();) {
		(*it)->destroy();
		it = list_life.erase(it);
	}

	int x = 240;
	for (int i = 1; i <= life; i++) {
		Sprite *heart = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 13, Sprite::ABSOLUTE);
		heart->setPos(x, 1);
		list_life.push_back(heart);
		x -= 17;
	}
}

void    keyUB()
{
	//PASSAGE AU LVL SUIVANT

	vilain_dec = 0;
	if (current_step == 4)
		current_step = 1;
	init_step(current_step++);
}


void		keyRight()
{
	if (mode_pause == false) {
		if (a->getPos().x < 240)
			a->setPos(a->getPos().x + v, a->getPos().y);
	}
}

void		keyLeft()
{
	if (mode_pause == false) {
		if (a->getPos().x > 1)
			a->setPos(a->getPos().x - v, a->getPos().y);
	}
}

int		main()
{
	Engine	engine;

	engine.start();
	return (0);
}
