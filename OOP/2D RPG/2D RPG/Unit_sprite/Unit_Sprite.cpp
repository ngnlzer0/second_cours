#include "Unit_Sprite.h"

Unit_Sprite::Unit_Sprite(const std::string name_file, sf::Vector2f pos , bool full_photo , sf::IntRect Size)
	:name_unit_texture(name_file), position_sprite(pos)
{
	if (full_photo)
		unit_texture.loadFromFile(name_unit_texture, Size);
	else
		unit_texture.loadFromFile(name_unit_texture);
	unit_sprite.setTexture(unit_texture);
}
 

void Unit_Sprite::move(sf::Vector2f offset)
{
    position_sprite += offset;         // Оновлення внутрішньої позиції
    unit_sprite.setPosition(position_sprite); // Оновлення позиції спрайта
}

void Unit_Sprite::update(float deltaTime)
{
    if (currentAnimation)
    {
        currentAnimation->update(deltaTime);
        unit_sprite.setTextureRect(currentAnimation->getCurrentFrame());

        // Перевірка, чи завершилась анімація
        if (currentAnimation->isFinished())
        {
            currentAnimation = nullptr;

            // Повернення до idle анімації
            if (currentTexture != &unit_texture)  // Перевірка на зміну текстури
            {
                currentTexture = &unit_texture;
                unit_sprite.setTexture(*currentTexture);
                unit_sprite.setTextureRect(sf::IntRect());  // Повний розмір текстури
            }

            // Запуск спокійної анімації (idle) після завершення поточної
            startAnimation(idleAnimationName);
        }
    }
}
 
void Unit_Sprite::startAnimation(const std::string& name)
{
    auto it = animations.find(name);
    if (it != animations.end())
    {
        currentAnimation = &it->second;
        currentAnimation->reset();

        // Зміна текстури, якщо вона не дорівнює поточній
        if (currentTexture != currentAnimation->getTexture())
        {
            currentTexture = currentAnimation->getTexture();
            if (currentTexture)
            {
                unit_sprite.setTexture(*currentTexture);
                unit_sprite.setTextureRect(currentAnimation->getCurrentFrame());
            }
        }
    }
}

void Unit_Sprite::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        startAnimation("attack"); // Запускаємо анімацію "attack" при натисканні Enter
    }
}