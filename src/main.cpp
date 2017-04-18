#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

#include <jugador.h>
#include <mesa.h>


using namespace std;

int main(int argc, char** argv)
{
	unsigned char cantidadJugadores = 5;
	bool esHijo = false;
	int i;

	Mesa mesa(1, cantidadJugadores);
	
	for(i = 0;i<cantidadJugadores && !esHijo;i++)
		esHijo = fork() == 0;	

	if(esHijo)
	{
		Jugador yo(i, mesa);
		yo.jugar();
	}
	else
		while(true)
		{
			sleep(3);
		}
}
