//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_SIETEHANDLER_H
#define TPCONCURRENTEATREVIDO_SIETEHANDLER_H

#include "../core/HandlerSenial.h"
#include "JugadorHandler.h"

class SieteHandler : public JugadorHandler
{
public:
    SieteHandler(Jugador *jugador) : JugadorHandler(jugador, HandlerSenial::SIGATREVIDO) {}
    void makeJugadorPlay(){
    	getJugador()->hacerAtrevido();
    }
};
#endif //TPCONCURRENTEATREVIDO_SIETEHANDLER_H
