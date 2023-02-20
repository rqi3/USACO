/**
 * Description: 1D range minimum query, with arrays.
 * Source: KACTL
 * Memory: O(N\log N)
 * Time: O(1)
 */

tcT, int SZ, int JMP> struct RMQ {
	int level(int x) { return 31-__builtin_clz(x); }
	T v[SZ]; 
	T jmp[JMP][SZ];

	void init() {
		for(int i = 0; i < SZ; i++){
			jmp[0][i] = v[i];
		}
		for (int j = 1; 1<<j <= SZ; ++j) {
			int upper = SZ-(1<<j)+1;
			for(int i = 0; i < upper; i++) jmp[j][i] = min(jmp[j-1][i], jmp[j-1][i+(1<<(j-1))]);
		}
	}
	T query(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return min(jmp[d][l],jmp[d][r-(1<<d)+1]); }
};
// RMQ<int, 500000, 19> rmq;