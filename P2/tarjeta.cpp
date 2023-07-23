#include "tarjeta.hpp"

std::set<Numero> Tarjeta::tarjetas_;
bool luhn(const Cadena& numero);

// Numero
struct EsBlanco
{
    bool operator()(char c)const {return isspace(c);}
    typedef char argument_type;
};

struct EsDigito
{
    bool operator()(char c)const {return isdigit(c);}
    typedef char argument_type;
};

//Constructores
Numero::Numero(const Cadena& cad)
{
    Cadena c = cad;

    // Eliminamos espacios
    auto it_espacios = std::remove_if(c.begin(), c.end(), [](char x){return std::isspace(x);});

    if (it_espacios != c.end())
    {
        int cont = 0;
        auto i = c.begin();

        while(i != it_espacios)
        {
            i++;
            cont++;
        }

        c = c.substr(0, cont);
    }

    // Comprobamos que sean digitos
    auto it_digitos = std::find_if(c.begin(), c.end(), std::not1(EsDigito()));

    if (it_digitos != c.end())
    {
        Numero::Incorrecto digito_incorrecto(Razon::DIGITOS);
        throw digito_incorrecto;
    }

    // Longitud incorrecta
    if (c.length() < 13 || c.length() > 19)
    {
        Numero::Incorrecto error_longitud(Razon::LONGITUD);
        throw error_longitud;
    }
    else if(!luhn(c))
    {
        Numero::Incorrecto error_no_valido(Razon::NO_VALIDO);
        throw error_no_valido;
    }else
    {
        // Copiamos la cadena sin espacios
        numero_ = c;   
    }


}

// TARJETA            

//Constructores
Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f): numero_{n}, titular_(&u), caducidad_{f}, activa_{true}
{
    Fecha hoy;

    if (f < hoy)
    {
        Tarjeta::Caducada c(f);
        throw c;   
    }else if (!tarjetas_.insert(n).second)  // Numero duplicado
    {
        Tarjeta::Num_duplicado duplicada(n);
        throw duplicada;
    }else
    {
        titular_->es_titular_de(*this);
    }
}

//Destructores
Tarjeta::~Tarjeta()
{
    if(titular_)
        titular_->no_es_titular_de(*this);

    // Borramos la tarjeta
    tarjetas_.erase(numero_);
}

//Funciones publicas


//Metodo Observador del tipo de la tarjeta
Tarjeta::Tipo Tarjeta::tipo()const noexcept
{
    //Tomamos los 2 primeros caracteres
    Cadena primeros(2);
    primeros[0] = numero_[0];
    primeros[1] = numero_[1];

    //Segun sean estos dos caracteres devolvemos un Tipo (podemos cambiarlo por un switch)
    if(primeros == "34" || primeros == "37")
        return Tarjeta::AmericanExpress;

    else if(primeros[0] == '3')
        return Tarjeta::JCB;

    else if(primeros[0] == '4')
        return Tarjeta::VISA;

    else if(primeros[0] == '5')
        return Tarjeta::Mastercard;

    else if(primeros[0] == '6')
        return Tarjeta::Maestro;

    else
        return Tarjeta::Otro;
}


// Metodo para anular tarjeta (solo lo puede llamar usuario)
void Tarjeta::anula_titular()
{
    //Desactivamos la tarjeta
    activa_ = false;
    
    // Se la quitamos a su titular
    const_cast<Usuario*&>(titular_) = nullptr;
}

// Insercion de flujo de tipo
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& t)
{
 //cadena representando el tipo segun sea el tipo de la tarjeta
    switch(t)
    {
        case Tarjeta::Otro: os << "Otro"; break;
        case Tarjeta::VISA: os << "VISA"; break;
        case Tarjeta::Mastercard: os << "MasterCard"; break;
        case Tarjeta::Maestro: os << "Maestro"; break;
        case Tarjeta::JCB: os << "JCB"; break;
        case Tarjeta::AmericanExpress: os << "AmericanExpress"; break;
        default: os <<"Error Tipo de Tarjeta";
    }
 
    return os;
}

// Insercion de flujo de Tarjeta
std::ostream& operator <<(std::ostream& os, const Tarjeta& t) noexcept
{
    os << " " << std::setfill('-') << std::setw(30) << " " << std::endl;
    os << "/                    \\" << std::endl;

    os << "| " << std::left << std::setfill(' ') << std::setw(28) << t.tipo() << "|" << std::endl;
    os << "| " << std::setfill(' ') << std::setw(28) << t.numero() << "|"<< std::endl;

    //Cadena auxiliar para mostrar el nombre en mayusculas
    Cadena cad_mostrar = t.titular()->nombre() + " " + t.titular()->apellidos();
    
    for(auto& x:cad_mostrar)
        if(islower(x))
            x = toupper(x);

    os << "| " << std::setfill(' ') << std::setw(28) << cad_mostrar << "|" << std::endl;

    //Fecha de vencimiento formateada
    os << std::right << "| Caduca: " << std::setfill('0') << std::setw(2) << (t.caducidad().mes()) << "/" << std::setw(2) << (t.caducidad().anno()%100) << std::setfill(' ') << std::setw(16) << "|" << std::endl;
 
    os << "\\                             /" << std::endl;
    os << " -----------------------------" << std::endl;
 
    return os;
}