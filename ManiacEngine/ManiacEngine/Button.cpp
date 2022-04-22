#include "Button.h"
#include "GameStateList.h"
#include "GameStateController.h" 

void NextLevelButton_Func();
void ContinueButton_Func();
void ExitButton_Func();
void RestartButton_Func();
void StartgameButton_Func();
void SettingButton_Func();

Button::Button(ButtonName buttonName, string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size ):GUI(fileName,row,column,Pos,Size)
{
	_textObject = new TextObject();
	this->buttonName = buttonName;


	buttonTypesFunc.push_back(NextLevelButton_Func);
	buttonTypesFunc.push_back(RestartButton_Func);
	buttonTypesFunc.push_back(StartgameButton_Func);

	buttonTypesFunc.push_back(ContinueButton_Func);
	cout << "BB1" << endl;


	buttonTypesFunc.push_back(ExitButton_Func);
	cout << "BB2" << endl;
	buttonTypesFunc.push_back(SettingButton_Func);
}

Button::Button(ButtonName buttonName, string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, string textString , SDL_Color textColor  , int frontSize ) :GUI(fileName, row, column, Pos, Size)
{

	_textObject = new TextObject();

	if (frontSize != 0) {
		_textObject->SetPosition(Pos);
		_textObject->LoadText(textString, textColor, frontSize);
	}

	this->buttonName = buttonName;

		buttonTypesFunc.push_back(NextLevelButton_Func);
		buttonTypesFunc.push_back(RestartButton_Func);
		buttonTypesFunc.push_back(StartgameButton_Func);

		buttonTypesFunc.push_back(ContinueButton_Func);
		cout << "BB1" << endl;
	 
	 
		buttonTypesFunc.push_back(ExitButton_Func);
		cout << "BB2" << endl;
		buttonTypesFunc.push_back(SettingButton_Func);
}

void Button::Render(glm::mat4 globalModelTransform) {
	GUI::Render(globalModelTransform); 
	if (_textObject != nullptr)
		_textObject->Render(globalModelTransform); 
}

bool Button::isClick(glm::vec3 CamSpace_MousePosition ) {
	bool CollideX;
	bool CollideY;
	CollideX = CamSpace_MousePosition.x <= GetPos().x + GetSize().x / 2 && CamSpace_MousePosition.x >= GetPos().x - GetSize().x / 2   ;
	CollideY = CamSpace_MousePosition.y <= GetPos().y + GetSize().y * -1 / 2 && CamSpace_MousePosition.y >= GetPos().y - GetSize().y * -1 / 2  	;

  	return CollideX && CollideY;

 }
void Button::OnClick(glm::vec3 CamSpace_MousePosition) {
	cout << "button on click" << endl; 
	if (IsPause())
		return;

	if (!isClick(CamSpace_MousePosition))
		return; 

	buttonTypesFunc[(int) this->buttonName](); 

}
 


void NextLevelButton_Func() {
	cout << "AAA" << endl; 
}
  
void ContinueButton_Func() {
	GameStateController::GetInstance()->currentLevel->SetPause(false); 
	GameStateController::GetInstance()->currentLevel->GetMenuHolder()[0]->disableButton();
}
 

void ExitButton_Func() {
	GameData::GetInstance()->gGameStateNext = GameState::GS_MAINMENU ;
}

void RestartButton_Func() {
	GameStateController::GetInstance()->currentLevel->GetRespawner()->ReSpawn(); 
}

void StartgameButton_Func() {
	GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL1 ;
}

void SettingButton_Func() {
	cout << "Option" << endl;
}

void Button::SetPause(bool b) {
	SpriteObject::SetPause(b); 
	if (_textObject != nullptr)
		_textObject->SetPause(b); 
}
