#include "Level2.h" 

#include "Level.h"
#include "TileMap.h"
#include "Audio.h"
#include "GameStateController.h"

static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;



void Level2::LevelLoad()
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

void Level2::LevelInit()
{
#pragma region tilemapss
	TileMap* tilemaps = new TileMap(MapHeight, MapWidth, sFrontMapData, sMiddleMapdata, sBackGroundMapData, sColMapdata, "../Resource/Texture/SpriteSheet/Map Asset/Level1.2 SpriteSheet.png", 33, 40);
	for (int i = 0; i < tilemaps->GetTiles().size(); i++) {
		for (int j = 0; j < tilemaps->GetTiles()[i].size(); j++) {
			objectsList.push_back(tilemaps->GetTiles()[i][j]);
		}
	}

	for (int i = 0; i < tilemaps->GetColTiles().size(); i++) {
		invisibleObjectsList.push_back(tilemaps->GetColTiles()[i]);
		objectsList.push_back(tilemaps->GetColTiles()[i]);
	}

#pragma endregion 

#pragma region interactableObject 
	Hiding* hiding = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(591.0f, -1152.0f - 18, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding);
	objectsList.push_back(hiding);

	Hiding* hiding2 = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(2618.21, -1152.0f - 18, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding2);
	objectsList.push_back(hiding2);


	Hiding* hiding4 = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(7209.93f, -1152.0f - 18, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding4);
	objectsList.push_back(hiding4);

	Hiding* hiding5 = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(7518.9f, -1152.0f - 18, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding5);
	objectsList.push_back(hiding5);

	Hiding* hiding6 = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(7841.48f, -1152.0f - 18, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding6);
	objectsList.push_back(hiding6);

	Hiding* hiding7 = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(8165.86f-64, -1152.0f - 18, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding7);
	objectsList.push_back(hiding7);

	Hiding* hiding8 = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(8472.94f, -1152.0f - 18, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding8);
	objectsList.push_back(hiding8);

	Hiding* hiding9 = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(8783.97f, -1152.0f - 18, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding9);
	objectsList.push_back(hiding9);


	Flower* flower_1 = new Flower("../Resource/Texture/Interactable/Flower.png", 1, 1, glm::vec3(3173.71, -1152 - 32, 0.0f), glm::vec3(64, -64, 1), glm::vec3(128, -128, 1));
	interactableObjectManager->addInteractableObjects(flower_1);
	objectsList.push_back(flower_1);

	Flower* flower_2 = new Flower("../Resource/Texture/Interactable/Flower.png", 1, 1, glm::vec3(6898.54, -1152 - 32, 0.0f), glm::vec3(64, -64, 1), glm::vec3(128, -128, 1));
	interactableObjectManager->addInteractableObjects(flower_2);
	objectsList.push_back(flower_2);

	Gate* gate_1 = new Gate(GameState::GS_LEVEL3, "../Resource/Texture/Interactable/Gate.png", 1, 1, glm::vec3(9680, -1176 + 65 - 60 + 64, 0.0f), glm::vec3(64 * 3.5f, -64 * 3.5f, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(gate_1);
	objectsList.push_back(gate_1);

	Trap* trap_1 = new Trap("../Resource/Texture/Interactable/Cross.png", 1, 1, glm::vec3(8296.67+16, -1152 + 20, 0.0f), glm::vec3(128, -168, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(trap_1);
	objectsList.push_back(trap_1);
	 
 
#pragma endregion 


#pragma region Entities 
	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite.png", 10, 16, 3, glm::vec3(164 , -1152.0f + 64, 0.0f), glm::vec3(128, -128, 0), false, false);
	obj->SetAnimationLoop(0, 0, 4, 100);
	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;

	Bishop* _bishopTest = new Bishop("../Resource/Texture/Enemy/Bishop/Bishop Sprite Sheet.png", 2, 9, glm::vec3(9005, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	_bishopTest->SetAnimationLoop(0, 0, 12, 100);
	_bishopTest->AddPatrolPos(glm::vec3(9005, -1152.0f, 0.0f));
	_bishopTest->AddPatrolPos(glm::vec3(9000, -1152.0f, 0.0f));

	EntityObjectsList.push_back(_bishopTest);
	objectsList.push_back(_bishopTest);

	Decon* d1 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(1094.37, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d1->AddPatrolPos(glm::vec3(501.42, -1152, 0.0f));
	d1->AddPatrolPos(glm::vec3(1094.37, -1152, 0.0f));
	d1->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d1);
	objectsList.push_back(d1);

	Decon* d2 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(1214.61, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d2->AddPatrolPos(glm::vec3(1214.61, -1152, 0.0f));
	d2->AddPatrolPos(glm::vec3(1718.16, -1152, 0.0f));
	d2->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d2);
	objectsList.push_back(d2);

	Decon* d3 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(2978.93, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d3->AddPatrolPos(glm::vec3(2451.01, -1152, 0.0f));
	d3->AddPatrolPos(glm::vec3(2978.93, -1152, 0.0f));
	d3->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d3);
	objectsList.push_back(d3);

	Decon* d4 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(4210, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d4->AddPatrolPos(glm::vec3(4210, -1152, 0.0f));
	d4->AddPatrolPos(glm::vec3(4210 + 64 *4, -1152, 0.0f));
	d4->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d4);
	objectsList.push_back(d4);

 

	Decon* d6 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(5877.93, -1152 + 64 , 0.0f), glm::vec3(128, -128, 1));
	d6->AddPatrolPos(glm::vec3(5877.93, -1152, 0.0f));
	d6->AddPatrolPos(glm::vec3(5877.93 + 64 * 3, -1152, 0.0f));
	d6->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d6);
	objectsList.push_back(d6);
 

	Decon* d8 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(7708.78, -1152 + 64 , 0.0f), glm::vec3(128, -128, 1));
	d8->AddPatrolPos(glm::vec3(7209.93, -1152, 0.0f));
	d8->AddPatrolPos(glm::vec3(8165.86, -1152, 0.0f));
	d8->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d8);
	objectsList.push_back(d8);


	
	 
#pragma endregion
	respawner = new ReSpawner();

#pragma region GUI 
	GUI* SangeImage = new GUI("../Resource/Texture/GUI/Sange.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));

	objectsList.push_back(SangeImage);
	GUIObjectsList.push_back(SangeImage);

	GUI* TakeDownIcon = new GUI("../Resource/Texture/GUI/AttackIcon.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, -GameEngine::GetInstance()->GetWindowHeight() / 2 + 64 + 16, 0), glm::vec3(128, -128, 1));
	objectsList.push_back(TakeDownIcon);
	GUIObjectsList.push_back(TakeDownIcon);

	HPBar* hpbar = new HPBar("../Resource/Texture/GUI/HPPoint.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 180, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));

	objectsList.push_back(hpbar);

	GUIObjectsList.push_back(hpbar);
	SDL_Color whilteColor;
	whilteColor.r = 255; whilteColor.g = 255; whilteColor.b = 255;
	MenuHolder* pauseMenuHolder = new MenuHolder("PauseMenu");
	Button* b1 = new Button(ButtonName::CONTINUE_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1), "Continue", whilteColor, 25);
	pauseMenuHolder->addButton(b1);
	objectsList.push_back(b1);
	GUIObjectsList.push_back(b1);

	Button* b2 = new Button(ButtonName::EXIT_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight() / 2 - 500, 0), glm::vec3(1920 / 10, 528 / 5 * -1, 1), "Exit", whilteColor, 25);
	pauseMenuHolder->addButton(b2);
	objectsList.push_back(b2);
	GUIObjectsList.push_back(b2);
	pauseMenuHolder->disableButton();

	_menuHolderList.push_back(pauseMenuHolder);
	#pragma endregion

	#pragma  Manager
	AnimatorManager* animatorManager = AnimatorManager::GetInstance();
	managersList.push_back(animatorManager);
	objectsList.push_back(animatorManager);

	#pragma endregion  

	SoundPlayer::GetInstance()->ClearSound();
	SoundPlayer::GetInstance()->PlayMusic("../Resource/Sound/BGM/Level2OST.mp3", 100);

}

void Level2::LevelUpdate()
{

	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();
	//Camera Controller Behavior
	cameraController->Update();

	/// Collision Check 
	for (DrawableObject* en : EntityObjectsList) {
		if (Entity* eptr = dynamic_cast<Entity*>(en)) {
			if (eptr->IsPause())
				continue;

			int CollideDetection = 0;
			glm::vec3 ivbobjs[4][2];
			for (DrawableObject* i : invisibleObjectsList) {
				if (InvisibleObject* Iptr = dynamic_cast<InvisibleObject*>(i)) {
					int p = Iptr->Collide_W_Entity(*eptr);
					if (p % 2 != 0) { //COLLIDE TOP
						if (CollideDetection % 2 == 0) {
							CollideDetection += 1;
							ivbobjs[0][0] = Iptr->GetPos();
							ivbobjs[0][1] = Iptr->GetSize();
						}
					}
					if ((p >> 1) % 2 != 0) { //COLLIDE BOTTOM
						if ((CollideDetection >> 1) % 2 == 0) {
							CollideDetection += 2;
							ivbobjs[1][0] = Iptr->GetPos();
							ivbobjs[1][1] = Iptr->GetSize();
						}
					}
					if ((p >> 2) % 2 != 0) { //COLLIDE LEFT
						if ((CollideDetection >> 2) % 2 == 0) {
							CollideDetection += 4;
							ivbobjs[2][0] = Iptr->GetPos();
							ivbobjs[2][1] = Iptr->GetSize();
						};
					}
					if ((p >> 3) % 2 != 0) { //COLLIDE RIGHT
						if ((CollideDetection >> 3) % 2 == 0) {
							CollideDetection += 8;
							ivbobjs[3][0] = Iptr->GetPos();
							ivbobjs[3][1] = Iptr->GetSize();
						}
					}
				}
				if (CollideDetection >= 8 + 4 + 2 + 1) break;
			}
			eptr->Collides_W_Inv_Wall(CollideDetection, ivbobjs);
		}

		if (Player* playerObj = dynamic_cast<Player*>(en)) {
			for (DrawableObject* nObj : objectsList) {
				if (Entity* eptr2 = dynamic_cast<Entity*>(nObj)) {
					if (playerObj != eptr2) {
						if (playerObj->Collides(*eptr2)) {
							playerObj->OnDamaged(999);
						}
					}
				}
			}
		}
	}



	if (isPause)
		return;

	//Update every objects 
	for (DrawableObject* obj : objectsList) {
		obj->Update(deltaTime);
	}

}

void Level2::LevelDraw()
{

	GameEngine::GetInstance()->Render(objectsList);
}

void Level2::LevelFree()
{
	/*for (int i = objectsList.size() - 1; i >= 0 ; i--) {
		delete objectsList[i];
	}*/

	//delete player;
	//delete cameraController;
	//delete tilemaps;
	//delete checkPoint;
}

void Level2::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
}

void Level2::HandleKey(char key)
{
	player->HandleKey(key);

	switch (key)
	{
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
	case 'e': player->HandleKey(key); break;
	case 'p': CheckPoint::GetInstance()->LoadCheckPoint(); break;
	case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL3; break;
	case 'f': break;
	case 't': break;
	case 'h': break;
	case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
	case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	case 'E': _menuHolderList[0]->enableButton(); GameStateController::GetInstance()->currentLevel->SetPause(true);  break;
	case '1': player->HandleKey(key); break;
	case '2': player->HandleKey(key); break;


	}

	interactableObjectManager->HandleKey(key);
}

void Level2::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;
	glm::vec3 mouseVec3;
	// Calculate Real X Y 
	Level2::WorldToCam(realX, realY);
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

void Level2::WorldToCam(float& realX, float& realY) {
	int x, y;
	x = realX; y = realY;

	realX = (x - GameEngine::GetInstance()->GetWindowWidth() / 2);
	realY = (y - GameEngine::GetInstance()->GetWindowHeight() / 2);
	realX = (realX / GameEngine::GetInstance()->GetWindowWidth());
	realY = (realY / GameEngine::GetInstance()->GetWindowHeight());
	realX = (realX * 1280.0f);
	realY = (realY * 720.0f) * -1;


}