#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;

using pi = pair<int,int>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>; 
using vi = V<int>;
using vpi = V<pi>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define pb push_back
#define bk back()

// const int MOD = 1e9+7; //comment out for Semyon

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

int main() { cin.tie(0)->sync_with_stdio(0); }