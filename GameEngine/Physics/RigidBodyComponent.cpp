#include "RigidBodyComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/ColliderComponent.h"
#include "Engine/Entity.h"

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	m_velocity = m_velocity + force / getMass();
}

void GamePhysics::RigidBodyComponent::applyForceToEntity(RigidBodyComponent* rigidBody, GameMath::Vector2 force)
{
	applyForce(force * -1);
	rigidBody->applyForce(force);
}

void GamePhysics::RigidBodyComponent::fixedUpdate(float fixedDeltaTime)
{
	GameMath::Vector2 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + m_velocity * fixedDeltaTime);

	GameMath::Vector2 gravity = { 0, getGravity() };
	applyForce(gravity * getMass());
}

void GamePhysics::RigidBodyComponent::resolveCollision(GamePhysics::Collision* collisionData)
{
	//variables to utilize in resoluion math
	RigidBodyComponent* otherRigidBodyComponent = collisionData->collider->getRigidBody();
	Vector2 normal = collisionData->normal;
	float impulse;

	//assuming both rigidbodies have infinite mass
	if (!otherRigidBodyComponent)
	{
		//temporary rigid body component
		otherRigidBodyComponent = new RigidBodyComponent();

	
		impulse = 2 * getMass() * normal.dotProduct(getVelocity(), normal);
		Vector2 force = normal * impulse;

		applyForceToEntity(otherRigidBodyComponent, force);
		return;
	}

	else if (getMass() != otherRigidBodyComponent->getMass())
	{

		return;
	}

	//Physics Math, for Collision Resolution/Response
	impulse = 2 * (normal.dotProduct(getVelocity() - otherRigidBodyComponent->getVelocity(), normal))
		/ normal.dotProduct(normal, normal) * (1 / getMass() + 1 / otherRigidBodyComponent->getMass());

	//Storing and applying force
	Vector2 force = normal * impulse;
	applyForceToEntity(otherRigidBodyComponent, force);
}