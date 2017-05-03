//
// Created by tobias on 26/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_JUGADORHANDLER_H
#define TPCONCURRENTEATREVIDO_JUGADORHANDLER_H

#include <csignal>
#include <assert.h>
#include <algorithm>
#include "HandlerEvento.h"
#include "../modelo/jugador.h"
#include "Log.h"

class JugadorHandler : public HandlerEvento {
private:
    Jugador* jugador;
public:
    JugadorHandler (Jugador* jugador, int signal) : HandlerEvento(signal) {
    	this->jugador = jugador;
    }
    ~JugadorHandler () {
    }
    Jugador* getJugador(){
    	return this->jugador;
    }

    virtual int handleSenial ( int signum ) {
    	assert ( signum == getSignal() );
    	makeJugadorPlay();
    	this->jugador->reaccionoPorCompleto();
    	return 0;
    }

    virtual void makeJugadorPlay() = 0;
};
#endif //TPCONCURRENTEATREVIDO_BASICHANDLER_H
