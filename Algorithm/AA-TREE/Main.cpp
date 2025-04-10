#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdlib>  // для system()

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

class AATree {
private:
    struct Node {
        Rational value;
        Node* left;
        Node* right;
        int level;

        Node(const Rational& val)
            : value(val), left(nullptr), right(nullptr), level(1) {
        }
    };

    Node* root = nullptr;

    Node* skew(Node* node) {
        if (!node || !node->left) return node;
        if (node->left->level == node->level) {
            Node* L = node->left;
            node->left = L->right;
            L->right = node;
            return L;
        }
        return node;
    }

    Node* split(Node* node) {
        if (!node || !node->right || !node->right->right) return node;
        if (node->right->right->level == node->level) {
            Node* R = node->right;
            node->right = R->left;
            R->left = node;
            R->level += 1;
            return R;
        }
        return node;
    }

    Node* insert(Node* node, const Rational& value) {
        if (!node) return new Node(value); // вставка

        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        else {
            // дублікати
            return node;
        }

        node = skew(node);
        node = split(node);
        return node;
    }

    void inOrder(Node* node) const {
        if (!node) return;
        inOrder(node->left);
        std::cout << node->value << " ";
        inOrder(node->right);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void printTree(Node* node, int indent = 0) const {
        if (!node) return;
        if (node->right) printTree(node->right, indent + 4);
        if (indent) std::cout << std::string(indent, ' ');
        std::cout << "[" << node->value << ", lvl=" << node->level << "]\n";
        if (node->left) printTree(node->left, indent + 4);
    }

    std::string nodeID(Node* node) const {
        std::ostringstream oss;
        oss << "n" << reinterpret_cast<uintptr_t>(node);
        return oss.str();
    }

    void exportDOT(Node* node, std::ofstream& out) const {
        if (!node) return;
        std::string nodeId = "\"" + nodeID(node) + "\"";
        out << "    " << nodeId << " [label=\"" << node->value << "\\nL" << node->level << "\"]\n";

        if (node->left) {
            std::string leftId = "\"" + nodeID(node->left) + "\"";
            out << "    " << nodeId << " -> " << leftId << ";\n";
            exportDOT(node->left, out);
        }

        if (node->right) {
            std::string rightId = "\"" + nodeID(node->right) + "\"";
            out << "    " << nodeId << " -> " << rightId;
            if (node->level == node->right->level)
                out << " [color=red]";
            out << ";\n";
            exportDOT(node->right, out);
        }
    }

    Node* decreaseLevel(Node* node) {
        int expected = 1;
        if (node->left && node->right)
            expected = std::min(node->left->level, node->right->level) + 1;
        else if (node->left)
            expected = node->left->level + 1;
        else if (node->right)
            expected = node->right->level + 1;

        if (expected < node->level) {
            node->level = expected;
            if (node->right && node->right->level > expected)
                node->right->level = expected;
        }
        return node;
    }

    Node* remove(Node* node, const Rational& val) {
        if (!node) return nullptr;

        if (val < node->value) node->left = remove(node->left, val);
        else if (val > node->value) node->right = remove(node->right, val);
        else {
            if (!node->left || !node->right) {
                Node* tmp = node->left ? node->left : node->right;
                delete node;
                return tmp;
            }
            else {
                Node* succ = node->right;
                while (succ->left)
                    succ = succ->left;
                node->value = succ->value;
                node->right = remove(node->right, succ->value);
            }
        }

        node = decreaseLevel(node);
        node = skew(node);
        node = split(node);

        // рекурсивно балансувати праве піддерево
        if (node->right) {
            node->right = skew(node->right);
            node->right = split(node->right);
            if (node->right->right) {
                node->right->right = skew(node->right->right);
                node->right->right = split(node->right->right);
            }
        }

        return node;
    }

    bool validate(Node* node, int& height, std::string& error, const Rational* min = nullptr, const Rational* max = nullptr) const {
        if (!node) {
            height = 0;
            return true;
        }

        if ((min && node->value <= *min) || (max && node->value >= *max)) {
            error = "BST property violated at value " + node->value.toString();
            return false;
        }

        int lh, rh;
        if (!validate(node->left, lh, error, min, &node->value)) return false;
        if (!validate(node->right, rh, error, &node->value, max)) return false;

        if (node->left && node->left->level >= node->level) {
            error = "Left child level >= parent at value " + node->value.toString();
            return false;
        }

        if (node->right && node->right->level > node->level) {
            error = "Right child level > parent at value " + node->value.toString();
            return false;
        }

        if (node->right && node->right->right && node->right->right->level == node->level) {
            error = "Consecutive right links at same level at value " + node->value.toString();
            return false;
        }

        height = std::max(lh, rh) + 1;
        return true;
    }

    bool contains(Node* node, const Rational& value) const {
        if (!node) return false;
        if (value < node->value) return contains(node->left, value);
        if (value > node->value) return contains(node->right, value);
        return true; // знайдено
    }

public:
    ~AATree() {
        clear(root);
    }

    void remove(const Rational& val) {
        root = remove(root, val);
        assert(validate());
    }

    bool validate() const {
        int h;
        std::string err;
        if (!validate(root, h, err)) {
            std::cerr << "Tree validation failed: " << err << "\n";
            return false;
        }
        return true;
    }

    bool contains(const Rational& value) const {
        return contains(root, value);
    }

    void insert(const Rational& val) {
        root = insert(root, val);
        assert(validate());
    }

    void printInOrder() const {
        inOrder(root);
        std::cout << std::endl;
    }

    void printTree() const {
        std::cout << "\nAA Tree structure:\n";
        printTree(root);
    }

    void exportToDOT(const std::string& filename) const {
        std::ofstream out(filename);
        out << "digraph AATree {\n";
        out << "    node [shape=circle style=filled fillcolor=black fontcolor=white];\n";
        exportDOT(root, out);
        out << "}\n";
        out.close();
        std::cout << "DOT-graph saved to " << filename << std::endl;
    }
};

void generateTreeImage(std::string dotFilename) {
    // Формуємо ім’я вихідного PNG-файлу
    std::string outputFilename = dotFilename.substr(0, dotFilename.find_last_of('.')) + ".png";

    // Формуємо команду для виконання
    std::string dotCommand = "dot -Tpng " + dotFilename + " -o " + outputFilename;

    // Виконуємо команду
    int result = system(dotCommand.c_str());

    if (result != 0) {
        std::cerr << "Error for start Graphviz comands\n";
    }
    else {
        std::cout << outputFilename << " sucses complete\n";
    }
}

void openFile(const std::string& filename) {
#ifdef _WIN32
    std::string command = "start " + filename; // Windows
#elif __APPLE__
    std::string command = "open " + filename;  // macOS
#else
    std::string command = "xdg-open " + filename; // Linux
#endif

    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
    }
}


int main() {

    AATree tree;
    tree.insert(Rational(1, 2));
    tree.insert(Rational(1, 3));
    tree.insert(Rational(3, 4));
    tree.exportToDOT("aatree.dot");
    generateTreeImage("aatree.dot");
    openFile("aatree.png");


    tree.insert(Rational(5, 6));
    tree.insert(Rational(8, 9));
    tree.exportToDOT("aatree_add2.dot");
    generateTreeImage("aatree_add2.dot");
    openFile("aatree_add2.png");

    tree.remove(Rational(5, 6));
    tree.exportToDOT("aatree_del1.dot");
    generateTreeImage("aatree_del1.dot");
    openFile("aatree_del1.png");

    tree.insert(Rational(1, 6));
    tree.insert(Rational(12, 9));
    tree.exportToDOT("aatree_add22.dot");
    generateTreeImage("aatree_add22.dot");
    openFile("aatree_add22.png");

    /*
    AATree tree;
    tree.insert(Rational(1, 2));
    tree.insert(Rational(3, 4));
    tree.insert(Rational(1, 3));
    tree.insert(Rational(5, 6));
    tree.insert(Rational(2, 3));
    tree.insert(Rational(5, 12));
   
    tree.printTree();

    tree.exportToDOT("aatree.dot");
    generateTreeImage("aatree.dot");
    openFile("aatree.png");     

    tree.insert(Rational(18, 34));
    tree.validate();

    tree.exportToDOT("aatree_addel.dot");
    generateTreeImage("aatree_addel.dot");
    openFile("aatree_addel.png");   

    tree.remove(Rational(3, 4));
    tree.validate();
    tree.exportToDOT("aatree_addel1.dot");
    generateTreeImage("aatree_addel1.dot");
    openFile("aatree_addel1.png");    


    tree.insert(Rational(22, 39));
    tree.insert(Rational(13, 47));
    tree.insert(Rational(14, 32));
    tree.insert(Rational(55, 69));
    tree.insert(Rational(21, 37));


    tree.exportToDOT("aatree_new.dot");
    generateTreeImage("aatree_new.dot");
    openFile("aatree_new.png");     // відкриває PNG

    if (tree.contains(Rational(1, 2))) {
        std::cout << "found 1/2\n";
    }
    else {
        std::cout << "not found 1/2\n";
    }

    if (tree.contains(Rational(121, 17))) {
        std::cout << "found 121/17\n";
    }
    else {
        std::cout << "not found 121/17\n";
    }
    tree.remove(Rational(22, 39));
    tree.remove(Rational(2, 3));

    tree.exportToDOT("aatree_new22.dot");
    generateTreeImage("aatree_new22.dot");
    openFile("aatree_new22.png");     // відкриває PNG
	*/

    return 0;
}
