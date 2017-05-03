#ifndef PIPE_H_
#define PIPE_H_
#include "Log.h"

class Pipe {
	public:
		Pipe();
		void setModo(const int mode);
		ssize_t leer(void* buffer, const int size);
		ssize_t escribir(const void* buffer, const int size);
		int getFdLectura() const;
		int getFdEscritura() const;
		void cerrarFdLectura();
		void cerrarFdEscritura();
		void cerrar();
		~Pipe();

		static const int MODO_LECTURA = 0;
		static const int MODO_ESCRITURA = 1;

	private:
		int descriptores[2];
		bool escritura;
		bool lectura;
		static const int CODE_ERROR = -1;

};

#endif /* PIPE_H_ */
