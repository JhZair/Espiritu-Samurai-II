#include "Menu.h"
#include <stdexcept>
#include <iostream>

// Constructor
Menu::Menu()
    : pos(0), pressed(false), theselect(false), state(GameState::MainMenu)
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
    window.create(sf::VideoMode(1920, 1080), "Menu Espíritu Samurai II",sf::Style::Fullscreen);
    window.setPosition(sf::Vector2i(0, 0));

    // Fuente
    if (!font.loadFromFile("../assets/fonts/upheavtt.ttf"))
        throw std::runtime_error("Error cargando la fuente");

     // Cargar imágenes del fondo animado
    for (int i = 1; i <= 100; ++i) {
        sf::Texture texture;
        std::string fileName = "../assets/images/Fondo_menu/img (" + std::to_string(i) + ").jpg";
        if (!texture.loadFromFile(fileName)) {
            std::cout << "Error cargando la imagen: " << fileName << std::endl;
            continue;
        }
        backgroundTextures.push_back(texture);
    }

    if (backgroundTextures.empty())
        throw std::runtime_error("No se pudieron cargar las texturas del fondo animado");

    // Configurar el primer frame
    bg.setTexture(backgroundTextures[0]);
    currentFrame = 0;

    //Titulo del juego
    
    titulotext.setFont(font);
    titulotext.setString("Espiritu Samurai II");
    titulotext.setCharacterSize(80);
    titulotext.setFillColor(sf::Color::White);
    
    // Centrar el título horizontalmente
    float titleX = (1920.f - titulotext.getLocalBounds().width) / 2;
    titulotext.setPosition(titleX, 200.f); // Posición vertical más arriba
    
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

   
    
}

// Mostrar ventana de controles
void Menu::showControls()
{
    if (!controlsWindow.isOpen())
    {
        controlsWindow.create(sf::VideoMode(1920, 1080), "Controles Espíritu Samurai II",sf::Style::Fullscreen);
        // Fondo de la ventana de controles
        if (!imagecontrolBackground.loadFromFile("../assets/images/controles.jpeg"))
            throw std::runtime_error("Error cargando la imagen de controles");

        controlsBackground.setTexture(imagecontrolBackground);

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

            if (event.type == sf::Event::KeyPressed)
            {
                    controlsWindow.close();
                    state = GameState::MainMenu;  // Volver al menú principal
            }
        }

        controlsWindow.clear();
        controlsWindow.draw(controlsBackground);
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
        if (animationClock.getElapsedTime().asMilliseconds() > 100) {
            currentFrame = (currentFrame + 1) % backgroundTextures.size(); // Ciclar frames
            bg.setTexture(backgroundTextures[currentFrame]); // Actualizar el fondo
            animationClock.restart();
        }
        window.clear();
        window.draw(bg);  // Fondo principal
        window.draw(titulotext);
        for (const auto& text : texts)
        {
            window.draw(text);
        }
        window.display();
    }
}

// Ejecuta el menú
void Menu::run_menu()
{
    bool isMenuMusicPlaying = false;
    while (window.isOpen()) // Mientras la ventana del menú esté abierta
    {
        if (!isMenuMusicPlaying)
        {
            SonidosM.PlayMenuSound(); // Reemplaza con tu método para reproducir música del menú
            isMenuMusicPlaying = true;
        }
        loop_events();
        draw_all();

        if (state == GameState::Controls)
        {
            showControls();
        }
        else if (state == GameState::Game || state == GameState::Exit)
        {
            SonidosM.PauseMenuSound();
            window.close(); // Cierra la ventana del menú
            break;
        }
    }
}
