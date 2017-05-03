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
										  maso(numeroJugador,RUTAJUGADOR,numeroJugador, cartas, RUTAJUGADOR),
										  numeroJugador(numeroJugador), mesa(mesa),
										  inicio(Jugador::ID_SEMAFORO_INICIO),
										  turnoTermino(Jugador::ID_SEMAFORO_TURNO_TERMINADO)
{
	initSignals();
	initPipes(pipes);

	decirDebug("Registro pipes y seniales. Esperando a todos inicializados");
    inicio.tomar();
    inicio.esperarACero();
    decirDebug("Inicializado");
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
	maso.invocar()->destruir();
	delete lectura;
	for (int i = 0; i < pipesEscritura.size(); i++){
		delete pipesEscritura.at(i);
	}
	decirDebug("Cerro todos los pipes");
}

void Jugador::pensar()
{
	int srand(clock());
    //int remaining_time = sleep(rand() % MAXIMOTIEMPOTURNO);
	int remaining_time = sleep(0);
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
    		decirDebug("Esperando a que todos reaccionen");
    		turnoTermino.esperarACero();
    		//me toca
    		decirDebug("Esperando a que sea mi turno");
    		mesa.pedirTurno(numeroJugador);
        	decir("Jugando");
        	pensar();
        	if (!mesa.terminoJuego()){
        		int carta = maso.invocar()->sacarCarta();
        		bool ultimaCarta = (maso.invocar()->contarCartas() == 0);	
        		mesa.hacerJugada(carta, ultimaCarta);
        		decir("paso turno");
        		mesa.pasarTurno(numeroJugador);
        	} else {
        		mesa.pasarTurno(numeroJugador);
        		break;
        	}
        	
        } catch(Error e){
        	if (errno != EINTR){
        		throw e;
        	}
        }
		
	}
}

void Jugador::decir(std::string mensaje) {
	Log::info("Jugador(" + std::to_string(numeroJugador) + "): " + mensaje);
}

void Jugador::decirDebug(std::string mensaje) {
	Log::debug("Jugador(" + std::to_string(numeroJugador) + "): " + mensaje);
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
		decir("Ultimo en poner mano");
		std::vector<int> robadas = mesa.robarCartas();
		maso.invocar()->agregarCartas(robadas);
		std::string robada = "";
		for (int i = 0; i < robadas.size(); i++){
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
	decir("se mostor a todos");
}

void Jugador::verATodos(){
	std::string vistos = "";
	decirDebug("viendo");
	for(int i = 0; i < pipesEscritura.size(); i++){
		int buffer = 0;
		lectura->leer(&buffer,sizeof(int));
		vistos += std::to_string(buffer) + " . ";
		decirDebug("vio a " + std::to_string(buffer));
	}
	decir("vio a " + vistos);
}
