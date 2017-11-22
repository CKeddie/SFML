#pragma once
#include "GUIControl.h"
class GUILabel 
	: public GUIControl
	, public sf::Text
{
public:
	GUILabel(const char * name, const char * text, sf::Font * font, sf::Color colour);
	~GUILabel();
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
	void HandleInput(InputHandler & input) override;
};

