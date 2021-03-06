#include "Level_Menu.h" 

#include "Level.h"
#include "TileMap.h"
#include "Audio.h"
#include "GameStateController.h"

static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;



void Level_Menu::LevelLoad()
{
 
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Level_1.2/Middle_Mapdata.txt");
	if (mapFile.is_open()) {
		mapFile >> MapHeight;
		mapFile >> MapWidth;
		sMiddleMapdata = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sMiddleMapdata[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
				mapFile >> sMiddleMapdata[y][x];
			}
		}
		mapFile.close();
	}


	ifstream FrontMapFile("../Resource/Map/Level_1.2/Front_Mapdata.txt");
	if (FrontMapFile.is_open()) {
		FrontMapFile >> MapHeight;
		FrontMapFile >> MapWidth;
		sFrontMapData = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sFrontMapData[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
				FrontMapFile >> sFrontMapData[y][x];
			}
		}
		FrontMapFile.close();
	}

	ifstream cMapFile("../Resource/Map/Level_1.2/Col_Mapdata.txt");
	if (cMapFile.is_open()) {
		cMapFile >> MapHeight;
		cMapFile >> MapWidth;
		sColMapdata = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sColMapdata[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
				cMapFile >> sColMapdata[y][x];
			}
		}
		cMapFile.close();
	}

	ifstream BackGroundMapFile("../Resource/Map/Level_1.2/Background_Mapdata.txt");
	if (BackGroundMapFile.is_open()) {
		BackGroundMapFile >> MapHeight;
		BackGroundMapFile >> MapWidth;
		sBackGroundMapData = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sBackGroundMapData[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
				BackGroundMapFile >> sBackGroundMapData[y][x];
			}
		}
		BackGroundMapFile.close();
	}
}

void Level_Menu::LevelInit()
{
	
	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite.png", 5, 10, 3, glm::vec3(7000, -1176.0f, 0.0f), glm::vec3(1, -1, 0), false, false);
	obj->SetAnimationLoop(0, 0, 4, 100);
	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;
	obj->SetPause(true);

	GUI* background = new GUI("../Resource/Texture/Button/Background.png", 1, 1, glm::vec3(0, 0, 0), glm::vec3(GameEngine::GetInstance()->GetWindowWidth(), -GameEngine::GetInstance()->GetWindowHeight(), 1));
	objectsList.push_back(background);

	GUI* Sangeimage = new GUI("../Resource/Texture/GUI/Sangeideal.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth()/2 - 350, -50, 0), glm::vec3(-300, -600, 1));
	objectsList.push_back(Sangeimage);

	MenuHolder* mainMenuHolder = new MenuHolder("MainMenu");
	SDL_Color SDL_WhiteColor = SDL_Color(); 
	SDL_WhiteColor.r = 255; SDL_WhiteColor.g = 255 ; SDL_WhiteColor.b = 255 ; 

	GUI* SangeLogo = new GUI("../Resource/Texture/GUI/SangeName_LOGO.png", 1, 1, glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 4, 528 / 5 + 528 / 4, 0), glm::vec3(1149/3, -372/2, 1));
	objectsList.push_back(SangeLogo);
	mainMenuHolder->addButton(SangeLogo);

	Button* m1 = new Button(ButtonName::START_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 4 , 528 / 5 - 50, 0), glm::vec3(1920 / 8, 528 /4* -1, 1),"Play",SDL_WhiteColor,40);
	mainMenuHolder->addButton(m1);
	objectsList.push_back(m1);
	GUIObjectsList.push_back(m1);

	Button* m3 = new Button(ButtonName::SETTING_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 4 , 528 / 5 - 528 / 3 - 30, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1), "Option", SDL_WhiteColor, 30);
	mainMenuHolder->addButton(m3);
	objectsList.push_back(m3);
	GUIObjectsList.push_back(m3);

	Button* m2 = new Button(ButtonName::EXIT_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 4 , 528 / 5 - 528 / 3 - 528 / 3, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1),"Exit", SDL_WhiteColor,30);
	mainMenuHolder->addButton(m2);
	objectsList.push_back(m2);
	GUIObjectsList.push_back(m2);

	MenuHolder* optionHolder = new MenuHolder("Option");

	Button* s1masterup = new Button(ButtonName::MASTER_SOUND_VOLUME_UP, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 450, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1), ">", SDL_WhiteColor, 20);
	optionHolder->addButton(s1masterup);
	objectsList.push_back(s1masterup);
	GUIObjectsList.push_back(s1masterup);

	Button* s1masterdown = new Button(ButtonName::MASTER_SOUND_VOLUME_DOWN, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 800, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1), "<", SDL_WhiteColor, 20);
	optionHolder->addButton(s1masterdown);
	objectsList.push_back(s1masterdown);
	GUIObjectsList.push_back(s1masterdown);

	Button* s2musicup = new Button(ButtonName::MUSIC_SOUND_VOLUME_UP, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 450, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1), ">", SDL_WhiteColor, 20);
	optionHolder->addButton(s2musicup);
	objectsList.push_back(s2musicup);
	GUIObjectsList.push_back(s2musicup);

	Button* s2musicrdown = new Button(ButtonName::MUSIC_SOUND_VOLUME_DOWN, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 800, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1), "<", SDL_WhiteColor, 20);
	optionHolder->addButton(s2musicrdown);
	objectsList.push_back(s2musicrdown);
	GUIObjectsList.push_back(s2musicrdown);

	Button* closeOption = new Button(ButtonName::CLOSE_OPTION_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight() / 2 - 650, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1), "Close", SDL_WhiteColor, 20);
	optionHolder->addButton(closeOption);
	objectsList.push_back(closeOption);
	GUIObjectsList.push_back(closeOption);
	
	
	TextObject* masterText = new TextObject() ;
	masterText->LoadText("Master Audio : ", SDL_WhiteColor, 30);
	masterText->SetPosition(glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 1100, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0));
 	objectsList.push_back(masterText);
	GUIObjectsList.push_back(masterText);
	optionHolder->addButton(masterText);

	TextObject* musicText = new TextObject();
	musicText->LoadText("Music Audio : ", SDL_WhiteColor, 30);
	musicText->SetPosition(glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 1100, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0));
	objectsList.push_back(musicText);
	GUIObjectsList.push_back(musicText);
	optionHolder->addButton(musicText);

 

	TextObject* masterSoundVal = new TextObject(); 
	masterSoundVal->LoadText("5", SDL_WhiteColor, 30);
	masterSoundVal->SetPosition(glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 625, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0));
	objectsList.push_back(masterSoundVal);
	optionHolder->addButton(masterSoundVal);
	soundScalerText[0] = masterSoundVal;

	TextObject* musicSoundVal = new TextObject();
	musicSoundVal->LoadText("5", SDL_WhiteColor, 30);
	musicSoundVal->SetPosition(glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 625, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0));
	objectsList.push_back(musicSoundVal);
	optionHolder->addButton(musicSoundVal);
	soundScalerText[1] = musicSoundVal;

	optionHolder->disableButton();

	_menuHolderList.push_back(mainMenuHolder);
	_menuHolderList.push_back(optionHolder);
#pragma endregion

#pragma  Manager
	AnimatorManager* animatorManager = AnimatorManager::GetInstance();
	managersList.push_back(animatorManager);
	objectsList.push_back(animatorManager);

#pragma endregion  

#pragma Sound
	SoundPlayer::GetInstance()->ClearSound();
	SoundPlayer::GetInstance()->PlayMusic("../Resource/Sound/BGM/MainMenuOST.mp3");


#pragma endregion 
}

void Level_Menu::LevelUpdate()
{
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();
	//Camera Controller Behavior
	cameraController->Update();

	/// Collision Check 
	



	//Update InteractableObject 
	interactableObjectManager->Update(deltaTime);

	// Update Game Objs
	for (DrawableObject* obj : EntityObjectsList) {
		//Play Update In every game object 
		if (Entity* eptr = dynamic_cast<Entity*>(obj))
			if (eptr->isDead())
				continue;
		obj->Update(deltaTime);
	}

	//Update Manager 
	for (Manager* m : managersList) {
		m->Update(deltaTime);
	}

}

void Level_Menu::LevelDraw()
{

	GameEngine::GetInstance()->Render(objectsList);
}

void Level_Menu::LevelFree()
{
	/*for (int i = objectsList.size() - 1; i >= 0 ; i--) {
		delete objectsList[i];
	}*/

	//delete player;
	//delete cameraController;
	//delete tilemaps;
	//delete checkPoint;
}

void Level_Menu::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
}

void Level_Menu::HandleKey(char key)
{
	player->HandleKey(key);

	switch (key)
	{
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
	case 'e': player->HandleKey(key); break;
	case 'p': CheckPoint::GetInstance()->LoadCheckPoint(); break;
	case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL2; break;
	case 'f': break;
	case 't': break;
	case 'h': break;
	case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
	case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	case '1': player->HandleKey(key); break;
	case '2': player->HandleKey(key); break;


	}

	interactableObjectManager->HandleKey(key);
}

void Level_Menu::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;
	glm::vec3 mouseVec3;
	// Calculate Real X Y 
	Level_Menu::WorldToCam(realX, realY);
	mouseVec3 = glm::vec3(realX, realY, 1);

	//Player HandleMouse 
	this->player->HandleMouse(mouseVec3);
	//Detecting Button 
	for (int i = 0; i < objectsList.size(); i++) {
		if (Button* bptr = dynamic_cast<Button*>(objectsList[i])) {
			bptr->OnClick(mouseVec3);
		}
	}

	//move object to current position with respect to Camera position 
	/*glm::vec3 MoveObjectToMuseVec3 = (glm::vec3(realX, realY, 0));
	MoveObjectToMuseVec3.x /= Camera::GetInstance()->GetZoomOffset();
	MoveObjectToMuseVec3.y /= Camera::GetInstance()->GetZoomOffset();

	MoveObjectToMuseVec3 += Camera::GetInstance()->GetCamOffset();

	player->SetPosition(MoveObjectToMuseVec3);*/
}

void Level_Menu::WorldToCam(float& realX, float& realY) {
	int x, y;
	x = realX; y = realY;

	realX = (x - GameEngine::GetInstance()->GetWindowWidth() / 2);
	realY = (y - GameEngine::GetInstance()->GetWindowHeight() / 2);
	realX = (realX / GameEngine::GetInstance()->GetWindowWidth());
	realY = (realY / GameEngine::GetInstance()->GetWindowHeight());
	realX = (realX * 1280.0f);
	realY = (realY * 720.0f) * -1;


}