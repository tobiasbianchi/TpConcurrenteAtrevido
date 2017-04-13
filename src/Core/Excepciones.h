#include <exception>
#include <string>

class Error : public std::exception
{
private:
	const std::string mensaje;
public:
	Error(const std::string prefijo, const std::string &mensaje) : mensaje(prefijo+mensaje)
	{
	}

	const char* what() const
	{
		return mensaje.c_str();
	}
}
