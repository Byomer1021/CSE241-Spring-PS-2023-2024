#include <iostream>
#include <cmath>
using namespace std;

class MyInteger
{

public:
	// Constructor
	MyInteger(int val) : value(val) {}

	// Getter for value
	int GetValue() const
	{
		return value;
	}

	// Setter for value
	void SetValue(int val)
	{
		value = val;
	}

	// Overloading [] operator
	int operator[](int index) const
	{
		if (index < 0)
			return -1;
		int divisor = pow(10, index);
		return (value / divisor) % 10;
	}

private:
	int value;
};

int main()
{
	// Some test numbers
	MyInteger num(418);
	cout << num[0] << " " << num[1] << " " << num[2] << endl;
	cout << num[3] << endl;
	cout << num[-1] << endl;
	return 0;
}
