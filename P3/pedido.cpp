#include "pedido.hpp"
#include "articulo.hpp"

int Pedido::numero_pedidos_ = 0;

// Constructor de pedido
Pedido::Pedido(Usuario_Pedido& usuariopedido, Pedido_Articulo& pedidoarticulo, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& f):
	numero_{numero_pedidos_ + 1}, tarjeta_{&tarjeta}, fecha_{f}, total_{0.}
{
	total_ = 0;

	if(usuario.n_articulos() == 0)
		throw Vacio(usuario);

	if (!tarjeta.activa())
		throw Tarjeta::Desactivada{};

	if (f > tarjeta.caducidad())
	{
		Tarjeta::Caducada tarjeta_caducada(tarjeta.caducidad());
		throw tarjeta_caducada;
	}

	if (&usuario != tarjeta.titular())
	{
		Pedido::Impostor usuario_impostor(usuario);
		throw usuario_impostor;
	}


	for (auto it : usuario.compra())
	{
		// El articulo no cabe
		if (it.first->stock() < it.second)
		{
			usuario.vaciar_carro();
			throw Pedido::SinStock(*it.first);
		}
	}

	for (auto it : usuario.compra())
	{
		// Importe = precio * cantidad
		total_ += it.first->precio() * it.second;
		pedidoarticulo.pedir(*this, *it.first, it.first->precio(), it.second);
	}

	usuariopedido.asocia(this, &usuario);
	usuariopedido.asocia(&usuario, this);
	usuario.vaciar_carro();

	numero_pedidos_++;
}

//Operadores externos
std::ostream& operator <<(std::ostream& os, const Pedido& pedido)
{
    os << "Núm. pedido: " << pedido.numero() << std::endl;
    os << "Fecha: " << pedido.fecha() << std::endl;
    os << "Pagado con: ";
    switch(pedido.tarjeta()->tipo())
    {
        case 0:
            os << "VISA" << std::endl;
        break;
        case 1:
            os << "Mastercard" << std::endl;
        break;
        case 2:
            os << "Maestro" << std::endl;
        break;
        case 3:
            os << "JBC" << std::endl;
        break;
        case 4:
            os << "AmericanExpress" << std::endl;
        break;
    	case 5:
    		os << "Tipo indeterminado" << std::endl;
    	break;
    }
    
    os << " n.º: " << pedido.tarjeta()->numero() << std::endl;
    os << "Importe: " << std::fixed << std::setprecision(2) << pedido.total()<<" €"<<std::endl;
    return os;
}