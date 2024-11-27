#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Sonido.h"
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

    

    // Constructor y Destructor
    Menu();
    ~Menu();

    // Métodos públicos
    void set_values();           
    void run_menu();             
    void loop_events();          
    void draw_all();             
    void showControls();         

    // Método de acceso para obtener el estado del juego o asignar un estado nuevo
    GameState get_state() const { return state; }
    GameState set_state(GameState nuevoEstado) { return state=nuevoEstado;}

private:
    // Miembros privados
    Sounds SonidosM;

    sf::RenderWindow window;                
    sf::RenderWindow controlsWindow;        
    sf::Font font;                          
    sf::Texture image;                      
    sf::Texture imagecontrolBackground;     
    sf::Sprite bg;                          
    sf::Sprite controlsBackground;      
    
        
    size_t currentFrame;
    sf::Clock animationClock;
    std::vector<sf::Texture> backgroundTextures;       

    sf::Text titulotext;
    std::vector<sf::Text> texts;            
    std::vector<std::string> options;       
    std::vector<sf::Vector2f> coords;       
    std::vector<int> sizes;                 
    int pos;                                
    bool pressed;                           
    bool theselect;                                                                    
             

    GameState state;
};

#endif
