#include "pedido.hpp"
#include "articulo.hpp"

int Pedido::numero_pedidos_ = 0;

// Constructor de pedido
Pedido::Pedido(Usuario_Pedido& usuariopedido, Pedido_Articulo& pedidoarticulo, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& f):
	numero_{numero_pedidos_ + 1}, tarjeta_{&tarjeta}, fecha_{f}, total_{0.}
{
	total_ = 0;
	bool pedido_vacio = true;

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

	auto it = usuario.compra().begin();

	while (it != usuario.compra().end())
	{
		// Si es almacenable
		if (ArticuloAlmacenable* art = dynamic_cast<ArticuloAlmacenable*>(it->first))
		{
			// Si no hay suficiente stock
			if (art->stock() < it->second)
			{
				SinStock error_stock{*it->first};
				const_cast<Usuario::Articulos&>(usuario.compra()).clear();
				throw error_stock;
			}
			
			else if (pedido_vacio)
				pedido_vacio = false;
			

			it++;
		}

		// Si es un libro digital
		else if (LibroDigital* ldig = dynamic_cast<LibroDigital*>(it->first))
		{
			// Comprobamos que la fecha de expiración sea posterior
			if (ldig->f_expir() < f)
			{
				// Primero guardamos el iterador para no perderlo
				auto aux = it;
				aux++;
				usuario.compra(*it->first, 0);
				it = aux;
			}

			else
			{
				it++;
		
				if (pedido_vacio)
					pedido_vacio = false;
				
			}
		}

		else
			throw std::logic_error("Error constructor de Pedido: tipo desconocido");
	}

	// Comprobacion pedido vacio
	if (pedido_vacio)
		throw Vacio(usuario);
	

	// Ahora compramos
	it = usuario.compra().begin();

	while (it != usuario.compra().end())
	{
		total_ += it->first->precio() * it->second;
		pedidoarticulo.pedir(*this, *it->first, it->first->precio(), it->second);

		if (ArticuloAlmacenable* art = dynamic_cast<ArticuloAlmacenable*>(it->first))
			art->stock() -= it->second;
		it++;
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