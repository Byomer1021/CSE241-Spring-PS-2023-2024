#include <iostream>

class HotDogStand {
private:
    int id;
    int hotDogsSold;
    static int totalHotDogsSold;

public:
    HotDogStand(int standId, int initialHotDogsSold) : id(standId), hotDogsSold(initialHotDogsSold) {}

    void justSold() {
        hotDogsSold++;
        totalHotDogsSold++;
    }
   
    int getHotDogsSold() const {
        return hotDogsSold;
    }

    static int getTotalHotDogsSold() {
        return totalHotDogsSold;
    }
};

// Initialize the static member variable outside the class
int HotDogStand::totalHotDogsSold = 0;

int main() {
    // Create three hot dog stands
    HotDogStand stand1(1, 0);
    HotDogStand stand2(2, 0);
    HotDogStand stand3(3, 0);

    // Simulate selling hot dogs
    stand1.justSold();
    stand1.justSold();
    stand2.justSold();
    stand3.justSold();
    stand3.justSold();
    stand3.justSold();

    // Print the number of hot dogs sold by each stand
    std::cout << "Stand 1 hot dogs sold: " << stand1.getHotDogsSold() << std::endl;
    std::cout << "Stand 2 hot dogs sold: " << stand2.getHotDogsSold() << std::endl;
    std::cout << "Stand 3 hot dogs sold: " << stand3.getHotDogsSold() << std::endl;

    // Print the total number of hot dogs sold by all stands
    std::cout << "Total hot dogs sold: " << HotDogStand::getTotalHotDogsSold() << std::endl;

    return 0;
}
