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


using namespace std;

int main(int argc, char** argv)
{
	unsigned char cantidadJugadores = 5;
	bool esHijo = false;
	int i=0;

	Semaforo esperarATodosInicializados(10,cantidadJugadores + 1);
	Semaforo esperarFinTurno(11,0);
	Mesa mesa(1, cantidadJugadores);
	//creo 7 semaforos, 5 por jugadores, 1 por barrera y 1 por mutex del maso.

	for(i = 0;i<cantidadJugadores && !esHijo;i++)
		esHijo = fork() == 0;

	if(esHijo)
	{
		Jugador yo(i, mesa, esperarATodosInicializados, esperarFinTurno);
		yo.jugar();
		std::cout << "Jugador " << i << "saliendo" <<std::endl;
		exit(0);
	}

	HandlerSenial::bloquearSenial(HandlerSenial::SIGNAL_10);
	HandlerSenial::bloquearSenial(HandlerSenial::SIGNAL_11);
	HandlerSenial::bloquearSenial(HandlerSenial::SIGNAL_12);
	HandlerSenial::bloquearSenial(HandlerSenial::SIG_MANO);
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
	std::cout << "Caso maestro saliendo" <<std::endl;
	return 0;
}
