#pragma once
#include "Entity.h"
#include <vector>

 

class Enemy : public Entity
{
	protected:
 	vector <glm::vec3> PatrolPos;
 	int CurrentPatrolPos = 0;

	public:
	Enemy(string fileName, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos, glm::vec3 Size);
 	void Update(int deltatime);
	void AddPatrolPos(glm::vec3 pos);
	bool virtual PlayerDetect(Entity* p);

	void virtual UpdateStateMachine(float deltatime) = 0 ;
	void virtual PlayerChase(Entity* p) = 0;
	void virtual Patrol() = 0;
	void virtual Attack(Entity* target) = 0;
	void virtual ChangeState(StateMachine NextState) = 0 ;


};