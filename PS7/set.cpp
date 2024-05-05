#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Include this for std::find

template<typename T>
class ItemSet {
private:
    std::vector<T> items;

public:
    // Add a new item to the set
    void addItem(const T& item) {
        // Check if the item already exists in the set
        if (std::find(items.begin(), items.end(), item) == items.end()) {
            items.push_back(item);
        }
    }

    // Get the number of items in the set
    size_t getSize() const {
        return items.size();
    }

    // Get a pointer to a dynamically created array containing each item in the set
    T* getItemsArray() const {
        T* array = new T[items.size()];
        for (size_t i = 0; i < items.size(); ++i) {
            array[i] = items[i];
        }
        return array;
    }
};

int main() {
    // Test with integers
    ItemSet<int> intSet;
    intSet.addItem(1);
    intSet.addItem(2);
    intSet.addItem(2); // Duplicate, won't be added
    intSet.addItem(3);

    std::cout << "Int set size: " << intSet.getSize() << std::endl;
    int* intArray = intSet.getItemsArray();
    for (size_t i = 0; i < intSet.getSize(); i++) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
    delete[] intArray;

    // Test with strings
    ItemSet<std::string> stringSet;
    stringSet.addItem("CSE241");
    stringSet.addItem("OOP");
    stringSet.addItem("CSE241"); // Duplicate, won't be added

    std::cout << "String set size: " << stringSet.getSize() << std::endl;
    std::string* stringArray = stringSet.getItemsArray();
    for (size_t i = 0; i < stringSet.getSize(); i++) {
        std::cout << stringArray[i] << " ";
    }
    std::cout << std::endl;
    delete[] stringArray;

    return 0;
}
