#ifndef MESA
#define MESA

#include <objetocompartido.h>
#include <maso.h>
#include <mutex.h>
#include <vector>

#include <iostream>

#define RUTAARCHIVOMESA "archivos/mesa"

class Mesa
{
private:
	ObjetoCompartido<Maso> maso;
	std::vector<Mutex> moderadorTurnos;
	unsigned int contador;

public:
	Mesa(unsigned char numeroPartida, unsigned char cantidadJugadores) : contador(numeroPartida), maso(idRecurso(), RUTAARCHIVOMESA, idRecurso(), RUTAARCHIVOMESA)
	{
		moderadorTurnos.reserve(cantidadJugadores);
		for(unsigned char i = 0; i<cantidadJugadores; i++)
			moderadorTurnos.emplace_back(idRecurso(), i != 0, RUTAARCHIVOMESA);	
	}

	unsigned int idRecurso()
	{
		return contador++;
	}

	bool hacerJugada(unsigned char numeroJugador, unsigned char carta)
	{
		std::cout << (int)numeroJugador << " voy a entrar" <<std::endl; 
		moderadorTurnos.at(numeroJugador-1).tomar();
		std::cout << (int)numeroJugador << " entre" <<std::endl; 
		//Inicio de seccion critica

		maso.invocar()->ponerCarta(carta);	

		//Fin de seccion critica


		if(numeroJugador < moderadorTurnos.size())
		{
			std::cout << (int)numeroJugador << " libere a " << (int)numeroJugador+1 << std::endl; 
			moderadorTurnos.at(numeroJugador).liberar();
		}
		else
		{	
			moderadorTurnos.at(0).liberar();
			std::cout << (int)numeroJugador << " libere a " << 0 << std::endl; 
		}

		return true;
	}

	void imprimir()
	{
		maso.invocar()->mostrarCartas();		
	}
};

#endif
