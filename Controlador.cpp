/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * controlador.cc
 * Copyright (C) 2016 Colosu <alfredocolosu@gmail.com>
 *
 * 2048 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * 2048 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Controlador.h"
#include "Partida.h"
#include "include/SDL2/SDL.h"

Controlador::~Controlador() {

}

Partida* Controlador::getPartida() {
	return partida;
}

bool Controlador::detectMove() {

	SDL_Event evento;
	bool finalizar = false;
	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT) { //Cierra la ventana con la X
			finalizar = true;
		}
	}
	return finalizar;
}
