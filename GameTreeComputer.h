/*
 * GameTreeComputer.h
 *
 *  Created on: 22 de may. de 2016
 *      Author: colosu
 */

#ifndef GAMETREECOMPUTER_H_
#define GAMETREECOMPUTER_H_

#include "GameTree.h"
#include "Config.h"

class GameTreeComputer: public GameTree {
public:
	GameTreeComputer(Partida* party, int parada, int plus = 0);
	~GameTreeComputer();
	void setChilds();
	direction chooseChild();
	int getValue();
	Partida* getPartida();
protected:

private:
	int value;
	GameTree* tree[ROWS][COLUMNS];
	Partida* partida;
	int stop;
};

#endif /* GAMETREECOMPUTER_H_ */
