#include <cstdio>
#include <cmath>

int main() {
	int x;
	while(scanf("%d", &x) != EOF) {
		if(x % 6 == 0) 
			printf("Y\n");
		else
			printf("N\n");
	}
}
