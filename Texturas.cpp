/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * texturas.cc
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

#include "Texturas.h"

#include <string>
using namespace std;
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_ttf.h"
#include "Fuentes.h"

Texturas::Texturas(string direccion, SDL_Window *ventana) {
	try {
		setRenderizado(ventana);
		fuentes = new Fuentes(direccion);
		cero = cargarTextura(direccion + "cero.png");
		dos = cargarTextura(direccion + "dos.png");
		cuatro = cargarTextura(direccion + "cuatro.png");
		ocho = cargarTextura(direccion + "ocho.png");
		dieciseis = cargarTextura(direccion + "dieciseis.png");
		treintaydos = cargarTextura(direccion + "treintaydos.png");
		sesentaycuatro = cargarTextura(direccion + "sesentaycuatro.png");
		cientoveintiocho = cargarTextura(direccion + "cientoveintiocho.png");
		doscientoscincuentayseis = cargarTextura(direccion + "doscientoscincuentayseis.png");
		quinientosdoce = cargarTextura(direccion + "quinientosdoce.png");
		milveinticuatro = cargarTextura(direccion + "milveinticuatro.png");
		dosmilcuarentayocho = cargarTextura(direccion + "dosmilcuarentayocho.png");

		puntuacion = renderizarTexto(fuentes->getFuenteJuego(), "Max:             Puntuación:", color);
		maximo = renderizarTexto(fuentes->getFuenteJuego(), "0", color);
		puntos = renderizarTexto(fuentes->getFuenteJuego(), "0", color);
	}
	catch (exception *e) {

		SDL_DestroyTexture(cero);
		SDL_DestroyTexture(dos);
		SDL_DestroyTexture(cuatro);
		SDL_DestroyTexture(ocho);
		SDL_DestroyTexture(dieciseis);
		SDL_DestroyTexture(treintaydos);
		SDL_DestroyTexture(sesentaycuatro);
		SDL_DestroyTexture(cientoveintiocho);
		SDL_DestroyTexture(doscientoscincuentayseis);
		SDL_DestroyTexture(quinientosdoce);
		SDL_DestroyTexture(milveinticuatro);
		SDL_DestroyTexture(dosmilcuarentayocho);
		SDL_DestroyTexture(puntuacion);
		SDL_DestroyTexture(puntos);
		throw e;
	}
}

Texturas::~Texturas() {
	SDL_DestroyRenderer(renderizado);
	delete fuentes;
	SDL_DestroyTexture(cero);
	SDL_DestroyTexture(dos);
	SDL_DestroyTexture(cuatro);
	SDL_DestroyTexture(ocho);
	SDL_DestroyTexture(dieciseis);
	SDL_DestroyTexture(treintaydos);
	SDL_DestroyTexture(sesentaycuatro);
	SDL_DestroyTexture(cientoveintiocho);
	SDL_DestroyTexture(doscientoscincuentayseis);
	SDL_DestroyTexture(quinientosdoce);
	SDL_DestroyTexture(milveinticuatro);
	SDL_DestroyTexture(dosmilcuarentayocho);
	SDL_DestroyTexture(puntuacion);
	SDL_DestroyTexture(puntos);
}

SDL_Renderer* Texturas::getRenderizado() {

	return renderizado;
}

void Texturas::setRenderizado(SDL_Window *ventana) {

	renderizado = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderizado == NULL) {

		logSDLError("SDL_CreateRenderer()", cerr);
		throw new runtime_error("renderer");
	}
	else {

		SDL_SetRenderDrawColor(renderizado, 0x00, 0x0, 0x00, 0xFF);
	}
}

Fuentes* Texturas::getFuentes() {

	return fuentes;
}

SDL_Texture* Texturas::getCero() {

	return cero;
}

SDL_Texture* Texturas::getDos() {

	return dos;
}

SDL_Texture* Texturas::getCuatro() {

	return cuatro;
}

SDL_Texture* Texturas::getOcho() {

	return ocho;
}

SDL_Texture* Texturas::getDieciseis() {

	return dieciseis;
}

SDL_Texture* Texturas::getTreintaydos() {

	return treintaydos;
}

SDL_Texture* Texturas::getSesentaycuatro() {

	return sesentaycuatro;
}

SDL_Texture* Texturas::getCientoveintiocho() {

	return cientoveintiocho;
}

SDL_Texture* Texturas::getDoscientoscincuentayseis() {

	return doscientoscincuentayseis;
}

SDL_Texture* Texturas::getQuinientosdoce() {

	return quinientosdoce;
}

SDL_Texture* Texturas::getMilveinticuatro() {

	return milveinticuatro;
}

SDL_Texture* Texturas::getDosmilcuarentayocho() {

	return dosmilcuarentayocho;
}

SDL_Texture* Texturas::getPuntuacion() {

	return puntuacion;
}

SDL_Color Texturas::getColor() {
	return color;
}

SDL_Texture* Texturas::getMaximo() {

	return maximo;
}

SDL_Texture* Texturas::getPuntos() {

	return puntos;
}

void Texturas::setMaximo(int m) {

	string cadena = intToString(m);


	try {

		maximo = renderizarTexto(fuentes->getFuenteJuego(), cadena, color);
	}
	catch (exception *e) {

		SDL_DestroyTexture(puntos);
		throw new exception();
	}
}

void Texturas::setPuntos(int p) {

	string cadena = intToString(p);


	try {

		puntos = renderizarTexto(fuentes->getFuenteJuego(), cadena, color);
	}
	catch (exception *e) {

		SDL_DestroyTexture(puntos);
		throw new exception();
	}
}

SDL_Texture* Texturas::cargarTextura(const string &archivo) {

	SDL_Texture *textura = NULL;
	textura = IMG_LoadTexture(renderizado, archivo.c_str());
	if (textura == NULL) {
		logSDLError("IMG_LoadTexture()", cerr);
		throw new runtime_error("Textura");
	}

	return textura;
}

void Texturas::renderizarTextura(SDL_Texture *textura, int x, int y, SDL_Rect *clip) {

	SDL_Rect rectangulo;

	rectangulo.x = x;
	rectangulo.y = y;

	if (clip != NULL) {

		rectangulo.w = clip->w;
		rectangulo.h = clip->h;
	}
	else {

		SDL_QueryTexture(textura, NULL, NULL, &rectangulo.w, &rectangulo.h);
	}

	renderizarTextura(textura, rectangulo, clip);
}

void Texturas::renderizarTextura(SDL_Texture *textura, SDL_Rect rectangulo, SDL_Rect *clip) {

	SDL_RenderCopy(renderizado, textura, clip, &rectangulo);
}

SDL_Texture* Texturas::renderizarTexto(TTF_Font *fuente, const string &mensaje, SDL_Color color) {

	SDL_Texture *textura = NULL;

	SDL_Surface *superficie = NULL;
	superficie = TTF_RenderUTF8_Blended(fuente, mensaje.c_str(), color);

	if (superficie == NULL) {

		logSDLError("TTF_RenderText_Blended()", cerr);
		throw new runtime_error("Superficie");
	}
	else {

		textura = SDL_CreateTextureFromSurface(renderizado, superficie);

		if (textura == NULL) {

			logSDLError("SDL_CreateTextureFromSurface", cerr);
			throw new runtime_error("Textura");
		}

		SDL_FreeSurface(superficie);
	}

	return textura;
}

void Texturas::logSDLError(const string &mensaje, ostream &oflujo) {

	oflujo << mensaje << " error: " << SDL_GetError() << endl;
}

string Texturas::intToString(int numero) {

	string cadena;

	if (numero != 0) {

		cadena = "";

		while (numero != 0) {

			cadena = char((numero % 10) + 48) + cadena;
			numero /= 10;
		}
	}
	else {

		cadena = "0";
	}

	return cadena;
}

