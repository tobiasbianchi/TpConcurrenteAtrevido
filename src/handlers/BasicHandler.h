//
// Created by tobias on 26/04/17.
//

#ifndef TPCONCURRENTEATREVIDO_BASICHANDLER_H
#define TPCONCURRENTEATREVIDO_BASICHANDLER_H

#include <csignal>
#include <assert.h>
#include "../core/HandlerEvento.h"

class BasicHandler : public HandlerEvento {
private:
    sig_atomic_t wasCalled;
    int signal;
public:

    BasicHandler (int signal) : wasCalled(0), signal(signal) {
    }

    ~BasicHandler () {
    }

    virtual int handleSenial ( int signum ) {
        assert ( signum == signal );
        this->wasCalled = 1;
        return 0;
    }

    sig_atomic_t getWasCalled() const {
        return this->wasCalled;
    }

    void reset(){
        this->wasCalled = 0;
    }

    int getSignal(){
        return signal;
    }
};
#endif //TPCONCURRENTEATREVIDO_BASICHANDLER_H
