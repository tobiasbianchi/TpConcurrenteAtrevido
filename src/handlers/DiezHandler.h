//
// Created by tobias on 22/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_10HANDLER_H
#define TPCONCURRENTEATREVIDO_10HANDLER_H

#include <HandlerEvento.h>

class DiezHandler : public HandlerEvento {
    int handleSenial(int signum);
};
#endif //TPCONCURRENTEATREVIDO_10HANDLER_H
