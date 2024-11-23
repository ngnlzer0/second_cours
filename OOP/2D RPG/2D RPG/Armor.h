#pragma once
#include <unordered_map>
#include "Buttons.h"
#include <SFML/Graphics.hpp>
#include "BaseItem.h"

enum Armor_type {
    helmet,
    jacket,
    gloves,
    ring,
    shoes,
};

class Armor : public sf::Drawable, public BaseItem {
private:
    Buttons* armor_button;
    Armor_type type;
    double weight;
    double block;
    double miss;
    int durability;

    static const std::unordered_map<Armor_type, std::string> armorTexturePaths;

protected:
    // Метод draw, щоб намалювати armor_button на екрані
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        armor_button->draw(target, states);
    }

public:
    Armor(int pos_x = 0, int pos_y = 0,
        double g_weight = 0.0, double g_block = 0.0, double g_missing = 0.0, int g_durability = 0, Armor_type g_type = helmet, bool random = true);

    // Гетери та сетери
    double Get_weight() const { return weight; }
    double Get_block() const { return block; }
    double Get_missing() const { return miss; }
    int Get_durability() const { return durability; }

    double Set_weight(double g_weight) { return (g_weight > 0.0 ? weight = g_weight : weight = 0.0); }
    double Set_block(double g_block) { return (block = g_block); }
    double Set_missing(double g_missing) { return (miss = g_missing); }
    int Set_durability(int g_durability) { return (g_durability > 0 ? durability = g_durability : durability = 0); }

    Buttons& Get_buttons() const { return *armor_button; }
};

