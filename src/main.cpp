#include "core/semaforo.h"
#include "core/objetocompartido.h"
#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	ObjetoCompartido<Semaforo> obj1(1,4,1);

	for(int i=0; i<10;i++)
	{
		if(fork()==0)
		{
			obj1.invocar()->tomar();
			cout << "Proceso" << getpid() << ": Hola" << endl;
			sleep(6);
			obj1.invocar()->liberar();
			cout << "Proceso" << getpid() << ": Termine" << endl;
			return 0;
		}
	}

	for(int i=0;i<10;i++)
	{
		cout << "Esperando a " << i << endl;
		wait(NULL);	
	}
	cout << "Soy el padre y termine" << endl;
	return 0;
}
