#include <mesa.h>
#include <signal.h>
#include <HandlerSenial.h>
#include <iostream>


Mesa::Mesa(unsigned char numeroPartida, unsigned char cantidadJugadores) : contador(numeroPartida), maso(idRecurso(), RUTAARCHIVOMESA, idRecurso(), RUTAARCHIVOMESA), turnoJugador(idRecurso(), RUTAARCHIVOMESA)
{
	//Como no se pueden copiar semaforos hay que reservar la memoria exacta antes o usar otra estructura contenedora.
	moderadorTurnos.reserve(cantidadJugadores);
	for(unsigned char i = 0; i<cantidadJugadores; i++)
		moderadorTurnos.emplace_back(idRecurso(), (i!=0) ? (0) : (1), RUTAARCHIVOMESA);	
}

unsigned int Mesa::idRecurso()
{
	return contador++;
}

bool Mesa::pedirTurno(unsigned char numeroJugador)
{
	std::cout << "pidiendo turno" << std::endl;
	moderadorTurnos.at(numeroJugador-1).tomar();
	std::cout << "turno dado" << std::endl;
	*(turnoJugador.invocar()) = numeroJugador;
}

bool Mesa::hacerJugada(unsigned char carta)
{
	maso.invocar()->ponerCarta(carta);
	if ((int)carta == 7){
		HandlerSenial::getInstancia()->broadcastSignal(SIGCHLD);
	} else if ((int)carta == 10){
		HandlerSenial::getInstancia()->broadcastSignal(SIGUSR1);
	} else if ((int)carta == 11) {
        HandlerSenial::getInstancia()->broadcastSignal(SIGTTOU);
    } else if ((int)carta == 12) {
        HandlerSenial::getInstancia()->broadcastSignal(SIGTTIN);
    }

	return true;
}

bool Mesa::pasarTurno()
{
	unsigned char numeroJugador = (*(turnoJugador.invocar()));

	if(numeroJugador < moderadorTurnos.size())
		moderadorTurnos.at(numeroJugador).liberar();
	else
		moderadorTurnos.at(0).liberar();
}

void Mesa::imprimir()
{
	maso.invocar()->mostrarCartas();		
}
