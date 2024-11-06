#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);

	sf::SoundBuffer buffer;
	sf::Music music;
	if (buffer.loadFromFile("/home/akuburas/personal_stuff/SFML_cmake_template/sounds/761401__wkalmar__distant-transmission.wav"))
	{
		std::cout << "Sound loaded successfully" << std::endl;
		sf::Sound sound;
		sound.setBuffer(buffer);
		sound.play();
	}

	if (music.openFromFile("/home/akuburas/personal_stuff/SFML_cmake_template/sounds/761401__wkalmar__distant-transmission.wav"))
	{
		std::cout << "Music loaded successfully" << std::endl;
		music.play();
	}

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
