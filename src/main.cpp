#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

#include <mutex.h>

using namespace std;

int main(int argc, char** argv)
{
	unsigned char cantidadJugadores = 5;
	bool esHijo = false;
	int i;

	Mutex m1(1), m2(2), m3(3), m4(4), m5(5);

	
	for(i = 0;i<cantidadJugadores && !esHijo;i++)
		esHijo = fork() == 0;


	if(i == 1)
		while(true)
		{
			m1.tomar();
			sleep(3);
			cout << i << endl;
			m2.liberar();		
		}

	if(i == 2)
	{
		m2.tomar();
		while(true)
		{
			m2.tomar();
			sleep(3);
			cout << i << endl;
			m3.liberar();		
		}
	}

	if(i == 3)
	{
		m3.tomar();
		while(true)
		{
			m3.tomar();
			sleep(3);
			cout << i << endl;
			m4.liberar();		
		}
	}

	if(i == 4)
	{
		m4.tomar();
		while(true)
		{
			m4.tomar();
			sleep(3);
			cout << i << endl;
			m5.liberar();		
		}
	}

	if(i == 5)
	{	
		m5.tomar();
		while(true)
		{
			m5.tomar();
			sleep(3);
			cout << i << endl;
			m1.liberar();		
		}
	}
	
	
}
