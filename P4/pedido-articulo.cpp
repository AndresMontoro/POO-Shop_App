#include "pedido-articulo.hpp"

// Metodos clase Linea Pedido

std::ostream& operator <<(std::ostream &os, const LineaPedido& linea)
{
	std::locale::global(std::locale(""));
	os << std::fixed << std::setprecision(2) << linea.precio_venta() << " €\t" << linea.cantidad();
	return os;
}

// Metodos clase Pedido_Articulo

void Pedido_Articulo::pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad)
{
	//articulo.stock() -= cantidad;
	pa[&pedido].insert(std::make_pair(&articulo, LineaPedido(precio, cantidad)));
	ap[&articulo].insert(std::make_pair(&pedido, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad)
{
	pedir(pedido, articulo, precio, cantidad);
}

Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(const Pedido& pedido) const
{
	// Buscamos el articulo (convierto referencia a puntero)
	auto it = pa.find((Pedido*)&pedido);

	// Si no lo encuentra, devolvemos un ItemPedido vacio
	if (it == pa.end())
		return ItemsPedido{};
	// Si lo encuentra devolvemos el ItemPedido
	else
		return it->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(const Articulo& art) const
{
	// Buscamos en el diccionario
	auto it = ap.find((Articulo*)&art);

	// Si no lo encuentra, devolvemos el pedido vacio
	if (it == ap.end())
		return Pedidos{};
	// Si lo encuentra, devolvemos el pedido correspondiente
	else
		return it->second;
}

// Insercion de flujo de ItemsPedido
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& item_pedido)
{
	double total = 0.0;

	os << " PVP     Cantidad      Artículo\n";
	os << std::setfill('=') << std::setw(75) << " " << std::endl;

	// Recorremos e imprimimos
	for(auto& it:item_pedido)
	{
		total = total + (it.second.precio_venta() * it.second.cantidad());
		os << it.second << "\t";
		os << "[" << it.first->referencia() << "] " << it.first->titulo() << std::endl;
	}

	// Añadimos el total
	os << std::setfill('=') << std::setw(75) << " " << std::endl;
 	os << "Total\t" << total << " €\n\n\n";

 	return os;
}

// Insercion de flujo de Pedidos
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& pedido)
{
	double total = 0.0;
	unsigned cantidad = 0;

	os << "[Pedidos: " << pedido.size() << "]" << std::endl;
	os << std::setfill('=') << std::setw(75) << " " << std::endl;
	os << " PVP      Cantidad      Fecha" << std::endl;
	os << std::setfill('=') << std::setw(75) << " " << std::endl;

	// Recorremos e imprimimos
	for(auto& it:pedido)
	{
		total = total + (it.second.precio_venta() * it.second.cantidad());
		cantidad = cantidad + it.second.cantidad();
		os << it.second << "\t\t" << it.first->fecha() << std::endl;
	}

	// Annadimos el total y la cantidad
	os << std::setfill('=') << std::setw(75) << " " << std::endl;
 	os << total << " €\t" << cantidad << "\n\n\n";

 	return os;
}


void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os) const /*noexcept*/
{
	double precio = 0.0;

	for(auto& i:pa)
	{
		os << "Pedido núm. " << i.first->numero() << std::endl;
		os << "Cliente: " << i.first->tarjeta()->titular()->id() << "\tFecha: " << i.first->fecha() << std::endl;

		//Imprimimos ItemsPedido
		os << detalle(*i.first);
		precio += i.first->total();
	}
	os << std::endl << "TOTAL VENTAS\t" << precio << " €" << std::endl; 
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os) const 
{
	for(auto& i:ap)
	{
		os << "Ventas de " << "[" << i.first->referencia() << "] " << i.first->titulo() << std::endl;

		//Imprimimos Pedidos
		os << ventas(*i.first);
	}
}

bool OrdenaArticulos::operator()(const Articulo* articulo1, const Articulo* articulo2)const noexcept
{
	return articulo1->referencia() < articulo2->referencia();
}

bool OrdenaPedidos::operator()(const Pedido* pedido1, const Pedido* pedido2)const noexcept
{
	return pedido1->numero() < pedido2->numero();
}
