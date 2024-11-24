#include "Unit_Sprite.h"
#include <iostream>

Unit_Sprite::Unit_Sprite(const std::string& textureFile, sf::Vector2f pos, bool fullPhoto, sf::IntRect size)
    : position_sprite(pos), idleAnimationName("idle"), currentAnimation(nullptr), currentTexture(nullptr)
{
    if (fullPhoto) {
        if (!unit_texture.loadFromFile(textureFile, size)) {
            throw std::runtime_error("Failed to load texture from file: " + textureFile);
        }
    }
    else {
        if (!unit_texture.loadFromFile(textureFile)) {
            throw std::runtime_error("Failed to load texture from file: " + textureFile);
        }
    }

    unit_sprite.setTexture(unit_texture); 

    unit_sprite.setOrigin(unit_texture.getSize().x / 2.0f, unit_texture.getSize().y / 2.0f);

    unit_sprite.setPosition(position_sprite);

    defaultTexture = unit_texture;
    currentTexture = &defaultTexture;

    initialScale = unit_sprite.getScale();  // Зберігаємо початковий масштаб
    unit_sprite.setScale(initialScale);  // Встановлюємо початковий масштаб
}

Unit_Sprite::~Unit_Sprite()
{
    for (auto& pair : animations) {
        delete pair.second; // Звільняємо пам'ять для кожної анімації
    }
}

sf::Vector2f Unit_Sprite::getPosition() const {
    return unit_sprite.getPosition();
}

void Unit_Sprite::setPosition(const sf::Vector2f& position) {
    unit_sprite.setPosition(position);
}

void Unit_Sprite::move(sf::Vector2f offset)
{
    position_sprite += offset;
    unit_sprite.setPosition(position_sprite);
}

void Unit_Sprite::update(float deltaTime) {
    if (currentAnimation) {
        currentAnimation->update(deltaTime);  // Оновлення кадрів анімації

        // Встановлюємо новий кадр тільки якщо він змінився
        unit_sprite.setTextureRect(currentAnimation->getCurrentFrame());

        // Перевірка завершення анімації
        if (currentAnimation->isFinished() && currentAnimation->getName() != idleAnimationName) {
            startAnimation(idleAnimationName);  // Повертаємось до idle
        }
    }
    else {
        std::cerr << "No current animation set!" << std::endl;
    }
}

void Unit_Sprite::draw(sf::RenderWindow& window)
{
    window.draw(unit_sprite);
}

void Unit_Sprite::startAnimation(const std::string& animationName)
{
    // Перевірка, чи анімація вже активна
    if (currentAnimation && currentAnimation->getName() == animationName) {
        return; // Якщо активна анімація відповідає, нічого не змінюємо
    }

    Animation* anim = getAnimation(animationName);
    if (anim) {
        currentAnimation = anim;      // Встановлюємо нову анімацію
        currentAnimation->reset();    // Починаємо з першого кадру
        unit_sprite.setTexture(*currentAnimation->getTexture()); // Оновлюємо текстуру спрайта
        std::cout << "Starting animation: " << animationName << std::endl;
    }
    else {
        std::cout << "Animation not found: " << animationName << std::endl;
    }
}

void Unit_Sprite::addAnimation(const std::string& name, const Animation& animation)
{
    animations[name] = new Animation(animation); // Копіюємо анімацію через динамічне виділення пам'яті
}

void Unit_Sprite::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        startAnimation("attack");  // Перехід на анімацію атаки
    }
}

void Unit_Sprite::setRotation(float angle) {
    unit_sprite.setRotation(angle);
}

void Unit_Sprite::setScale(float x, float y) {
    unit_sprite.setScale(x, y);
}

void Unit_Sprite::setFlipped(bool flipped) {
    unit_sprite.setScale(flipped ? -1.f : 1.f, 1.f);  // Відображення по горизонталі
}

Animation* Unit_Sprite::getAnimation(const std::string& name) {
    auto it = animations.find(name);  // it - це std::map<std::string, Animation>::iterator
    if (it != animations.end()) {
        return (it->second);  // Повертаємо вказівник на Animation
    }
    return nullptr;  // Повертаємо nullptr, якщо анімацію не знайдено
}