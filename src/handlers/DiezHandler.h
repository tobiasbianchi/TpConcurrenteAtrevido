//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_10HANDLER_H
#define TPCONCURRENTEATREVIDO_10HANDLER_H

#include "BasicHandler.h"
#include "../core/HandlerSenial.h"

class DiezHandler : public BasicHandler {
public:
    DiezHandler() : BasicHandler(HandlerSenial::SIGNAL_10) {}
};
#endif //TPCONCURRENTEATREVIDO_10HANDLER_H
