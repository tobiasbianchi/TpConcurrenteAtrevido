//
// Created by tobias on 26/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_PONERMANOHANDLER_H
#define TPCONCURRENTEATREVIDO_PONERMANOHANDLER_H

#include "../core/HandlerSenial.h"
#include "JugadorHandler.h"
#include "Log.h"

class CartaRepetidaHandler : public JugadorHandler {
public:
    CartaRepetidaHandler(Jugador *jugador) : JugadorHandler(jugador,HandlerSenial::SIG_REPETIDA) {}
    void makeJugadorPlay(){
    	getJugador()->hacerCartaRepetida();
    }
};
#endif //TPCONCURRENTEATREVIDO_PONERMANOHANDLER_H
