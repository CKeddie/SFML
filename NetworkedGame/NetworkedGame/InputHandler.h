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
	sf::Vector2i MousePosition();
	bool IsMouseButtonPressed(sf::Mouse::Button button);
	bool IsMouseButtonReleased(sf::Mouse::Button button);
	bool IsMouseButtonUp(sf::Mouse::Button button);
	bool IsMouseButtonDown(sf::Mouse::Button button);
private:
	std::array<bool, sf::Keyboard::KeyCount> _keystate;
	std::array<bool, sf::Mouse::ButtonCount> _mousestate;
	std::array<bool, sf::Keyboard::KeyCount> old_keystate;
	std::array<bool, sf::Mouse::ButtonCount> old_mousestate;
};

