
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <HandlerSenial.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include "jugador.h"
#include <errno.h>
#include <string>
#include "OnceHandler.h"
#include "DoceHandler.h"
#include "DiezHandler.h"
#include "SieteHandler.h"
#include "CartaRepetidaHandler.h"

const std::string Jugador::ATREVIDO = "Atrevido";
const std::string Jugador::BUENOSDIAS = "Buenos Dias Seniorita";
const std::string Jugador::BUENASNOCHES = "Buenas Noches Caballero";
const std::string Jugador::VENIA = "\"Hizo venia\"";

Jugador::Jugador(unsigned char numeroJugador, Mesa &mesa, Semaforo &inicio,
                 Semaforo &turnoTermino) : maso(numeroJugador, RUTAJUGADOR),
										  numeroJugador(numeroJugador), mesa(mesa),
										  inicio(inicio), turnoTermino(turnoTermino)
{
	this->gameSignals.push_back(new DiezHandler(this));
	this->gameSignals.push_back(new OnceHandler(this));
	this->gameSignals.push_back(new DoceHandler(this));
	this->gameSignals.push_back(new SieteHandler(this));
	this->gameSignals.push_back(new CartaRepetidaHandler(this));
	for (int i = 0; i < gameSignals.size(); i++){
		HandlerEvento *eh = gameSignals[i];
		HandlerSenial::getInstancia()->registrarHandler(eh->getSignal(),eh,getBlockedSignals());
	}
    inicio.tomar();
    inicio.esperarACero();
}

Jugador::~Jugador(){
	for (int i = 0; i < gameSignals.size(); i++){
		HandlerEvento *eh = gameSignals[i];
		delete eh;
	}
	gameSignals.clear();
}

void Jugador::pensar()
{
	int srand(clock());
    int remaining_time = sleep(rand() % MAXIMOTIEMPOTURNO);
	while (remaining_time != 0 && remaining_time != -1){ //if interrupted in sleep, will wait whole time
        remaining_time = sleep(remaining_time);
    }
}

void Jugador::jugar()
{
	while(quitHandler.getWasCalled() == 0)
	{
        try{
            //me toca
            mesa.pedirTurno(numeroJugador);
            //esperar a que todos reaccionen
            decir("valor turnoTermino " + std::to_string(turnoTermino.obtenerValor()));
            turnoTermino.esperarACero();

            pensar();
            mesa.hacerJugada(numeroJugador + 2, turnoTermino);

            mesa.pasarTurno();

        }catch (Error e){
            if (errno != EINTR) {
                throw e;
            }
        }
	}
}

void Jugador::decir(std::string mensaje) {
    std::cout << "Jugador("  << (int)numeroJugador << "): " << mensaje << std::endl;
}

void Jugador::hacerVenia(){
	decir(VENIA);
}

void Jugador::reaccionoPorCompleto(){
	decir("Reacciono, valor turnoTermino: " + std::to_string(turnoTermino.obtenerValor()));
	turnoTermino.tomar();
}

void Jugador::hacerBuenasNoches(){
	 decir(BUENASNOCHES);
}

void Jugador::hacerBuenosDias(){
	decir(BUENOSDIAS);
}

void Jugador::hacerAtrevido(){
	 decir(ATREVIDO);
	 ponerMano();
}
void Jugador::hacerCartaRepetida(){
	ponerMano();
}

void Jugador::ponerMano(){
	decir("pone mano");
	if (mesa.ponerMano()){
		decir("roba cartas");
		std::vector<unsigned char> robadas = mesa.robarCartas();
		std::string robada = "";
		for (int i = 0; i < robadas.size(); i++){
			//TODO robar cartas
			robada += std::to_string(robadas[i]) + ";";
		}
		decir("robo " + robada);
	}

}
