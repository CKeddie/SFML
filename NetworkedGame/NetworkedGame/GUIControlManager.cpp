#include "GUIControlManager.h"
#include "GUIControl.h"
#include <iostream>

GUIControlManager::GUIControlManager(InputHandler & inputHandler)
	: _input_handler(inputHandler)
{

}

GUIControlManager::~GUIControlManager()
{

}

void GUIControlManager::Update(float deltaTime)
{
	for (auto & control : _controls)
	{
		if (control->Enabled())
		{
			control->Update(deltaTime);
		}
	}

	for (auto & control : _controls)
	{
		if (control->Focused())
		{
			control->HandleInput(_input_handler);
		}
	}

	if (!_accept_input) return;

	if (_input_handler.IsKeyPressed(sf::Keyboard::Up))
		PreviousControl();
	else if (_input_handler.IsKeyPressed(sf::Keyboard::Down))
		NextControl();
}

void GUIControlManager::Draw(sf::RenderWindow * renderWindow)
{
	for (auto & control : _controls)
	{
		if (control->Visible())
		{
			control->Draw(renderWindow);
		}
	}
}

void GUIControlManager::AddControl(GUIControl * control)
{
	//control->Attach(this);
	_controls.push_back(control);
}

void GUIControlManager::OnNotify(bool state)
{
}

void GUIControlManager::NextControl()
{
	if (_controls.size() == 0)
		return;

	int currentControl = _selected_control;

	//set focus to false
	_controls[_selected_control]->SetFocus(false);

	do
	{
		_selected_control++;
		if (_selected_control == _controls.size())
			_selected_control = 0;
		
		if (_controls[_selected_control]->TabStop() &&
			_controls[_selected_control]->Enabled())
		{
			OnNotify(new bool(true));
			break;
		}
	} while (currentControl != _selected_control);

	_controls[_selected_control]->SetFocus(true);
}

void GUIControlManager::PreviousControl()
{
	if (_controls.size() == 0)
		return;

	int currentControl = _selected_control;

	//set focus to false
	_controls[_selected_control]->SetFocus(false);

	do
	{
		_selected_control--;
		if (_selected_control == _controls.size())
			_selected_control = 0;

		if (_controls[_selected_control]->TabStop() &&
			_controls[_selected_control]->Enabled())
		{
			OnNotify(new bool(true));
			break;
		}
	} while (currentControl != _selected_control);

	_controls[_selected_control]->SetFocus(true);
}
