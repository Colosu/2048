/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * vista.cc
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

#include "Vista.h"
#include "Ventana.h"
#include "Controlador.h"
#include "include/SDL2/SDL.h"

Vista::Vista(Controlador* control) {
	try {
		controlador = control;
		window = new Ventana(COLUMNS * 100, ROWS * 100, 0, 100, "2048");
		max = 0;
		punt = 0;
	} catch (exception *e) {
		throw e;
	}
}

Vista::~Vista() {
	delete window;
}

Ventana* Vista::getWindow() {

	return window;
}

void Vista::setControlador(Controlador* control) {

	controlador = control;
}

void Vista::updateVista() {
	SDL_Texture *textura = NULL;
	SDL_RenderClear(window->getTexturas()->getRenderizado());
	for (int i = 0; i < controlador->getPartida()->getTab()->getRows(); i++) {
		for (int j = 0; j < controlador->getPartida()->getTab()->getColumns(); j++) {
			switch (controlador->getPartida()->getTab()->getCasilla(i,j)->getNumber()) {
				case 2: textura = window->getTexturas()->getDos(); break;
				case 4: textura = window->getTexturas()->getCuatro(); break;
				case 8: textura = window->getTexturas()->getOcho(); break;
				case 16: textura = window->getTexturas()->getDieciseis(); break;
				case 32: textura = window->getTexturas()->getTreintaydos(); break;
				case 64: textura = window->getTexturas()->getSesentaycuatro(); break;
				case 128: textura = window->getTexturas()->getCientoveintiocho(); break;
				case 256: textura = window->getTexturas()->getDoscientoscincuentayseis(); break;
				case 512: textura = window->getTexturas()->getQuinientosdoce(); break;
				case 1024: textura = window->getTexturas()->getMilveinticuatro(); break;
				case 2048: textura = window->getTexturas()->getDosmilcuarentayocho(); break;
				default: textura = window->getTexturas()->getCero();
			}
			window->getTexturas()->renderizarTextura(textura, j*100, i*100);
		}
	}
	max = controlador->getPartida()->getMax();
	punt = controlador->getPartida()->getPunt();
	window->getTexturas()->renderizarTextura(window->getTexturas()->getPuntuacion(), 50, ROWS*100 + 40);
	window->getTexturas()->setMaximo(max);
	window->getTexturas()->setPuntos(punt);
	window->getTexturas()->renderizarTextura(window->getTexturas()->getMaximo(), 100, ROWS*100 + 40);
	window->getTexturas()->renderizarTextura(window->getTexturas()->getPuntos(), 280, ROWS*100 + 40);
	SDL_RenderPresent(window->getTexturas()->getRenderizado());
}

bool Vista::mostrarInicio(int &ancho, int &alto) {

	bool iniciado = false;
	SDL_Texture *titulo = NULL;
	SDL_Texture *inicio = NULL;
	SDL_Texture *automatico = NULL;
	SDL_Texture *manual = NULL;
	SDL_Color color = { 255, 255, 255, 255 };

	inicio = window->getTexturas()->cargarTextura(window->getDireccion() + "inicio.png");
	titulo = window->getTexturas()->renderizarTexto(window->getTexturas()->getFuentes()->getFuentePrincipal(), "2048", color);
	automatico = window->getTexturas()->renderizarTexto(window->getTexturas()->getFuentes()->getFuenteSecundaria(), "Automático", color);
	manual = window->getTexturas()->renderizarTexto(window->getTexturas()->getFuentes()->getFuenteSecundaria(), "Manual", color);

	if (inicio != NULL && titulo != NULL && automatico != NULL && manual != NULL) {

		SDL_RenderClear(window->getTexturas()->getRenderizado());

		SDL_QueryTexture(inicio, NULL, NULL, &ancho, &alto);
		window->getTexturas()->renderizarTextura(inicio, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 10)*5 - (alto / 2));
		window->getTexturas()->renderizarTextura(inicio, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 10)*8 - (alto / 2));
		SDL_QueryTexture(titulo, NULL, NULL, &ancho, &alto);
		window->getTexturas()->renderizarTextura(titulo, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 5) - (alto / 2));
		SDL_QueryTexture(automatico, NULL, NULL, &ancho, &alto);
		window->getTexturas()->renderizarTextura(automatico, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 10)*5 - (alto / 2));
		SDL_QueryTexture(manual, NULL, NULL, &ancho, &alto);
		window->getTexturas()->renderizarTextura(manual, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 10)*8 - (alto / 2));

		SDL_RenderPresent(window->getTexturas()->getRenderizado());

		iniciado = true;
	} else {

		iniciado = false;
	}

	SDL_QueryTexture(inicio, NULL, NULL, &ancho, &alto);

	SDL_DestroyTexture(inicio);
	SDL_DestroyTexture(titulo);
	SDL_DestroyTexture(automatico);
	SDL_DestroyTexture(manual);

	return iniciado;
}

bool Vista::mostrarFinal(int &ancho, int &alto) {

	bool iniciado = false;
	SDL_Texture *titulo = NULL;
	SDL_Texture *inicio = NULL;
	SDL_Texture *automatico = NULL;
	SDL_Texture *manual = NULL;
	SDL_Color color = { 255, 255, 255, 255 };

	inicio = window->getTexturas()->cargarTextura(window->getDireccion() + "inicio.png");
	if (controlador->getPartida()->getMax() == 2048) {

		titulo = window->getTexturas()->renderizarTexto(window->getTexturas()->getFuentes()->getFuentePrincipal(), "Ganaste", color);
	} else {

		titulo = window->getTexturas()->renderizarTexto(window->getTexturas()->getFuentes()->getFuentePrincipal(), "Perdiste", color);
	}
	automatico = window->getTexturas()->renderizarTexto(window->getTexturas()->getFuentes()->getFuenteSecundaria(), "Reintentar", color);
	manual = window->getTexturas()->renderizarTexto(window->getTexturas()->getFuentes()->getFuenteSecundaria(), "Salir", color);

	if (inicio != NULL && titulo != NULL && automatico != NULL && manual != NULL) {

		SDL_RenderClear(window->getTexturas()->getRenderizado());

		SDL_QueryTexture(inicio, NULL, NULL, &ancho, &alto);
		window->getTexturas()->renderizarTextura(inicio, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 10)*6 - (alto / 2));
		window->getTexturas()->renderizarTextura(inicio, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 20)*17 - (alto / 2));
		SDL_QueryTexture(titulo, NULL, NULL, &ancho, &alto);
		window->getTexturas()->renderizarTextura(titulo, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 5) - (alto / 2));
		SDL_QueryTexture(automatico, NULL, NULL, &ancho, &alto);
		window->getTexturas()->renderizarTextura(automatico, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 10)*6 - (alto / 2));
		SDL_QueryTexture(manual, NULL, NULL, &ancho, &alto);
		window->getTexturas()->renderizarTextura(manual, (window->getX() / 2) - (ancho / 2), ((window->getY() + window->getExtraY()) / 20)*17 - (alto / 2));

		max = controlador->getPartida()->getMax();
		punt = controlador->getPartida()->getPunt();
		window->getTexturas()->renderizarTextura(window->getTexturas()->getPuntuacion(), 50, 150 + 40);
		window->getTexturas()->setMaximo(max);
		window->getTexturas()->setPuntos(punt);
		window->getTexturas()->renderizarTextura(window->getTexturas()->getMaximo(), 100, 150 + 40);
		window->getTexturas()->renderizarTextura(window->getTexturas()->getPuntos(), 280, 150 + 40);

		SDL_RenderPresent(window->getTexturas()->getRenderizado());

		iniciado = true;
	} else {

		iniciado = false;
	}

	SDL_QueryTexture(inicio, NULL, NULL, &ancho, &alto);

	SDL_DestroyTexture(inicio);
	SDL_DestroyTexture(titulo);
	SDL_DestroyTexture(automatico);
	SDL_DestroyTexture(manual);

	return iniciado;
}
