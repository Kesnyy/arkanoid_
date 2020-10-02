#pragma once
#include "Renderable.h"
class TextInfo : public Renderable
{
public:
	TextInfo(const std::string &textString, const sf::Font &font, int id);
	~TextInfo();
	
	void setPosition(const sf::Vector2f& position);
	void setCharacterSize(unsigned int size);
	void setText(const std::string& textString);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Text text;
	

};

