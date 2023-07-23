# ifndef FECHA_HPP_
# define FECHA_HPP_

# include <iostream>
# include <chrono>
#include <ctime>
#include <cstdio>
#include <locale>

class Fecha
{
	public:
		// Constructores
		explicit Fecha(int d = 0, int m = 0, int a = 0);
		Fecha(const Fecha &f) = default;	// Constructor de copia (usaremos el default)
		Fecha(const char* c);	// A partir de una cadena de caracteres

		Fecha& operator =(const Fecha&) = default;

		// Atributos publicos
		static const int AnnoMinimo = 1902;
 		static const int AnnoMaximo = 2037;

		// Conversion a const char
		const char* cadena() const;

		// Clase invalida para excepciones
		class Invalida
		{
			public:
				Invalida(const char* inf);
				const char* por_que() const noexcept;
			private:
				const char* info_;
		};

		// Observadores
		int dia() const noexcept;
 		int mes() const noexcept;
 		int anno() const noexcept;

		// Operadores
		Fecha& operator +=(int n);
		Fecha& operator -=(int n);

		Fecha operator +(int n) const;
		Fecha operator -(int n) const;

		Fecha& operator ++();
		Fecha& operator --();
		Fecha operator ++(int);
		Fecha operator --(int);

		// Destructor
		~Fecha() = default;


	private:
		int _dia, _mes, _annio;
		
		void comprobar_fecha();
		int ultimo_dia() const;
		
};

// METODOS INLINE
inline int Fecha::dia() const noexcept{return _dia;}
inline int Fecha::mes() const noexcept{return _mes;}
inline int Fecha::anno() const noexcept{return _annio;}

// OPERADORES LOGICOS
bool operator ==(const Fecha& fecha1, const Fecha& fecha2);
bool operator !=(const Fecha& fecha1, const Fecha& fecha2);
bool operator <(const Fecha& fecha1, const Fecha& fecha2);
bool operator >(const Fecha& fecha1, const Fecha& fecha2);
bool operator >=(const Fecha& fecha1, const Fecha& fecha2);
bool operator <=(const Fecha& fecha1, const Fecha& fecha2);

// ENTRADA/SALIDA
std::ostream& operator <<(std::ostream& salida, const Fecha& fecha) noexcept;
std::istream& operator >>(std::istream& is, Fecha& f);


// METODOS INLINE INVALIDA
inline Fecha::Invalida::Invalida(const char* inf): info_(inf){}
inline const char* Fecha::Invalida::por_que() const noexcept{return info_;}

# endif