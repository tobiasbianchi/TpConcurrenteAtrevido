//
// Created by tobias on 22/04/17.
//
#include "DoceHandler.h"
#include <signal.h>
#include <iostream>

int DoceHandler::handleSenial(int signum) {
    if (signum == SIGTTIN){
        std::cout << "Buenas noches caballero" << std::endl;
        //TODO make everyone know
    }
}