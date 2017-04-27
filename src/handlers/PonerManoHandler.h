//
// Created by tobias on 26/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_PONERMANOHANDLER_H
#define TPCONCURRENTEATREVIDO_PONERMANOHANDLER_H

#include "BasicHandler.h"
#include "../core/HandlerSenial.h"

class PonerManoHandler : public BasicHandler {
public:
    PonerManoHandler() : BasicHandler(HandlerSenial::SIG_MANO) {}

};
#endif //TPCONCURRENTEATREVIDO_PONERMANOHANDLER_H
