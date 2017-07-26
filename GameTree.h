/*
 * GameTree.h
 *
 *  Created on: 17 de may. de 2016
 *      Author: colosu
 */

#ifndef GAMETREE_H_
#define GAMETREE_H_

#include "Partida.h"

enum direction {up, down, right, left};

class GameTree {
public:

	virtual ~GameTree();
	virtual void setChilds();
	virtual direction chooseChild();
	virtual int getValue();
	virtual int getSuccess();
	virtual Partida* getPartida();
protected:

private:
	int value;
	int success;
	Partida* partida;
};

#endif /* GAMETREE_H_ */
