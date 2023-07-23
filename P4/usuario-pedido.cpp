#include "usuario-pedido.hpp"

// Metodos de asociacion
void Usuario_Pedido::asocia(Usuario* usuario, Pedido* pedido)
{
	// Añadimos al diccionario los valores
	up[usuario].insert(pedido);
}

void Usuario_Pedido::asocia(Pedido* pedido, Usuario* usuario)
{
	pu.emplace(pedido, usuario);
}

// Metodos observadores
Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(const Usuario& u)const noexcept
{
	//Buscamos el usuario en el diccionario
	auto i = up.find((Usuario*)&u);

	// Si esta en el diccionario, lo devolvemos
	if(i != up.end())
		return i->second;

	// Si no esta en el diccionario, lo devolvemos vacio
	else 
		return Usuario_Pedido::Pedidos{};
}

const Usuario* Usuario_Pedido::cliente(const Pedido& p) const noexcept
{
	//Buscamos en el diccionario
	auto i = pu.find((Pedido*)&p);

	// Si esta en el diccionario, devolvemos el usuario
	if(i != pu.end())
		return i->second;

	// Si no esta en el diccionario, devolvemos nullptr
	else
		return nullptr;
}
