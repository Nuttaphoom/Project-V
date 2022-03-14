#pragma once
#include "GUI.h"
#include <map>
typedef void (*FuncPtr_ButtonType)();

enum class ButtonName {
	NEXT_LEVEL_BUTTON = 0,
	RESTART_BUTTON = 1,
	START_GAME_BUTTON = 2,
	CONTINUE_GAME_BUTTON = 3,
	EXIT_GAME_BUTTON = 4,
	SETTING_GAME_BUTTON = 5,
	NONE_GAME_BUTTON = 6
};

 
class Button : public GUI {
private :
	map<string, bool> a;
	ButtonName buttonName ; 
	vector<FuncPtr_ButtonType> buttonTypesFunc; 
public : 
		Button(ButtonName buttonName, string fileName, int row, int column,glm::vec3 Pos, glm::vec3 Size);
		bool isClick(glm::vec3 CamSpace_MousePosition);
		void OnClick(glm::vec3 CamSpace_MousePosition); 
};
 