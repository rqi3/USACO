using db = long double; // or double if tight TL
using str = string;

#define tcT template<class T
tcT, size_t SZ> using AR = array<T,SZ>;
using vb = V<bool>;

#define sor(x) sort(all(x))
#define rsz resize
#define ft front()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
