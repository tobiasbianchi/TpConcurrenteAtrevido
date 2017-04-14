#ifndef EXCEPCIONES
#define EXCEPCIONES  

#include <exception>
#include <string>

class Error : public std::exception
{
private:
	const std::string mensaje;
public:
	Error(const std::string prefijo, const std::string &mensaje);
	const char* what() const throw();
	~Error() throw(){};
};

#endif
