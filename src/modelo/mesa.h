#ifndef MESA
#define MESA

#include <objetocompartido.h>
#include <maso.h>
#include <semaforo.h>
#include <vector>
#include "definiciones.h"
#include "Log.h"


class Mesa
{
private:
	ObjetoCompartido<Maso> maso;
	ObjetoCompartido<bool> termino;
	std::vector<Semaforo> moderadorTurnos;
	Semaforo terminoControl;
	unsigned int contador;
	void hacerEsperarFinTurno();
public:
	Mesa(unsigned char numeroPartida, int cantidadJugadores);
	unsigned int idRecurso();
	bool terminoJuego();
	bool pedirTurno(int numeroJugador);
	void hacerJugada(int carta, bool ultimaCarta);
	bool pasarTurno(int numeroJugador);
	void imprimir();
	bool ponerMano();
	int cantidadJugadores();
	std::vector<int> robarCartas();
	void destruir(){
		for (int i = 0;  i < moderadorTurnos.size(); i++){
			moderadorTurnos[i].destruir();
		}
		maso.invocar()->destruir();
	}
};

#endif
