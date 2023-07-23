#include "usuario.hpp"

std::unordered_set<Cadena> Usuario::usuarios_;

//***************************************Clave***************************************

//Constructor
Clave::Clave(const char* pass)
{
    char *salt;
    static const Semilla s;

    if(strlen(pass)<5)
    {
        Clave::Incorrecta corta(Clave::CORTA);
        throw corta;
    }

    else
    {
        salt = new char[3];

        const char* alpha="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
        salt[0] = alpha[rand() % strlen(alpha)];
        salt[1] = alpha[rand() % strlen(alpha)];
        salt[2] = '\0';
        char* cc = crypt(pass,salt);
        delete[] salt;

        if(cc==NULL)
        {
            Clave::Incorrecta error(Clave::ERROR_CRYPT);
            throw error;
        }
        else
        {
            clave_=cc;
        }
    }
}

//Funciones publicas
bool Clave::verifica(const char* c) const
{
    return !strcmp(crypt(c, (const char *)clave_), (const char *)clave_);
}

//***************************************Usuario***************************************

//Constructor
Usuario::Usuario(const Cadena& id,const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& password):id_{id}, nombre_{nombre}, apellidos_{apellidos}, direccion_{direccion}, clave_{password}
{
    // Si el usuario ya existe
    if(!usuarios_.insert(id).second)
    {
        Usuario::Id_duplicado id_error(id);
        throw id_error;
    }
}

//Destructor
Usuario::~Usuario()
{
    for(auto& iterador:tarjetas_)
    {
        iterador.second->anula_titular();
    }

    usuarios_.erase(id_);
}

void Usuario::compra(const Articulo& articulo, size_t cantidad)
{
    // Buscamos el articulo (const cast para poder modificar una referencia constante)
    auto a = articulos_.find(const_cast<Articulo*>(&articulo));

    // Si no esta en la cesta
    if (a == articulos_.end())
    {
        if (cantidad > 0)
            articulos_[const_cast<Articulo*>(&articulo)] = cantidad;
    }
    // Si esta ya en la cesta
    else
    {
        // Le asignamos esa cantidad si es mayor que 0
        if (cantidad > 0)   
            a->second = cantidad;
        // Si es 0, es que el usuario quiere eliminarlo del carrito
        else    
            articulos_.erase(a);

    }
}

void Usuario::vaciar_carro()
{
    articulos_.clear();
}

// Metodos de asociacion
void Usuario::es_titular_de(const Tarjeta& tarjeta)
{
    if(tarjeta.titular()==this)
        tarjetas_[tarjeta.numero()]=const_cast<Tarjeta*>(&tarjeta);
}

void Usuario::no_es_titular_de(Tarjeta& tarjeta)
{
    tarjetas_.erase(tarjeta.numero());
    tarjeta.anula_titular();
}

std::ostream& operator <<(std::ostream &os, const Usuario& u) noexcept
{
    os << u.id_ << " [" << u.clave_.clave() << "] " << u.nombre_ << " " << u.apellidos_ << std::endl;
    os << u.direccion_ << std::endl;

    os << "Tarjetas: " << std::endl;
    for(auto& i:u.tarjetas_)
    os << *i.second << std::endl;
    
    return os;
}

void mostrar_carro(std::ostream& o,const Usuario& usuario) noexcept
{
    o << "Carrito de compra de "<< usuario.id() << " [Artículos: " << usuario.n_articulos() << "]" << std::endl;
    o << " Cant. Artículo" << std::endl;
    o << "=======================================================================" << std::endl;
    for(auto& iterador: usuario.compra())
    {
		o << "   " << iterador.second << " [" << iterador.first->referencia() <<"] \"" << iterador.first->titulo() << "\", " << iterador.first->f_publi().anno();
		o << ". " << std::fixed << std::setprecision(2) << iterador.first->precio() <<" €" << std::endl;
    }
}
