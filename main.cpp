#include "SafeVector.h"
#include <thread>
#include <iostream>

SafeVector<int> Vec;

void f1() {
	Vec.push_back(0);
	Vec.push_back(1);
	Vec.push_back(2);

}

void f2() {
	if (Vec.size() >= 2)
	 Vec[1] = -1;
}

void f3() {
	if (Vec.size() >= 2)
		Vec.erase(1);
}

int main() {
	std::thread t1(f1);
	std::thread t2(f2);
	std::thread t3(f3);
	t1.join();
	t2.join();
	t3.join();

	for (int i = 0; i < Vec.size(); ++i) {
		std::cout << Vec[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}