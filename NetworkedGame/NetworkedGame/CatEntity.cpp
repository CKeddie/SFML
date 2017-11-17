#include "CatEntity.h"

#include "CatAnimator.h"

CatEntity::CatEntity(float px, float py, float sx, float sy, float rot, float ox, float oy, float bw, float bh)
	: CatEntity(sf::Vector2f(px, py), sf::Vector2f(sx, sy), rot, sf::Vector2f(ox, oy), sf::Vector2f(bw, bh))
{
}

CatEntity::CatEntity(sf::Vector2f position, sf::Vector2f scale, float rotation, sf::Vector2f boxOffset, sf::Vector2f boxSize)
	: Entity(position, scale, rotation)
{
	AddComponent(new BoxCollider(*this, boxSize, boxOffset));
	AddComponent(new PhysicsBody(*this));
	AddComponent(new SpriteRenderer(*this, *_position));
	AddComponent(new CatAnimator(*this));

	int * anim;

	anim = new int[4]{ 0,1,2,4 }; //idle
	GetComponent<CatAnimator>()->AddAnimation(Idle, new Animation(anim, 3, 1024, 1024, 64, 64));

	anim = new int[8]{ 16, 17, 18, 19, 20, 21, 22, 23 }; //run
	GetComponent<CatAnimator>()->AddAnimation(Run, new Animation(anim, 4, 1024, 1024, 64, 64));

	anim = new int[1]{ 34 }; //jump
	GetComponent<CatAnimator>()->AddAnimation(Jump, new Animation(anim, 1, 1024, 1024, 64, 64));

	anim = new int[1]{ 35 }; //fall
	GetComponent<CatAnimator>()->AddAnimation(Fall, new Animation(anim, 1, 1024, 1024, 64, 64));
}

CatEntity::~CatEntity()
{
	Entity::~Entity();
}

void CatEntity::Update(float deltaTime)
{
	Entity::Update(deltaTime);
}

void CatEntity::Draw(sf::RenderWindow * window)
{
	Entity::Draw(window);
}