/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * texturas.h
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

#ifndef _TEXTURAS_H_
#define _TEXTURAS_H_

#include <string>
using namespace std;
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_ttf.h"
#include "Fuentes.h"

class Texturas {
public:
	Texturas(string direccion, SDL_Window *ventana);
	~Texturas();
	SDL_Renderer* getRenderizado();
	void setRenderizado(SDL_Window *ventana);
	Fuentes* getFuentes();
	SDL_Texture* getCero();
	SDL_Texture* getDos();
	SDL_Texture* getCuatro();
	SDL_Texture* getOcho();
	SDL_Texture* getDieciseis();
	SDL_Texture* getTreintaydos();
	SDL_Texture* getSesentaycuatro();
	SDL_Texture* getCientoveintiocho();
	SDL_Texture* getDoscientoscincuentayseis();
	SDL_Texture* getQuinientosdoce();
	SDL_Texture* getMilveinticuatro();
	SDL_Texture* getDosmilcuarentayocho();
	SDL_Texture* getPuntuacion();
	SDL_Texture* getMaximo();
	SDL_Texture* getPuntos();
	SDL_Color getColor();
	void setMaximo(int m);
	void setPuntos(int p);
	SDL_Texture* cargarTextura(const string &archivo); //Carga una textura gráfica del archivo "archivo" para poder usarla.
	void renderizarTextura(SDL_Texture *textura, int x, int y, SDL_Rect *clip = NULL); //Renderiza la textura "textura" para mostrarla por pantalla en la posición ("x", "y"). Con "clip" seleccionas una parte de la textura.
	void renderizarTextura(SDL_Texture *textura, SDL_Rect rectangulo, SDL_Rect *clip = NULL); //Renderiza la textura "textura" para mostrarla por pantalla dentro del rectángulo "rectangulo". Con "clip" seleccionas una parte de la textura.
	SDL_Texture* renderizarTexto(TTF_Font *fuente, const string &mensaje, SDL_Color color); //Crea una textura con el texto "mensaje" y con la fuente "fuente" y el color "color".

protected:

private:
	void logSDLError(const string &mensaje, ostream &oflujo); //Muestra por el flujo "oflujo" el error "mensaje" producido.
	string intToString(int numero);
	SDL_Renderer *renderizado; //El renderizado de la ventana.
	Fuentes *fuentes;
	SDL_Texture *cero;
	SDL_Texture *dos;
	SDL_Texture *cuatro;
	SDL_Texture *ocho;
	SDL_Texture *dieciseis;
	SDL_Texture *treintaydos;
	SDL_Texture *sesentaycuatro;
	SDL_Texture *cientoveintiocho;
	SDL_Texture *doscientoscincuentayseis;
	SDL_Texture *quinientosdoce;
	SDL_Texture *milveinticuatro;
	SDL_Texture *dosmilcuarentayocho;
	SDL_Texture *puntuacion;
	SDL_Texture *maximo;
	SDL_Texture *puntos;
	SDL_Color const color = {255, 255, 255, 255};

};

#endif // _TEXTURAS_H_

