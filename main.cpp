// Recurso 1 - Catálogo de Música con Dinarray
// Descripción: Gestiona un catálogo musical con búsqueda por título, álbum,
// género o grupo, usando una clase plantilla Dinarray.

#include <iostream>
#include <string>
#include <cctype>

// Plantilla de clase Dinarray
template <typename T>
class Dinarray {
private:
    T* data;         // bloque dinámico
    size_t size;     // elementos usados
    size_t capacity; // capacidad reservada

public:
    // Constructor
    Dinarray() {
        data = 0;
        size = 0;
        capacity = 0;
    }

    // Destructor
    ~Dinarray() {
        delete[] data;
        std::cout << "Memoria liberada (Dinarray)\n";
    }

    // Inserta elemento al final y amplía si se llena
    void insertar_final(T e) {
        if (size == capacity && size == 0) {
            capacity = 2;  // Capacidad mínima incial de 2
            data = new T[capacity];
        } else if (size == capacity) {
            capacity *= 2;  // Si el array se llena, se duplica la capacidad
            T* aux = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                aux[i] = data[i]; // Se copian los valores en el bloque nuevo
            }
            delete[] data;
            data = aux;
        }
        data[size] = e; // Se añade el nuevo elemento al final
        size++;  // Aumenta el tamaño
    }

    // Devuelve número de elementos
    size_t tam() {
        return size;
    }

    // Devuelve un elemento por posición
    T at(size_t pos) {
        if (pos >= size) {
            throw std::out_of_range("Posicion invalida");
        } else {
            return data[pos];
        }
    }
};

// Clase Cancion
class Cancion {
public:
    std::string album;
    std::string grupo;
    std::string genero;
    std::string titulo;

    // Constructor vacío
    Cancion() {
        album = "";
        grupo = "";
        genero = "";
        titulo = "";
    }

    // Constructor con parámetros
    Cancion(std::string a, std::string g, std::string ge, std::string t) {
        album = a;
        grupo = g;
        genero = ge;
        titulo = t;
    }
};

// Funciones auxiliares de texto

// Convierte un carácter en minúscula (solo si es letra mayúscula)
char to_lower_char(char c) {
    return (char)std::tolower((unsigned char)c);
}

// Convierte toda una cadena a minúsculas, carácter a carácter
std::string to_lower(std::string s) {
    // Recorre el string y aplica to_lower_char a cada posición
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = to_lower_char(s[i]);
    }
    return s; // Devuelve la versión en minúsculas
}

// Comprueba si una cadena contiene otra
bool contiene_subcadena_insensible(std::string texto, std::string patron) {
    // Se convierten ambas cadenas a minúsculas para hacer la comparación insensible
    std::string a = to_lower(texto);
    std::string b = to_lower(patron);

    // Si el patrón está vacío, se considera que sí se encuentra
    if (b.size() == 0) {
        return true;
    } else {
        // Si el patrón es más largo que el texto, no puede contenerlo
        if (a.size() < b.size()) {
            return false;
        }
    }

    // Recorre el texto posición por posición
    for (size_t i = 0; i <= a.size() - b.size(); i++) {
        size_t j = 0;
        // Compara carácter a carácter desde la posición actual
        while (j < b.size() && a[i + j] == b[j]) {
            j++;
        }
        // Si se recorrió todo el patrón, se encontró coincidencia
        if (j == b.size()) {
            return true;
        }
    }

    // Si se llega aquí, no hay coincidencias
    return false;
}

// Búsqueda por campo

// Búsqueda por título
int buscar_por_titulo(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Cancion c = catalogo->at(i);
        // Comprueba si el título contiene el texto buscado
        if (contiene_subcadena_insensible(c.titulo, textoBuscado)) {
            if (resultados == 0) {
                std::cout << "\nResultados por Título:\n";
            }
            std::cout << " - [" << c.titulo << "]  Álbum: " << c.album
                      << "  Grupo: " << c.grupo << "  Género: " << c.genero << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Búsqueda por álbum
int buscar_por_album(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Cancion c = catalogo->at(i);
        // Comprueba si el álbum contiene el texto buscado
        if (contiene_subcadena_insensible(c.album, textoBuscado)) {
            if (resultados == 0) {
                std::cout << "\nResultados por Álbum:\n";
            }
            std::cout << " - [" << c.titulo << "]  Álbum: " << c.album
                      << "  Grupo: " << c.grupo << "  Género: " << c.genero << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Búsqueda por género
int buscar_por_genero(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Cancion c = catalogo->at(i);
        // Comprueba si el género contiene el texto buscado
        if (contiene_subcadena_insensible(c.genero, textoBuscado)) {
            if (resultados == 0) {
                std::cout << "\nResultados por Género:\n";
            }
            std::cout << " - [" << c.titulo << "]  Álbum: " << c.album
                      << "  Grupo: " << c.grupo << "  Género: " << c.genero << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Búsqueda por grupo
int buscar_por_grupo(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Cancion c = catalogo->at(i);
        // Comprueba si el grupo contiene el texto buscado
        if (contiene_subcadena_insensible(c.grupo, textoBuscado)) {
            if (resultados == 0) {
                std::cout << "\nResultados por Grupo:\n";
            }
            std::cout << " - [" << c.titulo << "]  Álbum: " << c.album
                      << "  Grupo: " << c.grupo << "  Género: " << c.genero << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Carga de datos de ejemplo
void cargar_demo(Dinarray<Cancion>* cat) {
    cat->insertar_final(Cancion("Parachutes", "Coldplay", "Rock Alternativo", "Yellow"));
    cat->insertar_final(Cancion("Parachutes", "Coldplay", "Rock Alternativo", "Trouble"));
    cat->insertar_final(Cancion("Random Access Memories", "Daft Punk", "Electronica", "Get Lucky"));
    cat->insertar_final(Cancion("A Night at the Opera", "Queen", "Rock", "Bohemian Rhapsody"));
    cat->insertar_final(Cancion("1989", "Taylor Swift", "Pop", "Blank Space"));
    cat->insertar_final(Cancion("Hybrid Theory", "Linkin Park", "Nu Metal", "In the End"));
    cat->insertar_final(Cancion("Californication", "Red Hot Chili Peppers", "Rock", "Scar Tissue"));
    cat->insertar_final(Cancion("Abbey Road", "The Beatles", "Rock", "Come Together"));
    cat->insertar_final(Cancion("Abbey Road", "The Beatles", "Rock", "Something"));
}

// Método para el menú principal
void menu_busquedas(Dinarray<Cancion>* cat) {
    int opcion = -1;
    bool continuar = true;

    while (continuar) {
        std::cout << "\n--- Buscador de Canciones ---\n";
        std::cout << "1) Buscar por titulo\n";
        std::cout << "2) Buscar por album\n";
        std::cout << "3) Buscar por genero\n";
        std::cout << "4) Buscar por grupo\n";
        std::cout << "0) Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(1000, '\n');

        if (opcion == 0) {
            continuar = false;
        } else {
            std::string q;
            std::cout << "Introduce texto de busqueda: ";
            std::getline(std::cin, q);

            int hits = 0;
            if (opcion == 1) {
                hits = buscar_por_titulo(cat, q);
            } else {
                if (opcion == 2) {
                    hits = buscar_por_album(cat, q);
                } else {
                    if (opcion == 3) {
                        hits = buscar_por_genero(cat, q);
                    } else {
                        if (opcion == 4) {
                            hits = buscar_por_grupo(cat, q);
                        } else {
                            std::cout << "Opcion invalida.\n";
                        }
                    }
                }
            }

            if (hits == 0 && opcion >= 1 && opcion <= 4) {
                // Mensaje solicitado cuando no hay coincidencias
                std::cout << "No se ha podido encontrar el album.\n";
            }
        }
    }
}

// Programa principal
int main() {
    Dinarray<Cancion>* catalogo = new Dinarray<Cancion>();
    cargar_demo(catalogo);
    menu_busquedas(catalogo);
    delete catalogo;
    return 0;
}