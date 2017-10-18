#pragma once

#include "SFML\Window\Joystick.hpp"
#include "SFML\Window\Event.hpp"
#include "SFML\Window.hpp"
#include "SFML\Window\Keyboard.hpp"
#include <array>
class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void HandleEvents(sf::Event e);
	void Update();
	bool IsKeyUp(sf::Keyboard::Key);
	bool IsKeyDown(sf::Keyboard::Key);
	bool IsKeyPressed(sf::Keyboard::Key);
	bool IsKeyReleased(sf::Keyboard::Key);
private:
	std::array<bool, sf::Keyboard::KeyCount> _keystate;
	std::array<bool, sf::Keyboard::KeyCount> old_keystate;
};

