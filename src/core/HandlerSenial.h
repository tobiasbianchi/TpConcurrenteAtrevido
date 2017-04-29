#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

#include <signal.h>
#include <stdio.h>
#include <memory.h>
#include <vector>
#include "HandlerEvento.h"

class HandlerSenial {

	private:
		static HandlerSenial* instance;
		static HandlerEvento* signal_handlers [ NSIG ];

		HandlerSenial ( void );
		static void dispatcher ( int signum );

	public:
		static const int SIGNAL_10 = SIGUSR1;
		static const int SIGNAL_11 = SIGUSR2;
		static const int SIGNAL_12  = SIGTTIN;
		static const int SIGATREVIDO = SIGTTOU;
		static const int SIG_REPETIDA = SIGCHLD;

		static HandlerSenial* getInstancia();
		static void destruir ();
		HandlerEvento* registrarHandler ( int signum,HandlerEvento* eh);
		HandlerEvento* registrarHandler ( int signum,HandlerEvento* eh, std::vector<int> blockSignums );
		int removerHandler ( int signum );
		static void bloquearSenial(int signum);
		static void desbloquearSenial(int signum);
		static void broadcastSignal(int signum);

};

#endif /* SIGNALHANDLER_H_ */
