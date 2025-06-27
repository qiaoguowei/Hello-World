#include<iostream>
//#include<Array>
void showall() { return; }

template <typename R1 ,typename...  Args>
void showall(R1&& var, Args&&...args) {

	std::cout << var << std::endl;
	showall(std::forward<Args>(args)...);
}

int main(int argc, char * args[]) {


	showall(1, 2, 3, 4, 5);
	showall("gxjun","dadw","dasds");
	showall(1.0,2.0,3.5);
	return 0;
}

