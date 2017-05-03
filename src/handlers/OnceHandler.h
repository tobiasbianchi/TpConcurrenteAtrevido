//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_ONCEHANLDER_H
#define TPCONCURRENTEATREVIDO_ONCEHANLDER_H

#include "../core/HandlerSenial.h"
#include "JugadorHandler.h"
#include "Log.h"

class OnceHandler : public JugadorHandler{
public:
    OnceHandler(Jugador *jugador) : JugadorHandler(jugador, HandlerSenial::SIGNAL_11) {}
    void makeJugadorPlay(){
    	getJugador()->hacerBuenasNoches();
    }
};
#endif //TPCONCURRENTEATREVIDO_ONCEHANLDER_H
