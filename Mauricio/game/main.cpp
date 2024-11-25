#include "Juego.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>

enum class AppState
{
    Menu,
    Game,
    Exit
};

int main() {
    AppState appState = AppState::Menu;

    while (appState != AppState::Exit) {
        if (appState == AppState::Menu) {
            // Crear menu
            Menu menu;
            menu.run_menu();

            if (menu.get_state() == Menu::GameState::Game) {
                appState = AppState::Game;
            } else if (menu.get_state() == Menu::GameState::Exit) {
                appState = AppState::Exit;
            }
        }

        if (appState == AppState::Game) {
            Juego juego;
            juego.ejecutar();

            // Despues de temrinar el juego
            appState = AppState::Menu; 
        }
    }

    return 0;
}
