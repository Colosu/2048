/*
 * ControladorAutomatico.cpp
 *
 *  Created on: 16 de may. de 2016
 *      Author: colosu
 */

#include "ControladorAutomatico.h"
#include "Partida.h"
#include "GameTreePlayer.h"
#include "include/SDL2/SDL.h"
#include "Config.h"


ControladorAutomatico::ControladorAutomatico(Partida* party) {

	partida = party;
	inicio = false;
	X = 0;
	Y = 0;
	tree = NULL;
}

ControladorAutomatico::~ControladorAutomatico() {

	if (tree != NULL) {
		delete tree;
		tree = NULL;
	}
}

Partida* ControladorAutomatico::getPartida() {
	return partida;
}

bool ControladorAutomatico::detectMove() {

	SDL_Event evento;
	bool finalizar = false;
	int moves = 0;
	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT) { //Cierra la ventana con la X
			finalizar = true;
		}
	}
	//Ejecución automática

	if (partida->getMax() == 0 || inicio) {
		if (!inicio) {
			moves = partida->moveUp();
			inicio = true;
		} else {
			moves = partida->moveLeft();
			inicio = false;
		}
	} else {

		direction dir;
		Partida* party = new Partida();
		*party = *partida;
		tree = new GameTreePlayer(party, SEARCH_DEEP, 0);
		tree->setChilds();
		dir = tree->chooseChild();
		delete tree;
		tree = NULL;
		if (dir == left) {

			moves = partida->moveLeft();
		} else if (dir == up) {

			moves = partida->moveUp();
		} else if (dir == down) {

			moves = partida->moveDown();
		} else if (dir == right) {

			moves = partida->moveRight();
		}
	}
	if (moves != 0) {
		partida->newCasilla();
	}
	SDL_Delay(200);
	return finalizar;
}
