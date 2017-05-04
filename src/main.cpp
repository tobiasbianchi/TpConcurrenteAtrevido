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
#include <time.h>

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

bool exists_file (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}
std::string newFileName(){
	std::string base = "Log.";
	std::string extension = ".txt";
	time_t timeLong = time(NULL);
	struct tm* timeNow = localtime(&timeLong);
	int year = timeNow->tm_year + 1900;
	int month = timeNow->tm_mon + 1;
	int day = timeNow->tm_mday;
	int hour = timeNow->tm_hour;
	int minute = timeNow->tm_min;
	int seconds = timeNow->tm_sec;
	return base + std::to_string(year) + "." +  std::to_string(month) + "."  + std::to_string(day) 
			+ "." + std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(seconds)
			+ extension;
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
	Log::init(newFileName(),configuration.debug);
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

	for (int i = 0; i < cantidadJugadores; i++){
		wait(NULL);
	}

	esperarATodosInicializados.destruir();
	esperarFinTurno.destruir();
	mesa.destruir();

	for (int i = 0; i < allPipes.size(); i++){
		delete allPipes.at(i);
	}

	terminoControl.destruir();
	Log::info("Arbitro saliendo");
	Log::destroy();
	return 0;
}
