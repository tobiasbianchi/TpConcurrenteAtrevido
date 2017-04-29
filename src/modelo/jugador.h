#ifndef JUGADOR
#define JUGADOR

#include <objetocompartido.h>
#include <maso.h>
#include <mesa.h>
#include "../core/semaforo.h"
#include "../core/HandlerEvento.h"
#include "../handlers/SIGINT_Handler.h"

#define MAXIMOTIEMPOTURNO 2

#define RUTAJUGADOR "archivos/jugador"

class Jugador
{
private:

	unsigned char numeroJugador;
	std::vector<HandlerEvento *> gameSignals;
	SIGINT_Handler quitHandler;
	Maso maso;
	Mesa &mesa;
    Semaforo &inicio;
	Semaforo &turnoTermino;
	void decir(std::string mensaje);
	void ponerMano();
	std::vector<int> getBlockedSignals() {
		int signals[] = {HandlerSenial::SIGNAL_10,HandlerSenial::SIGNAL_11,HandlerSenial::SIGNAL_12,
						HandlerSenial::SIGATREVIDO, HandlerSenial::SIG_REPETIDA,SIGINT};
		std::vector<int> allSignals(signals, signals + sizeof(signals)/sizeof(int));
		return allSignals;
	}
public:
	Jugador(unsigned char numeroJugador, Mesa &mesa, Semaforo &inicio, Semaforo &turnoTermino);
	~Jugador();
	void pensar();
	void jugar();
	void hacerAtrevido();
	void hacerBuenosDias();
	void hacerBuenasNoches();
	void hacerCartaRepetida();
	void hacerVenia();
	void reaccionoPorCompleto();
	static const std::string ATREVIDO;
	static const std::string BUENOSDIAS;
	static const std::string BUENASNOCHES;
	static const std::string VENIA;
};



#endif
