//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_DOCEHANLDER_H
#define TPCONCURRENTEATREVIDO_DOCEHANLDER_H

#include "HandlerSenial.h"
#include "JugadorHandler.h"

class DoceHandler : public JugadorHandler {
public:
    DoceHandler(Jugador *jugador) : JugadorHandler(jugador, HandlerSenial::SIGNAL_12) {}
    void makeJugadorPlay(){
    	getJugador()->hacerVenia();
	}
};
#endif //TPCONCURRENTEATREVIDO_DOCEHANLDER_H
