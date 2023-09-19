#include <iostream>
#define MAX 50
using namespace std;

int col[MAX];
int n, total = 0;

bool promising(int i) {
	bool flag = true;
	for (int k = 1; k < i && flag; k++) {
		//Check if queens in row i and queens in row k are located in the same column or diagonal
		if (col[i] == col[k] || ((abs(col[i] - col[k]) == (i - k))))
			flag = false;
	}
	return flag;
}

void queens(int i) {
	if (promising(i)) {
		if (i == n) {
			cout << ++total << ": [";
			for(int k = 1; k <= n; k++)
				cout << "<" << k << ", " << col[k] << ">, ";
			cout << "\b\b]\n";
		}
		else {
			for (int j = 1; j <= n; j++) {
				col[i+1] = j;
				queens(i + 1);
			}
		}
	}
}

int main(void) {
  cout << "insert N: ";
	cin >> n;
	queens(0);
	cout << "Total number : " << total << "\n";
	system("pause");	//Preventing the console window from turning off immediately

	return 0;
}
