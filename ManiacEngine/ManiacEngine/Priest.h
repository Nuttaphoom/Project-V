 #pragma once 
#include "Enemy.h"


class Priest : public Enemy {
private:
	StateMachine _priestState;

	//counter ; 
	int attack_delay = 0;
	int chasing_delay = 0;
	int attack_cooldown_counter = 0;

public:
	Priest(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);

	virtual void Attack(Entity* target);
	virtual void EnterAttackZone(Entity* target);
	virtual void Update(int deltaTime);
	virtual void StartAttack();
	virtual void UpdateStateMachine(float deltatime);
	virtual void ChangeState(StateMachine nextState);
	virtual StateMachine GetState();
	virtual void AddPatrolPos(glm::vec3 pos);
	virtual void Patrol();
	virtual void  PlayerChase(Entity* p);
};

class PriestLightBall : public Entity {
private : 
	glm::vec3 _destination ;
	Entity* _followedTarget ;
	float _speed ;  
public :
	PriestLightBall(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 Destination  ); 
	virtual void Update(int deltaTime) ; 
};