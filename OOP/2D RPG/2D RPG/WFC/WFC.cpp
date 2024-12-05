#include "WFC.h"
#include <random>

/// Конструктор
WFCMapGenerator::WFCMapGenerator(int w, int h, const std::vector<Tile>& availableTiles)
    : width(w), height(h), tiles(availableTiles) {
    if (tiles.empty()) {
        throw std::runtime_error("Tile list cannot be empty.");
    }

    for (const auto& tile : tiles) {
        bool hasCompatibleSides = false;
        for (const auto& side : tile.compatibleWith) {
            if (!side.empty()) {
                hasCompatibleSides = true;
                break;
            }
        }
        if (!hasCompatibleSides) {
            throw std::runtime_error("Tile " + std::to_string(tile.id) + " has no compatible sides.");
        }
    }

    grid = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
    for (auto& row : grid) {
        for (auto& cell : row) {
            for (const auto& tile : tiles) {
                cell.possibleTiles.insert(tile.id);
            }
        }
    }
}

/// Колапсація клітинки
void WFCMapGenerator::collapseCell(int x, int y) {
    if (grid[y][x].possibleTiles.empty() || grid[y][x].possibleTiles.find(-1) != grid[y][x].possibleTiles.end()) {
        throw std::runtime_error("Cannot collapse cell with no valid tiles.");
    }

    // Вибір випадкового тайла
    std::random_device rd;
    std::mt19937 gen(rd());
    auto it = grid[y][x].possibleTiles.begin();
    std::advance(it, gen() % grid[y][x].possibleTiles.size());
    int selectedTile = *it;

    grid[y][x].possibleTiles = { selectedTile };
    grid[y][x].isCollapsed = true;

    propagate(x, y);
}

/// Пропагування змін
void WFCMapGenerator::propagate(int x, int y) {
    std::queue<std::pair<int, int>> toUpdate;
    toUpdate.push({ x, y });

    while (!toUpdate.empty()) {
        auto current = toUpdate.front();
        int cx = current.first, cy = current.second;
        toUpdate.pop();

        int collapsedTile = *grid[cy][cx].possibleTiles.begin();

        for (size_t dir = 0; dir < directions.size(); ++dir) {
            int nx = cx + directions[dir].first;
            int ny = cy + directions[dir].second;

            if (nx >= 0 && ny >= 0 && nx < width && ny < height && !grid[ny][nx].isCollapsed) {
                std::set<int> validTiles;
                for (int tile : grid[ny][nx].possibleTiles) {
                    if (std::find(tiles[tile].compatibleWith[(dir + 2) % 4].begin(),
                        tiles[tile].compatibleWith[(dir + 2) % 4].end(),
                        collapsedTile) != tiles[tile].compatibleWith[(dir + 2) % 4].end()) {
                        validTiles.insert(tile);
                    }
                }

                if (validTiles.empty()) {
                    // Позначаємо проблемну клітинку як "недійсну"
                    grid[ny][nx].possibleTiles = { -1 };
                    std::cerr << "Warning: No valid tiles during propagation at (" << nx << ", " << ny << "). Cell set to -1.\n";
                    continue;
                }

                if (validTiles != grid[ny][nx].possibleTiles) {
                    grid[ny][nx].possibleTiles = validTiles;
                    toUpdate.push({ nx, ny });
                }
            }
        }
    }
}

/// Знайти клітинку з мінімальною ентропією
std::pair<int, int> WFCMapGenerator::findMinEntropyCell() {
    int minEntropy = std::numeric_limits<int>::max();
    int x = -1, y = -1;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (!grid[i][j].isCollapsed &&
                grid[i][j].possibleTiles.size() < minEntropy &&
                grid[i][j].possibleTiles.find(-1) == grid[i][j].possibleTiles.end()) { // Пропустити -1
                minEntropy = grid[i][j].possibleTiles.size();
                x = j;
                y = i;
            }
        }
    }

    return { x, y };
}

/// Генерація карти
void WFCMapGenerator::generate() {
    while (true) {
        auto cell = findMinEntropyCell();
        int x = cell.first;
        int y = cell.second;

        if (x == -1 && y == -1)
            break;

        try {
            collapseCell(x, y);
        }
        catch (const std::runtime_error&) {
            std::cerr << "Regenerating map due to invalid state...\n";

            // Очистити сітку та повторно ініціалізувати
            grid = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
            for (auto& row : grid) {
                for (auto& cell : row) {
                    for (const auto& tile : tiles) {
                        cell.possibleTiles.insert(tile.id);
                    }
                }
            }

            continue; // Перегенерація
        }
    }
}


/// Друк карти
void WFCMapGenerator::printGrid() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.isCollapsed) {
                std::cout << *cell.possibleTiles.begin() << " ";
            }
            else {
                std::cout << "? ";
            }
        }
        std::cout << "\n";
    }
}
