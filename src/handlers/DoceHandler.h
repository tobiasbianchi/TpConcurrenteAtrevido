//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_DOCEHANLDER_H
#define TPCONCURRENTEATREVIDO_DOCEHANLDER_H

#include "BasicHandler.h"
#include "../core/HandlerSenial.h"

class DoceHandler : public BasicHandler {
public:
    DoceHandler() : BasicHandler(HandlerSenial::SIGNAL_12) {}
};
#endif //TPCONCURRENTEATREVIDO_DOCEHANLDER_H
