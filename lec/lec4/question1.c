#include <stdio.h>

int main(){
	int a;
	int b = ((a^a)|0xFF)&0xF0;
	printf("result:0x%x\n",b);
	return 0;
}
