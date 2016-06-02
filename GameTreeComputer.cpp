/*
 * GameTreeComputer.cpp
 *
 *  Created on: 22 de may. de 2016
 *      Author: colosu
 */

#include "GameTreeComputer.h"
#include "GameTree.h"
#include "GameTreePlayer.h"
#include "Partida.h"
#include <stdio.h>
using namespace std;

GameTreeComputer::GameTreeComputer(Partida* party, int parada, int plus) {

	value = plus;
	partida = party;
	stop = parada;

	for (int i = 0; i < partida->getTab()->getRows(); i++) {
		for (int j = 0; j < partida->getTab()->getColumns(); j++) {
			tree[i][j] = NULL;
		}
	}

	if(partida->getMax() == 2048) {

		value += 100000;
	} else if (partida->isFinished()) {

		value -= 100000;
	}

	//Suma de los puntos del tablero
	value += partida->getPunt();


	//Suma de valores de las fichas multiplicados por la matriz de ponderación
	int zeros = 0;
	for (int i = 0; i < partida->getTab()->getRows(); i++) {
		for (int j = 0; j < partida->getTab()->getColumns(); j++) {
			if (partida->getTab()->getCasilla(i,j)->getNumber() > 4) {

				//Esquina Superior Izquierda
				if (i == 0 && j == 0) {
					value += partida->getTab()->getCasilla(i,j)->getNumber()*20;
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i+1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j+1)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber()*5;
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i+1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j+1)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber()*10;
					}*/
				}

				//Esquina Inferior Izquierda
				if (i == partida->getTab()->getRows() - 1 && j == 0) {
					value += partida->getTab()->getCasilla(i,j)->getNumber()*6;
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i-1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j+1)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber()*5;
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i-1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j+1)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber()*10;
					}*/
				}

				//Esquina Inferior Derecha
				if (i == partida->getTab()->getRows() - 1 && j == partida->getTab()->getColumns() - 1) {
					value += partida->getTab()->getCasilla(i,j)->getNumber();
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i-1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j-1)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber()*5;
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i-1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j-1)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber()*10;
					}*/
				}

				//Esquina Superior Derecha
				if (i == 0 && j == partida->getTab()->getColumns() - 1) {
					value += partida->getTab()->getCasilla(i,j)->getNumber();
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i+1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j-1)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber()*5;
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i+1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j-1)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber()*10;
					}*/
				}

				//Columna Izquierda
				if (i > 0 && i < partida->getTab()->getRows()-1 && j == 0) {
					value += partida->getTab()->getCasilla(i,j)->getNumber()*8;
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i+1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i-1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j+1)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber()*2;
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i+1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i-1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j+1)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber()*4;
					}*/
				}

				//Columna Derecha
				if (i > 0 && i < partida->getTab()->getRows()-1 && j == partida->getTab()->getColumns() - 1) {
					value += partida->getTab()->getCasilla(i,j)->getNumber();
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i+1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i-1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j-1)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber()/2;
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i+1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i-1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j-1)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber();
					}*/
				}

				//Fila Superior
				if (j > 0 && j < partida->getTab()->getColumns()-1 && i == 0) {
					value += partida->getTab()->getCasilla(i,j)->getNumber()*4;
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j+1)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j-1)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i+1,j)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber();
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j+1)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j-1)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i+1,j)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber()*2;
					}*/
				}

				//Fila Inferior
				if (j > 0 && j < partida->getTab()->getColumns()-1 && i == partida->getTab()->getRows() - 1) {
					value += partida->getTab()->getCasilla(i,j)->getNumber()*4;
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j+1)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j-1)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i-1,j)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber();
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j+1)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j-1)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i-1,j)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber()*2;
					}*/
				}

				//Cuadrado Central
				if (i > 0 && i < partida->getTab()->getRows()-1 && j > 0 && j < partida->getTab()->getColumns()-1) {
					value += partida->getTab()->getCasilla(i,j)->getNumber();
					/*if (partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i+1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i-1,j)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j+1)->getNumber() || partida.getTab()->getCasilla(i,j)->getNumber() == partida.getTab()->getCasilla(i,j-1)->getNumber()) {
						value += partida.getTab()->getCasilla(i,j)->getNumber()/2;
					}
					if (partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i+1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i-1,j)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j+1)->getNumber() && partida.getTab()->getCasilla(i,j)->getNumber()*2 < partida.getTab()->getCasilla(i,j-1)->getNumber()) {
						value -= partida.getTab()->getCasilla(i,j)->getNumber();
					}*/
				}

			} else if (partida->getTab()->getCasilla(i,j)->getNumber() == 0){
				zeros++;
			}
		}
	}

	/*if (partida.getTab()->getCasilla(0,0)->getNumber() == partida.getMax()){
		value -= partida.getTab()->getCasilla(0,0)->getNumber();
	}*/

	//Suma de los huecos vacíos del tablero
	value += zeros*partida->getMax();

}

GameTreeComputer::~GameTreeComputer() {

	for (int i = 0; i < partida->getTab()->getRows(); i++) {
		for (int j = 0; j < partida->getTab()->getColumns(); j++) {
			delete tree[i][j];
			tree[i][j] = NULL;
		}
	}
	delete partida;
}

void GameTreeComputer::setChilds() {

	Partida* party = new Partida();

	for (int i = 0; i < partida->getTab()->getRows(); i++) {
		for (int j = 0; j < partida->getTab()->getColumns(); j++) {

			if (partida->getTab()->getCasilla(i,j)->getNumber() == 0) {
				party = new Partida();
				*party = *partida;
				party->getTab()->setDos(i,j);
				tree[i][j] = new GameTreePlayer(party, stop - 1, 0);
			} else {

				tree[i][j] = NULL;
			}
		}
	}
}

direction GameTreeComputer::chooseChild() {

	int val = 0;
	int num = 0;

	for (int i = 0; i < partida->getTab()->getRows(); i++) {
		for (int j = 0; j < partida->getTab()->getColumns(); j++) {

			if (tree[i][j] != NULL) {
				if (stop > 1) {
					tree[i][j]->setChilds();
					tree[i][j]->chooseChild();
				}
				val += tree[i][j]->getValue();
				num++;
			}
		}
	}

	value += val/num;

	return up;
}

int GameTreeComputer::getValue() {

	return value;
}

Partida* GameTreeComputer::getPartida() {

	return partida;
}

