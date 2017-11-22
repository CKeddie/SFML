#include "GUIButton.h"

GUIButton::GUIButton(const char* name, const char * text, sf::Font * font, sf::Sprite * buttonGraphic, sf::Color colour)
	: GUIControl(name, colour)
{
	_text = new sf::Text(text, *font);
	_sprite = buttonGraphic;
	_text->setOrigin(_sprite->getOrigin() - sf::Vector2f(50,3));
}

GUIButton::~GUIButton()
{
	GUIControl::~GUIControl();
}

void GUIButton::Update(float deltaTime)
{

}

void GUIButton::Draw(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(*_sprite);
	renderWindow->draw(*_text);
}

void GUIButton::HandleInput(InputHandler & input)
{
	sf::Vector2f position (input.MousePosition());
	if (_sprite->getLocalBounds().contains(position))
	{
		Notify(std::pair<int, std::string>(_command_id, _state_id));
	}
}

void GUIButton::SetupSubject(int cmd, std::string id)
{
	_command_id = cmd;
	_state_id = id;
}
