#include "excepciones.h"
#include <exception>
#include <string>

using namespace std;

Error::Error(const string prefijo, const string &mensaje) : mensaje(prefijo+": "+mensaje)
{
}

const char* Error::what() const throw()
{
	return mensaje.c_str();
}


