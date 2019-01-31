#include <stdio.h>
int main(){
	int a = 0x34FF;
	printf("result: 0x%x\n", ((a<<0x10)>>0x08) & a);
	return 0;
}
