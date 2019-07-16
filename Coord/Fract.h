#pragma once
class CFract
{
public:
	CFract(int son = 1, int mom = 1);
	~CFract();

	int GetMom() const { return m_nMom; }
	int GetSon() const { return m_nSon; }

	CFract operator+(CFract& t);
	CFract operator-(CFract& t);
	CFract operator*(CFract& t);
	CFract operator/(CFract& t);
	CFract operator=(CFract& t);
	operator double();

	static int Gcd(int a, int b);
	static int Lcm(int a, int b);

	void Reduction();
	void Reduce(CFract& t);

private:
	int m_nMom;
	int m_nSon;
};

