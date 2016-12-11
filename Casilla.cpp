/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * casilla.cc
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

#include "Casilla.h"
#include <stdio.h>
using namespace std;

Casilla::Casilla() {
	number = 0;
	position[0] = 0;
	position[1] = 0;
	suma = false;
}

Casilla::Casilla(int pos[]) {
	number = 0;
	position[0] = pos[0];
	position[1] = pos[1];
	suma = false;
}

Casilla::Casilla(int XPosition, int YPosition) {
	number = 0;
	position[0] = XPosition;
	position[1] = YPosition;
	suma = false;
}

int* Casilla::getPosition() {
	return position;
}

int Casilla::getNumber() {
	return number;
}

int Casilla::getXPosition() {
	return position[0];
}

int Casilla::getYPosition() {
	return position[1];
}

bool Casilla::getSuma() {

	return suma;
}

void Casilla::setSuma(bool sum) {

	suma = sum;
}

void Casilla::setNumber(int num) {
	number = num;
}

Casilla& Casilla::operator =(const Casilla &A) {

    if(this!=&A && &A != 0){
        this->number = A.number;
        this->position[0] = A.position[0];
        this->position[1] = A.position[1];
        this->suma = A.suma;
    }
    return *this;

}
