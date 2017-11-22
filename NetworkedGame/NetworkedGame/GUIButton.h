#pragma once
#include "GUIControl.h"
#include "InputHandler.h"

class GUIButton 
	: public GUIControl
	, public sf::Transformable
	, public ISubject<std::pair<int, std::string>>
{
public:
	GUIButton(const char * name, const char * text, sf::Font * font, sf::Sprite * buttonGraphic, sf::Color colour);
	~GUIButton();
	void Update(float)override;
	void Draw(sf::RenderWindow*)override;
	void HandleInput(InputHandler & input) override;
	void SetupSubject(int cmd, std::string id);
private:
	int _command_id = 0;
	std::string _state_id;
	sf::Text * _text;
	sf::Sprite * _sprite;
};

