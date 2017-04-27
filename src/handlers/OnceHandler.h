//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_ONCEHANLDER_H
#define TPCONCURRENTEATREVIDO_ONCEHANLDER_H

#include "BasicHandler.h"
#include "../core/HandlerSenial.h"

class OnceHandler : public BasicHandler{
public:
    OnceHandler() : BasicHandler(HandlerSenial::SIGNAL_11) {}
};
#endif //TPCONCURRENTEATREVIDO_ONCEHANLDER_H
