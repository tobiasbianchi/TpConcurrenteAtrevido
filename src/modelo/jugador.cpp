
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <HandlerSenial.h>
#include <signal.h>
#include <iostream>
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

Jugador::Jugador(int numeroJugador, Mesa &mesa, std::vector<int> cartas,
		std::vector<Pipe*> pipes) :
										  maso(numeroJugador, cartas, RUTAJUGADOR),
										  numeroJugador(numeroJugador), mesa(mesa),
										  inicio(Jugador::ID_SEMAFORO_INICIO),
										  turnoTermino(Jugador::ID_SEMAFORO_TURNO_TERMINADO)
{
	initSignals();
	initPipes(pipes);

    inicio.tomar();
    inicio.esperarACero();
}

void Jugador::initSignals(){
	this->gameSignals.push_back(new DiezHandler(this));
	this->gameSignals.push_back(new OnceHandler(this));
	this->gameSignals.push_back(new DoceHandler(this));
	this->gameSignals.push_back(new SieteHandler(this));
	this->gameSignals.push_back(new CartaRepetidaHandler(this));
	this->gameSignals.push_back(&quitHandler);
	for (int i = 0; i < gameSignals.size(); i++){
		HandlerEvento *eh = gameSignals[i];
		HandlerSenial::getInstancia()->registrarHandler(eh->getSignal(),eh,getBlockedSignals());
	}
}

void Jugador::initPipes(std::vector<Pipe*> pipes){
	int indiceJugador = numeroJugador - 1;
	lectura = pipes.at(indiceJugador);
	pipes.erase(pipes.begin() + indiceJugador);
	pipesEscritura = pipes;
}


Jugador::~Jugador(){
	for (int i = 0; i < gameSignals.size(); i++){
		HandlerEvento *eh = gameSignals[i];
		delete eh;
	}
	gameSignals.clear();
}

void Jugador::destruir(){
	maso.destruir();
	delete lectura;
	for (int i = 0; i < pipesEscritura.size(); i++){
		delete pipesEscritura.at(i);
	}
}

void Jugador::pensar()
{
	int srand(clock());
    //int remaining_time = sleep(rand() % MAXIMOTIEMPOTURNO);
	int remaining_time = sleep(1);
	while (remaining_time != 0 && remaining_time != -1){ //if interrupted in sleep, will wait whole time
        remaining_time = sleep(remaining_time);
    }
}

void Jugador::jugar()
{
	while(quitHandler.getWasCalled() == 0)
	{
        try{
        	//esperar a que todos reaccionen
        	turnoTermino.esperarACero();
        	//me toca
        	mesa.pedirTurno(numeroJugador);
            decir("Jugando");
            pensar();
            int carta = maso.sacarCarta();
            bool ultimaCarta = (maso.contarCartas() == 0);
            mesa.hacerJugada(carta, ultimaCarta);

            mesa.pasarTurno(numeroJugador);
        }catch (Error e){
        	if (errno != EINTR) {
                throw e;
            }
        }
	}
}

void Jugador::decir(std::string mensaje) {
    std::cout << "Jugador("  << numeroJugador << "): " << mensaje << std::endl;
}

void Jugador::hacerVenia(){
	decir(VENIA);
}

void Jugador::reaccionoPorCompleto(){
	mostrarseATodos();
	verATodos();
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
		std::vector<int> robadas = mesa.robarCartas();
		maso.agregarCartas(robadas);
		std::string robada = "";
		for (int i = 0; i < robadas.size(); i++){
			//TODO robar cartas
			robada += std::to_string(robadas[i]) + ";";
		}
		decir("roba " + robada);
	}
}

void Jugador::mostrarseATodos(){
	const void* data = &numeroJugador;
	for(int i = 0; i < pipesEscritura.size(); i++){
		pipesEscritura.at(i)->escribir(data,sizeof(int));
	}
}

void Jugador::verATodos(){
	std::string vistos = "";
	for(int i = 0; i < pipesEscritura.size(); i++){
		int buffer = 0;
		lectura->leer(&buffer,sizeof(int));
		vistos += std::to_string(buffer) + " . ";
	}
	decir("vio a " + vistos);
}
