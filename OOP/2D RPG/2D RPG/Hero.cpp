#include "Hero.h"

Hero::Hero()
    : hero_sprite("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Comparison2x.png",
        { 0, 0 }, true, sf::IntRect{ 0, 0, 120, 80 }), speed(200.0f), isMoving(false), state(HeroState::Idle)
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

void Hero::update(float deltaTime) {
    updateAnimation();  // Оновлюємо анімацію в залежності від поточного стану
    hero_sprite.update(deltaTime); // Оновлюємо спрайт
}

void Hero::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        // Перевіряємо, чи анімація поточно задана перед її запуском
        if (hero_sprite.getCurrentAnimation() == nullptr || hero_sprite.getCurrentAnimation()->getName() != "attack") {
            hero_sprite.startAnimation("attack");  // Запуск анімації атаки
        }
    }
}

void Hero::processMovement(float deltaTime)
{
    isMoving = false;
    movement = { 0.0f, 0.0f };

    // Перевірка на натискання клавіш WASD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speed * deltaTime;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed * deltaTime;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= speed * deltaTime;
        isMoving = true;
        hero_sprite.setFlipped(true);  // Розворот вліво
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed * deltaTime;
        isMoving = true;
        hero_sprite.setFlipped(false);  // Розворот вправо
    }

    // Зміщення спрайту героя
    if (isMoving) {
        hero_sprite.move(movement);

        // Перевірка, чи є поточна анімація перед її зміною
        if (hero_sprite.getCurrentAnimation() != nullptr && hero_sprite.getCurrentAnimation()->getName() != "running") {
            hero_sprite.startAnimation("running");  // Запускаємо анімацію бігу
        }
    }
    else {
        if (hero_sprite.getCurrentAnimation() != nullptr && hero_sprite.getCurrentAnimation()->getName() != "idle") {
            hero_sprite.startAnimation("idle");  // Перехід до анімації "idle"
        }
    }
}

void Hero::updateAnimation()
{
    auto* currentAnim = hero_sprite.getCurrentAnimation();

    // Якщо герой атакує, відтворюємо анімацію атаки
    if (state == HeroState::Attacking) {
        if (currentAnim && currentAnim->isFinished()) {
            state = HeroState::Idle;
            hero_sprite.startAnimation("idle");  // Повертаємось до Idle після завершення атаки
        }
    }
    // Якщо герой рухається, відтворюємо анімацію бігу
    else if (state == HeroState::Running) {
        if (!currentAnim || currentAnim->getName() != "running") {
            hero_sprite.startAnimation("running");
        }
    }
    // Якщо герой стоїть, відтворюємо анімацію стояння
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