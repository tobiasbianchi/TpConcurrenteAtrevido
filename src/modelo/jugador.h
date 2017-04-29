#ifndef JUGADOR
#define JUGADOR

#include <objetocompartido.h>
#include <maso.h>
#include <mesa.h>
#include "../core/semaforo.h"
#include "../core/HandlerEvento.h"
#include "../handlers/SIGINT_Handler.h"
#include <vector>

#define MAXIMOTIEMPOTURNO 2

#define RUTAJUGADOR "archivos/jugador"

class Jugador
{
private:

	int numeroJugador;
	std::vector<HandlerEvento *> gameSignals;
	SIGINT_Handler quitHandler;
	Maso maso;
	Mesa &mesa;
    Semaforo inicio;
	Semaforo turnoTermino;
	void decir(std::string mensaje);
	void ponerMano();
	std::vector<int> getBlockedSignals() {
		int signals[] = {HandlerSenial::SIGNAL_10,HandlerSenial::SIGNAL_11,HandlerSenial::SIGNAL_12,
						HandlerSenial::SIGATREVIDO, HandlerSenial::SIG_REPETIDA,SIGINT};
		std::vector<int> allSignals(signals, signals + sizeof(signals)/sizeof(int));
		return allSignals;
	}
public:
	Jugador(int numeroJugador, Mesa &mesa, std::vector<int> cartas);
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
	static const std::string ATREVIDO;
	static const std::string BUENOSDIAS;
	static const std::string BUENASNOCHES;
	static const std::string VENIA;
	static const int ID_SEMAFORO_INICIO = 20;
	static const int ID_SEMAFORO_TURNO_TERMINADO = 21;
};



#endif
