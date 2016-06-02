/*
 * GameTreePlayer.cpp
 *
 *  Created on: 22 de may. de 2016
 *      Author: colosu
 */

#include "GameTreePlayer.h"
#include "GameTree.h"
#include "GameTreeComputer.h"
#include "Partida.h"
#include <stdio.h>
#include <math.h>
using namespace std;

GameTreePlayer::GameTreePlayer(Partida* party, int parada, int objetivo) {

	value = 0;
	success = 0;
	partida = party;
	stop = parada;
	upTree = NULL;
	downTree = NULL;
	rightTree = NULL;
	leftTree = NULL;
	target = objetivo;


	if (target == 0) {

		int valor = 1;

		for (int i = 0; i < partida->getTab()->getRows(); i++) {
			valor *= partida->getTab()->getCasilla(i,0)->getNumber();
		}

		if (partida->getTab()->getCasilla(0,0)->getNumber() != partida->getMax()) {

			target = 1;
		} else if (valor == 0) {

			target = 2;
		} else {

			target = 3;
		}
	}

	int i = 0;
	int j = 0;
	partida->getTab()->getLastDos(i,j);
	value -= partida->getTurn()*2;

	int I = i;
	while (I < partida->getTab()->getRows() - 1 && partida->getTab()->getCasilla(I,j)->getNumber() == 0) {
		I++;
	}
	if (partida->getTab()->getCasilla(I,j)->getNumber() == 2) {
		value += partida->getTurn()/2;
	}
	if (i < partida->getTab()->getRows() - 1 && partida->getTab()->getCasilla(i+1,j)->getNumber() > partida->getTab()->getCasilla(i,j)->getNumber()) {
		value -= partida->getTurn()*4;
	}


	int J = j;
	while (J < partida->getTab()->getColumns() - 1 && partida->getTab()->getCasilla(i,J)->getNumber() == 0) {
		J++;
	}
	if (partida->getTab()->getCasilla(i,J)->getNumber() == 2) {
		value += partida->getTurn()/2;
	}
	if (j < partida->getTab()->getColumns() - 1 && partida->getTab()->getCasilla(i,j+1)->getNumber() > partida->getTab()->getCasilla(i,j)->getNumber()) {
		value -= partida->getTurn()*4;
	}

	I = i;
	while (I > 0 && partida->getTab()->getCasilla(I,j)->getNumber() == 0) {
		I--;
	}
	if (partida->getTab()->getCasilla(I,j)->getNumber() == 2) {
		value += partida->getTurn()/2;
	}
	if (i > 0 && partida->getTab()->getCasilla(i-1,j)->getNumber() > partida->getTab()->getCasilla(i,j)->getNumber()) {
		value -= partida->getTurn()*4;
	}

	J = j;
	while (J > 0 && partida->getTab()->getCasilla(i,J)->getNumber() == 0) {
		J--;
	}
	if (partida->getTab()->getCasilla(i,J)->getNumber() == 2) {
		value += partida->getTurn()/2;
	}
	if (j > 0 && partida->getTab()->getCasilla(i,j-1)->getNumber() > partida->getTab()->getCasilla(i,j)->getNumber()) {
		value -= partida->getTurn()*4;
	}
}

GameTreePlayer::~GameTreePlayer() {

	if (&upTree != NULL) {
		delete upTree;
	}
	upTree = NULL;
	if (downTree != NULL) {
		delete downTree;
	}
	downTree = NULL;
	if (rightTree != NULL) {
		delete rightTree;
	}
	rightTree = NULL;
	if (leftTree != NULL) {
		delete leftTree;
	}
	leftTree = NULL;
	delete partida;
}

void GameTreePlayer::setChilds() {

	int moves = 0;
	Partida* party = new Partida();
	*party = *partida;
	moves = party->moveLeft();
	if (moves != 0) {

		leftTree = new GameTreeComputer(party, stop - 1, target);
	} else {

		leftTree = NULL;
	}

	party = new Partida();
	*party = *partida;
	moves = party->moveUp();
	if (moves != 0) {

		upTree = new GameTreeComputer(party, stop - 1, target);
	} else {

		upTree = NULL;
	}

	party = new Partida();
	*party = *partida;
	moves = party->moveDown();
	if (moves != 0) {

		downTree = new GameTreeComputer(party, stop - 1, target);
	} else {

		downTree = NULL;
	}

	party = new Partida();
	*party = *partida;
	moves = party->moveRight();
	if (moves != 0) {

		rightTree = new GameTreeComputer(party, stop - 1, target);
	} else {

		rightTree = NULL;
	}
}

direction GameTreePlayer::chooseChild() {

	direction dir = left;
	int val = 0;


	if (stop > 1 && success == 0) {
		if (leftTree != NULL) {
			leftTree->setChilds();
			leftTree->chooseChild();
		} else {
			delete leftTree;
			leftTree = NULL;
		}
		if (upTree != NULL) {
			upTree->setChilds();
			upTree->chooseChild();
		} else {
			delete upTree;
			upTree = NULL;
		}
		if (downTree != NULL) {
			downTree->setChilds();
			downTree->chooseChild();
		} else {
			delete downTree;
			downTree = NULL;
		}
		if (rightTree != NULL) {
			rightTree->setChilds();
			rightTree->chooseChild();
		} else {
			delete rightTree;
			rightTree = NULL;
		}
	}

	if (target != 3) {
		if (leftTree != NULL) {
			dir = left;
			val = leftTree->getSuccess();
		}
		if (upTree != NULL && upTree->getSuccess() > val) {
			dir = up;
			val = upTree->getSuccess();
		} else if (upTree != NULL && val == 0) {
			dir = up;
			val = upTree->getSuccess();
		}
		if (downTree != NULL && downTree->getSuccess() > val) {
			dir = down;
			val = downTree->getValue();
		} else if (downTree != NULL && val == 0) {
			dir = down;
			val = downTree->getSuccess();
		}
		if (rightTree != NULL && rightTree->getSuccess() > val) {
			dir = right;
			val = rightTree->getSuccess();
		} else if (rightTree != NULL && val == 0) {
			dir = right;
			val = rightTree->getSuccess();
		}

		success = val;

		if (success == 0) {

			if (leftTree != NULL) {
				dir = left;
				val = leftTree->getValue();
			}
			if (upTree != NULL && upTree->getValue() > val) {
				dir = up;
				val = upTree->getValue();
			} else if (upTree != NULL && val == 0) {
				dir = up;
				val = upTree->getValue();
			}
			if (downTree != NULL && downTree->getValue() > val) {
				dir = down;
				val = downTree->getValue();
			} else if (downTree != NULL && val == 0) {
				dir = down;
				val = downTree->getValue();
			}
			if (rightTree != NULL && rightTree->getValue() > val) {
				dir = right;
				val = rightTree->getValue();
			} else if (rightTree != NULL && val == 0) {
				dir = right;
				val = rightTree->getValue();
			}
			value += val;
		}
	} else {

		if (leftTree != NULL) {
			dir = left;
			val = leftTree->getValue();
		}
		if (upTree != NULL && upTree->getValue() > val) {
			dir = up;
			val = upTree->getValue();
		} else if (upTree != NULL && val == 0) {
			dir = up;
			val = upTree->getValue();
		}
		if (downTree != NULL && downTree->getValue() > val) {
			dir = down;
			val = downTree->getValue();
		} else if (downTree != NULL && val == 0) {
			dir = down;
			val = downTree->getValue();
		}
		if (rightTree != NULL && rightTree->getValue() > val) {
			dir = right;
			val = rightTree->getValue();
		} else if (rightTree != NULL && val == 0) {
			dir = right;
			val = rightTree->getValue();
		}
		value += val;
	}


	return dir;
}

int GameTreePlayer::getValue() {

	return value;
}

int GameTreePlayer::getSuccess() {

	return success;
}

Partida* GameTreePlayer::getPartida() {

	return partida;
}
