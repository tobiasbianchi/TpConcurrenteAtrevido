#include <maso.h>
#include <vector>
#include <mutex.h>
#include "maso.h"

Maso::Maso(int idProyecto, const char *rutaArchivo) : mutex(idProyecto, rutaArchivo)
{	
}

Maso::Maso(int idProyecto,std::vector<int> cartas, const char *rutaArchivo) : mutex(idProyecto, rutaArchivo)
{
	this->agregarCartas(cartas);
}

bool Maso::ponerCarta(int carta)
{
	mutex.tomar();

	bool mismaQueLaAnterior = carta == cartas.ultimaCarta();
    cartas.ponerCarta(carta);

	mutex.liberar();

    return mismaQueLaAnterior;
}

int Maso::sacarCarta()
{
	mutex.tomar();
	int cartaAux = cartas.sacarCarta();
	mutex.liberar();
	return cartaAux;
}

void Maso::mostrarCartas()
{
	mutex.tomar();

	for(int i=0;i<cartas.cantidadCartas;i++)
		Log::info("Carta en maso: " + std::to_string(cartas.cartas[i]));

	mutex.liberar();
}

void Maso::agregarCartas(std::vector<int> cartas){
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

std::vector<int> Maso::robarMaso() {
    std::vector<int> cartarRobadas;

    mutex.tomar();
    int sacada = cartas.sacarCarta();
    while ( sacada != 0){
        cartarRobadas.push_back(sacada);
        sacada = cartas.sacarCarta();
    }
    mutex.liberar();

    return cartarRobadas;
}

int Maso::contarCartas(){
	mutex.tomar();
	int cartas = this->cartas.contarCartas();
	mutex.liberar();
	return cartas;
}
