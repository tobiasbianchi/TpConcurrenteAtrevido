#include <exception>
#include <string>

class Error : public std::exception
{
private:
	const string mensaje;
public:
	Error(const string prefijo, const string &mensaje) : mensaje(prefijo+mensaje)
	{
	}

	const char* what() const
	{
		return mensaje.c_str();
	}
}
