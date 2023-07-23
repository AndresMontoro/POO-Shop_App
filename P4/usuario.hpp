#ifndef USUARIO_H_
#define USUARIO_H_

#include "articulo.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"

#include <map> 
#include <unordered_map>
#include <unordered_set>
#include <cstdlib> 
#include <unistd.h> 
#include <cstring>

class Numero;
class Tarjeta;

class Clave
{
	struct Semilla;

public:
	//Enumeradores
	enum Razon{CORTA,ERROR_CRYPT};

	//Constructores
    Clave(const char* pass);

    //Funciones publicas
    bool verifica(const char* pass)const;
    const Cadena& clave()const noexcept;

    //Clases de apoyo
    class Incorrecta{
    public:
        Incorrecta(Clave::Razon causa);
        Clave::Razon razon()const noexcept;
    private:
        Clave::Razon causa_;
    };
private:
	//Atributos
	//Cifrada
    Cadena clave_;

    // Semilla
    struct Semilla
    {
    	inline Semilla(){srand(time(nullptr));}
    };
};

// Metodos inline
inline const Cadena& Clave::clave() const noexcept {return clave_;}

	//Metodos de la clase de excepcion
inline Clave::Incorrecta::Incorrecta(const Clave::Razon causa): causa_{causa}{}
inline Clave::Razon Clave::Incorrecta::razon() const noexcept{return causa_;}

	
class Usuario
{
public:
	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned int> Articulos;

	//Constructores
    Usuario(const Cadena& identificador, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& password);
    Usuario(const Usuario& usuario) = delete;
    Usuario& operator =(const Usuario& u) = delete;

    //Destructor
	~Usuario();

	//Observadores
	const Cadena& id() const noexcept;
	const Cadena& nombre() const noexcept;
	const Cadena& apellidos() const noexcept;
	const Cadena& direccion() const noexcept;
	const Tarjetas& tarjetas() const noexcept;
	const Articulos& compra() const noexcept;
	size_t n_articulos() const noexcept;

	// Asociacion
	void es_titular_de(const Tarjeta& t);
	void no_es_titular_de(Tarjeta& t);
	void compra(const Articulo& articulo, size_t cantidad = 1);	// Relacion con articulos
	void vaciar_carro();

	//Clases de apoyo
	class Id_duplicado
	{
		public:
			Id_duplicado(const Cadena& id);
			const Cadena& idd() const noexcept;
		private:
			Cadena idd_;
	};

	friend std::ostream& operator <<(std::ostream& os, const Usuario& u) noexcept;

private:
	//Atributos
    const Cadena id_, nombre_, apellidos_, direccion_;
    Clave clave_;
    Tarjetas tarjetas_;
    Articulos articulos_;

    static std::unordered_set<Cadena> usuarios_;
};


void mostrar_carro(std::ostream& os,const Usuario& usuario) noexcept;

// Metodos inline
inline const Cadena& Usuario::id() const noexcept{return id_;}
inline const Cadena& Usuario::nombre() const noexcept{return nombre_;}
inline const Cadena& Usuario::apellidos() const noexcept{return apellidos_;}
inline const Cadena& Usuario::direccion() const noexcept{return direccion_;}
inline const Usuario::Tarjetas& Usuario::tarjetas() const noexcept{return tarjetas_;}
inline const Usuario::Articulos& Usuario::compra() const noexcept{return articulos_;}
inline size_t Usuario::n_articulos() const noexcept{return articulos_.size();}

// Metodos inline de la clase de excepcion
inline Usuario::Id_duplicado::Id_duplicado(const Cadena& id):idd_(id){}
inline const Cadena& Usuario::Id_duplicado::idd() const noexcept{return idd_;}

#endif
