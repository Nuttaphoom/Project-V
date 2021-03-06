#pragma once
#include "SpriteObject.h"
enum class StateMachine {
	IDLE,
	RUNNING,
	JUMPPING,
	HOPPING,
	MIDJUMP,
	FALLING,
	LANDING,
	ATTACKING,
	CHASING,
	HIDING,
	CLIMBING,
	CLIMBINGIDLE,
	CASTING,
	CLIFFEDGE,
	CLIFFEDGEDOWN,
	Die,
	BAT,
	TRANSFORM,
	AMULET,
	Dying,
};

class Entity : public SpriteObject
{
	protected:
		float HP;
		float MoveSpeed;
		glm::vec3 velocity; 
		glm::vec3 applyingVelocity; 
		enum StateMachine stateMachine ;
		int collisionNumber; //1 = TOP, 2 = BOTTOM , 3 = LEFT , 4 = RIGHT  

		/*Default Value that will be used when we respawn this obj*/ 
		glm::vec3 Default_pos; 
		float Default_HP;  
		float Default_MoveSpeed;
	public:
		bool OnGround = false;
		bool _inv = false;
		int _renderType = 1;
		//Will be changed when StateMachine is changed 
		glm::vec3 collisionSize;

		Entity(string fileName, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos,glm::vec3 Size, glm::vec3 collisionSize);
		Entity(unsigned int texture, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize);
		Entity(){}
		
		virtual bool Death();
		virtual void Render(glm::mat4 globalModelTransform);
		virtual int Collides(Entity e);
		virtual void Collides_W_Inv_Wall(int CollisionDetection, glm::vec3 ivbObj[4][2]);
 		virtual void InvincibleFrame(int deltatime);
		virtual void ChangeState(StateMachine nextState);
		virtual void Update(int deltatime);
		virtual void Translate(glm::vec3 moveDistance);
		virtual void TranslateVelocity(glm::vec3 velocity);

		virtual void OnDamaged(int damage); 
		virtual void Attack(Entity* target) ;
		virtual bool isDead();
		virtual glm::vec3 GetVelocity();
		virtual void RespawnThisObject(); 
		virtual void VelocityControl();
		virtual void ResetVelocity(); 
		virtual void Heal(int heal);

		virtual void Stop();

		virtual void SetHP(float data);
		virtual void SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame, bool loop = true);
		virtual void SetVelocity(glm::vec3 velocity);
		virtual void SetDirection(int x);
		virtual void SetRenderType(int x);

		virtual StateMachine  GetState();
		virtual float GetHP();
		virtual float GetMoveSpeed();
		virtual int GetDirection();

		bool isInv() { return _inv; }

};