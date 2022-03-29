#include <algorithm>
#include <iostream>
void neg_before_pos(int* A, int n)
{
	if (!A || n < 2) return;
	int i(0), j(n-1);
	while (i <= j)
	{
		if (A[i] < 0) {++i;}	// shrink the unknown section from the left
		else{
			std::swap(A[i], A[j]);
			--j;
		}
	}
}
int main()
{
	neg_before_pos(NULL, 0);
	int A[7] = {5,-5,1,0,0,-2,-3};
	neg_before_pos(A, 7);
	for (int i = 0; i < 7; ++i)
	{
		std::cout << A[i] << " ";
	}
	system("Pause");
}