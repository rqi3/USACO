/**
 * Description: Multiply two 64-bit integers mod another. Assumes 128-bit available.
	* Works for $0\le a,b<mod<2^{63}.$
 * Source: KACTL
 */

using ul = uint64_t;
ul modMul(ul a, ul b, const ul mod){
	return __int128(a) * __int128(b) % mod;
}
ul modPow(ul a, ul b, const ul mod) {
	if (b == 0) return 1;
	ul res = modPow(a,b/2,mod); res = modMul(res,res,mod);
	return b&1 ? modMul(res,a,mod) : res;
}