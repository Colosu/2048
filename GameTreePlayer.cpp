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

GameTreePlayer::GameTreePlayer(Partida* party, int parada, int plus) {

	value = plus;
	partida = party;
	stop = parada;
	upTree = NULL;
	downTree = NULL;
	rightTree = NULL;
	leftTree = NULL;

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

		leftTree = new GameTreeComputer(party, stop - 1, 0);
	} else {

		leftTree = NULL;
	}

	party = new Partida();
	*party = *partida;
	moves = party->moveUp();
	if (moves != 0) {

		upTree = new GameTreeComputer(party, stop - 1, 0);
	} else {

		upTree = NULL;
	}

	party = new Partida();
	*party = *partida;
	moves = party->moveDown();
	if (moves != 0) {

		downTree = new GameTreeComputer(party, stop - 1, 0);
	} else {

		downTree = NULL;
	}

	party = new Partida();
	*party = *partida;
	moves = party->moveRight();
	if (moves != 0) {

		rightTree = new GameTreeComputer(party, stop - 1, 0);
	} else {

		rightTree = NULL;
	}
}

direction GameTreePlayer::chooseChild() {

	direction dir = left;
	int val = 0;
//	int max = 0;


	if (stop > 1) {
		if (leftTree != NULL/* && leftTree->getPartida()->getMax()+(pow(2,leftTree->getPartida()->getZeros()))+leftTree->getPartida()->getAdyacentes() >= max*/) {
			leftTree->setChilds();
			leftTree->chooseChild();
//			max = leftTree->getPartida()->getMax()+(pow(2,leftTree->getPartida()->getZeros()))+leftTree->getPartida()->getAdyacentes();
		} else {
			delete leftTree;
			leftTree = NULL;
		}
		if (upTree != NULL/* && upTree->getPartida()->getMax()+(pow(2,upTree->getPartida()->getZeros()))+upTree->getPartida()->getAdyacentes() >= max*/) {
			upTree->setChilds();
			upTree->chooseChild();
//			max = upTree->getPartida()->getMax()+(pow(2,upTree->getPartida()->getZeros()))+upTree->getPartida()->getAdyacentes();
		} else {
			delete upTree;
			upTree = NULL;
		}
		if (downTree != NULL/* && downTree->getPartida()->getMax()+(pow(2,downTree->getPartida()->getZeros()))+downTree->getPartida()->getAdyacentes() >= max*/) {
			downTree->setChilds();
			downTree->chooseChild();
//			max = downTree->getPartida()->getMax()+(pow(2,downTree->getPartida()->getZeros()))+downTree->getPartida()->getAdyacentes();
		} else {
			delete downTree;
			downTree = NULL;
		}
		if (rightTree != NULL/* && rightTree->getPartida()->getMax()+(pow(2,rightTree->getPartida()->getZeros()))+rightTree->getPartida()->getAdyacentes() >= max*/) {
			rightTree->setChilds();
			rightTree->chooseChild();
//			max = rightTree->getPartida()->getMax()+(pow(2,rightTree->getPartida()->getZeros()))+rightTree->getPartida()->getAdyacentes();
		} else {
			delete rightTree;
			rightTree = NULL;
		}
	}

	if (leftTree != NULL /*&& leftTree->getPartida()->getMax()+(pow(2,leftTree->getPartida()->getZeros()))+leftTree->getPartida()->getAdyacentes() >= max*/) {
		dir = left;
		val = leftTree->getValue();
	}
	if (upTree != NULL && upTree->getValue() > val /*&& upTree->getPartida()->getMax()+(pow(2,upTree->getPartida()->getZeros()))+upTree->getPartida()->getAdyacentes() >= max*/) {
		dir = up;
		val = upTree->getValue();
	} else if (upTree != NULL && val == 0) {
		dir = up;
		val = upTree->getValue();
	}
	if (downTree != NULL && downTree->getValue() > val /*&& downTree->getPartida()->getMax()+(pow(2,downTree->getPartida()->getZeros()))+downTree->getPartida()->getAdyacentes() >= max*/) {
		dir = down;
		val = downTree->getValue();
	} else if (downTree != NULL && val == 0) {
		dir = down;
		val = downTree->getValue();
	}
	if (rightTree != NULL && rightTree->getValue() > val /*&& rightTree->getPartida()->getMax()+(pow(2,rightTree->getPartida()->getZeros()))+rightTree->getPartida()->getAdyacentes() >= max*/) {
		dir = right;
		val = rightTree->getValue();
	} else if (rightTree != NULL && val == 0) {
		dir = right;
		val = rightTree->getValue();
	}

	value += val;

	return dir;
}

int GameTreePlayer::getValue() {

	return value;
}

Partida* GameTreePlayer::getPartida() {

	return partida;
}
