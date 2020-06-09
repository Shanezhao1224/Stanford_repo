#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
std::string recursivemultiply(std::string numA, std::string numB);
std::string stringaddition(std::string numA, std::string numB);
std::string stringsub(std::string A, std::string B, std::string C);

int main() {
	std::string numA = "3141592653589793238462643383279502884197169399375105820974944592";
	std::string numB = "2718281828459045235360287471352662497757247093699959574966967627";
	//std::string numA = "90109928";
	//std::string numB = "95084501";
	std::string printval = recursivemultiply(numA, numB);
	std::cout << "value of multiplication = \n" << printval << std::endl;
}

std::string recursivemultiply(std::string numA, std::string numB) {
	
	std::string returnstring;
	if (numA.size() <= 1 && numB.size() <= 1) {//base case start multiplying up
		//std::cout << "reached base case" << std::endl;
		std::cout << "value of numA = " << numA << " numB= " << numB << std::endl;
		int a;
		int b;
		if (numA.empty()) {
			returnstring.push_back('0');
			return returnstring;
		}
		if (numB.empty()) {
			returnstring.push_back('0');
			return returnstring;
		}
		a = numA[0] - '0';
		b = numB[0] - '0';
		int temp = a * b;
		if (temp / 10 == 0) {
			returnstring.push_back(temp + '0');
			std::cout << "value of returnstring after multi = " << returnstring << std::endl;
			return returnstring;
		}
		else {
			returnstring.push_back(temp/10 + '0');
			returnstring.push_back(temp % 10 + '0');
		}
		//std::cout << "value of temp = " << temp << std::endl;
		std::cout << "value of returnstring after multi = " << returnstring << std::endl;
		return returnstring;
	}
	else {
		//std::cout << "value of numA = " << numA << "\nvalue of numB = " << numB <<"\n value of n = "<< n<< std::endl;
		std::string a = numA.substr(0, numA.size() / 2);
		std::string b = numA.substr(numA.size() / 2, numA.size() - a.size());
		std::string c = numB.substr(0, numB.size() / 2);
		std::string d = numB.substr(numB.size() / 2, numB.size()-c.size());
		std::string bd = recursivemultiply(b, d);
		std::string ac = recursivemultiply(a, c);
		std::string ad = recursivemultiply(a, d);
		std::string bc = recursivemultiply(b, c);
		int x_n = b.size();
		int y_n = d.size();
		for (int i = 0; i <x_n; i++) {
			ad.push_back('0');
		}
		for (int i = 0; i < y_n; i++) {
			bc.push_back('0');
		}
		std::string adplusbc = stringaddition(ad, bc);
		
		for (int i = 0; i < x_n+y_n; i++) {
			ac.push_back('0');
		}
		returnstring = stringaddition(adplusbc, bd);
		returnstring = (stringaddition(ac, returnstring));
		//TODO: for karatsuba algorithm
		//std::string aplusb = stringaddition(a, b);
		//std::string cplusd = stringaddition(c, d);
		//std::string adbc = stringsub(recursivemultiply(aplusb, cplusd,std::max(aplus.size(),cplusb.size()),ac,bd);
		//values are ready need to shift and create return string;
		return returnstring;
	}
}

std::string stringaddition(std::string numA, std::string numB) {
	std::cout << "value of numA = " << numA << " numB= " << numB << std::endl;
	std::string returnstring;
	std::reverse(numA.begin(), numA.end());
	std::reverse(numB.begin(), numB.end());
	bool carry = 0;
	int i;
	for (i = 0; i < numA.size() && i < numB.size(); i++) {
		int a = numA[i] - '0';
		int b = numB[i] - '0';
		int c = a + b + carry;
		if (c / 10) {
			carry = 1;
		}
		else {
			carry = 0;
		}
		returnstring.push_back(c%10 + '0');
	}
	if (i < numA.size()) {
		while (i < numA.size()) {
			int c = numA[i] - '0' + carry;
			returnstring.push_back(c % 10 + '0');
			if (c / 10) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			i++;
		}	
	}
	if (i < numB.size()) {
		while (i < numB.size()) {
			int c = numB[i] - '0' + carry;
			returnstring.push_back(c % 10 + '0');
			if (c / 10) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			i++;
		}
	}
	if (carry)returnstring.push_back('1');
	std::reverse(returnstring.begin(), returnstring.end());
	std::cout << "value of returnstring after add =" << returnstring << std::endl;
	return returnstring;

}
std::string stringsub(std::string A, std::string B, std::string C) {
	std::string returnstring;
	return returnstring;
}