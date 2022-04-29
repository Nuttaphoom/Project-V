#pragma once

#include "Entity.h"
#include "Subject.h"
#include "Observer.h"
#include "Skill.cpp"


class Player : public Entity, public Subject
{
	private :
		static Player* instance;
		vector<Entity*> detectingEntity ;  
		int delay = 0;
		int delay1 = 0;
		float _climbSpeed = 500.0f;
		float _jump;
		float _moveSpeed;
		float _hp;
		bool bat = false;
		bool _skill1 = false;
		bool _skill2 = false;
	public :
		Player(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, bool _res1, bool _res2);
 		void Update(int deltatime);
		void UpdateStateMachine(float deltatime);
		void UpdateCollision(); 
  		void ChangeState(StateMachine NextState);
 		void HandleKey(char key);
		void HandleMouse(glm::vec3 mouseRealPos); 
		void SetClimbing();
		float GetClimbSpeed();
		void UpdateClimbing();
		void UpdateInv();
		void SetBat();
		void SetInv();
		float GetJump();
		float GetMoveSpeed();
		void BatChange(bool);
		void InvChange(bool);

		void AddDetectingEntity(Entity* entity); 
		void RemoveDetectingEntity(Entity* entity);
		bool isSeen(); 
		
		virtual void Attack(Entity* target);
		virtual void RespawnThisObject();  

	 
		static Player* GetInstance();
		static Player* GetInstance(string fileName, int row, int column, float HP, glm::vec3 Pos, glm::vec3 Size, bool _res1, bool _res2);

		void OnDamaged(int damage);
 };




 