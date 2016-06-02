/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
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

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;
#include "Vista.h"
#include "Partida.h"
#include "Controlador.h"
#include "ControladorAutomatico.h"
#include "ControladorManual.h"
#include "Config.h"


int main() {
	srand(time(NULL));

	bool iniciado = false;
	bool finalizado = false;
	bool salir = false;
	bool automatico = false;

	int ancho = 0;
	int alto = 0;

	SDL_Event evento;

	Partida* partida;
	Controlador *controlador;
	Vista* vista;

	try {

		partida = new Partida(COLUMNS,ROWS);
		controlador = new ControladorManual(partida);
		vista = new Vista(controlador);
	} catch (exception *e) {

		salir = true;
	}

	while (!salir) {

		ancho = 0;
		alto = 0;
		iniciado = vista->mostrarInicio(ancho, alto);

		while (iniciado) {

			SDL_WaitEvent(&evento);
			if (evento.type == SDL_QUIT) { //Cierra la ventana con la X

				iniciado = false;
				salir = true;
				finalizado = true;
			}
			if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT && evento.button.x >= (vista->getWindow()->getX() / 2) - (ancho / 2) && evento.button.x <= (vista->getWindow()->getX() / 2) + (ancho / 2) && evento.button.y >= ((vista->getWindow()->getY() + vista->getWindow()->getExtraY()) / 10)*5 - (alto / 2) && evento.button.y <= ((vista->getWindow()->getY() + vista->getWindow()->getExtraY()) / 10)*5 + (alto / 2)) {  //Presiona el enter

				iniciado = false;
				automatico = true;
				partida->resetPartida(COLUMNS,ROWS);
			}
			if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT && evento.button.x >= (vista->getWindow()->getX() / 2) - (ancho / 2) && evento.button.x <= (vista->getWindow()->getX() / 2) + (ancho / 2) && evento.button.y >= ((vista->getWindow()->getY() + vista->getWindow()->getExtraY()) / 10)*8 - (alto / 2) && evento.button.y <= ((vista->getWindow()->getY() + vista->getWindow()->getExtraY()) / 10)*8 + (alto / 2)) {  //Presiona el botón

				iniciado = false;
				automatico = false;
				partida->resetPartida(COLUMNS,ROWS);
			}
		}

		if (!salir) {
			if (automatico) {

				delete controlador;
				controlador = new ControladorAutomatico(partida);
				vista->setControlador(controlador);
			} else {

				delete controlador;
				controlador = new ControladorManual(partida);
				vista->setControlador(controlador);
			}
		}

		while (!finalizado && !salir) {

			salir = controlador->detectMove();
			if (!salir) {

				vista->updateVista();
				finalizado = partida->isFinished();
			} else {

				finalizado = true;
			}
		}

		if (finalizado && !salir) {

			ancho = 0;
			alto = 0;
			SDL_Delay(3000);
			iniciado = vista->mostrarFinal(ancho, alto);

			while (iniciado) {

				SDL_WaitEvent(&evento);
				if (evento.type == SDL_QUIT) { //Cierra la ventana con la X

					iniciado = false;
					salir = true;
				}
				if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT && evento.button.x >= (vista->getWindow()->getX() / 2) - (ancho / 2) && evento.button.x <= (vista->getWindow()->getX() / 2) + (ancho / 2) && evento.button.y >= ((vista->getWindow()->getY() + vista->getWindow()->getExtraY()) / 10)*5 - (alto / 2) && evento.button.y <= ((vista->getWindow()->getY() + vista->getWindow()->getExtraY()) / 10)*5 + (alto / 2)) {  //Presiona el enter

					iniciado = false;
					finalizado = false;
				}
				if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT && evento.button.x >= (vista->getWindow()->getX() / 2) - (ancho / 2) && evento.button.x <= (vista->getWindow()->getX() / 2) + (ancho / 2) && evento.button.y >= ((vista->getWindow()->getY() + vista->getWindow()->getExtraY()) / 10)*8 - (alto / 2) && evento.button.y <= ((vista->getWindow()->getY() + vista->getWindow()->getExtraY()) / 10)*8 + (alto / 2)) {  //Presiona el botón

					iniciado = false;
					salir = true;
				}
			}
		}
	}

	delete vista;
	delete controlador;
	delete partida;

	return 0;
}

