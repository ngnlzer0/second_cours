#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "BaseItem.h"
#include"Includer.h"

class Inventors {
private:
    double maxWeight;                          // Максимальна вага
    double currentWeight;                      // Поточна вага
    unsigned int size;                         // Кількість клітинок інвентаря
    sf::Sprite background;                     // Фон інвентаря
    sf::Texture backgroundTexture;             // Текстура для фону
    std::vector<std::shared_ptr<BaseItem>> slots; // Слоти для предметів (може бути порожнім)
    std::vector<sf::RectangleShape> cells;    // Клітинки інвентаря

    std::shared_ptr<BaseItem> draggedItem;         // Предмет, який ми переміщуємо
    sf::Vector2f originalPosition;  // Початкова позиція спрайта захопленого предмета
    int originalSlotIndex;          // Індекс клітинки, з якої взяли предмет
    bool isDragging;                // Флаг для визначення, чи виконується перетягування

public:
    // Конструктор
    Inventors(unsigned int size, double maxWeight, const std::string& bgTexturePath);

    // Деструктор
    ~Inventors() = default;

    // Додати предмет в інвентар
    bool addItem(const std::shared_ptr<BaseItem>& item);

    // Видалити предмет зі слоту
    bool removeItem(unsigned int index);

    // Отримати предмет зі слоту
    std::shared_ptr<BaseItem> getItem(unsigned int index) const;

    // Отримати поточну вагу
    double getCurrentWeight() const;

    // Отримати максимальну вагу
    double getMaxWeight() const;

    // Відобразити інвентар
    void draw(sf::RenderWindow& window) const;

    // Ініціалізувати клітинки
    void initializeCells(unsigned int columns, float slotSize, float padding);

    void update(const sf::RenderWindow& window);
    void handleInput(sf::Event& event, const sf::RenderWindow& window);
};

