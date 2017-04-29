#include <maso.h>
#include <vector>
#include <mutex.h>
#include "maso.h"

Maso::Maso(int idProyecto, const char *rutaArchivo) : mutex(idProyecto, rutaArchivo)
{	
}

Maso::Maso(int idProyecto,std::vector<unsigned char> cartas, const char *rutaArchivo) : mutex(idProyecto, rutaArchivo)
{
	this->agregarCartas(cartas);
}

bool Maso::ponerCarta(unsigned char carta)
{
	mutex.tomar();

	bool mismaQueLaAnterior = carta == cartas.ultimaCarta();
    cartas.ponerCarta(carta);

	mutex.liberar();

    return mismaQueLaAnterior;
}

unsigned char Maso::sacarCarta()
{
	mutex.tomar();
	unsigned char cartaAux = cartas.sacarCarta();
	mutex.liberar();
	return cartaAux;
}

void Maso::mostrarCartas()
{
	mutex.tomar();

	for(int i=0;i<cartas.cantidadCartas;i++)
		std::cout << (int)cartas.cartas[i] << std::endl;

	mutex.liberar();
}

void Maso::agregarCartas(std::vector<unsigned char> cartas){
	mutex.tomar();
	for (int i = 0; i < cartas.size(); i++){
		this->cartas.ponerCarta(cartas.at(i));
	}
	mutex.liberar();
}

bool Maso::ponerMano(int cantidadJugadores) {
    mutex.tomar();

    manosApoyadas++;
    if (manosApoyadas >= cantidadJugadores)
        manosApoyadas = 0;
    mutex.liberar();

    return manosApoyadas == 0;
}

std::vector<unsigned char> Maso::robarMaso() {
    std::vector<unsigned char> cartarRobadas;

    mutex.tomar();
    unsigned char sacada = cartas.sacarCarta();
    while ( sacada != 0){
        cartarRobadas.push_back(sacada);
        sacada = cartas.sacarCarta();
    }
    mutex.liberar();

    return cartarRobadas;
}

int Maso::contarCartas(){
	int cartas = 0;
	mutex.tomar();
	cartas = this->cartas.contarCartas();
	mutex.liberar();
	return cartas;
}
