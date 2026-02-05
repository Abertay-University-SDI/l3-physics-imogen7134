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
	void SetWorldSize();

private:
	
	const float ACCELERATION = 30.0f;
	const float DRAG_FACTOR = 0.95f;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_worldSize;

	Animation m_walkDown;
	Animation m_walkUp;
	Animation m_walkUpRight;
	Animation m_walkRight;
	Animation m_walkDownRight;    

	Animation* m_currentAnimation;
};

