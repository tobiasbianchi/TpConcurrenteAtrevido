#include "Arbitro.h"
#include "jugador.h"
#include "mesa.h"

Arbitro::Arbitro(int numeroJugadores){
	this->numeroJugadores = numeroJugadores;
	for (int i = 1; i <= numeroJugadores; i++){
		masosJugadores.push_back(new ObjetoCompartido<Maso>(i,RUTAJUGADOR,i,RUTAJUGADOR));
	}
}

void Arbitro::bloquearMaso(){
	Semaforo mutexMasoMaestro(ID_MASO_GENERAL_MUTEX,RUTAARCHIVOMESA);
	mutexMasoMaestro.tomar();
}

void Arbitro::liberarMaso(){
	Semaforo mutexMasoMaestro(ID_MASO_GENERAL_MUTEX,RUTAARCHIVOMESA);
	mutexMasoMaestro.liberar();
}

void Arbitro::contarCartas(){
	bloquearMaso();
	int random = rand() % 100;
	float percentage = random / 100.0;
	if (PROBABILIDAD_ARBITRO >= percentage){
		for( int i = 0; i < masosJugadores.size(); i++ ){
			int cartas = masosJugadores.at(i)->invocar()->contarCartas();
			Log::info("Jugador " + std::to_string(i+1) + " tiene " + std::to_string(cartas) + " cartas");
		}
	}
	liberarMaso();
}

Arbitro::~Arbitro(){
	for( int i = 0; i < masosJugadores.size(); i++ ){
		delete masosJugadores.at(i);
	}
}