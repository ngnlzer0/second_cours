#pragma once
#include <vector>

class EntropyCell {
public:
    EntropyCell(const std::vector<int>& initialOptions);

    int getEntropy() const;
    bool isCollapsed() const;
    void collapse(int chosenTile);
    const std::vector<int>& getOptions() const;
    void setOptions(const std::vector<int>& newOptions);

private:
    std::vector<int> options;
    int collapsedTile;
};
