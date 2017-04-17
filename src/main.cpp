#include <semaforo.h>
#include <objetocompartido.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <maso.h>
#include <jugador.h>
#include <mesa.h>

using namespace std;

int main(int argc, char** argv)
{
	unsigned char cantidadJugadores = atoi(argv[2]);
	bool esHijo = false;
	int i;

	for(i=0; i< cantidadJugadores && !esHijo; i++)
	{
		esHijo = fork() == 0;
	}

	cout << "Voy a crear!" << endl;
	Mesa mesa(1, cantidadJugadores);

	if(esHijo)
	{
		cout << "Soy hijo!" << endl;
		Jugador jugador(i,mesa);
		jugador.jugar();
	}
	else
	{
		while(true)
		{
			sleep(1);
			cout << "Soy padre! Voy a imprimir" << endl;
			mesa.imprimir();
		}
	}	
	
}
