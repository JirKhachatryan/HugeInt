#include "HugeInt.h"

int main() {
	HugeInt x(9);
	HugeInt y(999);
	HugeInt z;
	while (true) {
		std::cin >> x>>y;
		z = x%y;
		std::cout <<std::endl<< z<< std::endl<<x<<std::endl<<y<< std::endl;
		system("pause");
	}
	return 0;
}
