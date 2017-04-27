#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "BasicHandler.h"

class SIGINT_Handler : public BasicHandler {
public:
	SIGINT_Handler() : BasicHandler(SIGINT) {}
};

#endif /* SIGINT_HANDLER_H_ */
