//**Hecho y comentado por Brent y Lucía

// Recurso 1 - Catálogo de Música con Dinarray
// Recurso 2 - Catálogo de Películas con Dinarray
// Decripcion general del codigo:

#include <iostream>
#include <string>
#include <cctype>

// Plantilla de clase Dinarray
template <typename T>
class Dinarray {
private:
    T* data;         // Puntero al bloque de memoria donde se almacenan los elementos
    size_t size;     // Número de elementos actualmente almacenados
    size_t capacity; // Capacidad máxima actual del array antes de necesitar redimensionarse

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
        // Si no hay memoria reservada aún, se reserva una capacidad mínima
        if (size == capacity && size == 0) {
            capacity = 2;  // Capacidad mínima incial de 2
            data = new T[capacity];
        } else if (size == capacity) {
            // Si el array está lleno, se duplica la capacidad y se copian los elementos
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

// **Funciones auxiliares de texto**

// Convierte un carácter en minúscula (solo si es mayuscula)
char to_lower_char(char c) { //Se usa el cast a unsigned char para evitar problemas con caracteres negativos
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

// Búsqueda por campo para CANCIONES

// Búsqueda por título
int buscar_por_titulo_cancion(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    // Recorre el catálogo comprobando coincidencias en el título
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Cancion c = catalogo->at(i);
        // Comprueba si el título contiene el texto buscado
        if (contiene_subcadena_insensible(c.titulo, textoBuscado)) {
            if (resultados == 0) {
                std::cout << "\nResultados por Titulo:\n";
            }
            std::cout << " - [" << c.titulo << "]  Album: " << c.album
                      << "  Grupo: " << c.grupo << "  Genero: " << c.genero << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Búsqueda por álbum
int buscar_por_album(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    // Recorre el catálogo comprobando coincidencias en el álbum
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Cancion c = catalogo->at(i);
        // Comprueba si el álbum contiene el texto buscado
        if (contiene_subcadena_insensible(c.album, textoBuscado)) {
            if (resultados == 0) {
                std::cout << "\nResultados por Album:\n";
            }
            std::cout << " - [" << c.titulo << "]  Album: " << c.album
                      << "  Grupo: " << c.grupo << "  Genero: " << c.genero << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Búsqueda por género
int buscar_por_genero_cancion(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    // Recorre el catalogo comprobando coincidencias en el género
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Cancion c = catalogo->at(i);
        // Comprueba si el género contiene el texto buscado
        if (contiene_subcadena_insensible(c.genero, textoBuscado)) {
            if (resultados == 0) {
                std::cout << "\nResultados por Genero:\n";
            }
            std::cout << " - [" << c.titulo << "]  Álbum: " << c.album
                      << "  Grupo: " << c.grupo << "  Genero: " << c.genero << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Búsqueda por grupo
int buscar_por_grupo(Dinarray<Cancion>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    // Recorre el catalogo comprobando coincidencias en el grupo
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Cancion c = catalogo->at(i);
        // Comprueba si el grupo contiene el texto buscado
        if (contiene_subcadena_insensible(c.grupo, textoBuscado)) {
            if (resultados == 0) {
                std::cout << "\nResultados por Grupo:\n";
            }
            std::cout << " - [" << c.titulo << "]  Álbum: " << c.album
                      << "  Grupo: " << c.grupo << "  Genero: " << c.genero << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Carga de datos de ejemplo
void cargar_demo_cancion(Dinarray<Cancion>* cat) {
    // Se inserta varias canciones de ejemplo en el catálogo
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

// Metodo para el menú principal del módulo canciones
void menu_busquedas_cancion(Dinarray<Cancion>* cat) {
    int opcion = -1;
    bool continuar = true;

    while (continuar) {
        // Muestra el menú de opciones del módulo canciones
        std::cout << "\n--- Buscador de Canciones ---\n";
        std::cout << "1) Buscar por titulo\n";
        std::cout << "2) Buscar por album\n";
        std::cout << "3) Buscar por genero\n";
        std::cout << "4) Buscar por grupo\n";
        std::cout << "0) Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(1000, '\n'); // Limpia el buffer para leer líneas completas después

        if (opcion == 0) {
            continuar = false; // Sale del menú y vuelve al menú principal
        } else {
            std::string q;
            std::cout << "Introduce texto de busqueda: ";
            std::getline(std::cin, q); // Permite búsquedas con espacios

            int hits = 0;
            // Dependiendo de la opción elegida, llama a la búsqueda correspondiente
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

            // Mensaje mostrado cuando no hay coincidencias
            if (hits == 0 && opcion >= 1 && opcion <= 4) {
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

    // Constructor por defecto: película disponible por defecto
    Pelicula() {
        titulo = "";
        genero = "";
        calidad = "";
        disponible = true;
    }
    // Constructor con parámetros
    Pelicula(std::string t, std::string g, std::string c, bool d = true) {
        titulo = t;
        genero = g;
        calidad = c;
        disponible = d;
    }

    // Marca la película como alquilada
    void alquilar() {
        disponible = false;
    }
};

// === BÚSQUEDAS ===
//Busqueda por titulo
int buscar_por_titulo(Dinarray<Pelicula>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    // Recorre las películas buscando coincidencias en el título
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Pelicula p = catalogo->at(i);
        if (contiene_subcadena_insensible(p.titulo, textoBuscado)) {
            if (resultados == 0) std::cout << "\nResultados por Titulo:\n";
            std::cout << " - [" << p.titulo << "]  Genero: " << p.genero
                      << "  Calidad: " << p.calidad
                      << "  Estado: " << (p.disponible ? "Disponible" : "Alquilada") << "\n";
            resultados++;
        }
    }
    return resultados;
}

//Busqueda por genero
int buscar_por_genero(Dinarray<Pelicula>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    // Recorre las películas buscando coincidencias en el género
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Pelicula p = catalogo->at(i);
        if (contiene_subcadena_insensible(p.genero, textoBuscado)) {
            if (resultados == 0) std::cout << "\nResultados por Genero:\n";
            std::cout << " - [" << p.titulo << "]  Genero: " << p.genero
                      << "  Calidad: " << p.calidad
                      << "  Estado: " << (p.disponible ? "Disponible" : "Alquilada") << "\n";
            resultados++;
        }
    }
    return resultados;
}

//Busqueda por calidad
int buscar_por_calidad(Dinarray<Pelicula>* catalogo, std::string textoBuscado) {
    int resultados = 0;
    // Recorre las películas buscando coincidencias en la calidad (e.g., UHD, FHD)
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Pelicula p = catalogo->at(i);
        if (contiene_subcadena_insensible(p.calidad, textoBuscado)) {
            if (resultados == 0) std::cout << "\nResultados por Calidad:\n";
            std::cout << " - [" << p.titulo << "]  Genero: " << p.genero
                      << "  Calidad: " << p.calidad
                      << "  Estado: " << (p.disponible ? "Disponible" : "Alquilada") << "\n";
            resultados++;
        }
    }
    return resultados;
}

// Alquilar pelicula
// Busca una película por título y cambia su estado a alquilada si está disponible
void alquilar_pelicula(Dinarray<Pelicula>* catalogo, std::string tituloBuscado) {
    for (size_t i = 0; i < catalogo->tam(); i++) {
        Pelicula& p = catalogo->at_modificable(i); // Se obtiene referencia para modificar el objeto
        if (contiene_subcadena_insensible(p.titulo, tituloBuscado)) {
            if (p.disponible) {
                p.alquilar();
                std::cout << "Pelicula '" << p.titulo << "' alquilada correctamente.\n";
            } else {
                std::cout << "La pelicula '" << p.titulo << "' ya esta alquilada.\n";
            }
            return; // Sale después de procesar la primera coincidencia
        }
    }
    std::cout << "Pelicula no encontrada.\n";
}

// === CARGA DE DATOS ===
void cargar_demo_pelicula(Dinarray<Pelicula>* cat) {
    // Se inserta películas de ejemplo en el catálogo
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
        // Muestra el menú del módulo de películas
        std::cout << "\n--- Buscador de Peliculas ---\n";
        std::cout << "1) Buscar por titulo\n";
        std::cout << "2) Buscar por genero\n";
        std::cout << "3) Buscar por calidad\n";
        std::cout << "4) Alquilar pelicula\n";
        std::cout << "5) Mostrar catalogo completo\n";
        std::cout << "0) Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(1000, '\n'); // Limpia el buffer

        if (opcion == 0) {
            continuar = false; // Vuelve al menú general
        } else {
            std::string q;
            int hits = 0;

            // Para las búsquedas, pide el texto de búsqueda
            if (opcion >= 1 && opcion <= 3) {
                std::cout << "Introduce texto de busqueda: ";
                std::getline(std::cin, q);
            }

            // Ejecuta la acción según la opción seleccionada
            switch (opcion) {
                case 1:
                    hits = buscar_por_titulo(cat, q);
                    break;
                case 2:
                    hits = buscar_por_genero(cat, q);
                    break;
                case 3:
                    hits = buscar_por_calidad(cat, q);
                    break;
                case 4:
                    // Alquilar: pide el título y llama a la función de alquiler
                    std::cout << "Titulo de la pelicula a alquilar: ";
                    std::getline(std::cin, q);
                    alquilar_pelicula(cat, q);
                    break;
                case 5:
                    // Muestra el catálogo completo con estado
                    std::cout << "\n=== CATALOGO COMPLETO ===\n";
                    for (size_t i = 0; i < cat->tam(); i++) {
                        Pelicula p = cat->at(i);
                        std::cout << " - [" << p.titulo << "]  Genero: " << p.genero
                                  << "  Calidad: " << p.calidad
                                  << "  Estado: " << (p.disponible ? "Disponible" : "Alquilada") << "\n";
                    }
                    break;
                default:
                    std::cout << "Opcion invalida.\n";
            }

            // Si fue una búsqueda y no hubo resultados, informa al usuario
            if (hits == 0 && opcion >= 1 && opcion <= 3) {
                std::cout << "No se encontraron peliculas con ese criterio.\n";
            }
        }
    }
}

// === MENÚ GENERAL (de canciones y peliculas) ===
void menu_general() {
    int opcion = -1;
    bool continuar = true;

    while (continuar) {
        // Muestra el menú principal del sistema
        std::cout << "\n";
        std::cout << "======================================\n";
        std::cout << "     SISTEMA DE GESTION MULTIMEDIA    \n";
        std::cout << "======================================\n";
        std::cout << "1) Modulo de Canciones\n";
        std::cout << "2) Modulo de Peliculas\n";
        std::cout << "0) Salir del programa\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(1000, '\n'); // Limpia el buffer antes de leer líneas

        switch (opcion) {
            case 1: {
                // Crea catálogo dinámico para canciones, carga datos y muestra el menú
                Dinarray<Cancion>* catalogo_canciones = new Dinarray<Cancion>();
                cargar_demo_cancion(catalogo_canciones);
                menu_busquedas_cancion(catalogo_canciones);
                std::cout << "Saliendo del modulo de canciones...\n";
                delete catalogo_canciones; // Libera memoria al salir del módulo
                break;
            }
            case 2: {
                // Crea catálogo dinámico para películas, carga datos y muestra el menú
                Dinarray<Pelicula>* catalogo_peliculas = new Dinarray<Pelicula>();
                cargar_demo_pelicula(catalogo_peliculas);
                menu_busquedas_pelicula(catalogo_peliculas);
                std::cout << "Saliendo del modulo de películas...\n";
                delete catalogo_peliculas; // Libera memoria al salir del módulo
                break;
            }
            case 0:
                // Opción para salir del sistema
                continuar = false;
                std::cout << "Saliendo del Sistema...\n";
                break;
            default:
                std::cout << "Opcion no válida. Intentelo de nuevo.\n";
        }
    }
}

int main() {
    // Punto de entrada: inicia el menú principal
    menu_general();
    return 0;
}
