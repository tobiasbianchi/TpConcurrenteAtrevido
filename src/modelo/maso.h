#ifndef MASO
#define MASO

#include <vector>
#include <mutex.h>
#include <iostream>

class Maso
{
private:
	std::vector<unsigned char> cartas;
	Mutex mutex;
public:
	Maso(int idProyecto, const char *rutaArchivo = "/bin/bash");
	void ponerCarta(unsigned char carta);
	unsigned char sacarCarta();
	
	void mostrarCartas()
	{
		auto i = cartas.begin();

		while(i != cartas.end())
			std::cout << *i++ << " ";
	}
};


#endif
