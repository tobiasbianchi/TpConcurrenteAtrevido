#include "HandlerSenial.h"
#include "excepciones.h"
#include <errno.h>

HandlerSenial* HandlerSenial :: instance = NULL;
HandlerEvento* HandlerSenial :: signal_handlers [ NSIG ];

HandlerSenial :: HandlerSenial () {
}

HandlerSenial* HandlerSenial :: getInstancia() {

	if ( instance == NULL )
		instance = new HandlerSenial ();

	return instance;
}

void HandlerSenial :: destruir () {
	if ( instance != NULL ) {
		delete ( instance );
		instance = NULL;
	}
}
HandlerEvento* HandlerSenial::registrarHandler(int signum, HandlerEvento * eh){
	std::vector<int> signalsToBlock;
	return registrarHandler(signum,eh,signalsToBlock);
}

HandlerEvento* HandlerSenial :: registrarHandler ( int signum,HandlerEvento* eh, std::vector<int> blockSignums ) {

	HandlerEvento* old_eh = HandlerSenial :: signal_handlers [ signum ];
	HandlerSenial :: signal_handlers [ signum ] = eh;

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = HandlerSenial :: dispatcher;
	sa.sa_flags = SA_RESTART; //makes system calls restart if interrupted (not aplicable to all)

	if (sigemptyset ( &sa.sa_mask ) == -1){
		throw Error("Senial empty mask",strerror(errno));
	}

	if (sigaddset ( &sa.sa_mask,signum ) == -1){
		throw Error("Senial agregar set", strerror(errno));
	}

	for (int i = 0; i < blockSignums.size(); i++){
		if (sigaddset ( &sa.sa_mask,blockSignums[i] ) == -1){
			throw Error("Senial Bloquear agregar set", strerror(errno));
		}
	}

	if (sigaction ( signum,&sa,0) == -1 ){ // cambiar accion de la senial
		throw Error("Senial set action",strerror(errno));
	}
	return old_eh;
}

void HandlerSenial :: dispatcher ( int signum ) {

	if ( HandlerSenial :: signal_handlers [ signum ] != 0 )
        HandlerSenial::signal_handlers[signum]->handleSenial(signum);
}

int HandlerSenial :: removerHandler ( int signum ) {

	HandlerSenial :: signal_handlers [ signum ] = NULL;
	return 0;
}

void HandlerSenial::bloquearSenial(int signum) {
	sigset_t sa;
	if (sigemptyset ( &sa ) == -1){
		throw Error("Senial empty mask",strerror(errno));
	}
	if (sigaddset ( &sa,signum ) == -1){
		throw Error("Senial agregar set", strerror(errno));
	}
	if (sigprocmask ( SIG_BLOCK,&sa,NULL )== -1){
		throw Error("Bloquear senial", strerror(errno));
	}
}

void HandlerSenial::desbloquearSenial(int signum) {
	sigset_t sa;
	if (sigemptyset ( &sa ) == -1){
		throw Error("Senial empty mask",strerror(errno));
	}
	if (sigaddset ( &sa, signum ) == -1){
		throw Error("Senial agregar set", strerror(errno));
	}
	if (sigprocmask ( SIG_UNBLOCK,&sa,NULL ) == -1){
		throw Error("Desbloquear Senial", strerror(errno));
	}
}

void HandlerSenial::broadcastSignal(int signum) {
	if (kill(0,signum) == -1){
		throw Error("Broadcast senial", strerror(errno));
	}
}
