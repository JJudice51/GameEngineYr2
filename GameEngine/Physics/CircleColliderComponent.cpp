#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>

/// <summary>
/// 
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    //this is for getting a direction to another collider
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;
    float distance = direction.getMagnitude();


    //if there is no collision don't do anything
    if (distance > other->m_radius + m_radius)
    return nullptr;


    //data for Circle collision
    GamePhysics::Collision* collisionData = new Collision();
    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();
    collisionData->contactPoint = position + direction.getNormalized() * getRadius();
    collisionData->penetrationDistance = other->m_radius + m_radius - distance;

    return collisionData;
}


/// <summary>
/// checks for collision with an AABB collider 
/// </summary>
/// <param name="other">the AABB collider we are checking for collision with</param>
/// <returns></returns>
GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;

    //If collision detcected return the data for that collision
    if (position.x < otherPosition.x + other->getWidth() && position.x + getRadius() > otherPosition.x &&
        position.y < otherPosition.y + other->getHeight() && position.y + getRadius() > otherPosition.y)
    {
        //Data for an AABB Collision
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        collisionData->normal = direction.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * getRadius();
        collisionData->penetrationDistance = (other->getRadius() + getRadius());

        return collisionData;
    }
    
    
    else
        return nullptr;


}


/// <summary>
/// draws a circle collider to the scene
/// </summary>
void GamePhysics::CircleColliderComponent::draw()
{
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

    RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(getColor()));
}
