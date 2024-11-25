#ifndef SONIDO_H
#define SONIDO_H


#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Sounds{
	private:
		Music music;
		Sound PlayMenu;
		SoundBuffer PlayMenuBuffer;
		
	public:
		Sounds();
		void PlayMusic();
		void PauseMusic();
		void PlayMenuSound();
        void PauseMenuSound();
		
};
#endif