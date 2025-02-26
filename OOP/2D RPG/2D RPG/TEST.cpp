#include"docktest/doctest.h"
#include"Unit_sprite/Unit_Sprite.h"
#include"Unit_sprite/Animation/Animation.h"
#include "Inventors.h"
#include "BaseItem.h"
#include "weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "stamina_pot.h"
#include <memory>

TEST_CASE("initialization rexture")
{
	weapon sword;

	switch (sword.Get_type_weapon())
	{
	case Sword:
		CHECK(sword.Get_Buttons().Get_texture_name() == "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/sword_01.png");
		break;
	case Bow:
		CHECK(sword.Get_Buttons().Get_texture_name() == "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/bow_02.png");
		break;
	case Sword_and_shield:
		CHECK(sword.Get_Buttons().Get_texture_name() == "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/shield_01.png");
		break;
	case Staff:
		CHECK(sword.Get_Buttons().Get_texture_name() == "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/wand_01.png");
		break;
	default:
		break;
	}
}

TEST_CASE("Unit_Sprite animation handling") {
    sf::Vector2f startPosition(100.f, 100.f);
    Unit_Sprite sprite("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Comparison2x.png", startPosition, false);

    sf::IntRect SIZE{ 0, 0, 120, 80 };
    Animation idleAnim("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/_Idle.png",
        10, SIZE, "idle", true);
    Animation attackAnim("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Attack.png",
        4, SIZE, "attack", false);
    Animation running("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Run.png",
        10, SIZE, "running", true);

    sprite.addAnimation("idle", idleAnim);
    sprite.addAnimation("attack", attackAnim);
    sprite.addAnimation("run", running);

    SUBCASE("Default animation is idle") {
        CHECK(sprite.getAnimation("idle") != nullptr);
        CHECK(sprite.getAnimation("attack") != nullptr);
        CHECK(sprite.getAnimation("run") != nullptr);
    }

    SUBCASE("Start animation changes current animation") {
        sprite.startAnimation("attack");
        CHECK(sprite.getAnimation("attack") == sprite.getAnimation("attack"));
        sprite.startAnimation("run");
        CHECK(sprite.getAnimation("run") == sprite.getCurrentAnimation());
    }

    SUBCASE("Animation resets correctly") {
        sprite.startAnimation("attack");
        sprite.getAnimation("attack")->reset();
        CHECK(sprite.getAnimation("attack")->getCurrentFrame().left == 0);
    }
    SUBCASE("Animation run loops correctly") {
        sprite.startAnimation("run");

        // Примусово оновлюємо анімацію до кінця
        for (int i = 0; i < 9; ++i) { // 10 - кількість кадрів в анімації run
            sprite.update(1.0f); // Симуляція оновлення анімації (1.0f - час оновлення)
        }

        // Перевіряємо, що анімація повернулася на перший кадр
        CHECK(sprite.getCurrentAnimation()->getCurrentFrame().left == 0);
    }
}

std::string text_texture = "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Button/Rect/Default.png";

TEST_CASE("Inventors initialization") {
    Inventors inv(10, 50.0, text_texture);
    CHECK(inv.getCurrentWeight() == doctest::Approx(0.0));
    CHECK(inv.getMaxWeight() == doctest::Approx(50.0));
}

TEST_CASE("Inventors: Add Items") {
    Inventors inv(5, 50.0, text_texture);  // Інвентар з 5 слотами та максимальною вагою 50.0

    auto bow = std::make_shared<weapon>(0, 0, 15, 6.3, 1.1, 3.4, 85, Bow, false);
    auto ring = std::make_shared<Armor>(10, 10, 3, 9, 18, 56, Armor_type::ring, false);
    auto healthPotion = std::make_shared<potion>(50.0f, 5.0f, 1, 10.0);
    auto staminaPotion = std::make_shared<stamina_pot>(30.0f, 3.0f, 1, 5.0);


    CHECK(inv.addItem(bow) == true);
    CHECK(inv.addItem(ring) == true);
    CHECK(inv.addItem(healthPotion) == true);
    CHECK(inv.addItem(staminaPotion) == true);
}

// Тест 2: Перевірка перевищення ваги
TEST_CASE("Inventors: Exceed Max Weight") {
    Inventors inv(3, 20.0, text_texture); // Інвентар з 3 слотами, ліміт ваги 20.0

    auto heavyArmor = std::make_shared<Armor>(10, 10,25, 9, 18, 56, Armor_type::ring, false);

    CHECK(inv.addItem(heavyArmor) == false); // Не повинно додати через перевищення ваги
}

TEST_CASE("Inventors: Get Item_new") {
    Inventors inv(3, 100.0, text_texture);

    auto sword = std::make_shared<weapon>(10, 100, 45, 50.0, 1.5, 2.0, 1, weapon_type::Sword, false);

    bool added = inv.addItem(sword);
    std::cout << "Added item? " << added << "\n";

    auto retrieved = inv.getItem(0);
    std::cout << "Retrieved: " << retrieved.get() << "\n";

    CHECK(retrieved == sword);
}

// Тест 4: Перевірка видалення предмета
TEST_CASE("Inventors: Remove Item") {
    Inventors inv(3, 30.0, text_texture);


    auto healthPotion = std::make_shared<potion>(50.0f, 5.0f, 1, 5.0);
    inv.addItem(healthPotion);

    CHECK(inv.removeItem(0) == true);
    CHECK(inv.getItem(0) == nullptr);
}

// Тест 5: Перевірка заповнення та очищення
TEST_CASE("Inventors: Fill and Clear") {
    Inventors inv(2, 150.0, text_texture);

    std::cout << std::endl << " Перевірка заповнення та очищення" << std::endl;

    auto bow = std::make_shared<weapon>(0, 0, 15, 6.3, 1.1, 3.4, 85, Bow, false);
    auto ring = std::make_shared<Armor>(10, 10, 3, 9, 18, 56, Armor_type::ring, false);

    CHECK(inv.addItem(bow) == true);
    CHECK(inv.addItem(ring) == true);
    CHECK(inv.addItem(std::make_shared<potion>(1,1,15,20)) == false); // Інвентар повний

    inv.removeItem(1); // Видаляємо щит
    CHECK(inv.addItem(std::make_shared<potion>(1, 1, 15, 20)) == true); // Тепер можна додати
}


