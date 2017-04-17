#ifndef MESA
#define MESA

#include <objetocompartido.h>
#include <maso.h>
#include <mutex.h>
#include <vector>

#define RUTAARCHIVOMESA "archivos/mesa"

class Mesa
{
private:
	ObjetoCompartido<Maso> maso;
	std::vector<ObjetoCompartido<Mutex>> moderadorTurnos;
	unsigned int contador;

public:
	Mesa(unsigned char numeroPartida, unsigned char cantidadJugadores) : contador(numeroPartida), maso(idRecurso(), RUTAARCHIVOMESA, idRecurso(), RUTAARCHIVOMESA)
	{
		for(unsigned char i = 0; i<cantidadJugadores; i++)
			moderadorTurnos[i] = ObjetoCompartido<Mutex>(idRecurso(), RUTAARCHIVOMESA,idRecurso(), i != 0,RUTAARCHIVOMESA);	
	}

	unsigned int idRecurso()
	{
		return contador++;
	}

	bool hacerJugada(unsigned char numeroJugador, unsigned char carta)
	{
		moderadorTurnos.at(numeroJugador).invocar()->tomar();

		//Inicio de seccion critica

		maso.invocar()->ponerCarta(carta);	

		//Fin de seccion critica


		if(numeroJugador < moderadorTurnos.size())
			moderadorTurnos.at(numeroJugador+1).invocar()->liberar();
		else
			moderadorTurnos.at(0).invocar()->liberar();

		return true;
	}

	void imprimir()
	{
		maso.invocar()->mostrarCartas();		
	}
};

#endif
