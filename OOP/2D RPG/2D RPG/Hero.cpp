#include "Hero.h"
#include <iostream>

Hero::Hero()
    : hero_sprite("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Comparison2x.png",
        { 0, 0 }, true, sf::IntRect{ 0, 0, 120, 80 }), speed(200.0f), isMoving(false), state(HeroState::Idle), currentAnim(nullptr)
{
    sf::IntRect SIZE{ 0, 0, 120, 80 };
    std::cout << "Adding animation: attack" << std::endl;
    hero_sprite.addAnimation("attack", Animation("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Attack.png",
        4, SIZE, "attack"));
    std::cout << "Adding animation: running" << std::endl;
    hero_sprite.addAnimation("running", Animation("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Run.png",
        10, SIZE, "running"));
    std::cout << "Adding animation: attack_combo" << std::endl;
    hero_sprite.addAnimation("attack_combo", Animation("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_AttackCombo2hit.png",
        10, SIZE, "attack_combo"));
    std::cout << "Adding animation: idle" << std::endl;
    hero_sprite.addAnimation("idle", Animation("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Comparison2x.png",
        1, SIZE, "idle"));
}

void Hero::move(sf::Vector2f offset)
{
    hero_sprite.move(offset);
}

void Hero::update(float deltaTime)
{
    hero_sprite.update(deltaTime); // Оновлюємо анімацію
}

void Hero::startAnimation(const std::string& animationName)
{
    if (currentAnim == nullptr || currentAnim->getName() != animationName) {
        // Перевірка наявності анімації
        std::cout << "Starting animation: " << animationName << std::endl;

        // Якщо анімація змінилася, встановлюємо нову анімацію
        currentAnim = hero_sprite.getAnimation(animationName);
        if (currentAnim) {
            hero_sprite.startAnimation(animationName);  // Запускаємо анімацію
        }
        else {
            std::cout << "No animation found with name: " << animationName << std::endl;
        }
    }
}

void Hero::handleInput(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            direction = sf::Vector2f(0, -1);
            isMoving = true;
            state = HeroState::Running;
        }
        else if (event.key.code == sf::Keyboard::S) {
            direction = sf::Vector2f(0, 1);
            isMoving = true;
            state = HeroState::Running;
        }
        else if (event.key.code == sf::Keyboard::A) {
            direction = sf::Vector2f(-1, 0);
            isMoving = true;
            state = HeroState::Running;
        }
        else if (event.key.code == sf::Keyboard::D) {
            direction = sf::Vector2f(1, 0);
            isMoving = true;
            state = HeroState::Running;
        }
        else if (event.key.code == sf::Keyboard::Enter && state != HeroState::Attacking) {
            isMoving = false;
            state = HeroState::Attacking;
            startAnimation("attack");
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S ||
            event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
            isMoving = false;
            state = HeroState::Idle;
        }
    }

    updateAnimation();
}


void Hero::processMovement(float deltaTime,const sf::RenderWindow& window)
{
    if (isMoving) {
        // Переміщаємо героя відповідно до напрямку
        hero_sprite.move({ direction.x * speed * deltaTime, direction.y * speed * deltaTime });
    }
}

void Hero::updateAnimation()
{
    auto* currentAnim = hero_sprite.getCurrentAnimation();

    if (state == HeroState::Attacking) {
        if (currentAnim && currentAnim->isFinished()) {
            state = HeroState::Idle;
            hero_sprite.startAnimation("idle");
        }
    }
    else if (state == HeroState::Running) {
        if (!currentAnim || currentAnim->getName() != "running") {
            hero_sprite.startAnimation("running");
        }
    }
    else if (state == HeroState::Idle) {
        if (!currentAnim || currentAnim->getName() != "idle") {
            hero_sprite.startAnimation("idle");
        }
    }
}

void Hero::updateSpriteOrientation(float scaleX) {
    // Встановлюємо масштаб спрайта для розвороту (ліворуч чи праворуч)
    hero_sprite.setScale(scaleX, 1.0f);

    // Встановлюємо походження спрайта по центру текстури
    sf::FloatRect bounds = hero_sprite.getLocalBounds();
    hero_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}
