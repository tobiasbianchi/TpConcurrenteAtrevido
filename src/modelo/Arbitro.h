#ifndef ARBITRO
#define ARBITRO


#include <vector>
#include "objetocompartido.h"
#include "maso.h"
#include "semaforo.h"
#include "definiciones.h"
#include "Log.h"

class Arbitro
{
	private:
		int numeroJugadores;
		std::vector<ObjetoCompartido<Maso>*> masosJugadores;
		void bloquearMaso();
		void liberarMaso();
	public:
		Arbitro(int numeroJugadores);
		void contarCartas();
		void destruirMasos();
		~Arbitro();
};



#endif
