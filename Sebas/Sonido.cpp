#include "Sonido.h"

Sounds::Sounds(){
	music.openFromFile("../assets/audios/Y2meta.app - BATTLE AGAINST A TRUE SAMURAI (128 kbps)(pelea).ogg");
	music.setLoop(true);
	music.setVolume(5);
	
	PlayMenu.openFromFile("../assets/audios/ASGORE THE SHOGUN OF THE MOUNTAIN(interfaz).ogg");
	PlayMenu.setLoop(true);
	PlayMenu.setVolume(5);
	
}
void Sounds::PlayMusic() {
    music.play();
}

void Sounds::PauseMusic() {
    music.pause();
}

void Sounds::PlayMenuSound() { // Implementación de la función renombrada
    PlayMenu.play();
}
void Sounds::PauseMenuSound()
{
    PlayMenu.pause();
}
