/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * casilla.h
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

#ifndef _CASILLA_H_
#define _CASILLA_H_

class Casilla {
public:

	Casilla();
	Casilla(int pos[]);
	Casilla(int XPosition, int YPosition);
	int* getPosition();
	int getNumber();
	int getXPosition();
	int getYPosition();
	bool getSuma();
	void setSuma(bool sum);
	void setNumber(int num);
	Casilla& operator =(const Casilla &A);
protected:

private:

	int number;
	int position[2];
	bool suma;
};
#endif // _CASILLA_H_

