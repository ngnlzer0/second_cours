#pragma once
#include <string>
#include <SFML/Graphics.hpp>

// Базовий клас предмета
class BaseItem {
protected:
    std::string name;       // Назва предмета
    double weight_i;          // Вага предмета
    sf::Texture texture;    // Текстура предмета

public:
    BaseItem(const std::string& name, double weight)
        : name(name), weight_i(weight) {
    }

    virtual ~BaseItem() = default;

    // Геттери
    const std::string& getName() const { return name; }
    double getWeight() const { return weight_i; }
    const sf::Texture& getTexture() const { return texture; }
    void Set_weight_i(double weight_g) { weight_i = weight_g; };

    // Віртуальний метод для завантаження текстури
    virtual void loadTexture(const std::string& texturePath) {
        texture.loadFromFile(texturePath);
    }
};