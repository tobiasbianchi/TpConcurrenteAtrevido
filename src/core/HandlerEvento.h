#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

class HandlerEvento {
	int signum;
public:
	HandlerEvento (int signum){
		this->signum = signum;
	}
	int getSignal(){
		return signum;
	}
	virtual int handleSenial(int signum) = 0;
	virtual ~HandlerEvento () {};
};

#endif /* EVENTHANDLER_H_ */
