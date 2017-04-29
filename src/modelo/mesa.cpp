#include <mesa.h>
#include <signal.h>
#include <HandlerSenial.h>
#include <iostream>
#include "../core/HandlerSenial.h"
#include "jugador.h"

Mesa::Mesa(unsigned char numeroPartida, int cantidadJugadores) : contador(numeroPartida),
							maso(ID_MASO_GENERAL_COMAPRTIDO, RUTAARCHIVOMESA, ID_MASO_GENERAL_MUTEX, RUTAARCHIVOMESA)
{
	//Como no se pueden copiar semaforos hay que reservar la memoria exacta antes o usar otra estructura contenedora.
	moderadorTurnos.reserve(cantidadJugadores);
	for(int i = 0; i<cantidadJugadores; i++)
		moderadorTurnos.emplace_back(idRecurso(), (i!=0) ? (0) : (1), RUTAARCHIVOMESA);
}

unsigned int Mesa::idRecurso()
{
	return contador++;
}

bool Mesa::pedirTurno(int numeroJugador)
{
	moderadorTurnos.at(numeroJugador-1).tomar();
}

void Mesa::hacerEsperarFinTurno(){
	Semaforo turnoTermino(Jugador::ID_SEMAFORO_TURNO_TERMINADO);
	for (int j = 0; j < moderadorTurnos.size(); j++){
		turnoTermino.liberar();
	}
}

bool Mesa::hacerJugada(int carta, bool ultimaCarta)
{
	bool repitioUltima = maso.invocar()->ponerCarta(carta);

	if (ultimaCarta){
		std::cout << "gano alguiend" << std::endl;
		HandlerSenial::getInstancia()->broadcastSignal(SIGINT);
	}else{
		switch (carta){
			case 10:
				hacerEsperarFinTurno();
				HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_10);
				break;
			case 11:
				hacerEsperarFinTurno();
				HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_11);
				break;
			case 12:
				hacerEsperarFinTurno();
				HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGNAL_12);
				break;
			case 7:
				hacerEsperarFinTurno();
				HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIGATREVIDO);
				break;
		}

		if (repitioUltima && ((int)carta != 7)){
			hacerEsperarFinTurno();
			HandlerSenial::getInstancia()->broadcastSignal(HandlerSenial::SIG_REPETIDA);
		}
	}

	imprimir();
	return true;
}

bool Mesa::pasarTurno(int numeroJugador)
{
	if(numeroJugador < moderadorTurnos.size()){
		moderadorTurnos.at(numeroJugador).liberar();
	}
	else{
		moderadorTurnos.at(0).liberar();
	}
}

void Mesa::imprimir()
{
	maso.invocar()->mostrarCartas();		
}

bool Mesa::ponerMano() {
	return maso.invocar()->ponerMano(moderadorTurnos.size());
}

std::vector<int> Mesa::robarCartas(){
	return maso.invocar()->robarMaso();
}

int Mesa::cantidadJugadores(){
	return moderadorTurnos.size();
}
