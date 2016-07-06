/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * tablero.cc
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

#include "Tablero.h"
#include <stdlib.h>
using namespace std;
#include "Casilla.h"
#include "Config.h"

Tablero::Tablero() {
	columns = COLUMNS;
	rows = ROWS;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			tablero[i][j] = NULL;
		}
	}

	iDos = 0;
	jDos = 0;
}

Tablero::Tablero(int X, int Y) {
	columns = X;
	rows = Y;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			tablero[i][j] = new Casilla(i,j);
		}
	}

	iDos = 0;
	jDos = 0;
	randomCasilla();
	randomCasilla();
}

Tablero::~Tablero() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (tablero[i][j] != NULL) {
				delete tablero[i][j];
				tablero[i][j] = NULL;
			}
		}
	}
}

Casilla* Tablero::getCasilla(int X, int Y) {
	return tablero[X][Y];
}

Casilla* Tablero::getCasilla(int position[2]) {
	return tablero[position[0]][position[1]];
}

int Tablero::getColumns() {
	return columns;
}

int Tablero::getRows() {
	return rows;
}

int Tablero::moveCasilla(int X1, int Y1, int X2, int Y2) {
	int moves = 0;
	if (X1 != X2 || Y1 != Y2) {
		int num = getCasilla(X1, Y1)->getNumber();
		getCasilla(X2, Y2)->setNumber(num);
		getCasilla(X1, Y1)->setNumber(0);
		moves++;
	}
	return moves;
}

int Tablero::moveCasilla(int position0[2], int position1[2]) {
	int moves = 0;
	if (position0[0] != position1[0] || position0[1] != position1[1]) {
		int num = getCasilla(position0)->getNumber();
		getCasilla(position1)->setNumber(num);
		getCasilla(position0)->setNumber(0);
		moves++;
	}
	return moves;
}

int Tablero::sumCasilla(int X1, int Y1, int X2, int Y2) {
	int moves = 0;
	if (X1 != X2 || Y1 != Y2) {
		int num1 = getCasilla(X1, Y1)->getNumber();
		int num2 = getCasilla(X2, Y2)->getNumber();
		getCasilla(X2, Y2)->setNumber(num1+num2);
		getCasilla(X2, Y2)->setSuma(true);
		getCasilla(X1, Y1)->setNumber(0);
		moves++;
	}
	return moves;
}

int Tablero::sumCasilla(int position0[2], int position1[2]) {
	int moves = 0;
	if (position0[0] != position1[0] || position0[1] != position1[1]) {
		int num1 = getCasilla(position0)->getNumber();
		int num2 = getCasilla(position1)->getNumber();
		getCasilla(position1)->setNumber(num1+num2);
		getCasilla(position1)->setSuma(true);
		getCasilla(position0)->setNumber(0);
		moves++;
	}
	return moves;
}

void Tablero::randomCasilla() {
	int i = rand() % rows;
	int j = rand() % columns;
	while (getCasilla(i,j)->getNumber() != 0) {
		i = rand() % rows;
		j = rand() % columns;
	}
	
	int num = rand() % 100;
	if (num < 90) {
		num = 2;
	} else {
		num = 4;
	}
	
	getCasilla(i,j)->setNumber(num);

	iDos = i;
	jDos = j;
}

void Tablero::setDos(int X, int Y) {

	if(tablero[X][Y] == 0) {
		getCasilla(X,Y)->setNumber(2);
		iDos = X;
		jDos = Y;
	}
}

void Tablero::getLastDos(int &X, int &Y) {

	X=iDos;
	Y=jDos;
}

Tablero& Tablero::operator =(const Tablero &A) {

    if(this!=&A){
    	for (int i = 0; i < this->rows; i++) {
    		for (int j = 0; j < this->columns; j++) {
				if (this->tablero[i][j] != NULL) {
					delete this->tablero[i][j];
					this->tablero[i][j] = NULL;
				}
    		}
    	}

        this->rows = A.rows;
        this->columns = A.columns;
        this->iDos = A.iDos;
        this->jDos = A.jDos;

    	for (int i = 0; i < this->rows; i++) {
    		for (int j = 0; j < this->columns; j++) {
				if (A.tablero[i][j] != NULL) {
					this->tablero[i][j] = new Casilla(i,j);
					*(this->tablero[i][j]) = *(A.tablero[i][j]);
				} else {
					this->tablero[i][j] = NULL;
				}
    		}
    	}
    }
    return *this;

}
