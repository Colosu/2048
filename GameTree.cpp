/*
 * GameTree.cpp
 *
 *  Created on: 17 de may. de 2016
 *      Author: colosu
 */

#include "GameTree.h"
#include "Partida.h"

GameTree::~GameTree() {

}

void GameTree::setChilds() {


}

direction GameTree::chooseChild() {

	return up;
}

int GameTree::getValue() {

	return value;
}

int GameTree::getSuccess() {

	return success;
}

Partida* GameTree::getPartida() {

	return partida;
}
