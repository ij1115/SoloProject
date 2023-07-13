#pragma once
#include "SpriteGo.h"
class UiButton : public SpriteGo
{
protected:
	bool isHover = false;
public:
	UiButton(const std::string& textureId="", const std::string& n="");
	virtual ~UiButton() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	sf::Text text;

	std::function<void()> OnClick;
	std::function<void()> OnEnter;
	std::function<void()> OnExit;

};

