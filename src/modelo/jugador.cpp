
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <HandlerSenial.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include "jugador.h"

const std::string Jugador::ATREVIDO = "Atrevido";
const std::string Jugador::BUENOSDIAS = "Buenos Dias Seniorita";
const std::string Jugador::BUENASNOCHES = "Buenas Noches Caballero";
const std::string Jugador::VENIA = "\"Hizo venia\"";

Jugador::Jugador(unsigned char numeroJugador, Mesa &mesa, Semaforo &inicio,
                 Semaforo &turnoTermino) : maso(numeroJugador, RUTAJUGADOR),
                                                                              numeroJugador(numeroJugador), mesa(mesa),
                                                                              inicio(inicio), turnoTermino(turnoTermino)
{
	HandlerSenial::getInstancia()->registrarHandler(diezHandler.getSignal(),&diezHandler);
	HandlerSenial::getInstancia()->registrarHandler(onceHandler.getSignal(),&onceHandler);
	HandlerSenial::getInstancia()->registrarHandler(doceHandler.getSignal(),&doceHandler);
	HandlerSenial::getInstancia()->registrarHandler(sieteHandler.getSignal(),&sieteHandler);
    HandlerSenial::getInstancia()->registrarHandler(ponerManoHandler.getSignal(),&ponerManoHandler);
    HandlerSenial::getInstancia()->registrarHandler(quitHandler.getSignal(),&quitHandler);
    inicio.tomar();
    inicio.esperarACero();
}

void Jugador::pensar()
{
	int srand(clock());
    int remaining_time = sleep(rand() % MAXIMOTIEMPOTURNO);
	while (remaining_time != 0 and remaining_time != -1){ //if interrupted in sleep, will wait whole time
        remaining_time = sleep(remaining_time);
    }
}

void Jugador::jugar()
{
	while(quitHandler.getWasCalled() == 0)
	{
        try{
            //me toca
            mesa.pedirTurno(numeroJugador);
            //esperar a que todos reaccionen
            std::cout << "valor turnoTermino " << turnoTermino.obtenerValor() << std::endl;
            turnoTermino.esperarACero();

            pensar();
            mesa.hacerJugada(numeroJugador + 2, turnoTermino);

            mesa.pasarTurno();

        }catch (Error e){
            if (errno != EINTR) {
                throw e;
            }
        }

        //problema -> no se asegura que mano y siete fueron handleadas
        // por lo que no tomar el semaforo y se queda bloqueado.
        if (diezHandler.getWasCalled()){
            decir(BUENOSDIAS);
            diezHandler.reset();
            //asi
            turnoTermino.tomar();
        } else if (onceHandler.getWasCalled()){
            decir(BUENASNOCHES);
            onceHandler.reset();
            //asi
            turnoTermino.tomar();
        } else if (doceHandler.getWasCalled()){
            decir(VENIA);
            doceHandler.reset();
            //asi
            turnoTermino.tomar();
        } else if (sieteHandler.getWasCalled()){
            decir(ATREVIDO);
            sieteHandler.reset();
        } else if (ponerManoHandler.getWasCalled()){

            if (mesa.ponerMano()){
                decir("roba cartas");
                std::vector<unsigned char> robadas = mesa.robarCartas();
                std::string robada = "";
                for (int i = 0; i < robadas.size(); i++){
                    //TODO robar cartas
                    robada += robadas[i] + ";";
                }
                decir("robo " + robada);
            }
            decir("pone mano");
            //asi
            turnoTermino.tomar();
        }
	}
}

void Jugador::decir(std::string mensaje) {
    std::cout << "Jugador("  << (int)numeroJugador << "): " << mensaje << std::endl;
}


