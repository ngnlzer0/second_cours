#include <iostream>
#include <string>
#include <vector>

void naiveSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            std::cout << "naive algoritm Pattern found at index " << i << std::endl;
        }
    }
}

std::vector<int> preprocess_Bad_Character(const std::string& pattern) {
    const int ALPHABET_SIZE = 256;
    std::vector<int> badChar(ALPHABET_SIZE, -1);
    for (int i = 0; i < pattern.size(); i++) {
        badChar[pattern[i]] = i;
    }
    return badChar;
}

void boyer_Moore_Search(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> badChar = preprocess_Bad_Character(pattern);

    int s = 0; // s is the shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            std::cout << "boyer_moore Pattern found at index " << s << std::endl;
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else {
            s += std::max(1, j - badChar[text[s + j]]);
        }
    }
}

std::vector<int> compute_Prefix_Function(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> prefix(m, 0);
    int k = 0;

    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = prefix[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            k++;
        }
        prefix[i] = k;
    }
    return prefix;
}

void KMP_search(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> prefix = compute_Prefix_Function(pattern);
    int q = 0;

    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = prefix[q - 1];
        }
        if (pattern[q] == text[i]) {
            q++;
        }
        if (q == m) {
            std::cout << "KMP_algoritm Pattern found at index " << i - m + 1 << std::endl;
            q = prefix[q - 1];
        }
    }
}

int main() {
    std::string text = "This mirror and integral frame are die formed from a single sheet of type 400 stainless steel polished to a mirror finish.";
    std::string pattern = " a single sheet ";
    naiveSearch(text, pattern);

    std::string textB = "This mirror and integral frame are die formed from a single sheet of type 400 stainless steel polished to a mirror finish.";
    std::string patternB = " a single sheet ";
    boyer_Moore_Search(textB, patternB);

    std::string textKMP = "This mirror and integral frame are die formed from a single sheet of type 400 stainless steel polished to a mirror finish.";
    std::string patternKMP = " a single sheet ";
    KMP_search(textKMP, patternKMP);

    return 0;
}
