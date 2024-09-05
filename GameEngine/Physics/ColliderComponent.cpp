#include "ColliderComponent.h"

void GamePhysics::ColliderComponent::start()
{
	//add collider to the scene 
	// Get Ownser's rigidbody
}

GamePhysics::Collision* GamePhysics::ColliderComponent::checkCollision(ColliderComponent* other)
{
	switch (other->getColliderType())
	{
	case CIRCLE:
		return checkCollisionCircle((CircleColliderComponent*)other);
	case AABB:
		return checkCollisionAABB((AABBColliderComponent*)other);
	}
		

	return nullptr;
}


void GamePhysics::ColliderComponent::onCollisionEnter(GamePhysics::Collision* other)
{
	m_color = 0xFF0000FF;
}

void GamePhysics::ColliderComponent::update(double deltaTime)
{
	m_color = 0x00FF00FF;
}
