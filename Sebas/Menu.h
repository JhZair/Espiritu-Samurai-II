#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Menu
{
public:
    enum class GameState
    {
        MainMenu,
        Game,
        Controls,
        Exit
    };

    friend class Juego;  // Permite que la clase Juego acceda a los miembros privados de Menu.

    // Constructor y Destructor
    Menu();
    ~Menu();

    // Métodos públicos
    void set_values();           // Inicializa los valores y objetos necesarios
    void run_menu();             // Ejecuta el menú y la lógica de eventos
    void loop_events();          // Maneja los eventos del menú
    void draw_all();             // Dibuja los elementos del menú
    void showControls();         // Muestra la ventana de controles

    // Método de acceso para obtener el estado del juego
    GameState get_state() const { return state; }

private:
    // Miembros privados
    sf::RenderWindow window;                // Ventana principal
    sf::RenderWindow controlsWindow;         // Ventana de controles
    sf::Font font;                          // Fuente para los textos
    sf::Texture image;                      // Textura del fondo principal
    sf::Texture imagecontrolBackground;     // Fondo de la ventana de controles
    sf::Sprite bg;                          // Sprite del fondo principal
    sf::Sprite controlsBackground;          // Fondo de la ventana de controles
    sf::Text backButton;                    // Botón de "Volver" en la ventana de controles
    sf::RectangleShape winclose;            // Rectángulo para el botón de cerrar

    std::vector<sf::Text> texts;            // Texto de las opciones del menú
    std::vector<std::string> options;       // Opciones del menú
    std::vector<sf::Vector2f> coords;       // Coordenadas de las opciones
    std::vector<int> sizes;                 // Tamaños de las opciones
    int pos;                                // Posición seleccionada
    bool pressed;                           // Variable para evitar que se presione repetidamente
    bool theselect;                         // Marca si se ha hecho una selección
    bool isPlaying;                         // Marca si se seleccionó "Jugar"
    bool seleccionJugar;                    // Variable que marca si "Jugar" ha sido seleccionado

    sf::Vector2i pos_mouse;                 // Posición del ratón
    sf::Vector2f mouse_coord;               // Coordenadas del ratón

    // Método privado
    bool getSeleccionJugar() const;

    GameState state;  // Estado actual del juego (usando enum)
};

#endif // MENU_H
