#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

class HandlerEvento {

public:
	virtual int handleSenial(int signum) = 0;
	virtual ~HandlerEvento () {};
};

#endif /* EVENTHANDLER_H_ */
