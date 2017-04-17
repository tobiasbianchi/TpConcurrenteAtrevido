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
	unsigned char cantidadJugadores = atoi(argv[1]);
	bool esHijo = false;
	int i;

	
	if(fork() == 0)
	{
		Mutex mutex1(1);
		Mutex mutex2(2, true);
		while(true)
		{
			mutex1.tomar();
			cout << 1 << endl;
			mutex2.liberar();
	
		}
	}	
	else
	{
		Mutex mutex1(1);
		Mutex mutex2(2, true);
		while(true)
		{
			mutex2.tomar();
			cout << 2 << endl;
			mutex1.liberar();
		}
	}
	
	
}
