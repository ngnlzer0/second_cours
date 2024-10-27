#include "EntropyCell.h"

EntropyCell::EntropyCell(const std::vector<int>& initialOptions)
    : options(initialOptions), collapsedTile(-1) {
}

int EntropyCell::getEntropy() const {
    return options.size();
}

bool EntropyCell::isCollapsed() const {
    return collapsedTile != -1;
}

void EntropyCell::collapse(int chosenTile) {
    options = { chosenTile };
    collapsedTile = chosenTile;
}

const std::vector<int>& EntropyCell::getOptions() const {
    return options;
}

void EntropyCell::setOptions(const std::vector<int>& newOptions) {
    options = newOptions;
}
