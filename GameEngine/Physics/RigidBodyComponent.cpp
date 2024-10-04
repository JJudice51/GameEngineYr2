#include "RigidBodyComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/ColliderComponent.h"
#include "Engine/Entity.h"
//#include "Math/Vector2.h"

/// <summary>
/// Applies a force divdied by the mass to change its current velocity 
/// </summary>
/// <param name="force">the force being applied to the velocity divided by the mass</param>
void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	m_velocity = m_velocity + force / getMass();
}

/// <summary>
/// Applies a force to a RigidBody 
/// </summary>
/// <param name="rigidBody"> the entity receiving the force</param>
/// <param name="force">the force being applied.</param>
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

/// <summary>
/// Completes the collision after one is detected by the collider
/// </summary>
/// <param name="collisionData">Data received by the collider for collision resolution</param>
void GamePhysics::RigidBodyComponent::resolveCollision(GamePhysics::Collision* collisionData)
{
	//variables to utilize in resoluion math
	RigidBodyComponent* otherRigidBodyComponent = collisionData->collider->getRigidBody();
	GameMath::Vector2 normal = collisionData->normal;
	float impulse;

	//assuming both rigidbodies have infinite mass 
	if (!otherRigidBodyComponent)
	{
		//temporary rigid body component
		otherRigidBodyComponent = new RigidBodyComponent();

		
		impulse = 2 * getMass() * normal.dotProduct(getVelocity(), normal);
		GameMath::Vector2 force = normal * impulse;

		applyForceToEntity(otherRigidBodyComponent, force);
		return;
	}

	//Physics Math, for Collision Resolution/Response
	impulse = 2 * (normal.dotProduct(getVelocity() - otherRigidBodyComponent->getVelocity(), normal))
		/ normal.dotProduct(normal, normal) * (1 / getMass() + 1 / otherRigidBodyComponent->getMass());

	//Store and apply force
	GameMath::Vector2 force = normal * impulse;
	applyForceToEntity(otherRigidBodyComponent, force);
}