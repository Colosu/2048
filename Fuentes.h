/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * fuentes.h
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

#ifndef _FUENTES_H_
#define _FUENTES_H_

#include <iostream>
#include <string>
using namespace std;
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_ttf.h"

class Fuentes {
public:
	Fuentes(string direccion);
	~Fuentes();
	TTF_Font* getFuentePrincipal();
	TTF_Font* getFuenteSecundaria();
	TTF_Font* getFuenteJuego();
	TTF_Font* inicializarFuente(const string &archivo, int tamano); //Carga la fuente de texto "fuente" del archivo "archivo" al tamaño "tamano" para poder usarla.

protected:

private:
	void logSDLError(const string &mensaje, ostream &oflujo); //Muestra por el flujo "oflujo" el error "mensaje" producido.

	TTF_Font *fuentePrincipal;
	TTF_Font *fuenteSecundaria;
	TTF_Font *fuenteJuego;
};

#endif // _FUENTES_H_

