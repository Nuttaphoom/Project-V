#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GameObject.h"
#include "GameData.h"
#include "ImageObject.h"
#include "SpriteObject.h"
#include "Button.h" 
#include "InvisibleObject.h" 
#include "Player.h" 
#include "CameraController.h"
#include "InteractableObjectManager.h"
 #include "HPBar.h"
#include "CheckPoint.h"
#include "Raycast.h"
#include "Decon.h"
#include <fstream>
#include "ReSpawner.h"
#include "Bishop.h"
#include "Priest.h"
#include "Pope.h" 
#include "AnimatorManager.h"
#include "MenuHolder.h"
#include "Gate.h"
#include "ToxicGas.h"

class Level
{
protected:
	vector<DrawableObject*> objectsList;
	vector< DrawableObject*> invisibleObjectsList;
	vector < DrawableObject*> EntityObjectsList;
	vector <DrawableObject*>   GUIObjectsList;
	vector <Manager*> managersList;
	Player* player;
	vector<MenuHolder*> _menuHolderList;

	CameraController* cameraController;

	InteractableObjectManager* interactableObjectManager = new InteractableObjectManager() ;
 
	int MapHeight;
	int MapWidth;
	int** sMiddleMapdata;
	int** sColMapdata;
	int** sFrontMapData;
	int** sBackGroundMapData;
	ReSpawner* respawner; 

	bool isPause ; 
public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate();
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);

	void WorldToCam(float& x, float& y);
	#pragma region adder
	virtual void AddObjectList(DrawableObject* obj) { objectsList.push_back(obj);  } 
	virtual void AddEntityObject(DrawableObject* obj) { EntityObjectsList.push_back(obj);  }
	virtual void AddGUIObject(DrawableObject* obj) { GUIObjectsList.push_back(obj); } 
	virtual void AddMenuHolder(MenuHolder* menuholder) { _menuHolderList.push_back(menuholder); }
	#pragma endregion 

	#pragma region getter 
	virtual vector<DrawableObject*> GetInvisibleWallList() { return this->invisibleObjectsList; }
	virtual vector<DrawableObject*> GetEntityList() { return this->EntityObjectsList; }
	virtual vector<DrawableObject*> GetGUIObjectsList() { return this->GUIObjectsList; }
	virtual InteractableObjectManager* GetInteractableObjectManager() { return this->interactableObjectManager ;  }
	virtual ReSpawner* GetRespawner(){ return this->respawner; }
	vector<MenuHolder*> GetMenuHolder() { return this->_menuHolderList; }
	#pragma endregion 

	virtual void SetPause(bool b) {
		isPause = b; 
	}
};
