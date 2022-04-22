#include "Player.h"
#include "CheckPoint.h"
#include "GameEngine.h"
#include "InvisibleObject.h"
#include "GameStateController.h"
#include "Level.h"
#include "EntityData.h"
#include "AnimatorManager.h"
#include "HandleKey.h"
#include <ostream>

#define ENTITYLIST GameStateController::GetInstance()->currentLevel->GetEntityList()
 
Player* Player::instance = nullptr; 

void Player::HandleMouse(glm::vec3 mouseRealPos) {
	if (IsPause())
		return;

	for (int i = 0 ; i < ENTITYLIST.size() ; i++) {
		if (Enemy* eptr = dynamic_cast<Enemy*>(ENTITYLIST[i])) {
			if (eptr->GetState() != StateMachine::Die && !  eptr->IsPause()) {    Attack(eptr); }
		}
	};
}

void Player::HandleKey(char Key)
{
	if (IsPause())
		return;

	class HandleKey k;
	k.KeyDetect(Key);
}

Player::Player(string fileName, int row, int column, glm::vec3 Pos,glm::vec3 Size) : Entity(fileName, row, column, _hp, _moveSpeed, Pos,Size)
{	
	this->collisionSize = glm::vec3(76, -128, 1);

	stateMachine = StateMachine::FALLING;
	EntityData ED;
	ED.Read();
	_moveSpeed = ED.GetPlayerMoveSpeed();
	_jump = ED.GetPlayerJumpHeight();
	_hp = 3 ;

	Default_HP = _hp;
	Default_MoveSpeed = _moveSpeed;
	Default_pos = Pos;

	CheckPoint::GetInstance()->SetCheckPoint(Default_pos);
	SetHP(_hp);


	 
}

void Player::Update(int deltatime)
{
	if (IsPause())
		return;

	Entity::Update(deltatime);

	UpdateStateMachine(deltatime);
	UpdateCollision();
	if (GetState() == StateMachine::CLIMBING)
		UpdateClimbing();
}

void Player::UpdateStateMachine(float deltatime)
{
 	if (GetState() == StateMachine::RUNNING)
	{
		//cout << "RUNNING" << endl; 
		if (GetVelocity().x < 1 && GetVelocity().x > -1 && OnGround == true)
		{
			ChangeState(StateMachine::IDLE);
		}

	}
	if (GetState() == StateMachine::LANDING)
	{
		//cout << "LANDING" << endl;

		if (GetVelocity().x < 2 && GetVelocity().x > -2)
		{
			int deltatime = GameEngine::GetInstance()->GetDeltaTime();
			delay1 += deltatime;
			if (delay1 >= 200)
			{
				delay1 = 0;
				ChangeState(StateMachine::IDLE);
			}
		}
		else
		{
			ChangeState(StateMachine::RUNNING);
		}
	}
	if (GetState() == StateMachine::FALLING)
	{
		//cout << "FALLING" << endl;

		if (GetVelocity().y == 0 && OnGround == true)
		{
			ChangeState(StateMachine::LANDING);
		}
	}
	if (GetState() == StateMachine::IDLE || GetState() == StateMachine::FALLING || GetState() == StateMachine::HIDING)
	{
 
		if (GetVelocity().x >= 0.5f || GetVelocity().x <= -0.5f)
		{
			if (OnGround == true)
			{
				ChangeState(StateMachine::RUNNING);
			}
 		}
	}
	if (GetState() == StateMachine::IDLE || GetState() == StateMachine::RUNNING || GetState() == StateMachine::FALLING || GetState() == StateMachine::HIDING)
	{
		if (GetVelocity().y > 0)
		{
			ChangeState(StateMachine::JUMPPING);
		}
	}

	if (GetState() == StateMachine::IDLE || GetState() == StateMachine::RUNNING || GetState() == StateMachine::JUMPPING  )
	{
		if (GetVelocity().y < 0.01 && OnGround == false)
		{
			ChangeState(StateMachine::MIDJUMP);
		}
	}
	if (GetState() == StateMachine::MIDJUMP  )
	{
		//cout << "MIDJUMPING" << endl; 
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (delay > 1)
		{
			delay = 0;
			ChangeState(StateMachine::FALLING);
		}
	}

	if (GetState() == StateMachine::IDLE)
	{
		//cout << "IDLE" << endl;

	}

	if (GetState() == StateMachine::CLIFFEDGE)
	{
		//cout << "CLIFFEDGE" << endl;
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (delay > 400)
		{
			delay = 0;
			ChangeState(StateMachine::CLIFFEDGEDOWN);
		}
		TranslateVelocity(glm::vec3 (0, 24, 0));
	}

	if (GetState() == StateMachine::CLIFFEDGEDOWN)
	{
		//cout << "CLIFFEDGEDOWN" << endl;
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (OnGround != false && delay > 400)
		{
			delay = 0;
			ChangeState(StateMachine::IDLE);
		}
		if (GetDirection() == 1) {
			TranslateVelocity(glm::vec3(60, 0, 0));
		}
		if (GetDirection() == -1) {
			TranslateVelocity(glm::vec3(-60, 0, 0));
		}
	}

	if (GetState() == StateMachine::BAT)
	{
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (delay > 5000)
		{
			delay = 0;
			bat = false;
			ChangeState(StateMachine::FALLING);
		}
	}

	if (GetState() == StateMachine::TRANSFORM) {
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (delay > 700)
		{
			delay = 0;
			ChangeState(StateMachine::BAT);
		}
	}
}
 
void Player::UpdateCollision() {
	 
}

void Player::ChangeState(StateMachine NextState)
{
	if (NextState == stateMachine)
		return; 

	stateMachine = NextState;

	if (this->GetState() == StateMachine::IDLE)
	{
		SetAnimationLoop(0, 0, 1, 100);
	}
	else if (this->GetState() == StateMachine::RUNNING)
	{
		SetAnimationLoop(2, 0, 8, 100);
	}
	else if (this->GetState() == StateMachine::JUMPPING)
	{
		SetAnimationLoop(1, 4, 2, 300);
	}
	else if (this->GetState() == StateMachine::MIDJUMP)
	{
		SetAnimationLoop(1, 6, 1, 100);

	}
	else if (this->GetState() == StateMachine::FALLING)
	{
		SetAnimationLoop(1, 7, 1, 300);
	}
	else if (this->GetState() == StateMachine::LANDING)
	{
		SetAnimationLoop(1, 8, 2, 100);
	}
	else if (this->GetState() == StateMachine::CLIMBING)
	{
		SetAnimationLoop(3, 0, 8, 100);
		//if ()
	}
	else if (this->GetState() == StateMachine::CLIFFEDGE)
	{
		SetAnimationLoop(4, 0, 1, 100);
	}
	else if (this->GetState() == StateMachine::CLIFFEDGEDOWN)
	{
		SetAnimationLoop(4, 1, 1, 100);
	}
	else if (this->GetState() == StateMachine::TRANSFORM)
	{
		SetAnimationLoop(6, 0, 7, 100);
	}
	else if (this->GetState() == StateMachine::BAT)
	{
		SetAnimationLoop(7, 0, 6, 100);
	}
}

 

Player* Player::GetInstance() {
	if (instance == nullptr) {
		while (instance == nullptr) {
			cout << "ERROR -- Player Instance is called before init" << endl; 
			cout << "See more at Player.cpp -- " << endl; 
		}
	}
	return instance;
}

Player* Player::GetInstance(string fileName, int row, int column, float HP,glm::vec3 Pos,glm::vec3 Size) 
{
	instance = new Player(fileName, row, column, Pos,Size);
	CheckPoint::GetInstance()->LoadCheckPoint();
	return instance;

}
 
void Player::OnDamaged(int damage) {
	if (IsPause())
		true; 

	this->HP -= damage;
	notify(0); //Notify HP Observer 

	if (this->HP <= 0) {
		notify(1);  //Notify Dead Observer , In Respawner.h
	}
}

void Player::Attack(Entity* target) {


	InvisibleObject invWALLs[2] ;
	 
	for (int i = 0; i < 2; i++) {
		invWALLs[i].SetPosition(glm::vec3(this->GetPos().x + (64 * this->DirectionSet * i), this->GetPos().y + this->GetSize().y * -1 / 2, 1));
		invWALLs[i].SetSize(64, 64);
	}
	if (target->DirectionSet == this->DirectionSet) {
		for (int i = 0; i < 2; i++) {
			if (invWALLs[i].Collide_W_Entity(*target)) {
 				target->OnDamaged(999999);

			}
		}
	}
}

void Player::RespawnThisObject() {
	HP = Default_HP;
	MoveSpeed = Default_MoveSpeed;
	CheckPoint::GetInstance()->LoadCheckPoint();
}

void Player::AddDetectingEntity(Entity* ePtr) {
	for (int i = 0; i < detectingEntity.size(); i++) {
		if (ePtr == detectingEntity[i]) {
			return; 
		}
	} 	
	this->detectingEntity.push_back(ePtr);
}

void Player::RemoveDetectingEntity(Entity* ePtr) {
	for (int i = 0; i < detectingEntity.size() ; i++) {
		if (ePtr == detectingEntity[i]) {
			detectingEntity.erase(detectingEntity.begin() + i);
		}
	}
}

bool Player::isSeen() {
	if (detectingEntity.size() > 0)
		return true;
	else
		return false;
}

float Player::GetClimbSpeed()
{
	return _climbSpeed;
}

void Player::SetClimbing()
{
	int l = GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size();
	for (int k = 0; k < l; k++){
		if (abs(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k)->GetPos().x - GetPos().x) < 72.0f &&
			abs(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k)->GetPos().y - GetPos().y) < 32.0f)
		{
			//cout << "climb" << endl;
			ChangeState(StateMachine::CLIMBING);
		}
		 
		
	}
}

void Player::UpdateClimbing()
{
	if (GetState() == StateMachine::CLIMBING)
	{
		int l = GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size();
		for (int k = 0; k < l; k++) {
			if (abs(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k)->GetPos().x - GetPos().x) < 75.0f &&
				abs(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k)->GetPos().y - GetPos().y) < 106.0f &&
				GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k)->GetPos().y > GetPos().y) {
				//cout << "Climb" << endl;
				break;
			}
			else if (k == l - 1) {
				ChangeState(StateMachine::CLIFFEDGE);
			}
		}
	}
}

void Player::SetBat() {
	if (GetState() == StateMachine::IDLE ||
		GetState() == StateMachine::RUNNING ||
		GetState() == StateMachine::JUMPPING ||
		GetState() == StateMachine::MIDJUMP ||
		GetState() == StateMachine::CLIMBING ||
		GetState() == StateMachine::FALLING ||
		GetState() == StateMachine::LANDING) {
		if (bat == true)
			ChangeState(StateMachine::TRANSFORM);
	}
}

float Player::GetJump() {
	return _jump;
}

float Player::GetMoveSpeed() {
	return _moveSpeed;
}

void Player::BatChange(bool x) {
	bat = x;
}



 