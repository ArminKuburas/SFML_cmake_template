#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	fs::path exePath = fs::canonical(argv[0]).parent_path();
	fs::path soundPath = exePath / "resources/sounds/178172__deitzis__deitzis.ogg";

    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);

	sf::SoundBuffer buffer;
	sf::Music music;
	if (buffer.loadFromFile(soundPath.string()))
	{
		std::cout << "Sound loaded successfully" << std::endl;
		sf::Sound sound;
		sound.setBuffer(buffer);
		sound.play();
	}

	if (music.openFromFile(soundPath.string()))
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
