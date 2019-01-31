#include <iostream>

void func(int &a){
	a = 10;
}
int main(){
	int a = 0;
	func(a);
	std::cout<<a<<std::endl;
	return 0;
}
