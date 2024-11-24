#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>

class BaseItem {
protected:
    std::string name_text;
    sf::Texture texture;  // Текстура предмета
    sf::Sprite sprite;    // Спрайт предмета
    double weight_i;        // Вага предмета

public:
    BaseItem(const std::string& texturePath, double weight, bool rect = false, sf::IntRect size_t ={0,0,0,0} )
        : texture(), sprite(), weight_i(weight) 
    {
        if (rect)
        {
            if (!texture.loadFromFile(texturePath,size_t) && texturePath != "") {
                std::cerr << "Error loading texture from path: " << texturePath << std::endl;
                throw std::runtime_error("Failed to load texture: " + texturePath);
            }
        }
        else if (!texture.loadFromFile(texturePath) && texturePath != "") {
            std::cerr << "Error loading texture from path: " << texturePath << std::endl;
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
    }
    // Отримати спрайт предмета
    sf::Sprite* getSprite() {
        return &sprite;
    }

    // Отримати вагу предмета
    double getWeight() const {
        return weight_i;
    }

    // Встановити нову вагу
    void set_Weight_i(double newWeight) {
        weight_i = newWeight;
    }

    void setNewTexture(const std::string& texturePath, bool rect = false, sf::IntRect size_t = { 0,0,0,0 })
    {
        name_text = texturePath;
        if (rect)
        {
            if (!texture.loadFromFile(texturePath, size_t) && texturePath != "") {
                std::cerr << "Error loading texture from path: " << texturePath << std::endl;
                throw std::runtime_error("Failed to load texture: " + texturePath);
            }
        }
        else if(!texture.loadFromFile(texturePath)) {
            std::cerr << "Error loading texture from path: " << texturePath << std::endl;
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
        sprite.setTexture(texture);  // Оновлюємо спрайт із новою текстурою
    }

    virtual ~BaseItem() = default;
};
