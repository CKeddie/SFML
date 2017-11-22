#pragma once

#include "SFML\Graphics.hpp"
#include "IObserver.h"
#include "InputHandler.h"

class GUIControl;

class GUIControlManager
	: public IObserver<bool>
{
public:
	GUIControlManager(InputHandler & inputHandler);
	~GUIControlManager();
	void Update(float);
	void Draw(sf::RenderWindow*);
	void AddControl(GUIControl*);
	void OnNotify(bool) override;
private:
	void NextControl();
	void PreviousControl();
private:
	int _selected_control = 0;
	bool _accept_input = true;
	std::vector<GUIControl*> _controls;
	InputHandler & _input_handler;
};

