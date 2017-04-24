//
// Created by tobias on 22/04/17.
//

#include "OnceHandler.h"
#include <signal.h>
#include <iostream>

int OnceHandler::handleSenial(int signum) {
    if (signum == SIGUSR2){
        std::cout << "Buenas noches caballero" << std::endl;
        //TODO make everyone know
    }
}
