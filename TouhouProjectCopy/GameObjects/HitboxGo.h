#pragma once
#include "GameObject.h"
#include "ObjectPool.h"

enum class Types
{
	Player,
	Boss,
};
class HitboxGo : public GameObject
{
protected:
	//sf::RectangleShape shape;
	sf::CircleShape shape;
	Types type;

	ObjectPool<HitboxGo>* pool = nullptr;
public:

	HitboxGo(const std::string& n="");
	virtual ~HitboxGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Draw(sf::RenderWindow& window) override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetHitBoxSize(float s) { shape.setRadius(s); }
	void SetHitBoxFillColor(sf::Color c) { shape.setFillColor(c); }
	void SetHitBoxOutLineColor(sf::Color c) { shape.setOutlineColor(c); }
	void SetHitBoxOutLineThickness(float t) { shape.setOutlineThickness(t); }
	void SetType(int n) { type = (Types)n; }
	void SetPool(ObjectPool<HitboxGo>* hitBoxPool);
	sf::FloatRect GetCollider();
	float GetRaidus() { return shape.getRadius(); }
	sf::Vector2f GetPos() { return this->GetPosition(); }
};

