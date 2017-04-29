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
	void hacerEsperarFinTurno();
public:
	Mesa(unsigned char numeroPartida, int cantidadJugadores);
	unsigned int idRecurso();
	bool pedirTurno(int numeroJugador);
	bool hacerJugada(int carta, bool ultimaCarta);
	bool pasarTurno(int numeroJugador);
	void imprimir();
	bool ponerMano();
	std::vector<int> robarCartas();
	void destruir(){
		for (int i = 0;  i < moderadorTurnos.size(); i++){
			moderadorTurnos[i].destruir();
		}
		maso.invocar()->destruir();
	}
};

#endif
