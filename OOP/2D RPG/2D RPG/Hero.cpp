#include "Hero.h"
#include <iostream>

Hero::Hero()
    : hero_sprite("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Comparison2x.png",
        { 0, 0 }, true, sf::IntRect{ 0, 0, 120, 80 }), speed(200.0f), isMoving(false), state(HeroState::Idle), currentAnim(nullptr)
{

    sf::IntRect SIZE{ 0, 0, 120, 80 };
    std::cout << "Adding animation: attack" << std::endl;
    hero_sprite.addAnimation("attack", Animation("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Attack.png",
        4, SIZE, "attack",false));
    std::cout << "Adding animation: running" << std::endl;
    hero_sprite.addAnimation("running", Animation("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Run.png",
        10, SIZE, "running",true));
    std::cout << "Adding animation: attack_combo" << std::endl;
    hero_sprite.addAnimation("attack_combo", Animation("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_AttackCombo2hit.png",
        10, SIZE, "attack_combo",false));
    std::cout << "Adding animation: idle" << std::endl;
    hero_sprite.addAnimation("idle", Animation("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/_Idle.png",
        10, SIZE, "idle",true));
    hero_sprite.setPosition({ WIDHT_WINDOW / 2 , HIGHT_WINDOW / 2});

    initialScale_h = { 2,2 };
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
        std::cout << "Starting animation: " << animationName << std::endl;

        currentAnim = hero_sprite.getAnimation(animationName);
        if (currentAnim) {
            hero_sprite.startAnimation(animationName);  // Запускаємо анімацію
            // Не змінюйте масштаб тут
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

            // Розвертаємо героя ліворуч
            hero_sprite.setScale(-std::abs(initialScale_h.x), initialScale_h.y);
        }
        else if (event.key.code == sf::Keyboard::D) {
            direction = sf::Vector2f(1, 0);
            isMoving = true;
            state = HeroState::Running;

            // Розвертаємо героя праворуч
            hero_sprite.setScale(std::abs(initialScale_h.x), initialScale_h.y);
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




void Hero::processMovement(float deltaTime, const sf::RenderWindow& window)
{
    if (isMoving) {
        sf::Vector2f newPosition = hero_sprite.getPosition() + sf::Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);

        sf::Vector2u windowSize = window.getSize();
        sf::FloatRect heroBounds = hero_sprite.getGlobalBounds();

        // Перевіряємо, чи не виходить за межі екрану
        if (newPosition.x - heroBounds.width / 2 < 0) {
            newPosition.x = heroBounds.width / 2;
        }
        else if (newPosition.x + heroBounds.width / 2 > windowSize.x) {
            newPosition.x = windowSize.x - heroBounds.width / 2;
        }

        if (newPosition.y - heroBounds.height / 2 < 0) {
            newPosition.y = heroBounds.height / 2;
        }
        else if (newPosition.y + heroBounds.height / 2 > windowSize.y) {
            newPosition.y = windowSize.y - heroBounds.height / 2;
        }

        hero_sprite.setPosition(newPosition);
    }
}

void Hero::updateAnimation()
{
    auto* currentAnim = hero_sprite.getCurrentAnimation();

    // Якщо герой атакує, пріоритет атаки
    if (state == HeroState::Attacking) {
        if (currentAnim && currentAnim->isFinished()) {
            // Повертаємось до стану "Idle" після завершення атаки
            state = HeroState::Idle;
            hero_sprite.startAnimation("idle");
            hero_sprite.setScale(2, 2); // Відновлення масштабу після атаки
        }
        else if (!currentAnim || currentAnim->getName() != "attack") {
            // Запуск анімації атаки тільки якщо вона не активна
            hero_sprite.startAnimation("attack");
        }
        return; // Атака має найвищий пріоритет
    }

    // Якщо герой біжить
    if (state == HeroState::Running) {
        // Перевірка, чи вже виконується анімація "running"
        if (!currentAnim || currentAnim->getName() != "running") {
            // Запускаємо анімацію бігу тільки якщо вона не активна
            hero_sprite.startAnimation("running");
            hero_sprite.setScale(2, 2); // Відновлення масштабу
        }
        return; // Якщо біжимо, то анімація "running" не має змінюватися
    }

    // Якщо герой стоїть нерухомо
    if (state == HeroState::Idle) {
        if (!currentAnim || currentAnim->getName() != "idle") {
            // Запуск анімації "Idle" тільки якщо вона не активна
            hero_sprite.startAnimation("idle");
            hero_sprite.setScale(2, 2); // Відновлення масштабу
        }
    }
}

void Hero::updateSpriteOrientation(float scaleX) {
    // Не змінюємо масштаб тут, якщо не потрібно
    hero_sprite.setScale(initialScale_h.x * scaleX, initialScale_h.y);  // Якщо треба перевертати героя по осі X

    // Встановлюємо походження спрайта по центру текстури
    sf::FloatRect bounds = hero_sprite.getLocalBounds();
    hero_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

