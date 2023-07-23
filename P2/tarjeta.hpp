#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"


#include <set> 
#include <iostream> 
#include <cctype> 
#include <iomanip> 
#include <algorithm>


class Usuario;      // No entiendo por que hay que hacer una declaracion adelantada

class Numero
{
public:
    //Enumeradores
    enum Razon{LONGITUD, DIGITOS, NO_VALIDO};

    //Constructor
    Numero(const Cadena& cad);

    //Operadores internos
    operator const char*() const noexcept;

    //Clases de excepcion
    class Incorrecto{
    public:
        Incorrecto(Numero::Razon r);
        Numero::Razon razon() const noexcept;
    private:
        Numero::Razon razon_;
    };

private:
    //Atributos
    Cadena numero_;
};

// Metodos inline
    //Constructor y observador clase incorrecto
inline Numero::Incorrecto::Incorrecto(Numero::Razon r):razon_{r}{}
inline Numero::Razon Numero::Incorrecto::razon() const noexcept{return razon_;}
    
    // Conversor a const char
inline Numero::operator const char*() const noexcept{return (const char *)numero_;}

    //Operador de comparación
inline bool operator <(const Numero& n1, const Numero& n2){ return static_cast<Cadena>(n1) < static_cast<Cadena>(n2);}



class Tarjeta{
public:
    //Enumeradores
    enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress, Otro};

    //Constructores
    Tarjeta(const Numero& n, Usuario& u, const Fecha& f);

    Tarjeta(const Tarjeta& t) = delete;
    Tarjeta& operator=(const Tarjeta& t) = delete;


    //Destructores
    ~Tarjeta();

    //Observadores
    //Metodos Observadores
     const Numero& numero() const noexcept;
     Usuario* titular() const noexcept;
     const Fecha& caducidad() const noexcept;
     Tipo tipo() const noexcept;
     bool activa() const noexcept;

    // Sobrecarga operador activa para modificar el estado
    bool activa(bool b) noexcept;     

    //Clases de apoyo
    class Desactivada{
    public:
        inline Desactivada(){};
    };
    
    class Caducada{
    public:
        Caducada(const Fecha& fecha);
        const Fecha& cuando()const noexcept;
    private:
        Fecha caducidad_;
    };

    class Num_duplicado{
    public:
        Num_duplicado(const Numero& numero);
        const Numero& que()const noexcept;
    private:
        Numero numero_;
    };

private:
    //Atributos
    //Tipo tipo_;
    const Numero numero_;
    Usuario* const titular_;
    const Fecha caducidad_;
    bool activa_;

    friend class Usuario;
    void anula_titular();

    static std::set<Numero> tarjetas_;
};


//Inserción en flujo
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tip);
std::ostream& operator <<(std::ostream& os, const Tarjeta& t) noexcept;

// Metodos inline
    // Operador de comparacion
inline bool operator <(const Tarjeta& t1, const Tarjeta& t2) noexcept
{
    return t1.numero() < t2.numero();
}

    // Observadores
inline const Numero& Tarjeta::numero() const noexcept
{
    return numero_;
}

inline Usuario* Tarjeta::titular() const noexcept
{
    return titular_;
}

inline const Fecha& Tarjeta::caducidad() const noexcept
{
    return caducidad_;
}

inline bool Tarjeta::activa(bool b) noexcept
{
    activa_ = b;
    return activa_;
}

inline bool Tarjeta::activa() const noexcept
{
    return activa_;
}

    // Metodos inline clase de excepcion Caducada
inline Tarjeta::Caducada::Caducada(const Fecha& f): caducidad_{f}{}     // Constructor
inline const Fecha& Tarjeta::Caducada::cuando() const noexcept{return caducidad_;}      // Observador


    // Metodos inline clase de excepcion Num_duplicado
inline Tarjeta::Num_duplicado::Num_duplicado(const Numero& n): numero_{n}{}     // Constructor
inline const Numero& Tarjeta::Num_duplicado::que() const noexcept{return numero_;}      // Observador


#endif // TARJETA_H