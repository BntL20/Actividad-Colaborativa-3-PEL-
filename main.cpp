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

    T& at_modificable(size_t pos) {
        if (pos >= size) {
            throw std::out_of_range("Posición inválida");
        }
        return data[pos];  // ← DEVUELVE REFERENCIA
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
int buscar_por_titulo_cancion(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
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
int buscar_por_genero_cancion(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
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
void cargar_demo_cancion(Dinarray<Cancion>* cat) {
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
void menu_busquedas_cancion(Dinarray<Cancion>* cat) {
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
                hits = buscar_por_titulo_cancion(cat, q);
            } else {
                if (opcion == 2) {
                    hits = buscar_por_album(cat, q);
                } else {
                    if (opcion == 3) {
                        hits = buscar_por_genero_cancion(cat, q);
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


// === CLASE PELICULA ===
class Pelicula {
public:
    std::string titulo;
    std::string genero;
    std::string calidad;
    bool disponible;

    Pelicula() : disponible(true) {}
    Pelicula(std::string t, std::string g, std::string c, bool d = true)
        : titulo(t), genero(g), calidad(c), disponible(d) {}

    void alquilar() { disponible = false; }
};

// === BÚSQUEDAS ===
int buscar_por_titulo(Dinarray<Pelicula>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Pelicula p = catalogo->at(i);
        if (contiene_subcadena_insensible(p.titulo, textoBuscado)) {
            if (resultados == 0) std::cout << "\nResultados por Título:\n";
            std::cout << " - [" << p.titulo << "]  Género: " << p.genero
                      << "  Calidad: " << p.calidad
                      << "  Estado: " << (p.disponible ? "Disponible" : "Alquilada") << "\n";
            resultados++;
        }
    }
    return resultados;
}

int buscar_por_genero(Dinarray<Pelicula>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Pelicula p = catalogo->at(i);
        if (contiene_subcadena_insensible(p.genero, textoBuscado)) {
            if (resultados == 0) std::cout << "\nResultados por Género:\n";
            std::cout << " - [" << p.titulo << "]  Género: " << p.genero
                      << "  Calidad: " << p.calidad
                      << "  Estado: " << (p.disponible ? "Disponible" : "Alquilada") << "\n";
            resultados++;
        }
    }
    return resultados;
}

int buscar_por_calidad(Dinarray<Pelicula>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Pelicula p = catalogo->at(i);
        if (contiene_subcadena_insensible(p.calidad, textoBuscado)) {
            if (resultados == 0) std::cout << "\nResultados por Calidad:\n";
            std::cout << " - [" << p.titulo << "]  Género: " << p.genero
                      << "  Calidad: " << p.calidad
                      << "  Estado: " << (p.disponible ? "Disponible" : "Alquilada") << "\n";
            resultados++;
        }
    }
    return resultados;
}

// === ALQUILAR ===
void alquilar_pelicula(Dinarray<Pelicula>* catalogo, std::string tituloBuscado) {
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Pelicula& p = catalogo->at_modificable(i);
        if (contiene_subcadena_insensible(p.titulo, tituloBuscado)) {
            if (p.disponible) {
                p.alquilar();
                std::cout << "Película '" << p.titulo << "' alquilada correctamente.\n";
            } else {
                std::cout << "La película '" << p.titulo << "' ya está alquilada.\n";
            }
            return;
        }
    }
    std::cout << "Película no encontrada.\n";
}

// === CARGA DE DATOS ===
void cargar_demo_pelicula(Dinarray<Pelicula>* cat) {
    cat->insertar_final(Pelicula("Inception", "Ciencia Ficcion", "UHD", true));
    cat->insertar_final(Pelicula("The Matrix", "Ciencia Ficcion", "FHD", false));
    cat->insertar_final(Pelicula("Pulp Fiction", "Crimen", "FHD", true));
    cat->insertar_final(Pelicula("Interstellar", "Ciencia Ficcion", "UHD", true));
    cat->insertar_final(Pelicula("The Godfather", "Crimen", "FHD", false));
    cat->insertar_final(Pelicula("Oppenheimer", "Drama", "UHD", true));
    cat->insertar_final(Pelicula("Dune", "Ciencia Ficcion", "UHD", true));
    cat->insertar_final(Pelicula("Blade Runner 2049", "Ciencia Ficcion", "UHD", true));
}

// === MENÚ ===
void menu_busquedas_pelicula(Dinarray<Pelicula>* cat) {
    int opcion = -1;
    bool continuar = true;

    while (continuar) {
        std::cout << "\n--- Buscador de Películas ---\n";
        std::cout << "1) Buscar por título\n";
        std::cout << "2) Buscar por género\n";
        std::cout << "3) Buscar por calidad\n";
        std::cout << "4) Alquilar película\n";
        std::cout << "5) Mostrar catálogo completo\n";
        std::cout << "0) Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore(1000, '\n');

        if (opcion == 0) {
            continuar = false;
        } else {
            std::string q;
            int hits = 0;

            if (opcion >= 1 && opcion <= 3) {
                std::cout << "Introduce texto de búsqueda: ";
                std::getline(std::cin, q);
            }

            switch (opcion) {
                case 1: hits = buscar_por_titulo(cat, q); break;
                case 2: hits = buscar_por_genero(cat, q); break;
                case 3: hits = buscar_por_calidad(cat, q); break;
                case 4:
                    std::cout << "Título de la película a alquilar: ";
                    std::getline(std::cin, q);
                    alquilar_pelicula(cat, q);
                    break;
                case 5:
                    std::cout << "\n=== CATÁLOGO COMPLETO ===\n";
                    for (size_t i = 0; i < cat->tam(); i++) {
                        Pelicula p = cat->at(i);
                        std::cout << " - [" << p.titulo << "]  Género: " << p.genero
                                  << "  Calidad: " << p.calidad
                                  << "  Estado: " << (p.disponible ? "Disponible" : "Alquilada") << "\n";
                    }
                    break;
                default:
                    std::cout << "Opción inválida.\n";
            }

            if (hits == 0 && opcion >= 1 && opcion <= 3) {
                std::cout << "No se encontraron películas con ese criterio.\n";
            }
        }
    }
}

// === MENÚ GENERAL ===
void menu_general() {
    int opcion = -1;
    bool continuar = true;

    while (continuar) {
        std::cout << "\n";
        std::cout << "======================================\n";
        std::cout << "     SISTEMA DE GESTIÓN MULTIMEDIA    \n";
        std::cout << "======================================\n";
        std::cout << "1) Módulo de Canciones\n";
        std::cout << "2) Módulo de Películas\n";
        std::cout << "0) Salir del programa\n";
        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore(1000, '\n');

        switch (opcion) {
            case 1: {
                Dinarray<Cancion>* catalogo_canciones = new Dinarray<Cancion>();
                cargar_demo_cancion(catalogo_canciones);
                menu_busquedas_cancion(catalogo_canciones);
                std::cout << "Saliendo del módulo de canciones...\n";
                delete catalogo_canciones;
                break;
            }
            case 2: {
                Dinarray<Pelicula>* catalogo_peliculas = new Dinarray<Pelicula>();
                cargar_demo_pelicula(catalogo_peliculas);
                menu_busquedas_pelicula(catalogo_peliculas);
                std::cout << "Saliendo del módulo de películas...\n";
                delete catalogo_peliculas;
                break;
            }
            case 0:
                continuar = false;
                std::cout << "¡Gracias por usar el sistema! Hasta pronto.\n";
                break;
            default:
                std::cout << "Opción no válida. Inténtelo de nuevo.\n";
        }
    }
}

    // Programa principal
int main() {
        menu_general();
    return 0;
}