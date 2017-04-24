//
// Created by tobias on 22/04/17.
//
#include "SieteHandler.h"
#include <signal.h>
#include <iostream>

int SieteHandler::handleSenial(int signum) {
    if (signum == SIGCHLD){
        std::cout << "Atrevido" << std::endl;
        //TODO ponermano o mandar nueva senial?
    }
}
