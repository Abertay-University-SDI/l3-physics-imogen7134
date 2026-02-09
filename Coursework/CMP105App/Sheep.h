#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Sheep :
	public GameObject
{

public:
	Sheep();
	~Sheep();

	void handleInput(float dt) override;
	void update(float dt) override;
	void setWorldSize(float x, float y);
	void checkWallAndBounce();
	void collisionResponse(GameObject& collider) override;

private:
	
	const float ACCELERATION = 30.0f;
	const float DRAG_FACTOR = 0.95f;
	const float COEFF_OF_RESTITUTION = 0.85f;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_worldSize;


	Animation m_walkDown;
	Animation m_walkUp;
	Animation m_walkUpRight;
	Animation m_walkRight;
	Animation m_walkDownRight;    

	Animation* m_currentAnimation;
};

