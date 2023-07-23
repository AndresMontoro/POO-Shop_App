# ifndef CADENA_HPP_
# define CADENA_HPP_

# include <iostream>
# include <string.h>

class Cadena
{
    public:
        // Constructores
        explicit Cadena(size_t s = 0, char c = ' ');
        Cadena(const Cadena& str);
        Cadena(const char* str);

        // Operador de asignacion
        Cadena& operator =(const Cadena&);

        // Operador de conversion
        explicit operator const char *() const;

        // Observadores
        size_t length() const noexcept;

        // Operador de concatenacion
        Cadena& operator +=(const Cadena& cad);

        // Operadores de indice
        char& operator[](size_t i);
        const char& operator[](size_t i) const;

        // Metodos at
        char& at(size_t i);
        const char& at(size_t i) const;

        // Funcion subcadena
        Cadena substr(size_t i, size_t tam) const;

        // Destructor
        ~Cadena();

    private:
        char *cadena_;
        size_t size_;
};

// OPERADORES LOGICOS
bool operator ==(const Cadena& cad1, const Cadena& cad2);
bool operator !=(const Cadena& cad1, const Cadena& cad2);
bool operator <(const Cadena& cad1, const Cadena& cad2);
bool operator >(const Cadena& cad1, const Cadena& cad2);
bool operator <=(const Cadena& cad1, const Cadena& cad2);
bool operator >=(const Cadena& cad1, const Cadena& cad2);

// Metodos inline
inline size_t Cadena::length() const noexcept {return size_;}
inline char& Cadena::operator [](size_t i) {return cadena_[i];} 
inline const char& Cadena::operator[](size_t i) const {return cadena_[i];}

inline Cadena::operator const char*() const {return cadena_;} 

// Concatenacion de cadenas
Cadena operator +(const Cadena& cadena1, const Cadena& cadena2);

# endif