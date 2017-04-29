/*
 * CartasFactory.h
 *
 *  Created on: Apr 29, 2017
 *      Author: tobias
 */

#ifndef CARTASFACTORY_H_
#define CARTASFACTORY_H_

class CartasFactory {
public:
	CartasFactory();
	static std::vector<std::vector<unsigned char>> prepararCartas(int jugadores);
	virtual ~CartasFactory();
};

#endif /* CARTASFACTORY_H_ */
