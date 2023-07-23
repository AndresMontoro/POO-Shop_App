# include "cadena.hpp"

/*-------------------------CONSTRUCTORES-------------------------*/
Cadena::Cadena(size_t size, char c):
    cadena_{new char[size + 1]}, size_{size}
{
    for (size_t i = 0; i < size_; i++)
    {
        cadena_[i] = c;
    }

    cadena_[size] = '\0';
}

Cadena::Cadena(const Cadena& str):
    cadena_{new char[str.size_ + 1]}, size_ {str.size_}
{
    // Copiamos el string en otro
    strcpy(cadena_, str.cadena_);
}

Cadena::Cadena(const char* str):
    cadena_{new char[strlen(str) + 1]}, size_{strlen(str)}
{
    // Copiamos la cadena
    strcpy(cadena_, str);
}

Cadena::Cadena(Cadena&& str):
    cadena_{str.cadena_}, size_{str.size_}
{
    // Borrado logico cadena original
    str.size_ = 0;
    //str.cadena_ = nullptr;

    str.cadena_ = new char[1];
    str.cadena_[0] = '\0';

}

/*-------------------------OPERADOR DE ASIGNACION-------------------------*/
Cadena& Cadena::operator =(const Cadena& cad)   // Por copia
{
    if (this != &cad)
    {
        // Destruimos la cadena y la copiamos
        delete[] cadena_;
        cadena_ = new char[cad.size_ + 1];
        size_ = cad.size_;
        strcpy(cadena_, cad.cadena_);
    }

    return *this;
}

Cadena& Cadena::operator =(Cadena&& cad)    // Por movimiento
{
    if (this != &cad)
    {
        // Destruimos la cadena y la copiamos
        delete[] cadena_;
        cadena_ = cad.cadena_;
        size_ = cad.size_;
        
        cad.cadena_ = new char[1];
        cad.cadena_[0] = '\0';
        cad.size_ = 0;
    }

    return *this;
}


/*-------------------------OPERADORES DE CONCATENACION-------------------------*/
Cadena& Cadena::operator +=(const Cadena& cad)
{
    // Nos guardamos la cadena en una variable auxiliar
    char* aux = new char[size_ + 1];
    strcpy(aux, cadena_);

    // El tamannio de las cadenas concatenadas es la suma de ambas
    size_ = size_ + cad.size_;

    // Borramos la cadena actual y reservamos la nueva memoria
    delete[] cadena_;
    cadena_ = new char[size_ + 1];

    // Copiamos la cadena anterior
    strcpy(cadena_, aux);

    // Concatenamos
    strcat(cadena_, cad.cadena_);

    // Eliminamos la variable auxiliar
    delete[] aux;

    return *this;
}

Cadena operator +(const Cadena& cadena1, const Cadena& cadena2)
{
    // Creamos una cadena auxiliar
    Cadena concatenada(cadena1);
    return concatenada += cadena2;
}

/*-------------------------OPERADORES LÓGICOS-------------------------*/
bool operator ==(const Cadena& cad1, const Cadena& cad2)
{
    return !strcmp((const char*)cad1, (const char*)cad2);
}

bool operator !=(const Cadena& cad1, const Cadena& cad2)
{
    return strcmp((const char*)cad1, (const char*)cad2);
}

bool operator <(const Cadena& cad1, const Cadena& cad2)
{
    return (strcmp((const char*)cad1, (const char*)cad2) < 0);
}

bool operator >(const Cadena& cad1, const Cadena& cad2)
{
    return cad2 < cad1;
}

bool operator <=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad2 < cad1);
}

bool operator >=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad1 < cad2);
}

/*-------------------------METODOS AT-------------------------*/
char& Cadena::at(size_t i)
{
    if (i < size_)
        return cadena_[i];
    
    else
        throw std::out_of_range("Funcion at(): fuera de limites.");
}

const char& Cadena::at(size_t i) const
{
    if (i < size_)
        return cadena_[i];
    
    else
        throw std::out_of_range("Funcion at(): fuera de limites.");
}

/*-------------------------METODOS SUBSTR-------------------------*/
Cadena Cadena::substr(size_t i, size_t tam) const
{
    if(i+tam > size_ || tam > size_ || i > size_)
        throw std::out_of_range("Funcion substr(): fuera de limites.");

    else
    {
        Cadena aux(tam);
        strncpy(aux.cadena_, cadena_ + i, tam);
        aux.cadena_[tam] = '\0';
        return aux;
    }
}

/*-------------------------DESTRUCTOR-------------------------*/
Cadena::~Cadena()
{
    delete[] cadena_;
    size_ = 0;
}

/*-------------------------ENTRADA/SALIDA-------------------------*/

std::ostream& operator << (std::ostream& os, const Cadena& original)
{
    os << (const char*)original; // Le metemos la cadena a bajo nivel
    return os;
}

std::istream& operator >> (std::istream& is, Cadena& original)
{
    char s[33] = "";
    is.width(33);   // 32 caracteres y \0

    is >> s;
    original = s;
    

    return is;
}