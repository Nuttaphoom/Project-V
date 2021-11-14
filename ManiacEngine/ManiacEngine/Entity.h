#pragma once
#include "SpriteObject.h"
 
class Entity : public SpriteObject
{
	protected:
		float HP;
		float MoveSpeed;
		glm::vec3 velocity; 
		glm::vec3 applyingVelocity; 
		float IFrame;
		int DirectionSet = 1;

	public:
		bool OnGround = false;

		Entity(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame);
		virtual bool Death();
		virtual int Collides(Entity e);
		virtual void Collides_W_Inv_Wall(int CollisionDetection, glm::vec3 ivbObj[4][2]);
		virtual void Render(glm::mat4 globalModelTransform);
		virtual void InvincibleFrame(int deltatime);
		virtual void Update(int deltatime);
		virtual void Translate(glm::vec3 moveDistance);
		virtual void TranslateVelocity(glm::vec3 velocity);
		virtual void SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame);
 		virtual float GetMoveSpeed();
		virtual void SetDirection(int x);
		virtual void OnDamaged(int damage); 
		virtual glm::vec3 GetVelocity();

		float GetHP(); 
};