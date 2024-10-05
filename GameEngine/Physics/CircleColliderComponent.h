#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
	class CircleColliderComponent : public ColliderComponent
	{
	public:
		CircleColliderComponent(float radius) : ColliderComponent() { m_radius = radius; }

		GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;
	
		void draw() override;

		float getRadius() { return m_radius; }

	private:
		//the distance from the center of the circle to any point on it's circumference.
		float m_radius;
	};
}


