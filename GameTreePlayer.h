/*
 * GameTreePlayer.h
 *
 *  Created on: 22 de may. de 2016
 *      Author: colosu
 */

#ifndef GAMETREEPLAYER_H_
#define GAMETREEPLAYER_H_

#include "GameTree.h"

class GameTreePlayer: public GameTree {
public:
	GameTreePlayer(Partida* party, int parada, int objetivo = 0);
	~GameTreePlayer();
	void setChilds();
	direction chooseChild();
	int getValue();
	int getSuccess();
	Partida* getPartida();
protected:

private:
	int value;
	int success;
	GameTree *upTree;
	GameTree *downTree;
	GameTree *rightTree;
	GameTree *leftTree;
	Partida* partida;
	int stop;
	int target;
};

#endif /* GAMETREEPLAYER_H_ */
