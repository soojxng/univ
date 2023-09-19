// just a pseudo-code

/*
* Given a value N, if we want to make change for N cents,
* and we have infinite supply of each of S = {S1, S2, ..., Sm} valued coins,
* how many ways can we make the change? The order of coins does not matter.
*
* For example, for N = 4 and S = {1, 2, 3},
* there are four ways: {1, 1, 1, 1}, {1, 1, 2}, {2, 2}, {1, 3}.
* So output should be 4.
* For N = 10 and S = {2, 3, 5, 6},
* there are five ways: {2, 2, 2, 2, 2}, {2, 2, 3, 3}, {2, 2, 6}, {2, 3, 5} and {5, 5}. 
* So the output should be 5.
*/

//S[]: the array of coins
//m: the size of S[]
//N: the cent value that we want to make
//cnt[]: the array for counting the number of ways for making N

int coinChangeCount(S[], N) {
	int cnt[N+1]= {0,};
	cnt[0] = 1;
	for(int i=0; i<m; i++){
		for(int j=0; j<N+1; j++){
			if(S[i] <= j)
				cnt[j] += cnt[(j – S[i])];
		}
	}
	return cnt[N];
}
