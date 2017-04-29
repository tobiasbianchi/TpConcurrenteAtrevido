#ifndef MESA
#define MESA

#include <objetocompartido.h>
#include <maso.h>
#include <semaforo.h>
#include <vector>

#define RUTAARCHIVOMESA "archivos/mesa"

class Mesa
{
private:
	ObjetoCompartido<Maso> maso;
	std::vector<Semaforo> moderadorTurnos;
	unsigned int contador;
	ObjetoCompartido<unsigned char> turnoJugador;
	void hacerEsperarFinTurno();
public:
	Mesa(unsigned char numeroPartida, unsigned char cantidadJugadores);
	unsigned int idRecurso();
	bool pedirTurno(unsigned char numeroJugador);
	bool hacerJugada(unsigned char carta);
	bool pasarTurno(unsigned char numeroJugador);
	void imprimir();
	bool ponerMano();
	std::vector<unsigned char> robarCartas();
	void destruir(){
		for (int i = 0;  i < moderadorTurnos.size(); i++){
			moderadorTurnos[i].destruir();
		}
		maso.invocar()->destruir();
	}
};

#endif
