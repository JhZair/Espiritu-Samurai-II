#include "Juego.h"
#include <SFML/Graphics.hpp>

int main() {
    Juego juego;   // Instancia del juego
    Menu menu;     // Instancia del menú

    // Comenzamos por ejecutar el menú
    
    menu.run_menu(juego);
    return 0;
}
