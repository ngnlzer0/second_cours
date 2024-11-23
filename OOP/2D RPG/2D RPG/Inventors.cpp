#include "Inventors.h"
#include"iostream"

// Конструктор
Inventors::Inventors() : weight_inventors(0.0),name_texture("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Button/Square/Hover.png") 
{
    texture_background.loadFromFile(name_texture);
    background.setTexture(texture_background);
    background.setPosition(400.0f, 0.0f);

    // Ініціалізація сітки
    initializeGrid(64.0f, 10.0f, sf::Vector2f(100.0f, 100.0f));
}

void Inventors::initializeGrid(float cell_size, float spacing, sf::Vector2f start_position) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
            cell.setFillColor(sf::Color::Transparent);
            cell.setOutlineColor(sf::Color::White);
            cell.setOutlineThickness(1.0f);
            cell.setPosition(
                start_position.x + col * (cell_size + spacing),
                start_position.y + row * (cell_size + spacing)
            );
            grid_cells.push_back(cell);
        }
    }
}

// Додавання предмета з перевіркою на вагу
bool Inventors::addItem(const std::shared_ptr<BaseItem>& item) {
    if (items.size() >= max_items) {
        std::cout << "Інвентар переповнений! Не можна додати більше " << max_items << " предметів.\n";
        return false;
    }

    if (weight_inventors + item->getWeight() > max_weight) {
        std::cout << "Перевищено максимальну вагу інвентаря! Предмет занадто важкий.\n";
        return false;
    }

    items.push_back(item);
    weight_inventors += item->getWeight();
    return true;
}

// Видалення предмета
bool Inventors::removeItem(const std::shared_ptr<BaseItem>& item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        weight_inventors -= (*it)->getWeight();
        items.erase(it);
        return true;
    }
    return false;
}

// Відображення інвентаря
void Inventors::draw(sf::RenderTarget& target) const {
    target.draw(background);

    // Малюємо клітинки
    for (const auto& cell : grid_cells) {
        target.draw(cell);
    }

    // Малюємо предмети
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Sprite sprite;
        sprite.setTexture(items[i]->getTexture());
        sprite.setScale(0.5f, 0.5f); // Масштабування текстури
        sprite.setPosition(grid_cells[i].getPosition());
        target.draw(sprite);
    }
}
