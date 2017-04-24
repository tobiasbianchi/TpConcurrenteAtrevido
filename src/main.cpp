#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

#include <mesa.h>
#include <maso.h>
#include <jugador.h>
#include "core/semaforo.h"
#include "core/HandlerSenial.h"
#include "handlers/SIGINT_Handler.h"
#include "excepciones.h"


using namespace std;

int main(int argc, char** argv)
{
	unsigned char cantidadJugadores = 5;
	bool esHijo = false;
	int i=0;

	Semaforo esperarATodosInicializados(10,cantidadJugadores + 1);
	Mesa mesa(1, cantidadJugadores);
	SIGINT_Handler handler;
	HandlerSenial::getInstancia()->registrarHandler(SIGINT,&handler);
	for(i = 0;i<cantidadJugadores && !esHijo;i++)
		esHijo = fork() == 0;	

	if(esHijo)
	{
		std::cout << "something" << std::endl;
		Jugador yo(i, mesa);
		esperarATodosInicializados.tomar();
		esperarATodosInicializados.esperarACero();
		while(handler.getGracefulQuit() != 1)
		{
			try {
				yo.jugar();
			}catch (Error e){
				std::cout << i << e.what() << std::endl;
			}
		}
		std::cout << "Jugador " << i << "saliendo" <<std::endl;
		exit(0);
	}
	HandlerSenial::bloquearSenial(SIGCHLD);
	HandlerSenial::bloquearSenial(SIGTTIN);
	HandlerSenial::bloquearSenial(SIGUSR1);
	HandlerSenial::bloquearSenial(SIGUSR2);

	esperarATodosInicializados.tomar();
	esperarATodosInicializados.esperarACero();

	while(handler.getGracefulQuit() != 1)
	{
		//system("clear");
		std::cout<< "nuevo impresion" << std::endl;
		mesa.imprimir();
		sleep(1);
	}

	for (int i = 0; i < cantidadJugadores; i++){
		wait(NULL);
	}
	std::cout << "Caso maestro saliendo" <<std::endl;
	return 0;
}
