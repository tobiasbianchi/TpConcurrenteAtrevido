//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_10HANDLER_H
#define TPCONCURRENTEATREVIDO_10HANDLER_H

#include "../core/HandlerSenial.h"
#include "JugadorHandler.h"

class DiezHandler : public JugadorHandler {
public:
    DiezHandler(Jugador *jugador) : JugadorHandler(jugador,HandlerSenial::SIGNAL_10) {}
    void makeJugadorPlay(){
    	getJugador()->hacerBuenosDias();
    }
};
#endif //TPCONCURRENTEATREVIDO_10HANDLER_H
