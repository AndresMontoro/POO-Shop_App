#include "articulo.hpp"


//Constructor
Articulo::Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio):
	f_publi_{publicacion}, autores_{autores}, referencia_{referencia}, titulo_{titulo}, precio_{precio}
{}

//Operadores externos
std::ostream& operator<<(std::ostream& os,const Articulo& articulo) noexcept
{
	os << "["<<articulo.referencia() << "] \"" << articulo.titulo() << "\", de ";

    for(Articulo::Autores::const_iterator iter=articulo.autores().begin();iter!=articulo.autores().end();++iter)
	{
        if(iter!=articulo.autores().begin())
		{
            os << ", ";
        }

        os<<(*iter)->apellidos();
    }

    os << ". " << articulo.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << articulo.precio() << " €" << std::endl;
	os << "\t";
    articulo.impresion_especifica(os);

    return os;
}


// Funciones de impresion especifica
void LibroDigital::impresion_especifica(std::ostream& os) const noexcept
{
	os << "A la venta hasta el " << (f_expir()).cadena() << ".";
}

void Libro::impresion_especifica(std::ostream& os) const noexcept
{
	os << n_pag() << " págs., " << stock() << " unidades.";
    //std::cout << n_pag();
    //std::cout << "---";
}

void Revista::impresion_especifica(std::ostream& os) const noexcept
{
    /*
    // Necesitaremos saber la fecha de hoy para sumarle los dias de la periodicidad
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    int dia = tiempo_descompuesto->tm_mday;
    int mes = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
    int anno = tiempo_descompuesto->tm_year + 1900; // tm_year: a~nos desde 1900

    Fecha aux{dia, mes, anno};
    aux = aux + periodicidad();
    */

    //std::cout << (f_publi_ + periodicidad()).cadena();
    //std::cout << "---";

    os << "Número: " << numero() << ", Periodicidad: " << periodicidad() << " días.\n";
    os << "\tPróximo número a partir de: " << (f_publi_ + periodicidad()).cadena() << ".";   // Fecha salida = fecha publicacion + periodicidad
}