#include <iostream>
#include <string>
#include <vector>

using namespace std;

class A {

public:
	A(string name) : s(name) {
		cout << "ctor() for " << s << endl;
	}

	//copy ctor
	A(const A& other) : s(other.s) {
		cout << "copy constructor for " << s << endl;
	}

	//assign operator
	A& operator=(const A& other) {
		cout << "assign operator for " << s << endl;
		if (this != &other) {
			s = other.s;
		}
		return *this;
	}

	//move constructor
	A(A&& other) : s(std::move(other.s)) {
		cout << "move constructor " << s << endl;
	}

	//move operator
	A& operator=(const A&& other){
		cout << "move operator " << s << endl;
		if (this != &other) {
			s = std::move(other.s);
		}
		return *this;
	}

	string printObj() { return s; }

private:
	string s;
};

A temp(A other) {
	return other;
}

class B : public A
{
public:
	B(string name) :A(name) {}
};

class C : public B {
public:
	C(string name) :B(name) { }
	~C() {}; // Since we have our own destructor for C, the move won't call C::(C&&) instead it used copy constructor
};


class D : public B {
public:
	D(string name) :B(name) { }
	~D() {}; 
	D(D&&) = default;
};


int main() {

	A a1{ "A1" };
	A a2{ "A2" };
	A a3{ "A3" };
	A a4{ "A4" };

	cout << "-------------------------------" << endl;
	vector<A> allClass;
	allClass.push_back(std::move(a1));
	allClass.push_back(std::move(a2));
	allClass.push_back(std::move(a3));
	cout << "-------------------------------" << endl;
	A a10("A10");
	A a11 = std::move(a10);

	cout << "-------------------------------" << endl;

	a3 = a2;
	a4 = std::move(a3); // move operator !! if not defined it will use normal copy operator

	cout << "-------------------------------" << endl;

	cout << "after move() : a3 = " << a3.printObj() << endl; // a1 was moved to a6
	cout << "after move() : a4 = " << a4.printObj() << endl;

	cout << "-------------------------------" << endl;
	//move constructor from rvalue temporary
	A a5 = temp(a4);

	cout << "-------------------------------" << endl;

	//move-constructor from lvalue
	cout << "before move() a1 =" << a1.printObj() << endl;
	A a6 = std::move(a1);
	cout << "after move() : a1 = " << a1.printObj() << endl; // a1 was moved to a6
	cout << "after move() : a6 = " << a6.printObj() << endl;

	cout << "-------------------------------" << endl;

	B b1("B1");
	B b2 = std::move(b1);

	cout << "-------------------------------" << endl;

	C c1("C1");
	C c2 = std::move(c1);

	cout << "-------------------------------" << endl;

	D d1("D1");
	D d2 = std::move(d1);

	return 0;
}
