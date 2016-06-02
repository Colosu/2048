/*
 * ControladorAutomatico.h
 *
 *  Created on: 16 de may. de 2016
 *      Author: colosu
 */

#ifndef CONTROLADORAUTOMATICO_H_
#define CONTROLADORAUTOMATICO_H_

#include "Controlador.h"
#include "Partida.h"
#include "GameTree.h"
#include <stdlib.h>
using namespace std;

class ControladorAutomatico: public Controlador {
public:
	ControladorAutomatico(Partida* party);
	~ControladorAutomatico();
	Partida* getPartida();
	bool detectMove();
protected:

private:

	Partida *partida;
	bool inicio;
	int X;
	int Y;
	GameTree *tree;
};

#endif /* CONTROLADORAUTOMATICO_H_ */
