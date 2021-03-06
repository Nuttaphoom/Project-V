
#include "DrawableObject.h"
#include "Camera.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
 

glm::mat4 DrawableObject::getTransform()
{
	glm::mat4 transform = glm::mat4(1.0);

	transform = glm::translate(transform, glm::vec3(pos.x, pos.y, 0));
 	transform = glm::scale(transform, glm::vec3(size.x, size.y, 1));
  
	return transform;
}

DrawableObject::DrawableObject()
{
	pos = glm::vec3(0.0, 0.0, 0.0);
	size = glm::vec3(1.0, 1.0, 1.0);
}

DrawableObject::~DrawableObject() {
	
}

void DrawableObject::SetSize(float sizeX, float sizeY)
{
	size = glm::vec3(sizeX, sizeY, 1);
}

void DrawableObject::SetPosition(glm::vec3 newPosition)
{ 
	pos = newPosition;
}

void DrawableObject::Translate(glm::vec3 moveDistance)
{
	pos = pos + moveDistance;
}

void DrawableObject::Rotate(float xAmout, float yAmout) {
	rotation.x = xAmout; 
	rotation.y = yAmout; 
}

void DrawableObject::Update(int deltaTime)
{
 
}


glm::vec3 DrawableObject::GetPos() {
	return pos;
}

glm::vec3 DrawableObject::GetSize() {
	return size; 
}

 

