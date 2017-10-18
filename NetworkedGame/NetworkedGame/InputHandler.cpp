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