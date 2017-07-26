/*
 * ControladorManual.cpp
 *
 *  Created on: 16 de may. de 2016
 *      Author: colosu
 */

#include "ControladorManual.h"
#include "Partida.h"
#include "include/SDL2/SDL.h"


ControladorManual::ControladorManual(Partida* party) {

	partida = party;
}

ControladorManual::~ControladorManual() {

}

Partida* ControladorManual::getPartida() {
	return partida;
}

bool ControladorManual::detectMove() {

	SDL_Event evento;
	bool finalizar = false;
	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT) { //Cierra la ventana con la X
			finalizar = true;
		} else if (evento.type == SDL_KEYDOWN) {  //Presiona una tecla

			int moves = 0;
			if (evento.key.keysym.sym == SDLK_a || evento.key.keysym.sym == SDLK_LEFT) {

				moves = partida->moveLeft();
			} else if (evento.key.keysym.sym == SDLK_w || evento.key.keysym.sym == SDLK_UP) {

				moves = partida->moveUp();
			} else if (evento.key.keysym.sym == SDLK_d || evento.key.keysym.sym == SDLK_RIGHT) {

				moves = partida->moveRight();
			} else if (evento.key.keysym.sym == SDLK_s || evento.key.keysym.sym == SDLK_DOWN) {

				moves = partida->moveDown();
			}

			if (moves != 0) {
				partida->newCasilla();
			}
		}
	}
	return finalizar;
}

