# include "fecha.hpp"

// METODOS PRIVADOS
void Fecha::comprueba()
{
	if(_dia > ultimo_dia() || _dia < 1)
	{
		Fecha::Invalida dia_invalido("Dia incorrecto");
		throw dia_invalido;
	}

	if (_annio < Fecha::AnnoMinimo || _annio > Fecha::AnnoMaximo)
	{
		Fecha::Invalida annio_invalido("Annio incorrecto");
		throw annio_invalido;
	}
}

int Fecha::ultimo_dia() const 
{
	if (_mes == 1 || _mes == 3 || _mes == 5 || _mes == 7 || _mes == 8 || _mes == 10 || _mes == 12)
		return 31;
	
	else
	{
		if(_mes == 4 || _mes == 6 || _mes == 9 || _mes == 11)
			return 30;
		
		else
		{
			// Bisiesto
			if(_mes == 2) 
			{
				if(_annio % 4 == 0 && (_annio % 400 == 0 || _annio % 100 != 0))
					return 29;

				else
					return 28;
			}

			else
			{
				Fecha::Invalida invalida("Mes Incorrecto");
				throw invalida;
				return 0;
			}
		}
	}
}

// CONSTRUCTORES
Fecha::Fecha(int d, int m, int a):
	_dia(d), _mes(m), _annio(a)
{
	std::time_t tiempo = std::time(nullptr);
	std::tm* tiempo_desc = std::localtime(&tiempo);

	if (_annio == 0)
		_annio = tiempo_desc->tm_year + 1900;

	if (_mes == 0)
		_mes = tiempo_desc->tm_mon + 1;
	
	if (_dia == 0)	
		_dia = tiempo_desc->tm_mday;
}

Fecha::Fecha(const char* c)
{
	if (sscanf(c, "%d/%d/%d", &_dia, &_mes, &_annio) != 3)
	{
		Fecha::Invalida formato_invalido("Formato de la cadena incorrecto.");
		throw formato_invalido;
	}

	else
	{
		sscanf(c, "%d/%d/%d", &_dia, &_mes, &_annio);

		if (_dia == 0 || _mes == 0 || _annio == 0)
		{
			// Necesitaremos la fecha del sistema
			std::time_t tiempo = std::time(nullptr);
			std::tm* tiempo_desc = std::localtime(&tiempo);

			if (_annio == 0)
				_annio = tiempo_desc->tm_year + 1900;

			if (_mes == 0)
				_mes = tiempo_desc->tm_mon + 1;
			
			if (_dia == 0)	
				_dia = tiempo_desc->tm_mday;
		}

		comprueba();
	}
}

// CONVERSION DE FECHA A CONST CHAR
Fecha::operator const char*() const
{
	std::locale::global(std::locale("es_ES.utf8"));
	char *aux = new char[100];

	std::time_t tiempo = std::time(nullptr);
	std::tm* f = std::localtime(&tiempo);

	f->tm_mday = _dia;
	f->tm_mon = _mes - 1;
	f->tm_year = _annio - 1900;
	mktime(f);

	strftime(aux, 100, "%A %e de %B de %Y",f);
 	return aux;
}


// OPERADORES
Fecha& Fecha::operator +=(int n)
{
	//Creamos una estructura con la fecha ya operada con el entero y la formateamos
	std::tm f_aux{};
	f_aux.tm_mday = _dia + n;
	f_aux.tm_mon = _mes - 1;
	f_aux.tm_year = _annio - 1900;
	std::mktime(&f_aux);

	//Pasamos la fecha formateada a los atributos de la clase
	_dia = f_aux.tm_mday;
	_mes = f_aux.tm_mon + 1;
	_annio = f_aux.tm_year + 1900;
	comprueba();
	return *this;
}

Fecha& Fecha::operator -=(int n)
{
	*this += -n;
	return *this;
}

Fecha Fecha::operator +(int n) const
{
	Fecha f(*this);
	return f += n;
}

Fecha Fecha::operator -(int n) const
{
	Fecha f(*this);
	return f += -n;
}

		// No se si estos estan bien (pre y postincremento)
Fecha& Fecha::operator ++()
{
	// ++f
	*this += 1;
	return *this;
}


Fecha& Fecha::operator --()
{
	// --f
	*this += -1;
	return *this;
}

Fecha& Fecha::operator ++(int)
{ 
	// f++
	*this += 1;
	return *this;
}

Fecha& Fecha::operator --(int)
{
	// f--
	*this += -1;
	return *this;
}


// OPERADORES LOGICOS
bool operator ==(const Fecha& fecha1, const Fecha& fecha2)
{
	return (fecha1.dia() == fecha2.dia() && fecha1.mes() == fecha2.mes() && fecha1.anno() == fecha2.anno());
}

bool operator !=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1 == fecha2);
}

bool operator <(const Fecha& fecha1, const Fecha& fecha2)
{
	return (fecha1.anno() < fecha2.anno() || 
		(fecha1.anno() == fecha2.anno() && fecha1.mes() < fecha2.mes()) ||
		(fecha1.anno() == fecha2.anno() && fecha1.mes() == fecha2.mes() && fecha1.dia() < fecha2.dia()));
}

bool operator >(const Fecha& fecha1, const Fecha& fecha2)
{
	return fecha2 < fecha1;
}

bool operator >=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1 < fecha2);
}

bool operator <=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1 > fecha2);
}