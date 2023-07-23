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
        Cadena(Cadena&& str);

        // Operador de asignacion
        Cadena& operator =(const Cadena&);

        // Operador de asignacion por movimiento
        Cadena& operator =(Cadena&&);

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

        //Iteradores
		typedef char* iterator;
		typedef char const* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    	inline iterator begin() noexcept { return cadena_; }
		inline const_iterator cbegin() const noexcept { return cadena_; }
   		inline const_iterator begin() const noexcept { return cbegin(); }

		inline iterator end() noexcept { return cadena_ + size_; }
		inline const_iterator cend() const noexcept { return cadena_ + size_; }
		inline const_iterator end() const noexcept { return cend(); }

		inline const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		inline reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		inline const_reverse_iterator rbegin() const noexcept { return crbegin(); }

		inline const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		inline reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		inline const_reverse_iterator rend() const noexcept { return crend(); }

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

// ENTRADA/SALIDA      
std::ostream& operator<< (std::ostream& os, const Cadena& original); 
std::istream& operator>> (std::istream& is, Cadena& original);

// Para P2 y ss.
// Especializaci ón de la plantilla std ::hash<Key> para definir la función hash a usar
// en contenedores desordenados de Cadena, unordered_[set|map|multiset|multimap].
namespace std { // Estaremos dentro del espacio de nombres std.
    template <> // Es una especializaci ón de una plantilla para Cadena.
    struct hash<Cadena> 
    { // Es una clase con solo un operador público.
        size_t operator() (const Cadena& cad) const // El operador función.
        {
            hash<string> hs; // Creamos un objeto hash de string.
            auto p{(const char*)(cad)}; // Convertimos Cadena a cadena de bajo nivel.
            string s{p}; // Creamos un string desde la cadena de b. nivel .
            size_t res{hs(s)}; // El hash del string . Como hs.operator()(s);
            return res; // Devolvemos el hash del string.
            // En forma abreviada:
            // return hash<string>{}((const char*)(cad));
        }
    };
}


# endif