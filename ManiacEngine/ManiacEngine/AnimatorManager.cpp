#include "AnimatorManager.h"

AnimatorManager* AnimatorManager::instance = nullptr;

void AnimatorManager::HandleKey(char key) {

}

 AnimatorManager* AnimatorManager::GetInstance() {
	if (instance == nullptr) {
		instance = new AnimatorManager();
	}
	return instance;
}


AnimatorManager::AnimatorManager() :Manager("TEST", 0, 0, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)) {
	textures[ETextureName::DeconDeadAnimationTexture] = GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/Enemy/Decon/Decon_Dead_SpriteSheet.png");
	textures[ETextureName::BishopThunder] = GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/VisualEffect/Thunder.png");
	textures[ETextureName:: PriestDeadAnimationTexture] = GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/Enemy/Priest/Priest_Dead_SpriteSheet.png");
	textures[ETextureName::BishopDeadAnimationTexture] = GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/Enemy/Bishop/Bishop_Dead_SpriteSheet.png");
	textures[ETextureName::PopeDeadAnimationTexture] = GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/Enemy/Pope/Pope_Dead_SpriteSheet.png");
}

//Responsible to "hide" (not replace) object(s) and spawn animationObj in their position with some given adjustment 
void AnimatorManager::CreateAnimationFactory(vector<SpriteObject*> objToHide, glm::vec3 pos, glm::vec3 size, float _lifespan, string fileName,
	int row, int column, int howManyFrame, int delayBetaweenFrame, ETextureName texture)   {
 	AnimatorObj* anim = new AnimatorObj();
	anim->lifespan = _lifespan;

	unsigned int tex = textures[texture] ;

 	anim->AnimationObject = new SpriteObject(tex, row, column, pos, size);
	anim->AnimationObject->SetAnimationLoop(0, 0, howManyFrame, delayBetaweenFrame, true);

	for (SpriteObject* s : objToHide) {
		anim->PausedObj.push_back(s);
		s->SetPause(true);
	}

	spriteObjectDict.push_back(anim);


	return;
}

void AnimatorManager::CreateAnimationFactory(vector<SpriteObject*> objToHide, glm::vec3 pos, glm::vec3 size, float _lifespan, string fileName,
	int row, int column, int howManyFrame, int delayBetaweenFrame  ) {
	AnimatorObj* anim = new AnimatorObj();
	anim->lifespan = _lifespan;

 
	anim->AnimationObject = new SpriteObject(fileName, row, column, pos, size);
	anim->AnimationObject->SetAnimationLoop(0, 0, howManyFrame, delayBetaweenFrame, true);

	for (SpriteObject* s : objToHide) {
		anim->PausedObj.push_back(s);
		s->SetPause(true);
	}

	spriteObjectDict.push_back(anim);


	return;
}

float dataText = 0;
void AnimatorManager::Update(int deltaTime) {
	dataText += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime(); ;
	for (int i = 0; i < spriteObjectDict.size(); i++) {
		//Update for aniation object 
		AnimatorObj* spriteObject = spriteObjectDict[i];
		spriteObject->AnimationObject->Update(deltaTime);

		spriteObject->lifespan -= 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime();
  		if (spriteObject->lifespan <= 0) {
			delete spriteObject->AnimationObject;

			for (int k = 0; k < spriteObject->PausedObj.size(); k++) {
				spriteObject->PausedObj[k]->SetPause(false);
			}

			spriteObjectDict.erase(spriteObjectDict.begin() + i);
			break;
		}
	}
	cout << endl;
}

void AnimatorManager::Render(glm::mat4 globalModelTransform) {
	for (int i = 0; i < spriteObjectDict.size(); i++) {
		spriteObjectDict[i]->AnimationObject->Render(globalModelTransform);
	}
}