//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_DOCEHANLDER_H
#define TPCONCURRENTEATREVIDO_DOCEHANLDER_H

#include <HandlerEvento.h>

class DoceHandler : public HandlerEvento {
    int handleSenial(int signum);
};
#endif //TPCONCURRENTEATREVIDO_DOCEHANLDER_H
