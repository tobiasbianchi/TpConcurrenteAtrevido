#ifndef MESA
#define MESA

#include <objetocompartido.h>
#include <maso.h>
#include <semaforo.h>
#include <vector>

#define RUTAARCHIVOMESA "archivos/mesa"

class Mesa
{
private:
	ObjetoCompartido<Maso> maso;
	std::vector<Semaforo> moderadorTurnos;
	unsigned int contador;

public:
	Mesa(unsigned char numeroPartida, unsigned char cantidadJugadores) : contador(numeroPartida), maso(idRecurso(), RUTAARCHIVOMESA, idRecurso(), RUTAARCHIVOMESA)
	{
		moderadorTurnos.reserve(cantidadJugadores);
		for(unsigned char i = 0; i<cantidadJugadores; i++)
			moderadorTurnos.emplace_back(idRecurso(), (i!=0) ? (0) : (1), RUTAARCHIVOMESA);	
	}

	unsigned int idRecurso()
	{
		return contador++;
	}

	bool hacerJugada(unsigned char numeroJugador, unsigned char carta)
	{
		moderadorTurnos.at(numeroJugador-1).tomar();
		//Inicio de seccion critica

		maso.invocar()->ponerCarta(carta);	

		//Fin de seccion critica


		if(numeroJugador < moderadorTurnos.size())
			moderadorTurnos.at(numeroJugador).liberar();
		else
			moderadorTurnos.at(0).liberar();

		return true;
	}

	void imprimir()
	{
		maso.invocar()->mostrarCartas();		
	}
};

#endif
