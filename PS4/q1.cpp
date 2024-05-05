#include <iostream>
using namespace std;

class Vector2D
{

public:
	// Constructor
	Vector2D(int x_val, int y_val) : x(x_val), y(y_val) {}

	// Getter for x component
	int GetX() const
	{
		return x;
	}

	// Setter for x component
	void SetX(int x_val)
	{
		x = x_val;
	}

	// Getter for y component
	int GetY() const
	{
		return y;
	}

	// Setter for y component
	void SetY(int y_val)
	{
		y = y_val;
	}

	// Overloading * operator for dot product
	int operator*(const Vector2D &other) const
	{
		return (x * other.x) + (y * other.y);
	}

private:
	int x;
	int y;
};

int main()
{
	// Some test vectors
	Vector2D v1(10, 0), v2(0, 10), v3(10, 10), v4(5, 4);
	cout << "(" << v1.GetX() << "," << v1.GetY() << ") * (" << v2.GetX() << "," << v2.GetY() << ") = " << (v1 * v2) << endl;
	cout << "(" << v2.GetX() << "," << v2.GetY() << ") * (" << v3.GetX() << "," << v3.GetY() << ") = " << (v2 * v3) << endl;
	cout << "(" << v3.GetX() << "," << v3.GetY() << ") * (" << v4.GetX() << "," << v4.GetY() << ") = " << (v3 * v4) << endl;
	return 0;
}
