#include "Level4.h" 

#include "Level.h"
#include "TileMap.h"
#include "Audio.h"
#include "GameStateController.h"

static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;



void Level4::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Level_3.1/Middle_Mapdata.txt");
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


	ifstream FrontMapFile("../Resource/Map/Level_3.1/Front_Mapdata.txt");
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

	ifstream cMapFile("../Resource/Map/Level_3.1/Col_Mapdata.txt");
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

	ifstream BackGroundMapFile("../Resource/Map/Level_3.1/Background_Mapdata.txt");
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

void Level4::LevelInit()
{
	AudioEngine audio;
	audio.init();

	SoundEffect sound1 = audio.loadSoundEffect("../Resource/Sound/Sword_Draw.mp3");
	//sound1.play();

#pragma region tilemapss
	TileMap* tilemaps = new TileMap(MapHeight, MapWidth, sFrontMapData, sMiddleMapdata, sBackGroundMapData, sColMapdata, "../Resource/Texture/SpriteSheet/Map Asset/Level3.1 SpriteSheet.png", 15, 23);

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
	Flower * flower_1 = new Flower("../Resource/Texture/Interactable/Flower.png", 1, 1, glm::vec3(4205.96, -1152 - 32, 0.0f), glm::vec3(64, -64, 1), glm::vec3(128, -128, 1));
	interactableObjectManager->addInteractableObjects(flower_1);
	objectsList.push_back(flower_1);

	Hiding* hiding1 = new Hiding("../Resource/Texture/Interactable/Closet.png", 1, 1, glm::vec3(2320.64, -900.7  + 64, 0.0f), glm::vec3(128, -256, 1), glm::vec3(128, -256, 1));
	interactableObjectManager->addInteractableObjects(hiding1);
	objectsList.push_back(hiding1);

	Hiding* hiding2 = new Hiding("../Resource/Texture/Interactable/Closet.png", 1, 1, glm::vec3(4494.55, -1152  + 64, 0.0f), glm::vec3(128, -256, 1), glm::vec3(128, -256, 1));
	interactableObjectManager->addInteractableObjects(hiding2);
	objectsList.push_back(hiding2);

	Hiding* hiding3 = new Hiding("../Resource/Texture/Interactable/Closet.png", 1, 1, glm::vec3(6447.64, -774 + 64, 0.0f), glm::vec3(128, -256, 1), glm::vec3(128, -256, 1));
	interactableObjectManager->addInteractableObjects(hiding3);
	objectsList.push_back(hiding3);

	Hiding* hiding4 = new Hiding("../Resource/Texture/Interactable/Closet.png", 1, 1, glm::vec3(7378.39, -774  + 64, 0.0f), glm::vec3(128, -256, 1), glm::vec3(128, -256, 1));
	interactableObjectManager->addInteractableObjects(hiding4);
	objectsList.push_back(hiding4);

	Hiding* hiding5 = new Hiding("../Resource/Texture/Interactable/Closet.png", 1, 1, glm::vec3(8162.69, -1152  + 64, 0.0f), glm::vec3(128, -256, 1), glm::vec3(128, -256, 1));
	interactableObjectManager->addInteractableObjects(hiding5);
	objectsList.push_back(hiding5);

	Hiding* hiding6 = new Hiding("../Resource/Texture/Interactable/Closet.png", 1, 1, glm::vec3(9185.27, -1152  + 64, 0.0f), glm::vec3(128, -256, 1), glm::vec3(128, -256, 1));
	interactableObjectManager->addInteractableObjects(hiding6);
	objectsList.push_back(hiding6);

	ToxicGas* toxicGas1 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1005.63, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas1);
	objectsList.push_back(toxicGas1);

	ToxicGas* toxicGas2 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1136.17, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas2);
	objectsList.push_back(toxicGas2);

	ToxicGas* toxicGas3 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1258.43, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas3);
	objectsList.push_back(toxicGas3);

	ToxicGas* toxicGas4 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1379.71, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas4);
	objectsList.push_back(toxicGas4);

	ToxicGas* toxicGas5 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1498.48, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas5);
	objectsList.push_back(toxicGas5);

	ToxicGas* toxicGas6 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1890.74, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas6);
	objectsList.push_back(toxicGas6);

	ToxicGas* toxicGas7 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(2013.75, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas7);
	objectsList.push_back(toxicGas7);

	ToxicGas* toxicGas8 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(2637.85, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas8);
	objectsList.push_back(toxicGas8);

	ToxicGas* toxicGas9 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(2770.11, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas9);
	objectsList.push_back(toxicGas9);

	ToxicGas* toxicGas10 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5345.98, -837, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas10);
	objectsList.push_back(toxicGas10);

	ToxicGas* toxicGas11 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5464.31, -837, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas11);
	objectsList.push_back(toxicGas11);

	ToxicGas* toxicGas12 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5665.13, -837, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas12);
	objectsList.push_back(toxicGas12);

	ToxicGas* toxicGas13 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5785.4, -837, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas13);
	objectsList.push_back(toxicGas13);

	ToxicGas* toxicGas14 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5040.43, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas14);
	objectsList.push_back(toxicGas14);

	ToxicGas* toxicGas15 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5164.47, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas15);
	objectsList.push_back(toxicGas15);

	ToxicGas* toxicGas16 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5417.03, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas16);
	objectsList.push_back(toxicGas16);

	ToxicGas* toxicGas17 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5536.04, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas17);
	objectsList.push_back(toxicGas17);

	ToxicGas* toxicGas18 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5793.58, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas18);
	objectsList.push_back(toxicGas18);

	ToxicGas* toxicGas19 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5912.34, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas19);
	objectsList.push_back(toxicGas19);

	ToxicGas* toxicGas20 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(6615.39, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas20);
	objectsList.push_back(toxicGas20);

	ToxicGas* toxicGas21 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(6741.42, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas21);
	objectsList.push_back(toxicGas21);

	Gate* gate = new Gate(GameState::GS_CUTSCENES2,"../Resource/Texture/Interactable/BabyBed.png", 1, 1, glm::vec3(9918.51     * 5, -778.524f + 5, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, -128, 1));
	interactableObjectManager->addInteractableObjects(gate);
	objectsList.push_back(gate);

#pragma endregion 


#pragma region Entities 
	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite.png", 10, 16, 3, glm::vec3(574.999 - 64 * 4, -1176.0f + 64, 0.0f), glm::vec3(128, -128, 0), true, true);
	obj->SetAnimationLoop(0, 0, 4, 100);
	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;
	/*
	Decon* d1 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(574.999, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d1->SetDirection(1);
	EntityObjectsList.push_back(d1);
	objectsList.push_back(d1);*/

	Priest* p1 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(802.578, -837.6 + 64, 0.0f), glm::vec3(128, -128, 1));
	p1->AddPatrolPos(glm::vec3(712.545, -837.6, 0.0f));
	p1->AddPatrolPos(glm::vec3(924.84, -837.6, 0.0f));
	EntityObjectsList.push_back(p1);
	objectsList.push_back(p1);

	Decon* d2 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(1639.7, -837.55 + 64, 0.0f), glm::vec3(128, -128, 1));
	d2->AddPatrolPos(glm::vec3(1639.7, -837.55, 0.0f));
	d2->AddPatrolPos(glm::vec3(1780.97, -837.55, 0.0f));
	EntityObjectsList.push_back(d2);
	objectsList.push_back(d2);

	Priest* p2 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(2312.47, -459 + 64, 0.0f), glm::vec3(128, -128, 1));
	p2->AddPatrolPos(glm::vec3(2296.7, -459, 0.0f));
	p2->AddPatrolPos(glm::vec3(2353.99, -459, 0.0f));
	EntityObjectsList.push_back(p2);
	objectsList.push_back(p2);

	Decon* d3 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(2108.99, -900 + 64, 0.0f), glm::vec3(128, -128, 1));
	d3->AddPatrolPos(glm::vec3(2108.99, -900, 0.0f));
	d3->AddPatrolPos(glm::vec3(2268.51, -900, 0.0f));
	EntityObjectsList.push_back(d3);
	objectsList.push_back(d3);

	Decon* d4 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(2547.88, -900 + 64, 0.0f), glm::vec3(128, -128, 1));
	d4->AddPatrolPos(glm::vec3(2547.88, -900, 0.0f));
	d4->AddPatrolPos(glm::vec3(2304.51, -900, 0.0f));
	EntityObjectsList.push_back(d4);
	objectsList.push_back(d4);

	Decon* d5 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(2910.83, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d5->AddPatrolPos(glm::vec3(2910.83, -1152, 0.0f));
	d5->AddPatrolPos(glm::vec3(3068.15, -1152, 0.0f));
	EntityObjectsList.push_back(d5);
	objectsList.push_back(d5);

	Decon* d6 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(3386.86, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d6->AddPatrolPos(glm::vec3(3262.06, -1152, 0.0f));
	d6->AddPatrolPos(glm::vec3(3548.34, -1152, 0.0f));
	EntityObjectsList.push_back(d6);
	objectsList.push_back(d6);

	Decon* d7 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(3722.84, -774.55 + 64, 0.0f), glm::vec3(128, -128, 1));
	d7->AddPatrolPos(glm::vec3(3722.84, -774.55, 0.0f));
	d7->AddPatrolPos(glm::vec3(3853.13, -774.55, 0.0f));
	EntityObjectsList.push_back(d7);
	objectsList.push_back(d7);

	Decon* d9 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(5606.49, -837 + 64, 0.0f), glm::vec3(128, -128, 1));
	EntityObjectsList.push_back(d9);
	objectsList.push_back(d9);

	/*Priest* p5 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(6163.74, -837 + 64, 0.0f), glm::vec3(128, -128, 1));
	p5->SetDirection(-1);
	EntityObjectsList.push_back(p5);
	objectsList.push_back(p5);*/

	Priest* p6 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(6857.56, -774 + 64, 0.0f), glm::vec3(128, -128, 1));
	EntityObjectsList.push_back(p6);
	objectsList.push_back(p6);
	p6->SetDirection(-1);


	/*Decon* d10 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(6522.81, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d10->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d10);
	objectsList.push_back(d10);

	Decon* d11 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(7518.79, -774.6 + 64, 0.0f), glm::vec3(128, -128, 1));
	d11->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d11);
	objectsList.push_back(d11);*/

	Priest* p7 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(7735.59, -585.6 + 64, 0.0f), glm::vec3(128, -128, 1));
	EntityObjectsList.push_back(p7);
	objectsList.push_back(p7);

	Priest* p8 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(8430.65, -837 + 64, 0.0f), glm::vec3(128, -128, 1));
	EntityObjectsList.push_back(p8);
	objectsList.push_back(p8);

	Priest* p9 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(9187.31, -774 + 64, 0.0f), glm::vec3(128, -128, 1));
	EntityObjectsList.push_back(p9);
	objectsList.push_back(p9);

	Decon* d12 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(9701.04, -1152 + 64, 0.0f), glm::vec3(128, -128, 1));
	d12->AddPatrolPos(glm::vec3(9701.04, -1152, 0.0f));
	d12->AddPatrolPos(glm::vec3(9284.45, -1152, 0.0f));
	EntityObjectsList.push_back(d12);
	objectsList.push_back(d12);

	Pope* popeTest = new Pope("../Resource/Texture/Enemy/Pope/Pope_SpriteSheet.png", 1, 4, glm::vec3(9918.51+128, -778.524f + 64, 0.0f), glm::vec3(128, -128, 1));
	EntityObjectsList.push_back(popeTest);
	objectsList.push_back(popeTest);

#pragma endregion
	respawner = new ReSpawner();


#pragma region GUI 
	GUI* SangeImage = new GUI("../Resource/Texture/GUI/Sange.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));

	objectsList.push_back(SangeImage);
	GUIObjectsList.push_back(SangeImage);


	GUI* TakeDownIcon = new GUI("../Resource/Texture/GUI/AttackIcon.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, -GameEngine::GetInstance()->GetWindowHeight() / 2 + 64 + 16, 0), glm::vec3(128, -128, 1));
	objectsList.push_back(TakeDownIcon);
	GUIObjectsList.push_back(TakeDownIcon);

	GUI* BatIcon = new GUI("../Resource/Texture/GUI/BatIcon.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90 + 128, -GameEngine::GetInstance()->GetWindowHeight() / 2 + 64 + 16, 0), glm::vec3(128, -128, 1));
	objectsList.push_back(BatIcon);
	GUIObjectsList.push_back(BatIcon);

	GUI* InviSkillIcon = new GUI("../Resource/Texture/GUI/InviSkillIcon.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90 + 128 + 128, -GameEngine::GetInstance()->GetWindowHeight() / 2 + 64 + 16, 0), glm::vec3(128, -128, 1));
	objectsList.push_back(InviSkillIcon);
	GUIObjectsList.push_back(InviSkillIcon);

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

#pragma Sound
	SoundPlayer::GetInstance()->ClearSound();
	SoundPlayer::GetInstance()->PlayMusic("../Resource/Sound/BGM/Level4OST.mp3");
#pragma endregion 




}

void Level4::LevelUpdate()
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

void Level4::LevelDraw()
{

	GameEngine::GetInstance()->Render(objectsList);
}

void Level4::LevelFree()
{
	/*for (int i = objectsList.size() - 1; i >= 0 ; i--) {
		delete objectsList[i];
	}*/

	//delete player;
	//delete cameraController;
	//delete tilemaps;
	//delete checkPoint;
}

void Level4::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
}

void Level4::HandleKey(char key)
{
	player->HandleKey(key);

	switch (key)
	{
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
	case 'e': player->HandleKey(key); break;
	case 'p': CheckPoint::GetInstance()->LoadCheckPoint(); break;
	case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_CUTSCENES2; break;
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

void Level4::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;
	glm::vec3 mouseVec3;
	// Calculate Real X Y 
	Level4::WorldToCam(realX, realY);
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

void Level4::WorldToCam(float& realX, float& realY) {
	int x, y;
	x = realX; y = realY;

	realX = (x - GameEngine::GetInstance()->GetWindowWidth() / 2);
	realY = (y - GameEngine::GetInstance()->GetWindowHeight() / 2);
	realX = (realX / GameEngine::GetInstance()->GetWindowWidth());
	realY = (realY / GameEngine::GetInstance()->GetWindowHeight());
	realX = (realX * 1280.0f);
	realY = (realY * 720.0f) * -1;


}