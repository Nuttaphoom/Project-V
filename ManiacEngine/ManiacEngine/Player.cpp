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
#include "SoundPlayer.h"
#define ENTITYLIST GameStateController::GetInstance()->currentLevel->GetEntityList()
 

void CreateDeadAnimation() {
	vector<SpriteObject*> playerOnly;
	Player* p = Player::GetInstance();
	playerOnly.push_back(dynamic_cast<SpriteObject*>(p));
	AnimatorManager::GetInstance()->CreateAnimationFactory(playerOnly, p->GetPos(), p->GetSize(), 1800.0f / 1000.0f, "../Resource/Texture/Sange/SangeDeadSprite.png", 1, 18, 18, 100);
}


Player* Player::instance = nullptr; 

void Player::HandleMouse(glm::vec3 mouseRealPos) {
	if (IsPause())
		return;

	for (int i = 0 ; i < ENTITYLIST.size() ; i++) {
		if (Enemy* eptr = dynamic_cast<Enemy*>(ENTITYLIST[i])) {
			if (eptr->GetState() != StateMachine::Die &&  ! eptr->Death() ) {    Attack(eptr); }
		}
	};


}

void Player::HandleKey(char Key)
{
	if (IsPause() || GetState() == StateMachine::Die)
		return;

	if (Key == 'g') {
		for (int i = 0; i < ENTITYLIST.size(); i++) {
			if (Enemy* eptr = dynamic_cast<Enemy*>(ENTITYLIST[i])) {
				if (eptr->GetState() != StateMachine::Die && !eptr->Death()) { Attack(eptr); }
			}
		};
	}

	if (Key == 'i') {
		cout << "imortal actived" << endl; 
		immortal = true ; 
	}
 	class HandleKey k;
	k.KeyDetect(Key);
}

Player::Player(string fileName, int row, int column, glm::vec3 Pos,glm::vec3 Size, bool _res1, bool _res2) : Entity(fileName, row, column, _hp, _moveSpeed, Pos,Size,glm::vec3(64, -128, 0))
{	
	stateMachine = StateMachine::FALLING;
	EntityData ED;
	ED.Read();
	_moveSpeed = ED.GetPlayerMoveSpeed();
	_jump = ED.GetPlayerJumpHeight();
	_hp = 3 ;
	_skill1 = _res1;
	_skill2 = _res2;

	Default_HP = _hp;
	Default_MoveSpeed = _moveSpeed;
	Default_pos = Pos;

	CheckPoint::GetInstance()->SetCheckPoint(Default_pos);
	SetHP(_hp);
	notify(0);
}

void Player::Update(int deltatime)
{
 
	if (IsPause()) 
 		return;
	
	Entity::Update(deltatime);
 

	UpdateStateMachine(deltatime);
	UpdateInv();
	UpdateCollision();
	if (GetState() == StateMachine::CLIMBING || GetState() == StateMachine::CLIMBINGIDLE) {
		ClimbCheck();
		UpdateClimbing();
	}
}

void Player::UpdateStateMachine(float deltatime)
{
 	if (GetState() == StateMachine::RUNNING)
	{
		if (GetVelocity().x < 1 && GetVelocity().x > -1 && OnGround == true)
		{
			ChangeState(StateMachine::IDLE);
		}

	}
	if (GetState() == StateMachine::LANDING)
	{

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

	}

	if (GetState() == StateMachine::CLIFFEDGE)
	{
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += 1.0f / 1000.0f * deltatime;
		//cout << delay << endl;
		cout << loop << endl;
		if (delay > 0.1)
		{
			delay = 0;
			ChangeState(StateMachine::CLIFFEDGEDOWN);
		}
		if (loop < 1) {
			TranslateVelocity(glm::vec3(0, 600, 0));
			loop++;
		}
	}

	if (GetState() == StateMachine::CLIFFEDGEDOWN)
	{
		loop = 0;
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += 1.0f / 1000.0f * deltatime;
		if (OnGround == false) {
			TranslateVelocity(glm::vec3(0, -50, 0));
		}
		if (OnGround != false && delay > 0.1)
		{
			delay = 0;
			TranslateVelocity(glm::vec3(0, 50, 0));
			ChangeState(StateMachine::IDLE);
		}
		if (GetDirection() == 1) {
			TranslateVelocity(glm::vec3(150, 0, 0));
		}
		if (GetDirection() == -1) {
			TranslateVelocity(glm::vec3(-150, 0, 0));
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

	if (GetState() == StateMachine::CLIMBING) {
		if (GetVelocity().y == 0) {
			ChangeState(StateMachine::CLIMBINGIDLE);
		}
	}

	if (GetState() == StateMachine::CLIMBINGIDLE) {
		if (GetVelocity().y != 0) {
			ChangeState(StateMachine::CLIMBING);
		}
	}

	if (GetState() == StateMachine::AMULET) {
		float deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (delay > 1300) {
			delay = 0;
			ChangeState(StateMachine::IDLE);
		}
	}

	if (GetState() == StateMachine::Dying) {
		ResetVelocity();
		ChangeState(StateMachine::Die);

	}

	if (GetState() == StateMachine::JUMPPING) {
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (OnGround == true && delay > 100) {
			ChangeState(StateMachine::IDLE);
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
	delay = 0;
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
	else if (this->GetState() == StateMachine::CLIMBINGIDLE)
	{
		SetAnimationLoop(3, 1, 1, 100);
	}
	else if (this->GetState() == StateMachine::Dying) {
		SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/SangeDying.mp3");
		CreateDeadAnimation();
	} 
	else if (this->GetState() == StateMachine::AMULET) {
		SetAnimationLoop(8, 0, 7, 200);
	}
	else if (this->GetState() == StateMachine::Die) {
		SetPause(true);
		SetAnimationLoop(9, 12, 1, 100,false);
				notify(1);  //Notify Dead Observer , In Respawner.h

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

Player* Player::GetInstance(string fileName, int row, int column, float HP,glm::vec3 Pos,glm::vec3 Size, bool _res1, bool _res2) 
{
	instance = new Player(fileName, row, column, Pos,Size, _res1, _res2);
	CheckPoint::GetInstance()->LoadCheckPoint();
	return instance;

}
 
void Player::OnDamaged(int damage) {
	if (IsPause() || GetState() == StateMachine::ATTACKING || immortal)
		return ; 

	this->HP -= damage;
	notify(0); //Notify HP Observer 
		
	if (this->HP <= 0) {
		ChangeState(StateMachine::Dying); 
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
				ChangeState(StateMachine::ATTACKING);
  				target->OnDamaged(999999);
				Heal(1);
				SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/TakeDownStartTrigger.mp3");

			}
		}
	}
}

void Player::RespawnThisObject() {
	HP = Default_HP;
	MoveSpeed = Default_MoveSpeed;
	bat = false;
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
			InvisibleObject* o = dynamic_cast<InvisibleObject*>(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k));
			if (o != nullptr && o->IsClimbable()) {
				ChangeState(StateMachine::CLIMBING);
			}
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
				break;
			}
			else if (k == l - 1) {
				ChangeState(StateMachine::CLIFFEDGE);
			}
		}
	}
}        

void Player::SetBat() {
	if (_inv == false) {
		if (GetState() == StateMachine::IDLE ||
			GetState() == StateMachine::RUNNING ||
			GetState() == StateMachine::JUMPPING ||
			GetState() == StateMachine::MIDJUMP ||
			GetState() == StateMachine::CLIMBING ||
			GetState() == StateMachine::FALLING ||
			GetState() == StateMachine::LANDING) {
			if (bat == false && GetHP() > 1 && _skill1 != false) {
				bat == true;
				OnDamaged(1);
				ResetVelocity();
				ChangeState(StateMachine::TRANSFORM);
				SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/Skill_Metamorphosys.mp3");
			}
		}
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

void Player::InvChange(bool x) {
	_inv = x;
}

void Player::SetInv() {
	if (bat == false && OnGround && _inv == false && _skill2 && ! isSeen() )
	{
		if (GetState() == StateMachine::IDLE ||
			GetState() == StateMachine::RUNNING ||
			GetState() == StateMachine::LANDING) {
			if (GetHP() > 1) {
				ChangeState(StateMachine::AMULET);
				OnDamaged(1);
				InvChange(true);
				SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/Skill_Invisibility.mp3");


			}
		}
	}
}

void Player::UpdateInv() {
	if (_inv == true)
	{
		SetRenderType(2);
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (GetVelocity().x > 0 || GetVelocity().y > 0) {
			SetRenderType(1);
			InvChange(false);
		}
		if (delay > 3500)
		{
			delay1 += deltatime;
			if (delay1 >= 100) {
				if (loop == 0)
				{
					//cout << "here" << endl;
					SetRenderType(1);
					loop = 1;
					delay1 = 0;
				}
				else if (loop == 1)
				{
					//cout << "there" << endl;
					SetRenderType(2);
					loop = 0;
					delay1 = 0;
				}
			}
			if (delay > 5000)
			{
				delay = 0;
				loop = 0;
				SetRenderType(1);
				InvChange(false);
			}
		}
	}
}

bool Player::GetBlock() {
	return _block;
}

void Player::ClimbCheck() {
		int l = GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size();
		for (int k = 0; k < l; k++) {
			if (abs(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k)->GetPos().x - GetPos().x) < 30.0f &&
				abs(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k)->GetPos().y - GetPos().y) < 80.0f &&
				GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().at(k)->GetPos().y > GetPos().y) {
				TranslateVelocity(glm::vec3(0, -1 * GetClimbSpeed(), 0));
			}
		}
}



 