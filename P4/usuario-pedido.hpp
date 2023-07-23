#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <set>
#include <map>

class Usuario;
class Pedido;

class Usuario_Pedido
{
public:
	typedef std::set<Pedido*> Pedidos;

	// Metodos de asociacion
	void asocia(Usuario* usuario, Pedido* pedido);
	void asocia(Pedido* pedido, Usuario* usuario);

	// Metodos observadores
	Pedidos pedidos(const Usuario& usuario) const noexcept;
	const Usuario* cliente(const Pedido& usuario) const noexcept;

private:
	typedef std::map<Usuario*, Pedidos> UsuarioPedido;
	typedef std::map<Pedido*, Usuario*> PedidoUsuario;
	UsuarioPedido up;
	PedidoUsuario pu;
};

#endif