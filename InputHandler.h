#pragma once
#include "ICommand.h"

/// <summary>
/// InputHandleクラスの宣言
/// </summary>
class InputHandler
{
public:

	ICommand* HandleInput();

	void AssignMoveRIghtCommand2PressKeyD();
	void AssignMoveLeftCommand2PressKeyA();
	void AssignMoveUpCommand2PressKeyW();
	void AssignMoveDownCommand2PressKeyS();

private:

	ICommand* pressKeyD_;
	ICommand* pressKeyA_;
	ICommand* pressKeyW_;
	ICommand* pressKeyS_;
};

