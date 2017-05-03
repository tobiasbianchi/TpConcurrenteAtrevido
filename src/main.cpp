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
#include "Arbitro.h"
#include <fstream>
#include <exception>

#define LLAMAR_TP "Llamarl como | .tp 6 debug | .tp debug | .tp |"
using namespace std;
typedef struct {
	bool debug;
	int jugadores;
} config;


config getConfig(int argc, char** argv){
	config configuration;
	configuration.debug = false;
	configuration.jugadores = 2;
	if (argc == 2){
		try{
			configuration.jugadores = std::stoi(argv[1]);
		} catch (std::exception e){
			if (strcmp(argv[1],"debug") == 0){
				configuration.debug = true;
			}
		}
	} else if (argc == 3){
		try{
			int temp = std::stoi(argv[1]);
			if (temp % 2 == 0 && temp <= 8 && temp >= 2){
				configuration.jugadores = temp;	
			} else {
				std::cout << "La cantidad de jugadores debe ser par entre 2 y 8" << std::endl;
				exit(1);
			}
		} catch (std::exception e){
			std::cout << LLAMAR_TP;
			exit(1);
		}
		if (strcmp(argv[2],"debug") == 0){
			configuration.debug = true;
		}
	}
	return configuration;

}

void printConfig(config configuration){
	std::cout << "Comenzando juego con " << configuration.jugadores <<" jugadores" << std::endl;
	std::cout << "Debug set to " << configuration.debug << std::endl;
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	config configuration = getConfig(argc,argv);
	printConfig(configuration);
	int cantidadJugadores = configuration.jugadores;
	Log::init("log.txt",configuration.debug);
	std::vector<Pipe*> allPipes = PipeFactory::getPipes(cantidadJugadores);
	std::vector<std::vector<int>> masosRepartidos = CartasFactory::prepararCartas(cantidadJugadores);
	Semaforo esperarATodosInicializados(Jugador::ID_SEMAFORO_INICIO, cantidadJugadores + 1);
	Semaforo esperarFinTurno(Jugador::ID_SEMAFORO_TURNO_TERMINADO,0);
	Mesa mesa(1, cantidadJugadores);

	bool esHijo = false;
	int i=0;

	for(i = 0;i < cantidadJugadores && !esHijo;i++)
		esHijo = fork() == 0;

	if(esHijo)
	{
		Jugador yo(i, mesa, masosRepartidos[i - 1], allPipes);
		yo.jugar();
		yo.destruir();
		Log::info("Jugador " + std::to_string(i) + " saliendo");
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
	
	Arbitro arbitro(cantidadJugadores);
	ObjetoCompartido<bool> termino(ID_TERMINO_COMPARTIDO,RUTAARCHIVOMESA);
	Semaforo terminoControl(ID_TERMINO_MUTEX, RUTAARCHIVOMESA);

	while(handler.getWasCalled() != 1)
	{
		bool temp;
		terminoControl.tomar();
		temp = *(termino.invocar());
		terminoControl.liberar();
		if (temp){
			break;
		}
		arbitro.contarCartas();
	}
	
	std::cout << 1 << std::endl;

	for (int i = 0; i < cantidadJugadores; i++){
		wait(NULL);
	}

	std::cout << 2 << std::endl;

	esperarATodosInicializados.destruir();
	esperarFinTurno.destruir();
	mesa.destruir();
	
	std::cout << 3 << std::endl;

	for (int i = 0; i < allPipes.size(); i++){
		delete allPipes.at(i);
	}

	std::cout << 4 << std::endl;

	terminoControl.destruir();
	Log::info("Arbitro saliendo");
	std::cout << 5 << std::endl;	
	Log::destroy();
	std::cout << 6 << std::endl;
	return 0;
}
