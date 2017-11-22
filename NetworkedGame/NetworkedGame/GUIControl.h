#pragma once

#include "SFML\Graphics.hpp"
#include "ISubject.h"

class InputHandler;

class GUIControl
{
public:
	GUIControl(const char * name, sf::Color colour);
	virtual ~GUIControl() = default;
	virtual void Update(float) = 0;
	virtual void Draw(sf::RenderWindow*) = 0;
	virtual void HandleInput(InputHandler & inputHandler) = 0;
	bool TabStop() { return _tabstop; };
	bool Enabled() { return _enabled; };
	bool Visible() { return _visible; };
	bool Focused() { return _focus; };
	void SetTabStop(bool state) { _tabstop = state; };
	void SetEnabled(bool state) { _enabled = state; };
	void SetVisible(bool state) { _visible = state; };
	void SetFocus(bool state) { _focus = state; };
protected:
	std::string _name;
	sf::Color _colour;
	bool _enabled = true;
	bool _tabstop = true;
	bool _visible = true;
	bool _focus = true;
};

