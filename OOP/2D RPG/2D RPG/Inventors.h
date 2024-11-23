#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "BaseItem.h"

class Inventors {
private:
    double weight_inventors;                      // Поточна вага інвентаря
    const double max_weight = 55.0;               // Максимальна вага інвентаря
    const int max_items = 9;                      // Максимальна кількість предметів
    std::vector<std::shared_ptr<BaseItem>> items; // Предмети в інвентарі
    std::vector<sf::RectangleShape> grid_cells;   // Клітинки інвентаря

    const std::string name_texture;
    sf::Sprite background;                        // Фон інвентаря
    sf::Texture texture_background;

public:
    Inventors();

    // Додавання предмета
    bool addItem(const std::shared_ptr<BaseItem>& item);

    // Видалення предмета
    bool removeItem(const std::shared_ptr<BaseItem>& item);

    // Отримати загальну вагу інвентаря
    double getWeight() const { return weight_inventors; }

    // Отримати максимальну вагу
    double getMaxWeight() const { return max_weight; }

    // Відображення інвентаря
    void draw(sf::RenderTarget& target) const;

private:
    void initializeGrid(float cell_size, float spacing, sf::Vector2f start_position);
};

