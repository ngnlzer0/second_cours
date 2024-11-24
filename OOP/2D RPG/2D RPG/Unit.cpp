#include "Unit.h"
#include<iostream>
#include<time.h>

Unit::Unit(const std::string texture_file, sf::Vector2f pos, sf::Vector2f size, bool chois_rect, sf::IntRect Pos_texture,
	int X, int Y, const double max_weight, const double g_max_hp, const int g_max_stamina,int g_speed, double g_block, double g_miss)
	:c_weapon(new weapon()), c_armor(new Armor()), position(X, Y),max_weight(max_weight), max_HP(g_max_hp),max_stamina(g_max_stamina),cur_weight(max_weight),
	HP(g_max_hp),stamina(g_max_stamina),speed(g_speed),block(g_block),miss(g_miss),
	hpBackground(sf::Vector2f(200, 30)), staminaBackground(sf::Vector2f(200, 30)), hpBar(sf::Vector2f(0, 30)), staminaBar(sf::Vector2f(0, 30))
{
	
	cur_weight += c_armor->Get_weight();
	cur_weight += c_weapon->Get_weight();

	hpBackground.setPosition(10, 10);
	hpBackground.setFillColor(sf::Color(150, 150, 150)); // Сірий фон для HP
	hpBackground.setOutlineThickness(2);
	hpBackground.setOutlineColor(sf::Color::Black); // Чорна обводка

	staminaBackground.setPosition(10, 50);
	staminaBackground.setFillColor(sf::Color(150, 150, 150)); // Сірий фон для Stamina
	staminaBackground.setOutlineThickness(2);
	staminaBackground.setOutlineColor(sf::Color::Black); // Чорна обводка

	hpBar.setPosition(10, 10);
	hpBar.setFillColor(sf::Color::Red);  // Червоний колір для HP

	staminaBar.setPosition(10, 50);
	staminaBar.setFillColor(sf::Color::Green);  // Зелений колір для Stamina

	if (!font.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Angel wish.ttf")) {
		// Перевірка на помилку при завантаженні шрифта
		std::cerr << "Error loading font!" << std::endl;
	}

	// Налаштування текстових об'єктів для HP
	hpText.setFont(font);
	hpText.setCharacterSize(20);
	hpText.setFillColor(sf::Color::Black);  // Чорний текст для HP
	hpText.setPosition(90, 10);  // Текст буде на 90 пікселів по X, щоб не перекривати бар

	// Налаштування текстових об'єктів для Stamina
	staminaText.setFont(font);
	staminaText.setCharacterSize(20);
	staminaText.setFillColor(sf::Color::Black);  // Чорний текст для Stamina
	staminaText.setPosition(90, 50);  // Текст буде на 90 пікселів по X, щоб не перекривати бар

}

void Unit::received_damage(double minus_damage)
{
	std::srand(std::time(NULL));
	if (Genereta_int_random_number() % 2 == 1)
		c_armor->Set_durability(c_armor->Get_durability() - 1);
	HP -= minus_damage;
	if (HP <= 0)
		this->~Unit();
}

void Unit::attack_enemi(Unit* enemi)
{
	if (Get_stamina() > 12)
	{
		enemi->received_damage(this->Get_weapon()->Get_damage() * ((100 - enemi->Get_block()) / 100));
		srand(time(NULL));
		if (Genereta_int_random_number() % 2 == 1)
			c_weapon->Set_durability(c_weapon->Get_durability() - 1);
		this->Set_new_stamina(Get_stamina() - 12);
	}
}

void Unit::updateBars() {
	// Обчислення відсотка HP і Stamina
	float hpPercentage = static_cast<float>(HP) / max_HP;
	float staminaPercentage = static_cast<float>(stamina) / max_stamina;

	// Оновлення ширини барів на основі відсотка
	hpBar.setSize(sf::Vector2f(200 * hpPercentage, 30));  // HP Bar змінюється по ширині пропорційно до HP
	staminaBar.setSize(sf::Vector2f(200 * staminaPercentage, 30));  // Stamina Bar змінюється по ширині пропорційно до Stamina

	// Оновлення текстів
	hpText.setString(std::to_string(static_cast<int>(HP)) + " / " + std::to_string(static_cast<int>(max_HP)));
	staminaText.setString(std::to_string(stamina) + " / " + std::to_string(max_stamina));
}

// Малювання кнопок на екрані
void Unit::drawBars(sf::RenderTarget& target) const {
	// Малюємо фони барів (сірі)
	target.draw(hpBackground);
	target.draw(staminaBackground);

	// Малюємо бари HP та Stamina (червоний і зелений)
	target.draw(hpBar);
	target.draw(staminaBar);

	// Малюємо текст для HP та Stamina
	target.draw(hpText);
	target.draw(staminaText);

}


/*void Unit::Healt_self()
{
	if (inventar.Get_number_potion() > 0)
	{
		this->Set_new_HP(Get_HP() + inventar.Get_regeneration_hp());
		inventar.dell_potion(1);
	}
}

void Unit::push_stamina_self()
{
	if (inventar.Get_number_stamina_pot() > 0)
	{
		this->Set_new_stamina(Get_stamina() + inventar.Get_regeneration_stamina());
		inventar.dell_stamina_pot(1);
	}
}

void Unit::Get_accet_monstr(Unit* other)
{
	if ((this->Get_HP() * 0, 9) > other->Get_HP() && this->Get_stamina() > this->Get_max_stamina() * 0,12)
	{
		this->attack_enemi(other);
		return ;
	}
	else if (this->Get_HP() < (other->Get_HP() * 0,9) && this->inventar.Get_number_potion() > 0)
	{
		this->Healt_self();
		return;
	}
	else if (this->Get_stamina() < 20 && this->inventar.Get_number_stamina_pot() > 0)
	{
		this->push_stamina_self();
		return;
	}
	else 
	{
		this->attack_enemi(other);
		return;
	}
}

void Unit::user_step(Unit* other)
{
	int accept = 0;
	std::cout << "choise a steep in game \n 1) Attack enemi  \n2) Health, you have "<< this->inventar.Get_number_potion() <<"potion"
		      << " \n3) Up stamina, you have "<<this->inventar.Get_number_stamina_pot()<<" stamina potion  \n 4) skeep \n";
	std::cin >> accept;
	switch (accept)
	{
	case(1):
		this->attack_enemi(other);
		return;
	case(2):
		this->Healt_self();
		return;
	case(3):
		this->push_stamina_self();
		return;
	case(4):
		return;
	default:
		break;
	}
}


void Fight(Unit* hero, Unit* monstr)
{
	while (hero->aliwe() && monstr->aliwe())
	{
		if (hero->Get_speed() >= monstr->Get_speed())
		{
			hero->user_step(monstr);
			monstr->Get_accet_monstr(hero);
		}
		else
		{
			monstr->Get_accet_monstr(hero);
			hero->user_step(monstr);
		}
	}
	
}
*/