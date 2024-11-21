#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState { MainMenu, Game, Exit };

class Menu {
private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text menuText;
    GameState state;

    // Elementos del juego
    sf::RectangleShape player;
    sf::Texture gameBackground;
    sf::Sprite backgroundSprite;

public:
    Menu() : window(nullptr), state(GameState::MainMenu) {
        window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Menu SFML");
    }

    ~Menu() {
        delete window;
    }

    void set_values() {
        if (!font.loadFromFile("assets/fonts/upheavtt.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
            exit(-1);
        }

        // Menu
        menuText.setFont(font);
        menuText.setString("Press ENTER to Start Game");
        menuText.setCharacterSize(30);
        menuText.setPosition(400.f, 300.f);

        // Jugador
        player.setSize(sf::Vector2f(50.f, 50.f));  // Tamaño del jugador
        player.setFillColor(sf::Color::Green);  // Color verde para el jugador
        player.setPosition(600.f, 360.f);  // Posición inicial

        // Cargar el fondo del juego
        if (!gameBackground.loadFromFile("assets/images/Fondo_menu/img (1).jpg")) {
            std::cerr << "Error loading game background!" << std::endl;
            std::cerr << "Please check if the file path is correct." << std::endl;
            exit(-1);
        }
        backgroundSprite.setTexture(gameBackground);
    }

    void loop_events() {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                state = GameState::Exit;  // Cambiar el estado a Exit cuando se cierra la ventana
            }

            // Cambiar estado a Game cuando se presiona Enter
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                state = GameState::Game;
            }
        }
    }

    void draw_all() {
        window->clear();  // Limpiar la pantalla

        // Mostrar el contenido según el estado
        if (state == GameState::MainMenu) {
            window->draw(menuText);  // Mostrar el texto del menú
        } else if (state == GameState::Game) {
            window->draw(backgroundSprite);  // Mostrar el fondo del juego
            window->draw(player);  // Mostrar al jugador
        }

        window->display();  // Mostrar la ventana
    }

    void run_menu() {
        while (window->isOpen()) {
            loop_events();
            draw_all();

            if (state == GameState::Game) {
                // Lógica del juego: movimiento del jugador
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    player.move(-5.f, 0.f);  // Mover a la izquierda
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    player.move(5.f, 0.f);   // Mover a la derecha
                }
            }
        }
    }
};

int main() {
    Menu menu;
    menu.set_values();
    menu.run_menu();
    return 0;
}
