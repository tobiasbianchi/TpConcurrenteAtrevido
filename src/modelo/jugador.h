#ifndef JUGADOR
#define JUGADOR

#include <objetocompartido.h>
#include <maso.h>
#include <mesa.h>
#include "../core/semaforo.h"
#include "../core/HandlerEvento.h"
#include "../core/HandlerSenial.h"
#include "../handlers/SIGINT_Handler.h"
#include <vector>
#include "pipe.h"
#include "objetocompartido.h"
#include "Log.h"
#include "definiciones.h"

class Jugador
{
private:

	int numeroJugador;
	std::vector<HandlerEvento *> gameSignals;
	SIGINT_Handler quitHandler;
	ObjetoCompartido<Maso> maso;
	Mesa &mesa;
    Semaforo inicio;
	Semaforo turnoTermino;
	std::vector<Pipe*> pipesEscritura;
	Pipe* lectura;
	void decir(std::string mensaje);
	void ponerMano();
	std::vector<int> getBlockedSignals() {
		int signals[] = {HandlerSenial::SIGNAL_10,HandlerSenial::SIGNAL_11,HandlerSenial::SIGNAL_12,
						HandlerSenial::SIGATREVIDO, HandlerSenial::SIG_REPETIDA};
		std::vector<int> allSignals(signals, signals + sizeof(signals)/sizeof(int));
		return allSignals;
	}

	void initSignals();
	void initPipes(std::vector<Pipe*> pipes);
	void decirDebug(std::string data);
public:
	Jugador(int numeroJugador, Mesa &mesa, std::vector<int> cartas, std::vector<Pipe*> pipes);
	~Jugador();
	void pensar();
	void jugar();
	void hacerAtrevido();
	void hacerBuenosDias();
	void hacerBuenasNoches();
	void hacerCartaRepetida();
	void hacerVenia();
	void reaccionoPorCompleto();
	void destruir();
	void mostrarseATodos();
	void verATodos();
	int getNumeroJugador(){
		return numeroJugador;
	}
	static const std::string ATREVIDO;
	static const std::string BUENOSDIAS;
	static const std::string BUENASNOCHES;
	static const std::string VENIA;
	static const int ID_SEMAFORO_INICIO = 20;
	static const int ID_SEMAFORO_TURNO_TERMINADO = 21;
};



#endif
