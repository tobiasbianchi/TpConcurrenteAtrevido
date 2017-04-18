#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <excepciones.h>
#include <pipe.h>

Pipe::Pipe() {
	this->escritura = true;
	this->lectura = true;

	if(pipe(this->descriptores) == CODE_ERROR) {
		throw Error("Creación de pipe", strerror(errno));
	}

}

void Pipe::cerrarFdEscritura() {
	if(close(this->descriptores[1]) == CODE_ERROR) {
		throw Error("Cerrando descriptor escritura del pipe", strerror(errno));
	}
}

void Pipe::cerrarFdLectura() {
	if(close(this->descriptores[0]) == CODE_ERROR) {
			throw Error("Cerrando descriptor lectura del pipe", strerror(errno));
		}
}

void Pipe::cerrar() {
	if(this->escritura) {
		this->cerrarFdEscritura();
		this->escritura = false;
	}

	if(this->lectura) {
		this->cerrarFdLectura();
		this->lectura = false;
	}
}

// el modo se puede setear sólo una vez
void Pipe::setModo(const int mode) {
	if(this->lectura == false || this->escritura == false) return;

	if(mode == MODO_ESCRITURA) {
		this->cerrarFdLectura();
		this->lectura = false;
	} else {
		this->cerrarFdEscritura();
		this->escritura = false;
	}
}

int Pipe::getFdEscritura() const {
	return (this->escritura)? this->descriptores[1]: CODE_ERROR;
}

int Pipe::getFdLectura() const {
	return (this->lectura)? this->descriptores[0]: CODE_ERROR;
}

ssize_t Pipe::leer(void* buffer, const int size) {
	ssize_t bytes = 0;

	if(this->lectura) {
		this->setModo(MODO_LECTURA);

		if((bytes = read(getFdLectura(), buffer, size)) == CODE_ERROR) {
			throw Error("Leyendo del pipe", strerror(errno));
		}
	}

	return bytes;
}

ssize_t Pipe::escribir(const void* buffer, int size) {
	int bytes = 0;

	if(this->escritura) {
		this->setModo(MODO_ESCRITURA);

		if((bytes = write(getFdEscritura(), buffer, size) == CODE_ERROR)) {
			throw Error("Escribiendo en el pipe", strerror(errno));
		}
	}
	return bytes;
}

Pipe::~Pipe() {
	this->cerrar();
}

