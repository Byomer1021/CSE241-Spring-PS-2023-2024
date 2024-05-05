#include <iostream>
#include <string>

template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    // Default constructor
    Pair() : first(T1()), second(T2()) {}

    // Parameterized constructor
    Pair(const T1& firstValue, const T2& secondValue) : first(firstValue), second(secondValue) {}

    // Getters
    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }

    // Setters
    void setFirst(const T1& value) { first = value; }
    void setSecond(const T2& value) { second = value; }
};

int main() {
    // Test with int and string
    Pair<int, std::string> intStringPair(1, "Apple");
    std::cout << "Pair: " << intStringPair.getFirst() << " and " << intStringPair.getSecond() << std::endl;

    // Test with double and char
    Pair<double, char> doubleCharPair(3.14, 'A');
    std::cout << "Pair: " << doubleCharPair.getFirst() << " and " << doubleCharPair.getSecond() << std::endl;

    // Test with string and bool
    Pair<std::string, bool> stringBoolPair("Test", true);
    std::cout << "Pair: " << stringBoolPair.getFirst() << " and " << stringBoolPair.getSecond() << std::endl;

    return 0;
}
