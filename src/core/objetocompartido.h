#ifndef OBJETOCOMPARTIDO
#define OBJETOCOMPARTIDO

#define RUTAOBJETOCOMPARTIDO "/bin/bash"

template<typename T> class ObjetoCompartido
{
private:
	int id;
	T *memoria;
public:
	/*Inicializa el contenedor del objeto. Se pasa un id que identifica al objeto que se quiere crear/traer y la ruta de archivo.
	  Los demas argumentos solo son necesarios si se crea un objeto, si se trae uno ya creado no se usan, de todas formas
	  es buena practica ingresarlos aunque no vayan a usarse*/
 
	template<typename ...Argumentos>ObjetoCompartido(int idObjeto, const char* rutaArchivo, Argumentos... args);
	

	/* Se obtiene la instancia del objeto en la memoria compartida. NUNCA COPIAR EN UN VARIABLE LO RETORNADO POR invocar.*/
	T* invocar();

	~ObjetoCompartido();
private:
	bool estabaCreado(int idObjeto, const char* rutaArchivo);
};

//Solo por ser un template

#include "objetocompartidoimplementacion.h"

#endif
