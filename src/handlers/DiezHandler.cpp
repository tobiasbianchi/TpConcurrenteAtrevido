//
// Created by tobias on 22/04/17.
//

#include <signal.h>
#include <iostream>
#include "DiezHandler.h"

int DiezHandler::handleSenial(int signum) {
    if (signum == SIGUSR1){
        std::cout << "Buenos dias señorita" << std::endl;
        //TODO make everyone know
    }
}