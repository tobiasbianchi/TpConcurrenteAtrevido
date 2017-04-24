//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_ONCEHANLDER_H
#define TPCONCURRENTEATREVIDO_ONCEHANLDER_H

#include <HandlerEvento.h>

class OnceHandler : public HandlerEvento{
    int handleSenial(int signum);
};
#endif //TPCONCURRENTEATREVIDO_ONCEHANLDER_H
