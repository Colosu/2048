/*
 * ControladorManual.h
 *
 *  Created on: 16 de may. de 2016
 *      Author: colosu
 */

#ifndef CONTROLADORMANUAL_H_
#define CONTROLADORMANUAL_H_

#include "Controlador.h"
#include "Partida.h"

class ControladorManual: public Controlador {
public:
	ControladorManual(Partida* party);
	~ControladorManual();
	Partida* getPartida();
	bool detectMove();
protected:

private:

	Partida *partida;
};

#endif /* CONTROLADORMANUAL_H_ */
