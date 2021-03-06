#include "Trap.h" 
#include "Player.h"

int CollideWithInsideCollision(InteractableObject* in,Entity* e) {
	int CollideDetection = 0; //Check where it collide with Entity (In Entity POV) 
						  // 1 FOR TOP, 2 FOR BOTTOM, 4 FOR LEFT, AND 8 FOR RIGHT 

	if (e->GetPos().x - in->GetPos().x > 2000 || e->GetPos().x - in->GetPos().x < -2000)
		return 0;

	float LeftX_Inv_Obj = (float)in->GetPos().x - in->ColliderSize.x / 2;
	float RightX_Inv_Obj = (float)in->GetPos().x + in->ColliderSize.x / 2;

	float TOPY_Inv_Obj = (float)in->GetPos().y + in->ColliderSize.y / 2;
	float BOTTOMY_Inv_Obj = (float)in->GetPos().y - in->ColliderSize.y / 2;

	float TOP_BOTTOM_X = (float)e->GetPos().x - e->GetSize().x / 4;
	float TOP_Y = (float)e->GetPos().y + e->GetSize().y / 2 * -1;

	float Middle_1_2_X = (float)e->GetPos().x - e->GetSize().x / 2;
	float Middle_1_Y = (float)e->GetPos().y + e->GetSize().y * -1 / 4;

	float Middle_2_Y = (float)e->GetPos().y - e->GetSize().y * -1 / 4;

	float BOTTOM_Y = (float)e->GetPos().y - 1 - e->GetSize().y * -1 / 2;

	//TOP 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e->GetSize().x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e->GetSize().x / 2 > LeftX_Inv_Obj)) {
		if (TOP_Y > TOPY_Inv_Obj && TOP_Y < BOTTOMY_Inv_Obj) {
			CollideDetection += 1;
		}
	}

	//MIDDLE_LEFT
	if ((Middle_1_2_X < RightX_Inv_Obj && Middle_1_2_X > LeftX_Inv_Obj)) {
		if ((Middle_1_Y > TOPY_Inv_Obj && Middle_1_Y < BOTTOMY_Inv_Obj) ||
			(Middle_2_Y > TOPY_Inv_Obj && Middle_2_Y < BOTTOMY_Inv_Obj)) {
			CollideDetection += 4;
		}
	}

	//MIDDLE_RIGHT
	Middle_1_2_X += e->GetSize().x;
	if ((Middle_1_2_X < RightX_Inv_Obj)) {
		if ((Middle_1_Y > TOPY_Inv_Obj && Middle_1_Y < BOTTOMY_Inv_Obj) ||
			(Middle_2_Y > TOPY_Inv_Obj && Middle_2_Y < BOTTOMY_Inv_Obj)) {
			CollideDetection += 8;
		}
	}

	//TOP 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X   > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e->GetSize().x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e->GetSize().x / 2 > LeftX_Inv_Obj)) {
		if (BOTTOM_Y > TOPY_Inv_Obj && BOTTOM_Y < BOTTOMY_Inv_Obj) {
			CollideDetection += 2;
		}
	}

	return CollideDetection;
}


Trap::Trap(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize) : InteractableObject(fileName, row, column, Pos, Size, collisionSize) {

}
void Trap::getTrap() {
	 
}
void Trap::Called() {
	if (refused)
		return;
	//Creating trap mini game
	if (_crossMiniGamePtr == nullptr)
		_crossMiniGamePtr = new CrossMiniGame("../Resource/Texture/Interactable/MiniGameBoarder.png", 1, 1, glm::vec3(0, -200, 0), glm::vec3(256, 128, 1), 100, 0);
 
 
}

void Trap::Update(int deltaTime) {
	InteractableObject::Update(deltaTime); 

	if (refused)
		return; 

	if (_crossMiniGamePtr != nullptr) {
		if (_crossMiniGamePtr->IsDone()) {
			refused = true;
			delete _crossMiniGamePtr;
			_crossMiniGamePtr = nullptr;
		}
		else {
			_crossMiniGamePtr->Update(deltaTime);
		}
	}

	Player* player = Player::GetInstance();
	glm::vec3 insideColliderSize = glm::vec3( 0 , ColliderSize.y, 1);
	float offsetX = 30 + 26 + 128 / 8 ;
	InteractableObject* testObj = new InteractableObject(InteractableObject::InteractableObject("../Resource/Texture/Interactable/Cross.png", 0, 0, glm::vec3(GetPos().x + offsetX, GetPos().y, GetPos().z), GetSize() , glm::vec3(128 / 4 - 30,-128, 1)));
	
	if (testObj->InCollideRadius(testObj, player) > 0    ) {
 
		coolDown = 3; 
		refused = true; 
		player->OnDamaged(10);
	} 

	delete testObj;
}
 
void Trap::HandleKey(char key) {
	if (key == 'e') {
		if (_crossMiniGamePtr != nullptr) {
			_crossMiniGamePtr->HandleKey(key);
		}
	}
	else if (key == 'a' || key == 's' || key == 'd' || key == 'w') {
		if (_crossMiniGamePtr != nullptr) {
			delete _crossMiniGamePtr;
			_crossMiniGamePtr = nullptr; 
		}
	}
}
void Trap::Render(glm::mat4 globalModelTransform) {
	SpriteObject::Render(globalModelTransform); 
	if (_crossMiniGamePtr != nullptr) 
		_crossMiniGamePtr->Render(globalModelTransform);
}
 
void Trap::RespawnThisObject() {
	refused = false ;
	delete _crossMiniGamePtr;
	_crossMiniGamePtr = nullptr;
}

 