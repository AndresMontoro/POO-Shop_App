# include "fecha.hpp"

// METODOS PRIVADOS
void Fecha::comprobar_fecha()
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
				Fecha::Invalida mes_invalido("Mes Incorrecto");
				throw mes_invalido;
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

	comprobar_fecha();
}

Fecha::Fecha(const char* c)
{
	if (sscanf(c, "%d/%d/%d", &_dia, &_mes, &_annio) != 3)
	{
		Fecha::Invalida formato_invalido("Formato de incorrecto");
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

		comprobar_fecha();
	}
}

// CONVERSION DE FECHA A CONST CHAR
const char* Fecha::cadena() const
{
	std::locale::global(std::locale("es_ES.utf8"));
	static char aux[38];

	std::time_t tiempo = std::time(nullptr);
	std::tm* f = std::localtime(&tiempo);

	f->tm_mday = _dia;
	f->tm_mon = _mes - 1;
	f->tm_year = _annio - 1900;
	mktime(f);

	strftime(aux, 38, "%A %e de %B de %Y",f);
	//std::cout << aux;
 	return aux;

/*
 	tm tc = {0, 0, 0, _dia, _mes-1, _annio - 1900, 0, 0, -1};
 	mktime(&tc);
 	int dia = tc.tm_wday;

 	static char cadena[38];
 	const char* meses[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
 	const char* dias[]{"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};

 	sprintf(cadena, "%s %d de %s de %d", dias[_dia], _dia, meses[_mes-1], _annio);
 	return cadena;
*/
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
	comprobar_fecha();
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

Fecha Fecha::operator ++(int)
{ 
	// f++
	Fecha f = *this;
 	*this += 1;
 	return f;

}

Fecha Fecha::operator --(int)
{
	// f--
	Fecha f = *this;
 	*this -= 1;
 	return f;
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

// ENTRADA/SALIDA
std::ostream& operator <<(std::ostream& salida, const Fecha& fecha) noexcept
{
	// Convertimos explicitamente a cadena de caracteres
	salida << fecha.cadena();
	return salida;
}

std::istream& operator >>(std::istream& entrada, Fecha& fecha)
{
	char cad [11];

    entrada.width(11);

	try
	{
		if(entrada.width() > 11)
			throw Fecha::Invalida("Desbordamiento");

		entrada >> cad;
		fecha = cad;
	}catch(Fecha::Invalida error)
	{
		entrada.setstate(std::ios::failbit);
		throw error;
	}

	return entrada;
}