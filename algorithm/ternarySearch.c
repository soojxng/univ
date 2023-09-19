// just a pseudo-code

//S[]: the array used for a ternary search
//x: the value that we want to find
int ternary(int S[], int x, int low, int high) {
	int v1, v2;
	if (low > high) return -1;
	else {
		v1 = low + ((high - low) / 3);
		v2 = low + ((high - low) * 2 / 3);

		if (x == S[v1])
			return v1;
		else if (x == S[v2])
			return v2;

		if (x < S[v1])
			return ternary(S[], x, low, v1 - 1);
		else if (x > S[v2])
			return ternary(S[], x, v2 + 1, high);
		else
			return ternary(S[], x, v1 + 1, v2 - 1);
	}
}
