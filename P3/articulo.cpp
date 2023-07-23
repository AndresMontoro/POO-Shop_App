#include "articulo.hpp"

#include <iomanip>

//Constructores
Articulo::Articulo(Cadena referencia, Cadena titulo, Fecha publicacion, double precio, size_t stock):
	referencia_{referencia}, titulo_{titulo}, f_publi_{publicacion},
	precio_{precio}, stock_{stock}
{}

//Operadores externos
std::ostream& operator<<(std::ostream& os,const Articulo& a) noexcept
{
	os << "[" << a.referencia() <<"] \"" << a.titulo() << "\", " << a.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << a.precio() <<" €" << std::endl;
	return os;
}
