#include "InputHandler.h"


InputHandler::InputHandler()
{
	old_keystate.fill(false);
	_keystate.fill(false);
}

InputHandler::~InputHandler()
{
	//delete old_event;
	//old_event = nullptr;
	//delete current_event;
	//current_event = nullptr;
}

void InputHandler::HandleEvents(sf::Event e)
{
	if ((e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) & e.type != -1)
		_keystate[e.key.code] = sf::Keyboard::isKeyPressed(e.key.code);

	if ((e.type == sf::Event::MouseButtonPressed || e.type == sf::Event::MouseButtonReleased)
	   & e.type != -1)
		_mousestate[e.mouseButton.button] = sf::Mouse::isButtonPressed(e.mouseButton.button);
}

void InputHandler::Update()
{
	old_keystate = _keystate;
}

bool InputHandler::IsKeyUp(sf::Keyboard::Key key)
{
	return !sf::Keyboard::isKeyPressed(key) && !old_keystate[key];
}

bool InputHandler::IsKeyDown(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key) && old_keystate[key];
}

bool InputHandler::IsKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key) && !old_keystate[key];
}

bool InputHandler::IsKeyReleased(sf::Keyboard::Key key)
{
	return !sf::Keyboard::isKeyPressed(key) && old_keystate[key];
}

sf::Vector2i InputHandler::MousePosition()
{
	return sf::Mouse::getPosition();
}

bool InputHandler::IsMouseButtonPressed(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button) && !old_mousestate[button];
}
bool InputHandler::IsMouseButtonReleased(sf::Mouse::Button button)
{
	return !sf::Mouse::isButtonPressed(button) && old_mousestate[button];
}

bool InputHandler::IsMouseButtonUp(sf::Mouse::Button button)
{
	return !sf::Mouse::isButtonPressed(button) && !old_mousestate[button];;
}

bool InputHandler::IsMouseButtonDown(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button) && old_mousestate[button];;
}
