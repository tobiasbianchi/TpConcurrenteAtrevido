/*
 * CartasFactory.cpp
 *
 *  Created on: Apr 29, 2017
 *      Author: tobias
 */

#include "CartasFactory.h"
#include <stdlib.h>
#include <iostream>
#include <string>

CartasFactory::CartasFactory() {
	// TODO Auto-generated constructor stub

}


std::vector<std::vector<int>> CartasFactory::prepararCartas(int jugadores){
	std::vector<std::vector<int>> masos;

	int CANTIDAD_PALOS = 4;
	int CARTAS_POR_PALO = 12;
	int TOTAL_CARTAS = CANTIDAD_PALOS*CARTAS_POR_PALO;

	//maso
	std::vector<int> masoEntero;
	for (int j = 1; j <= CANTIDAD_PALOS; j++){
		for (int i = 1; i <= CARTAS_POR_PALO; i++ ){
			masoEntero.push_back(i);
		}
	}


	for ( int i = 0; i < jugadores; i++){
		std::vector<int> masoParticular;
		masos.push_back(masoParticular);
	}


	//asume reparticion equitativa
	for (int j = 0; j < TOTAL_CARTAS/jugadores; j++){
		for ( int i = 0; i < jugadores; i++){
			//select random card from maso
			int randomIndex = (rand() % masoEntero.size());
			int carta = masoEntero.at(randomIndex);
			masoEntero.erase(masoEntero.begin() + randomIndex);
			//add to player
			masos[i].push_back(carta);
		}
	}

	/*for ( int i = 0; i < masos.size(); i++){
		std::vector<unsigned char> cartas = masos[i];
		std::string robada = "";
		for (int j = 0; j < cartas.size(); j++){
			robada += std::to_string(cartas[j]) + ";";
		}
		std::cout << "Maso i: " << robada;
	}*/

	return masos;
}

CartasFactory::~CartasFactory() {
	// TODO Auto-generated destructor stub
}

