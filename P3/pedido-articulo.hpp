#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <iostream>
#include <map>
#include <iomanip>
#include <unordered_map>

#include "pedido.hpp"
#include "articulo.hpp"

class Pedido;

/*--------------------LINEA DE PEDIDO--------------------*/

class LineaPedido
{
public:
	explicit LineaPedido(double pedido, unsigned cantidad  = 1);
	double precio_venta() const noexcept;
	unsigned cantidad() const noexcept;

private:
	double precio_venta_;
	unsigned cantidad_;
};

// Metodos clase LineaPedido
inline LineaPedido::LineaPedido(double pedido, unsigned cant): precio_venta_{pedido}, cantidad_{cant}{}
inline double LineaPedido::precio_venta() const noexcept {return precio_venta_;}
inline unsigned LineaPedido::cantidad() const noexcept {return cantidad_;}

// Insercion de flujo linea pedido
std::ostream& operator <<(std::ostream& os, const LineaPedido& lineapedido);

/*--------------------PEDIDO_ARTICULO--------------------*/
class OrdenaArticulos
{
	public: bool operator()(const Articulo* articulo1, const Articulo* articulo2) const noexcept;
};
class OrdenaPedidos
{
	public: bool operator()(const Pedido* pedido1, const Pedido* pedido2) const noexcept;
};

class Pedido_Articulo
{
public:
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

	// Asociacion
	void pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad = 1);
	void pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad = 1);

	// Observadores
	ItemsPedido detalle(const Pedido& pedido) const;
	Pedidos ventas(const Articulo& articulo) const;
	void mostrarDetallePedidos(std::ostream& os) const /*noexcept*/;
	void mostrarVentasArticulos(std::ostream& os) const /*noexcept*/;

private:
	typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedidoArticulo;
 	typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArticuloPedido;

 	PedidoArticulo pa;
 	ArticuloPedido ap;
};

// Metodos externos
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& p);

#endif