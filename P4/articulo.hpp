#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream> 
#include <locale> 
#include <iomanip> 
#include <ctime>
#include <set>

// Clase autor
class Autor
{
	public:
		Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion);

		// Observadores
		const Cadena& nombre() const noexcept;
		const Cadena& apellidos() const noexcept;
		const Cadena& direccion() const noexcept;

	private:
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
};

// Metodos inline de la clase autor
inline Autor::Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion):
	nombre_{nombre}, apellidos_{apellido}, direccion_{direccion}{}

inline const Cadena& Autor::nombre() const noexcept{return nombre_;}
inline const Cadena& Autor::apellidos() const noexcept{return apellidos_;}
inline const Cadena& Autor::direccion() const noexcept{return direccion_;}


class Articulo
{
public:
	typedef std::set<Autor*> Autores;

	//Constructor
	Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio);

	//Observadores
	const Cadena& referencia()const noexcept;
	const Cadena& titulo()const noexcept;
	const Fecha& f_publi()const noexcept;
	const Autores& autores() const noexcept;


	double precio()const noexcept;
	double& precio() noexcept;

	//size_t stock()const noexcept;
	//size_t& stock() noexcept;

	// Clase de apoyo
	class Autores_vacios{};

	// Metodos virtuales
	virtual void impresion_especifica(std::ostream& os) const = 0;	// Virtual puro
	virtual ~Articulo(){}

protected:
	const Fecha f_publi_;

private:
	//Atributos
	const Autores autores_;
	const Cadena referencia_, titulo_;
	double precio_;
	//size_t stock_;
};

//Operadores externos
std::ostream& operator <<(std::ostream& os, const Articulo& art) noexcept;

// Metodos inline
inline const Cadena& Articulo::referencia() const noexcept{return referencia_;}
inline const Cadena& Articulo::titulo() const noexcept{return titulo_;}
inline const Fecha& Articulo::f_publi() const noexcept{return f_publi_;}
inline double Articulo::precio() const noexcept{return precio_;}
inline double& Articulo::precio() noexcept{return precio_;}
//inline size_t Articulo::stock() const noexcept{return stock_;}
//inline size_t& Articulo::stock() noexcept{return stock_;}
inline const Articulo::Autores& Articulo::autores() const noexcept{return autores_;}


// Clase Articulo Almacenable
class ArticuloAlmacenable: public Articulo
{
	public:
		ArticuloAlmacenable(const Autores& autor, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, size_t stock = 0);
		
		// Observador
		size_t stock() const noexcept;

		// Modificador
		size_t& stock() noexcept;

		//virtual void impresion_especifica(std::ostream& os) const noexcept;

	protected:
		size_t stock_;
};

// Metodos inline de la clase ArticuloAlmacenable
inline ArticuloAlmacenable::ArticuloAlmacenable(const Autores& autor, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, size_t stock):
	Articulo(autor, referencia, titulo, fecha, precio), stock_{stock}{}

inline size_t ArticuloAlmacenable::stock() const noexcept{return stock_;}
inline size_t& ArticuloAlmacenable::stock() noexcept{return stock_;}


// Clase libro digital
class LibroDigital: public Articulo 
{
	public:
		LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, const Fecha& f_expir);
		const Fecha& f_expir() const noexcept;
		void impresion_especifica(std::ostream& os) const noexcept;

	private:
		const Fecha f_expir_;
};

// Metodos inline de la clase LibroDigital
inline LibroDigital::LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, const Fecha& f_expir):
	Articulo(autores, referencia, titulo, publicacion, precio), f_expir_{f_expir}{}

inline const Fecha& LibroDigital::f_expir() const noexcept{return f_expir_;}


// Clase Libro
class Libro: public ArticuloAlmacenable
{
	public:
		//Constructor
		Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, size_t paginas, size_t stock = 0);

		//Observador
		size_t n_pag() const noexcept;

		//Impresion Especifica de Libro
		void impresion_especifica(std::ostream& os) const noexcept;

	private:
	const size_t n_pag_;
};

// Metodos inline de la clase Libro
inline Libro::Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, size_t paginas, size_t stock):
	ArticuloAlmacenable(autores, referencia, titulo, fecha, precio, stock), n_pag_{paginas}{}
inline size_t Libro::n_pag() const noexcept{return n_pag_;}


// Clase revista
class Revista: public ArticuloAlmacenable
{
	public:
		// Constructor
		Revista(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, size_t numrevista, size_t periodicidad, size_t stock = 0);

		// Observadores
		size_t numero() const noexcept;
		int periodicidad() const noexcept;

		// Impresion especifica de revista
		void impresion_especifica(std::ostream& os) const noexcept;

	private:
		const size_t numrevista_;
		const size_t periodicidad_;
};

// Metodos inline de la clase revista
inline Revista::Revista(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, size_t numrevista, size_t periodicidad, size_t stock):
	ArticuloAlmacenable(autores, referencia, titulo, fecha, precio, stock), numrevista_{numrevista}, periodicidad_{periodicidad}{}
inline size_t Revista::numero() const noexcept{return numrevista_;}
inline int Revista::periodicidad() const noexcept{return periodicidad_;}


#endif