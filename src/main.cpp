#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

#include <mesa.h>
#include <maso.h>
#include <jugador.h>


using namespace std;

int main(int argc, char** argv)
{
	unsigned char cantidadJugadores = 5;
	bool esHijo = false;
	int i=0;

	Mesa mesa(1, cantidadJugadores);
	
	for(i = 0;i<cantidadJugadores && !esHijo;i++)
		esHijo = fork() == 0;	

	if(esHijo)
	{
		Jugador yo(i, mesa);
		while(true)		
		{
			yo.jugar();
		}
	}
	else
		while(true)
		{
			system("clear");
			mesa.imprimir();
			sleep(1);
		}
}
