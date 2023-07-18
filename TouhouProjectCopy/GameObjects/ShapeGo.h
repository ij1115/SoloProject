#pragma once
#include "GameObject.h"
#include "ObjectPool.h"

enum class Types
{
	Player,
	Boss,
};
class ShapeGo : public GameObject
{
protected:
	sf::RectangleShape shape;
	Types type;
	ObjectPool<ShapeGo>* pool = nullptr;
public:

	ShapeGo(const std::string& n="");
	virtual ~ShapeGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Draw(sf::RenderWindow& window) override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetHitBoxSize(sf::Vector2f s) { shape.setSize(s); }
	void SetHitBoxFillColor(sf::Color c) { shape.setFillColor(c); }
	void SetHitBoxOutLineColor(sf::Color c) { shape.setOutlineColor(c); }
	void SetHitBoxOutLineThickness(float t) { shape.setOutlineThickness(t); }
	void SetType(int n) { type = (Types)n; }
	void SetPool(ObjectPool<ShapeGo>* hitBoxPool);
	sf::FloatRect GetCollider();
};

