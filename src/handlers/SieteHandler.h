//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_SIETEHANDLER_H
#define TPCONCURRENTEATREVIDO_SIETEHANDLER_H

#include <HandlerEvento.h>

class SieteHandler : public HandlerEvento
{
    int handleSenial(int signum);
};
#endif //TPCONCURRENTEATREVIDO_SIETEHANDLER_H
