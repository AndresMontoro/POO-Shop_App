#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream> 
#include <locale> 
#include <iomanip> 

class Articulo{
public:
	//Constructor
	Articulo(Cadena referencia, Cadena titulo, Fecha publicacion, double precio, size_t stock = 0);

	//Observadores
	const Cadena& referencia()const noexcept;
	const Cadena& titulo()const noexcept;
	const Fecha& f_publi()const noexcept;

	double precio()const noexcept;
	double& precio() noexcept;

	size_t stock()const noexcept;
	size_t& stock() noexcept;

private:
	//Atributos
	const Cadena referencia_, titulo_;
	const Fecha f_publi_;
	double precio_;
	size_t stock_;
};

//Operadores externos
std::ostream& operator <<(std::ostream& os, const Articulo& art) noexcept;

// Metodos inline
inline const Cadena& Articulo::referencia() const noexcept{return referencia_;}
inline const Cadena& Articulo::titulo() const noexcept{return titulo_;}
inline const Fecha& Articulo::f_publi() const noexcept{return f_publi_;}
inline double Articulo::precio() const noexcept{return precio_;}
inline double& Articulo::precio() noexcept{return precio_;}
inline size_t Articulo::stock() const noexcept{return stock_;}
inline size_t& Articulo::stock() noexcept{return stock_;}


#endif