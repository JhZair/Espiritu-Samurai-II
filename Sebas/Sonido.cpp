#include "Sonido.h"

Sounds::Sounds(){
	music.openFromFile("../assets/audios/ASGORE THE SHOGUN OF THE MOUNTAIN(interfaz).ogg");
	music.setLoop(true);
	music.setVolume(20);
	
	if(!PlayMenuBuffer.loadFromFile("../assets/audios/Y2meta.app - BATTLE AGAINST A TRUE SAMURAI (128 kbps)(pelea).ogg")){
		cout<<"Error al cargar sonido"<<endl;
	}
	PlayMenu.setBuffer(PlayMenuBuffer);
	
	
	
	
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
