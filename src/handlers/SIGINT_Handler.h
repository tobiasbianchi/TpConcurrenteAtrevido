#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "HandlerEvento.h"
#include "Log.h"

class SIGINT_Handler : public HandlerEvento {
	sig_atomic_t wasCalled;
public:
	SIGINT_Handler() : HandlerEvento(SIGINT), wasCalled(0) {}

	virtual int handleSenial ( int signum ) {
		assert ( signum == getSignal() );
		this->wasCalled = 1;
		return 0;
	}

	sig_atomic_t getWasCalled() const {
		return this->wasCalled;
	}
};

#endif /* SIGINT_HANDLER_H_ */
