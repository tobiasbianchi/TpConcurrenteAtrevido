#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <mesa.h>
#include <maso.h>
#include "core/semaforo.h"
#include "core/HandlerSenial.h"
#include "handlers/SIGINT_Handler.h"
#include "excepciones.h"
#include "modelo/jugador.h"
#include "CartasFactory.h"
#include <stdlib.h>
#include <time.h>
#include "pipe.h"
#include "PipesFactory.h"
using namespace std;

int main(int argc, char** argv)
{
	srand(time(NULL));
	int cantidadJugadores = 5;
	bool esHijo = false;
	int i=0;

	std::vector<Pipe*> allPipes = PipeFactory::getPipes(cantidadJugadores);
	std::cout << "pipes creados" << std::endl;
	std::vector<std::vector<int>> masosRepartidos = CartasFactory::prepararCartas(cantidadJugadores);
	Semaforo esperarATodosInicializados(Jugador::ID_SEMAFORO_INICIO,cantidadJugadores + 1);
	Semaforo esperarFinTurno(Jugador::ID_SEMAFORO_TURNO_TERMINADO,0);
	Mesa mesa(1, cantidadJugadores);

	//creo 7 semaforos, 5 por jugadores, 1 por barrera y 1 por mutex del maso.

	for(i = 0;i < cantidadJugadores && !esHijo;i++)
		esHijo = fork() == 0;

	if(esHijo)
	{
		Jugador yo(i, mesa, masosRepartidos[i - 1], allPipes);
		yo.jugar();
		yo.destruir();
		std::cout << "Jugador " << i  << " saliendo" <<std::endl;
		exit(0);
	}

	HandlerSenial::bloquearSenial(HandlerSenial::SIGNAL_10);
	HandlerSenial::bloquearSenial(HandlerSenial::SIGNAL_11);
	HandlerSenial::bloquearSenial(HandlerSenial::SIGNAL_12);
	HandlerSenial::bloquearSenial(HandlerSenial::SIG_REPETIDA);
	HandlerSenial::bloquearSenial(HandlerSenial::SIGATREVIDO);

    SIGINT_Handler handler;

    HandlerSenial::getInstancia()->registrarHandler(SIGINT,&handler);
	esperarATodosInicializados.tomar();
	esperarATodosInicializados.esperarACero();

	while(handler.getWasCalled() != 1)
	{
		//system("clear");
		//mesa.imprimir();
		sleep(1);
	}

	for (int i = 0; i < cantidadJugadores; i++){
		wait(NULL);
	}

	esperarATodosInicializados.destruir();
	esperarFinTurno.destruir();
	mesa.destruir();

	for (int i = 0; i < allPipes.size(); i++){
		delete allPipes.at(i);
	}
	std::cout << "Caso maestro saliendo" <<std::endl;
	return 0;
}
