#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

#include <signal.h>
#include <stdio.h>
#include <memory.h>

#include "HandlerEvento.h"

class HandlerSenial {

	private:
		static HandlerSenial* instance;
		static HandlerEvento* signal_handlers [ NSIG ];

		HandlerSenial ( void );
		static void dispatcher ( int signum );

	public:
		static HandlerSenial* getInstancia();
		static void destruir ();
		HandlerEvento* registrarHandler ( int signum,HandlerEvento* eh );
		int removerHandler ( int signum );
		static void bloquearSenial(int signum);
		static void desbloquearSenial(int signum);
		static void broadcastSignal(int signum);

};

#endif /* SIGNALHANDLER_H_ */
