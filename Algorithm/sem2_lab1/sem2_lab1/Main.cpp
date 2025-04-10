#include <iostream>
#include <vector>
#include <unordered_map>

class Hash_entry {
public:
    std::vector<double> key;
    int hash;
    Hash_entry* next;

    Hash_entry(std::vector<double> k, int h) : key(k), hash(h), next(nullptr) {}
};

class Hash_table {
private:
    std::vector<Hash_entry*> table;
    std::unordered_map<int, std::vector<Hash_entry*>> subTables;
    int size;

public:
    Hash_table(int s) : size(s) {
        table.resize(size, nullptr);
    }

    int hash(const std::vector<double>& key) {
        const size_t prime = 173;
        size_t num_hash = 0;
        for (double val : key) {
            size_t bits = *reinterpret_cast<const size_t*>(&val);
            num_hash ^= num_hash * prime + 2654435 + (bits << 5) + (bits >> 3);
        }
        return num_hash % size;
    }

    void insert(std::vector<double> key) {
        int h = hash(key);

        if (table[h] == nullptr) {
            table[h] = new Hash_entry(key, h);
        }
        else {
            std::vector<Hash_entry*>& bucket = subTables[h];

            // Перевіряємо, чи вже є цей ключ у підтаблиці
            for (Hash_entry* entry : bucket) {
                if (entry->key == key) {
                    std::cerr << "Key already exists in the hash table.\n";
                    return;
                }
            }

            // Додаємо новий елемент у підхеш-таблицю
            bucket.push_back(new Hash_entry(key, h));

            // Якщо кількість елементів у підтаблиці зросла, створюємо новий розмір (квадрат кількості)
            int subTableSize = bucket.size() * bucket.size();
            std::vector<Hash_entry*> newSubTable(subTableSize, nullptr);

            // Реінсертимо всі елементи у нову підтаблицю
            for (Hash_entry* entry : bucket) {
                int subHash = entry->hash % subTableSize;
                while (newSubTable[subHash] != nullptr) {
                    subHash = (subHash + 1) % subTableSize;
                }
                newSubTable[subHash] = entry;
            }

            // Оновлюємо підхеш-таблицю
            subTables[h] = newSubTable;
        }
    }

    int getHash(std::vector<double> key) {
        int h = hash(key);

        // Перевіряємо основну таблицю
        if (table[h] && table[h]->key == key) {
            return table[h]->hash;
        }

        // Перевіряємо підхеш-таблицю
        if (subTables.find(h) != subTables.end()) {
            for (Hash_entry* entry : subTables[h]) {
                if (entry && entry->key == key) {
                    return entry->hash;
                }
            }
        }
        return -1;
    }

    void printHash() {
        std::cout << "Main Hash Table:\n";
        for (int i = 0; i < size; i++) {
            if (table[i] != nullptr) {
                std::cout << "Hash for { ";
                for (double val : table[i]->key) {
                    std::cout << val << " ";
                }
                std::cout << "}: " << table[i]->hash << std::endl;
            }
        }

        std::cout << "\nSub Hash Tables:\n";
        for (const auto& pair : subTables) {
            std::cout << "Sub-table for index " << pair.first << ":\n";
            for (const Hash_entry* entry : pair.second) {
                if (entry) {
                    std::cout << "  { ";
                    for (double val : entry->key) {
                        std::cout << val << " ";
                    }
                    std::cout << "}: " << entry->hash << std::endl;
                }
            }
        }
    }
};

int main() {

    std::vector<std::vector<double>> HESH_LIST = {
        {24.2, -1.195, 12, 123.52},
        {413.41124, 195, 3193.12, -0.577},
        {0, -1238.132, 303.412, 9.669},
        {885.231, -13.231, 0, 123.42}
        ,{-3232.2, -12, 0.0032}
    };

    Hash_table hashing(HESH_LIST.size());


    for (auto& vec : HESH_LIST) {
        hashing.insert(vec);
    }

    hashing.printHash();
    std::cout << "Cheking a vector {24.2, -1.195, 12, 123.52} in our hesh-table, and it index = " << hashing.getHash(std::vector<double>{24.2, -1.195, 12, 123.52}) << std::endl;
    std::cout << "Cheking a vector {24, -1.195, 12, 123.52} in our hesh-table, and it index = " << hashing.getHash(std::vector<double>{24, -1.195, 12, 123.52}) << std::endl;


    return 0;
}