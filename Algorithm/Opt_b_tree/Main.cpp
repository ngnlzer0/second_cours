#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <cassert>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <tuple>
#include <numeric>     // для std::iota
#include <functional>  // для std::function


class Rational {
private:
    int numerator;
    int denominator;

    void reduce() {
        int g = gcd(abs(numerator), abs(denominator));
        numerator /= g;
        denominator /= g;

        // Знак зберігається тільки в чисельнику
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    int gcd(int a, int b) const {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

public:
    Rational(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denom == 0)
            throw std::invalid_argument("Denominator cannot be zero");
        reduce();
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    Rational operator+(const Rational& other) const {
        return Rational(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Rational operator-(const Rational& other) const {
        return Rational(
            numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Rational operator*(const Rational& other) const {
        return Rational(numerator * other.numerator, denominator * other.denominator);
    }

    Rational operator/(const Rational& other) const {
        if (other.numerator == 0)
            throw std::invalid_argument("Division by zero");
        return Rational(numerator * other.denominator, denominator * other.numerator);
    }

    bool operator==(const Rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator<=(const Rational& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Rational& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Rational& other) const {
        return !(*this < other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        os << r.numerator;
        if (r.denominator != 1)
            os << "/" << r.denominator;
        return os;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << numerator;
        if (denominator != 1)
            oss << "/" << denominator;
        return oss.str();
    }

};

struct OBSTNode {
    Rational key;
    double prob;
    OBSTNode* left = nullptr;
    OBSTNode* right = nullptr;

    OBSTNode(Rational k, double p) : key(k), prob(p) {}
};

struct KeyInfo {
    Rational key;
    double baseWeight;
    double accessFreq;

    double total() const { return baseWeight + accessFreq; }
};

class AdaptiveOBST {
    std::vector<KeyInfo> entries;
    OBSTNode* root = nullptr;
    int accessCount = 0;
    const int REBUILD_THRESHOLD = 3;

public:
    void insert(const Rational& key, double baseWeight = 1.0) {
        auto it = std::find_if(entries.begin(), entries.end(),
            [&](const KeyInfo& e) { return e.key == key; });

        if (it == entries.end()) {
            entries.push_back({ key, baseWeight, 0.0 });
            rebuild();
        }
    }

    void access(const Rational& key) {
        auto it = std::find_if(entries.begin(), entries.end(),
            [&](const KeyInfo& e) { return e.key == key; });

        if (it != entries.end()) {
            it->accessFreq += 1.0;
            accessCount++;
            if (accessCount >= REBUILD_THRESHOLD) {
                rebuild();
                accessCount = 0;
            }
        }
    }

    void rebuild() {
        std::sort(entries.begin(), entries.end(),
            [](const KeyInfo& a, const KeyInfo& b) {
                return a.key < b.key;
            });

        double total = 0.0;
        for (const auto& e : entries) total += e.total();
        std::vector<double> probs;
        for (const auto& e : entries) probs.push_back(e.total() / total);

        root = buildOBST(entries, probs);
    }

    OBSTNode* buildOBST(const std::vector<KeyInfo>& keys, const std::vector<double>& p) {
        int n = (int)p.size();
        std::vector<std::vector<double>> e(n, std::vector<double>(n));
        std::vector<std::vector<double>> w(n, std::vector<double>(n));
        std::vector<std::vector<int>> rootIdx(n, std::vector<int>(n));

        for (int i = 0; i < n; ++i) {
            e[i][i] = p[i];
            w[i][i] = p[i];
            rootIdx[i][i] = i;
        }

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                e[i][j] = std::numeric_limits<double>::infinity();
                w[i][j] = w[i][j - 1] + p[j];

                for (int r = i; r <= j; ++r) {
                    double cost = (r > i ? e[i][r - 1] : 0) +
                        (r < j ? e[r + 1][j] : 0) +
                        w[i][j];
                    if (cost < e[i][j]) {
                        e[i][j] = cost;
                        rootIdx[i][j] = r;
                    }
                }
            }
        }

        std::function<OBSTNode* (int, int)> build = [&](int i, int j) -> OBSTNode* {
            if (i > j) return nullptr;
            int r = rootIdx[i][j];
            OBSTNode* node = new OBSTNode(keys[r].key, p[r]);
            node->left = build(i, r - 1);
            node->right = build(r + 1, j);
            return node;
            };

        return build(0, n - 1);
    }

    void printFrequencies() const {
        std::cout << "Key\tBase\tAccess\tTotal\n";
        for (const auto& e : entries) {
            std::cout << e.key << "\t" << e.baseWeight << "\t" << e.accessFreq << "\t" << e.total() << "\n";
        }
    }

    void printTree(OBSTNode* node = nullptr, int depth = 0) const {
        if (!node) node = root;
        if (!node) return;
        printTree(node->right, depth + 1);
        std::cout << std::string(depth * 4, ' ') << node->key << " (" << node->prob << ")\n";
        printTree(node->left, depth + 1);
    }

    void exportToDOT(const std::string& filename) const {
        std::ofstream out(filename);
        out << "digraph G {\n";
        exportDOT(out, root);
        out << "}\n";
        out.close();
    }

    void exportDOT(std::ofstream& out, OBSTNode* node) const {
        if (!node) return;
        out << "\t\"" << node->key << " (" << node->prob << ")\" [style=filled, fillcolor=black, fontcolor=white];\n";
        if (node->left) {
            out << "\t\"" << node->key << " (" << node->prob << ")\" -> \""
                << node->left->key << " (" << node->left->prob << ")\";\n";
            exportDOT(out, node->left);
        }
        if (node->right) {
            out << "\t\"" << node->key << " (" << node->prob << ")\" -> \""
                << node->right->key << " (" << node->right->prob << ")\";\n";
            exportDOT(out, node->right);
        }
    }
};


void generateTreeImage(const std::string& dotFilename) {
    std::string outputFilename = dotFilename.substr(0, dotFilename.find_last_of('.')) + ".png";
    std::string dotCommand = "dot -Tpng " + dotFilename + " -o " + outputFilename;

    int result = system(dotCommand.c_str());
    if (result != 0) {
        std::cerr << "❌ error runing Graphviz\n";
    }
    else {
        std::cout << "image save as: " << outputFilename << std::endl;
    }
}

void openFile(const std::string& filename) {
#ifdef _WIN32
    std::string command = "start " + filename;
#elif __APPLE__
    std::string command = "open " + filename;
#else
    std::string command = "xdg-open " + filename;
#endif

    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "error dont open file " << filename << std::endl;
    }
}


// Демонстрація
int main() {
    AdaptiveOBST tree;

    // Додаємо ключі
    tree.insert(Rational(5,2),15);
    tree.insert(Rational(3,10),25);
    tree.insert(Rational(25,12),5);
    tree.insert(Rational(1,2),30);


    tree.exportToDOT("aatree.dot");
    generateTreeImage("aatree.dot");
    openFile("aatree.png");

    for (int i = 0;i < 5;i++)
    {
        tree.access(Rational(3, 10));
    }
    for (int i = 0; i < 10; i++)
    {
        tree.access(Rational(1, 2));
    }
    for (int i = 0; i < 30; i++)
    {
        tree.access(Rational(5, 2));
    }


    tree.exportToDOT("aatree_1.dot");
    generateTreeImage("aatree_1.dot");
    openFile("aatree_1.png");


    for (int i = 0; i < 90; i++)
    {
        tree.access(Rational(25, 12));
    }

    tree.exportToDOT("aatree_12.dot");
    generateTreeImage("aatree_12.dot");
    openFile("aatree_12.png");

    return 0;
}
