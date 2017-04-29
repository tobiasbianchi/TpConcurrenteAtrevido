/*
 * PipesFactory.h
 *
 *  Created on: Apr 29, 2017
 *      Author: tobias
 */

#ifndef PIPESFACTORY_H_
#define PIPESFACTORY_H_
#include <vector>
#include "pipe.h"
class PipeFactory{
public:
	static std::vector<Pipe*> getPipes(int cantidadJugadores){
		std::vector<Pipe*> pipes;
		for (int i = 0; i < cantidadJugadores; i++ ){
			pipes.push_back(new Pipe());
		}
		return pipes;
	}
};


#endif /* PIPESFACTORY_H_ */
