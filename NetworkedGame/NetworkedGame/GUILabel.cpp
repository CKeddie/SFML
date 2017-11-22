#include "GUILabel.h"

GUILabel::GUILabel(const char * name, const char * text, sf::Font * font, sf::Color colour)
	: GUIControl(name, colour)
	, sf::Text(text, *font)
{
	_visible = true;
	_enabled = false;
}

GUILabel::~GUILabel()
{
}

void GUILabel::Update(float)
{
}

void GUILabel::Draw(sf::RenderWindow * renderWindow)
{	
	renderWindow->draw(*this);
}

void GUILabel::HandleInput(InputHandler & input)
{
}
