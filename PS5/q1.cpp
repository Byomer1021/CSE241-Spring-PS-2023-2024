#include <iostream>
using namespace std;

class Polynomial {
private:
    double* coeffs;
    int size;

public:
    Polynomial() : coeffs(nullptr), size(0) {}

    Polynomial(const double coefficients[], int degree) : size(degree + 1) {
        coeffs = new double[size];
        for (int i = 0; i < size; i++) {
            coeffs[i] = coefficients[i];
        }
    }

    Polynomial(const Polynomial& other) : size(other.size) {
        coeffs = new double[size];
        for (int i = 0; i < size; i++) {
            coeffs[i] = other.coeffs[i];
        }
    }

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            delete[] coeffs;
            size = other.size;
            coeffs = new double[size];
            for (int i = 0; i < size; i++) {
                coeffs[i] = other.coeffs[i];
            }
        }
        return *this;
    }

    ~Polynomial() {
        delete[] coeffs;
    }

    double& operator[](int degree) {
        return coeffs[degree];
    }

    const double& operator[](int degree) const {
        return coeffs[degree];
    }

    Polynomial operator+(const Polynomial& other) const {
        int max_size = max(size, other.size);
        double result_coeffs[max_size] = {0};
        for (int i = 0; i < max_size; i++) {
            double a = (i < size) ? coeffs[i] : 0;
            double b = (i < other.size) ? other.coeffs[i] : 0;
            result_coeffs[i] = a + b;
        }
        return Polynomial(result_coeffs, max_size - 1);
    }

    Polynomial operator-(const Polynomial& other) const {
        int max_size = max(size, other.size);
        double result_coeffs[max_size] = {0};
        for (int i = 0; i < max_size; i++) {
            double a = (i < size) ? coeffs[i] : 0;
            double b = (i < other.size) ? other.coeffs[i] : 0;
            result_coeffs[i] = a - b;
        }
        return Polynomial(result_coeffs, max_size - 1);
    }

    Polynomial operator*(const Polynomial& other) const {
        int result_size = size + other.size - 1;
        double* result_coeffs = new double[result_size]();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < other.size; j++) {
                result_coeffs[i + j] += coeffs[i] * other.coeffs[j];
            }
        }
        Polynomial result(result_coeffs, result_size - 1);
        delete[] result_coeffs;
        return result;
    }

    double evaluate(double x) const {
        double result = 0;
        double x_pow = 1;
        for (int i = 0; i < size; i++) {
            result += coeffs[i] * x_pow;
            x_pow *= x;
        }
        return result;
    }

    int mySize() const {
        return size;
    }
};

int main() {
    Polynomial empty;
    double one[] = {1};
    Polynomial One(one, 1);
    double quad[] = {3, 2, 1};
    double cubic[] = {1, 2, 0, 3};
    Polynomial q(quad, 3); // q is 3 + 2*x + x*x
    Polynomial c(cubic, 4); // c is 1 + 2*x + 0*x*x + 3*x*x*x
    Polynomial p = q; // test copy constructor
    Polynomial r;
    r = q; //test operator=
    r = c;

    cout << "Polynomial q " << endl;
    for(int i = 0; i < q.mySize(); i++)
        cout << "term with degree " << i << " has coefficient " << q[i] << endl;

    cout << "Polynomial c " << endl;
    for(int i = 0; i < c.mySize(); i++)
        cout << "term with degree " << i << " has coefficient " << c[i] << endl;

    cout << "value of q(2) is " << q.evaluate(2) << endl;
    cout << "value of p(2) is " << p.evaluate(2) << endl;
    cout << "value of r(2) is " << r.evaluate(2) << endl;
    cout << "value of c(2) is " << c.evaluate(2) << endl;

    r = q + c;
    cout << "value of (q + c)(2) is " << r.evaluate(2) << endl;
    r = q - c;
    cout << "value of (q - c)(2) is " << r.evaluate(2) << endl;
    r = q * c;
    cout << "size of q*c is " << r.mySize() << endl;
    cout << "Polynomial r (= q*c) " << endl;
    for(int i = 0; i < r.mySize(); i++)
        cout << "term with degree " << i << " has coefficient " << r[i] << endl;
    cout << "value of (q * c)(2) is " << r.evaluate(2) << endl;
    return 0;
}
