/*
 * Partida.cpp
 *
 *  Created on: 15/05/2016
 *      Author: colosu
 */

#include "Partida.h"
#include "Casilla.h"
#include "Tablero.h"
#include <stdio.h>
using namespace std;

Partida::Partida() {

	tab = NULL;
	max = 0;
	punt = 0;
	turn = 0;
}

Partida::Partida(int X, int Y) {
	tab = new Tablero(X, Y);
	max = 0;
	punt = 0;
	turn = 0;
}

Partida::~Partida() {
	if (tab != NULL) {
		delete tab;
		tab = NULL;
	}
}

Tablero* Partida::getTab() {
	return tab;
}

int Partida::getMax() {
	return max;
}

int Partida::getPunt() {
	return punt;
}

int Partida::getTurn() {
	return turn;
}

int Partida::getZeros() {
	int zeros = 0;
	for (int i = 0; i < tab->getRows(); i++) {
		for (int j = 0; j < tab->getColumns(); j++) {
			if(tab->getCasilla(i,j)->getNumber() == 0) {
				zeros++;
			}
		}
	}
	return zeros;
}

int Partida::getAdyacentes() {
	int adyacentes = 0;
	for (int i = 0; i < tab->getRows(); i++) {
		for (int j = 0; j < tab->getColumns(); j++) {
			if (tab->getCasilla(i,j)->getNumber() > 0) {

				//Esquina Superior Izquierda
				if (i == 0 && j == 0) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i+1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j+1)->getNumber()) {
						adyacentes++;
					}
				}

				//Esquina Inferior Izquierda
				if (i == tab->getRows() - 1 && j == 0) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i-1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j+1)->getNumber()) {
						adyacentes++;
					}
				}

				//Esquina Inferior Derecha
				if (i == tab->getRows() - 1 && j == tab->getColumns() - 1) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i-1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j-1)->getNumber()) {
						adyacentes++;
					}
				}

				//Esquina Superior Derecha
				if (i == 0 && j == tab->getColumns() - 1) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i+1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j-1)->getNumber()) {
						adyacentes++;
					}
				}

				//Columna Izquierda
				if (i > 0 && i < tab->getRows()-1 && j == 0) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i+1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i-1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j+1)->getNumber()) {
						adyacentes++;
					}
				}

				//Columna Derecha
				if (i > 0 && i < tab->getRows()-1 && j == tab->getColumns() - 1) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i+1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i-1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j-1)->getNumber()) {
						adyacentes++;
					}
				}

				//Fila Superior
				if (j > 0 && j < tab->getColumns()-1 && i == 0) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j+1)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j-1)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i+1,j)->getNumber()) {
						adyacentes++;
					}
				}

				//Fila Inferior
				if (j > 0 && j < tab->getColumns()-1 && i == tab->getRows() - 1) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j+1)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j-1)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i-1,j)->getNumber()) {
						adyacentes++;
					}
				}

				//Cuadrado Central
				if (i > 0 && i < tab->getRows()-1 && j > 0 && j < tab->getColumns()-1) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i+1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i-1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j+1)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j-1)->getNumber()) {
						adyacentes++;
					}
				}

			}
		}
	}
	return adyacentes/2;
}

void Partida::resetPartida(int X, int Y) {
	delete tab;
	tab = new Tablero(X, Y);
	max = 0;
	punt = 0;
}

int Partida::moveUp() {
	int moves = 0;
	for (int i = 1; i < tab->getRows(); i++) {
		for (int j = 0; j < tab->getColumns(); j++) {
			if(tab->getCasilla(i,j)->getNumber() != 0) {
				int I = i-1;
				while (tab->getCasilla(I,j)->getNumber() == 0 && I > 0) {
					I--;
				}
				if (tab->getCasilla(I,j)->getNumber() == 0) {
					moves += tab->moveCasilla(i,j, I,j);
				} else if (tab->getCasilla(I,j)->getNumber() == tab->getCasilla(i,j)->getNumber() && !tab->getCasilla(I,j)->getSuma()) {
					moves += tab->sumCasilla(i,j, I,j);
					punt += tab->getCasilla(I,j)->getNumber();
					if (tab->getCasilla(I,j)->getNumber() > max) {
						max = tab->getCasilla(I,j)->getNumber();
					}
				} else {
					moves += tab->moveCasilla(i,j, I+1,j);
				}
			}
		}
	}
	for (int i = 0; i < tab->getRows(); i++) {
		for (int j = 0; j < tab->getColumns(); j++) {
			if(tab->getCasilla(i,j)->getSuma()) {
				tab->getCasilla(i,j)->setSuma(false);
			}
		}
	}
	if (moves != 0) {

		turn++;
	}
	return moves;
}

int Partida::moveDown() {
	int moves = 0;
	for (int i = tab->getRows()-2; i >= 0; i--) {
		for (int j = 0; j < tab->getColumns(); j++) {
			if(tab->getCasilla(i,j)->getNumber() != 0) {
				int I = i+1;
				while (tab->getCasilla(I,j)->getNumber() == 0 && I < tab->getRows()-1) {
					I++;
				}
				if (tab->getCasilla(I,j)->getNumber() == 0) {
					moves += tab->moveCasilla(i,j, I,j);
				} else if (tab->getCasilla(I,j)->getNumber() == tab->getCasilla(i,j)->getNumber() && !tab->getCasilla(I,j)->getSuma()) {
					moves += tab->sumCasilla(i,j, I,j);
					punt += tab->getCasilla(I,j)->getNumber();
					if (tab->getCasilla(I,j)->getNumber() > max) {
						max = tab->getCasilla(I,j)->getNumber();
					}
				} else {
					moves += tab->moveCasilla(i,j, I-1,j);
				}
			}
		}
	}
	for (int i = 0; i < tab->getRows(); i++) {
		for (int j = 0; j < tab->getColumns(); j++) {
			if(tab->getCasilla(i,j)->getSuma()) {
				tab->getCasilla(i,j)->setSuma(false);
			}
		}
	}
	if (moves != 0) {

		turn++;
	}
	return moves;
}

int Partida::moveRight() {
	int moves = 0;
	for (int j = tab->getColumns()-2; j >= 0; j--) {
		for (int i = 0; i < tab->getRows(); i++) {
			if(tab->getCasilla(i,j)->getNumber() != 0) {
				int J = j+1;
				while (tab->getCasilla(i,J)->getNumber() == 0 && J < tab->getColumns()-1) {
					J++;
				}
				if (tab->getCasilla(i,J)->getNumber() == 0) {
					moves += tab->moveCasilla(i,j, i,J);
				} else if (tab->getCasilla(i,J)->getNumber() == tab->getCasilla(i,j)->getNumber() && !tab->getCasilla(i,J)->getSuma()) {
					moves += tab->sumCasilla(i,j, i,J);
					punt += tab->getCasilla(i,J)->getNumber();
					if (tab->getCasilla(i,J)->getNumber() > max) {
						max = tab->getCasilla(i,J)->getNumber();
					}
				} else {
					moves += tab->moveCasilla(i,j, i,J-1);
				}
			}
		}
	}
	for (int i = 0; i < tab->getRows(); i++) {
		for (int j = 0; j < tab->getColumns(); j++) {
			if(tab->getCasilla(i,j)->getSuma()) {
				tab->getCasilla(i,j)->setSuma(false);
			}
		}
	}
	if (moves != 0) {

		turn++;
	}
	return moves;
}

int Partida::moveLeft() {
	int moves = 0;
	for (int j = 1; j < tab->getColumns(); j++) {
		for (int i = 0; i < tab->getRows(); i++) {
			if(tab->getCasilla(i,j)->getNumber() != 0) {
				int J = j-1;
				while (tab->getCasilla(i,J)->getNumber() == 0 && J > 0) {
					J--;
				}
				if (tab->getCasilla(i,J)->getNumber() == 0) {
					moves += tab->moveCasilla(i,j, i,J);
				} else if (tab->getCasilla(i,J)->getNumber() == tab->getCasilla(i,j)->getNumber() && !tab->getCasilla(i,J)->getSuma()) {
					moves += tab->sumCasilla(i,j, i,J);
					punt += tab->getCasilla(i,J)->getNumber();
					if (tab->getCasilla(i,J)->getNumber() > max) {
						max = tab->getCasilla(i,J)->getNumber();
					}
				} else {
					moves += tab->moveCasilla(i,j, i,J+1);
				}
			}
		}
	}
	for (int i = 0; i < tab->getRows(); i++) {
		for (int j = 0; j < tab->getColumns(); j++) {
			if(tab->getCasilla(i,j)->getSuma()) {
				tab->getCasilla(i,j)->setSuma(false);
			}
		}
	}
	if (moves != 0) {

		turn++;
	}
	return moves;
}

void Partida::newCasilla() {
	tab->randomCasilla();
}

bool Partida::isFinished() {

	bool finished = false;
	int value = 1;
	int i = 0;
	int j = 0;
	while (i < tab->getRows() && value != 0) {
		j = 0;
		while (j < tab->getColumns() && value != 0) {
			if (tab->getCasilla(i,j)->getNumber() == 0) {

				value = 0;
			} else {
				if (i > 0 && i < tab->getRows()-1) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i+1,j)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i-1,j)->getNumber()) {
						value = 0;
					}
				}
				if (j > 0 && j < tab->getColumns()-1) {
					if (tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j+1)->getNumber() || tab->getCasilla(i,j)->getNumber() == tab->getCasilla(i,j-1)->getNumber()) {
						value = 0;
					}
				}
			}
			j++;
		}
		i++;
	}

	if (value != 0 || max == 2048) {
		finished = true;
	} else {
		finished = false;
	}

	return finished;
}

Partida& Partida::operator =(const Partida &A) {

    if(this!=&A){
        this->max = A.max;
        this->punt = A.punt;
        this->turn = A.turn;

		if (A.tab != NULL) {
			if (this->tab != NULL) {
				*(this->tab) = *(A.tab);
			} else {

				this->tab = new Tablero();
				*(this->tab) = *(A.tab);
			}
		} else {

			this->tab = NULL;
		}
    }
    return *this;

}
