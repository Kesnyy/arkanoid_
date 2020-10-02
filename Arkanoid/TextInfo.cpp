#include "TextInfo.h"

TextInfo::TextInfo(const std::string& textString, const sf::Font& font, int id)
	:Renderable(id)
{
	setText(textString);
	setCharacterSize(25);
	text.setFont(font);
}
TextInfo::~TextInfo()
{

}

void TextInfo::setPosition(const sf::Vector2f& position)
{
	text.setPosition(position);
}

void TextInfo::setCharacterSize(unsigned int size)
{
	text.setCharacterSize(size);
}

void TextInfo::setText(const std::string& textString)
{
	text.setString(textString);
}

void TextInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text);
}
