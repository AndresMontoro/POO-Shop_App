#ifndef _PEDIDO_HPP_
#define _PEDIDO_HPP_

#include <iostream>
#include "tarjeta.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include "articulo.hpp"

class Usuario;
class Fecha;
class Articulo;
class Usuario_Pedido;
class Pedido_Articulo;

class Pedido
{
public:
	// Constructor
	Pedido(Usuario_Pedido& usuariopedido, Pedido_Articulo& pedidoarticulo, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& hoy = Fecha());

	// Observadores
	inline int numero() const noexcept{return numero_;}
	inline const Tarjeta* tarjeta() const noexcept{return tarjeta_;}
	inline const Fecha& fecha() const noexcept{return fecha_;}
	inline double total() const noexcept{return total_;}
	inline static int n_total_pedidos() noexcept{return numero_pedidos_;}

	// Excepciones
	class Vacio
	{
	public:
		Vacio(const Usuario& usuario);
		const Usuario& usuario() const;
	private:
		const Usuario* us;
	};

	class Impostor
	{
	public:
		Impostor(const Usuario& usuario);
		const Usuario& usuario() const;
	private:
		const Usuario* us;
	};

	class SinStock
	{
	public:
 		SinStock(const Articulo& articulo);
 		const Articulo& articulo() const;
 	private:
 		const Articulo* art;
	};

private:
	int numero_;
	const Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;
	static int numero_pedidos_;
};

// Metodos clase Vacio
inline Pedido::Vacio::Vacio(const Usuario& usuario): us{&usuario}{}
inline const Usuario& Pedido::Vacio::usuario() const{return *us;}

// Metodos clase Impostor
inline Pedido::Impostor::Impostor(const Usuario& usuario): us{&usuario}{}
inline const Usuario& Pedido::Impostor::usuario() const{return *us;}

// Metodos clase SinStock
inline Pedido::SinStock::SinStock(const Articulo& articulo): art{&articulo}{}
inline const Articulo& Pedido::SinStock::articulo() const{return *art;}


// Insercion en flujo
std::ostream& operator <<(std::ostream& os, const Pedido& pedido);



#endif