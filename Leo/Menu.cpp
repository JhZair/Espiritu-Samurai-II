#include "Menu.h"
#include <stdexcept>

// Constructor
Menu::Menu()
    : pos(0), pressed(false), theselect(false), isPlaying(false), seleccionJugar(false), state(GameState::MainMenu)
{
    // Llamada a la función de inicialización
    set_values();
}

// Destructor
Menu::~Menu()
{
    // No es necesario liberar memoria explícitamente ya que SFML maneja la memoria internamente para los objetos de ventana y gráficos
}

// Inicializa los valores y objetos necesarios
void Menu::set_values()
{
    // Ventana principal
    window.create(sf::VideoMode(1920, 1080), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(0, 0));

    // Fuente
    if (!font.loadFromFile("../assets/fonts/upheavtt.ttf"))
        throw std::runtime_error("Error cargando la fuente");

    // Fondo del menú
    if (!image.loadFromFile("../assets/images/Fondo_menu/img (1).jpg"))
        throw std::runtime_error("Error cargando la imagen de fondo");
    bg.setTexture(image);

    // Opciones del menú
    options = {"Jugar", "Controles", "Salir"};
    coords = {{860.f, 350.f}, {860.f, 475.f}, {860.f, 600.f}};
    sizes = {45, 60, 50};

    for (size_t i = 0; i < options.size(); ++i)
    {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(sizes[i]);
        text.setOutlineColor(sf::Color::Black);
        text.setPosition(coords[i]);
        texts.push_back(text);
    }
    texts[0].setOutlineThickness(4); // Resaltar "Jugar" inicialmente

    // Botón de cerrar
    winclose.setSize(sf::Vector2f(23.f, 26.f));
    winclose.setPosition(1178.f, 39.f);
    winclose.setFillColor(sf::Color::Transparent);
}

// Mostrar ventana de controles
void Menu::showControls()
{
    if (!controlsWindow.isOpen())
    {
        controlsWindow.create(sf::VideoMode(1920, 1080), "Controles", sf::Style::Titlebar | sf::Style::Close);

        // Fondo de la ventana de controles
        if (!imagecontrolBackground.loadFromFile("../assets/images/controles.jpeg"))
            throw std::runtime_error("Error cargando la imagen de controles");

        controlsBackground.setTexture(imagecontrolBackground);

        // Botón de "Volver"
        backButton.setFont(font);
        backButton.setString("Volver");
        backButton.setCharacterSize(30);
        backButton.setPosition(350.f, 500.f);
        backButton.setOutlineColor(sf::Color::Black);
    }

    // Mostrar ventana de controles
    while (controlsWindow.isOpen())
    {
        sf::Event event;
        while (controlsWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                controlsWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Detectar clic en el botón "Volver"
                if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    controlsWindow.close();
                    state = GameState::MainMenu;  // Volver al menú principal
                }
            }
        }

        controlsWindow.clear();
        controlsWindow.draw(controlsBackground);
        controlsWindow.draw(backButton);
        controlsWindow.display();
    }
}

// Maneja los eventos del menú
void Menu::loop_events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        pos_mouse = sf::Mouse::getPosition(window);
        mouse_coord = window.mapPixelToCoords(pos_mouse);

        // Navegar con teclas de dirección
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed)
        {
            if (pos < texts.size() - 1)
            {
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed)
        {
            if (pos > 0)
            {
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);
            }
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pressed = false;
        }

        // Selección con Enter
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect)
        {
            theselect = true;
            if (pos == 0) // Jugar
            {
                state = GameState::Game;  // Cambiar estado a Juego
                window.close();  // Cerrar la ventana del menú
                break;
            }
            else if (pos == 1) // Controles
            {
                state = GameState::Controls;  // Cambiar estado a Controles
            }
            else if (pos == 2) // Salir
            {
                state = GameState::Exit;  // Cambiar estado a Salir
                window.close();  // Cerrar la ventana del menú
                break;
            }
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            theselect = false;
        }
    }
}

// Dibuja todos los elementos del menú
void Menu::draw_all()
{
    if (window.isOpen())
    {
        window.clear();
        window.draw(bg);  // Fondo principal
        for (const auto& text : texts)
        {
            window.draw(text);
        }
        window.display();
    }
}

void Menu::run_menu()
{
    while (window.isOpen()) // Mientras la ventana del menú esté abierta
    {
        loop_events();
        draw_all();

        if (state == GameState::Controls)
        {
            showControls();
        }
        else if (state == GameState::Game || state == GameState::Exit)
        {
            window.close(); // Cierra la ventana del menú
            break;
        }
    }
}

