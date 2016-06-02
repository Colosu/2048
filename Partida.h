/*
 * Partida.h
 *
 *  Created on: 15/05/2016
 *      Author: colosu
 */

#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "Casilla.h"
#include "Tablero.h"

class Partida {
public:
	Partida();
	Partida(int X, int Y);
	~Partida();
	Tablero* getTab();
	int getMax();
	int getPunt();
	int getTurn();
	int getZeros();
	int getAdyacentes();
	void resetPartida(int X, int Y);
	int moveUp();
	int moveDown();
	int moveRight();
	int moveLeft();
	void newCasilla();
	bool isFinished();
	Partida& operator =(const Partida &A);
protected:

private:

	int max;
	int punt;
	int turn;
	Tablero* tab;
};

#endif /* PARTIDA_H_ */
