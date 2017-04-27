//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_SIETEHANDLER_H
#define TPCONCURRENTEATREVIDO_SIETEHANDLER_H

#include "BasicHandler.h"
#include "../core/HandlerSenial.h"

class SieteHandler : public BasicHandler
{
public:
    SieteHandler() : BasicHandler(HandlerSenial::SIGATREVIDO) {}

};
#endif //TPCONCURRENTEATREVIDO_SIETEHANDLER_H
