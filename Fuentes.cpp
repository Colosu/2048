/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * fuentes.cc
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

#include "Fuentes.h"

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_ttf.h"


Fuentes::Fuentes(string direccion) {
	try {
		fuentePrincipal = inicializarFuente(direccion + "Darleston.otf", 150);
		fuenteSecundaria = inicializarFuente(direccion + "Lighthouse.ttf", 50);
		fuenteJuego = inicializarFuente(direccion + "Square.ttf", 20);
	}
	catch (runtime_error *e) {

		TTF_CloseFont(fuentePrincipal);
		TTF_CloseFont(fuenteSecundaria);
		TTF_CloseFont(fuenteJuego);
		throw e;
	}
}

Fuentes::~Fuentes() {
	TTF_CloseFont(fuentePrincipal);
	TTF_CloseFont(fuenteSecundaria);
	TTF_CloseFont(fuenteJuego);
}

TTF_Font* Fuentes::getFuentePrincipal() {

	return fuentePrincipal;
}

TTF_Font* Fuentes::getFuenteSecundaria() {

	return fuenteSecundaria;
}

TTF_Font* Fuentes::getFuenteJuego() {

	return fuenteJuego;
}

TTF_Font* Fuentes::inicializarFuente(const string &archivo, int tamano) {

	TTF_Font *fuente = NULL;
	fuente = TTF_OpenFont(archivo.c_str(), tamano);

	if (fuente == NULL) {

		logSDLError("TTF_OpenFont()", cerr);
		throw new runtime_error("Fuentes");
	}
	return fuente;
}

void Fuentes::logSDLError(const string &mensaje, ostream &oflujo) {

	oflujo << mensaje << " error: " << SDL_GetError() << endl;
}
