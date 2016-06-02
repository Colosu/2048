/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * tablero.h
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

#ifndef _TABLERO_H_
#define _TABLERO_H_

#include "Casilla.h"
#include "Config.h"

class Tablero {
public:

	Tablero();
	Tablero(int X, int Y);
	~Tablero();
	Casilla* getCasilla(int X, int Y);
	Casilla* getCasilla(int position[2]);
	int getColumns();
	int getRows();
	int moveCasilla(int X1, int Y1, int X2, int Y2);
	int moveCasilla(int position0[2], int position1[2]);
	int sumCasilla(int X1, int Y1, int X2, int Y2);
	int sumCasilla(int position0[2], int position1[2]);
	void randomCasilla();
	void setDos(int X, int Y);
	void getLastDos(int &X, int &Y);
	Tablero& operator =(const Tablero &A);
	 
protected:

private:

	int columns;
	int rows;
	int iDos;
	int jDos;
	Casilla* tablero[ROWS][COLUMNS];
};

#endif // _TABLERO_H_

