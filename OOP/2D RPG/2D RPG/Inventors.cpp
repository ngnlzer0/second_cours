#include "Inventors.h"
#include <stdexcept>
#include <iostream>

// Конструктор
Inventors::Inventors(unsigned int size, double maxWeight, const std::string& bgTexturePath)
    : size(size), maxWeight(maxWeight), currentWeight(0.0), draggedItem(nullptr), originalSlotIndex(-1), isDragging(false)
{
    slots.resize(size, nullptr); // Ініціалізація слотів

    if (!backgroundTexture.loadFromFile(bgTexturePath)) {
        throw std::runtime_error("Failed to load inventory background texture.");
    }
    background.setTexture(backgroundTexture);
    background.setScale({ 3.5,1.0 });
    background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
    background.setPosition(WIDHT_WINDOW / 2, background.getLocalBounds().height / 2); // Встановлюємо позицію фону (можна змінити за потреби)
    initializeCells(9, 50.0f, 10.0f);
}

// Ініціалізувати клітинки
// Ініціалізувати клітинки
void Inventors::initializeCells(unsigned int columns, float slotSize, float padding) {
    cells.clear();

    // Вираховуємо кількість рядків
    unsigned int rows = (size + columns - 1) / columns; // Округлення вгору

    // Розміри всієї групи клітинок
    float totalWidth = columns * slotSize + (columns - 1) * padding;
    float totalHeight = rows * slotSize + (rows - 1) * padding;

    // Вираховуємо верхній лівий кут для розміщення клітинок (центр фону мінус піврозміру групи клітинок)
    sf::FloatRect bgBounds = background.getLocalBounds();
    float startX = background.getPosition().x - totalWidth / 2;
    float startY = background.getPosition().y - totalHeight / 2;

    for (unsigned int i = 0; i < size; ++i) {
        sf::RectangleShape cell(sf::Vector2f(slotSize, slotSize));

        // Вираховуємо позицію клітинки
        float x = startX + (i % columns) * (slotSize + padding);
        float y = startY + (i / columns) * (slotSize + padding);

        cell.setPosition(x, y);
        cell.setFillColor(sf::Color::Transparent);  // Прозорий фон
        cell.setOutlineColor(sf::Color::White);     // Білий контур
        cell.setOutlineThickness(1.0f);

        cells.push_back(cell);
    }
}



// Додати предмет в інвентар
bool Inventors::addItem(const std::shared_ptr<BaseItem>& item) {
    if (!item) {
        std::cerr << "Cannot add item: Null pointer!" << std::endl;
        return false;
    }

    std::cout << "Trying to add item: " << item.get() << " (weight: " << item->getWeight() << ")" << std::endl;

    if (currentWeight + item->getWeight() > maxWeight) {
        std::cerr << "Cannot add item: Exceeds max weight!" << std::endl;
        return false;
    }

    for (unsigned int i = 0; i < size; ++i) {
        if (!slots[i]) { // Знаходимо перший вільний слот
            slots[i] = item;
            currentWeight += item->getWeight();

            std::cout << "Item added at index: " << i << ", Address: " << slots[i].get() << std::endl;
            return true;
        }
    }

    std::cerr << "Cannot add item: Inventory is full!" << std::endl;
    return false;
}


// Видалити предмет зі слоту
bool Inventors::removeItem(unsigned int index) {
    if (index >= size || !slots[index]) {
        std::cerr << "Cannot remove item: Invalid slot!" << std::endl;
        return false;
    }

    currentWeight -= slots[index]->getWeight();
    slots[index] = nullptr;
    return true;
}

// Отримати предмет зі слоту
std::shared_ptr<BaseItem> Inventors::getItem(unsigned int index) const {
    if (index >= size) {
        throw std::out_of_range("Invalid slot index.");
    }
    return slots[index];
}

// Отримати поточну вагу
double Inventors::getCurrentWeight() const {
    return currentWeight;
}

// Отримати максимальну вагу
double Inventors::getMaxWeight() const {
    return maxWeight;
}

// Відобразити інвентар
void Inventors::draw(sf::RenderWindow& window) const {
    window.draw(background); // Малюємо фон

    // Малюємо клітинки
    for (const auto& cell : cells) {
        window.draw(cell);
    }

    // Малюємо предмети, крім перетягуваного
    for (size_t i = 0; i < slots.size(); ++i) {
        if (slots[i] && slots[i] != draggedItem) { // Порівнюємо адреси
            const sf::RectangleShape& cell = cells[i]; // Поточна клітинка
            sf::Sprite* itemSprite = slots[i]->getSprite(); // Спрайт предмета

            if (itemSprite) {
                // Масштабування предмета з пропорціями
                float scaleFactor = std::min(
                    cell.getSize().x / itemSprite->getLocalBounds().width,
                    cell.getSize().y / itemSprite->getLocalBounds().height
                );
                itemSprite->setScale(scaleFactor, scaleFactor);

                // Центрування предмета в клітинці
                sf::Vector2f cellCenter = cell.getPosition() + cell.getSize() / 2.0f;
                sf::FloatRect spriteBounds = itemSprite->getLocalBounds();
                sf::Vector2f spriteOffset(
                    spriteBounds.width * itemSprite->getScale().x / 2.0f,
                    spriteBounds.height * itemSprite->getScale().y / 2.0f
                );

                itemSprite->setPosition(cellCenter - spriteOffset);

                // Малюємо предмет
                window.draw(*itemSprite);
            }
        }
    }

    // Малюємо перетягуваний предмет поверх інших
    if (draggedItem) {
        sf::Sprite* draggedSprite = draggedItem->getSprite();
        if (draggedSprite) {
            // Масштабування предмета з пропорціями клітинки (використовуємо першу клітинку як еталон)
            const sf::RectangleShape& referenceCell = cells[0];
            float scaleFactor = std::min(
                referenceCell.getSize().x / draggedSprite->getLocalBounds().width,
                referenceCell.getSize().y / draggedSprite->getLocalBounds().height
            );
            draggedSprite->setScale(scaleFactor, scaleFactor);

            // Центрування предмета відносно курсора миші
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::FloatRect spriteBounds = draggedSprite->getLocalBounds();
            sf::Vector2f spriteOffset(
                spriteBounds.width * draggedSprite->getScale().x / 2.0f,
                spriteBounds.height * draggedSprite->getScale().y / 2.0f
            );

            draggedSprite->setPosition(static_cast<sf::Vector2f>(mousePosition) - spriteOffset);

            // Малюємо предмет
            window.draw(*draggedSprite);
        }
    }
}



void Inventors::update(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); // Перетворення до координат вікна

    for (auto& cell : cells) {
        if (cell.getGlobalBounds().contains(worldPos)) {
            // Якщо мишка над клітинкою, зробимо її трохи темнішою
            cell.setFillColor(sf::Color(100, 100, 100, 150)); // Темний відтінок
        }
        else {
            // Повертаємо прозорість
            cell.setFillColor(sf::Color::Transparent);
        }
    }
}

void Inventors::handleInput(sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // Отримуємо координати миші в пікселях
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);  // Перетворюємо координати в координати світу

    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Перевіряємо, чи натиснули на предмет
            for (size_t i = 0; i < cells.size(); ++i) {
                if (cells[i].getGlobalBounds().contains(worldMousePos) && slots[i]) {
                    draggedItem = slots[i];  // Записуємо обраний предмет
                    originalSlotIndex = i;   // Записуємо індекс слоту
                    originalPosition = draggedItem->getSprite()->getPosition(); // Початкова позиція
                    isDragging = true; // Починаємо перетягування
                    break;
                }
            }
        }
        break;

    case sf::Event::MouseMoved:
        if (isDragging && draggedItem) {
            // Оновлюємо позицію перетягуваного предмета
            sf::Sprite* sprite = draggedItem->getSprite();
            sf::FloatRect spriteBounds = sprite->getLocalBounds();
            sf::Vector2f offset(spriteBounds.width * sprite->getScale().x / 2.0f,
                spriteBounds.height * sprite->getScale().y / 2.0f);

            sprite->setPosition(worldMousePos - offset);  // Ставимо предмет на курсор
        }
        break;

    case sf::Event::MouseButtonReleased:
        if (event.mouseButton.button == sf::Mouse::Left && isDragging) {
            isDragging = false; // Завершуємо перетягування

            int targetSlotIndex = -1;  // Індекс клітинки, на яку було відпущено

            // Перевіряємо, чи знаходиться предмет над якоюсь клітинкою
            for (size_t i = 0; i < cells.size(); ++i) {
                if (cells[i].getGlobalBounds().contains(worldMousePos)) {
                    targetSlotIndex = i;
                    break;
                }
            }

            // Якщо предмет знаходиться над клітинкою, що не є порожньою або клітинка не та сама
            if (targetSlotIndex != -1 && targetSlotIndex != originalSlotIndex) {
                // Якщо клітинка пуста, переміщуємо предмет
                if (!slots[targetSlotIndex]) {
                    slots[targetSlotIndex] = draggedItem;
                    slots[originalSlotIndex] = nullptr;
                }
                // Якщо клітинка зайнята, міняємо предмети місцями
                else {
                    std::swap(slots[targetSlotIndex], slots[originalSlotIndex]);
                }
            }
            else {
                // Якщо предмет не знаходиться над жодною клітинкою, повертаємо його на початкову позицію
                draggedItem->getSprite()->setPosition(originalPosition);
            }

            draggedItem = nullptr; // Завершуємо перетягування
        }
        break;
    }
}







