#include <iostream>
#include <vector>

int findSurvivorPosition(int n) {
    std::vector<int> suitors(n);
    for (int i = 0; i < n; ++i) {
        suitors[i] = i + 1; // Assigning numbers to suitors
    }

    int index = 0; // Starting position
    while (suitors.size() > 1) {
        index = (index + 2) % suitors.size(); // Counting three suitors
        suitors.erase(suitors.begin() + index); // Eliminate the suitor
    }

    return suitors[0]; // Return the remaining suitor's number
}

int main() {
    int n;
    std::cout << "Enter the number of suitors: ";
    std::cin >> n;

    int position = findSurvivorPosition(n);
    std::cout << "The winning suitor's number is: " << position << std::endl;

    return 0;
}
