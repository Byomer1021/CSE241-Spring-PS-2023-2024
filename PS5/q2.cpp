#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int numClasses;
    string* classList;

public:
    Student() : name(""), numClasses(0), classList(nullptr) {}

    Student(const Student& other) {
        name = other.name;
        numClasses = other.numClasses;
        classList = new string[numClasses];
        for (int i = 0; i < numClasses; i++) {
            classList[i] = other.classList[i];
        }
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            delete[] classList;
            name = other.name;
            numClasses = other.numClasses;
            classList = new string[numClasses];
            for (int i = 0; i < numClasses; i++) {
                classList[i] = other.classList[i];
            }
        }
        return *this;
    }

    ~Student() {
        delete[] classList;
    }

    void InputData() {
        cout << "Enter student's name: ";
        getline(cin, name);
        cout << "Enter number of classes: ";
        cin >> numClasses;
        cin.ignore();
        classList = new string[numClasses];
        cout << "Enter the names of the classes:" << endl;
        for (int i = 0; i < numClasses; i++) {
            getline(cin, classList[i]);
        }
    }

    void OutputData() const {
        cout << "Student's name: " << name << endl;
        cout << "Classes:" << endl;
        for (int i = 0; i < numClasses; i++) {
            cout << classList[i] << endl;
        }
    }

    void ResetClasses() {
        delete[] classList;
        classList = nullptr;
        numClasses = 0;
    }
};

int main() {
    Student s1, s2;
    s1.InputData(); // Input data for student 1
    cout << "Student 1's data:" << endl;
    s1.OutputData(); // Output data for student 1
    cout << endl;

    s2 = s1;
    cout << "Student 2's data after assignment from student 1:" << endl;
    s2.OutputData(); // Should output same data as for student 1

    s1.ResetClasses();
    cout << "Student 1's data after reset:" << endl;
    s1.OutputData(); // Should have no classes

    cout << "Student 2's data, should still have original classes:" << endl;
    s2.OutputData(); // Should still have original classes

    cout << endl;
    return 0;
}
