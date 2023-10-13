/**
 * Description: Kth Shortest Walk
 * Time: O(\log N) per meld
 * Memory: O(\log N) per meld
 * Source:
 	* https://judge.yosupo.jp/submission/11843
 */

const ll INF = 1e18;
const int MX = 300005;

typedef pair<ll,int> T;
typedef struct heap* ph;
struct heap { // min heap
	ph l = NULL, r = NULL;
	int s = 0; T v; // s: path to leaf
	heap(T _v):v(_v) {}
};

ph meld(ph p, ph q) {
	if (!p || !q) return p?:q;
	if (p->v > q->v) swap(p,q);
	ph P = new heap(*p); P->r = meld(P->r,q);
	if (!P->l || P->l->s < P->r->s) swap(P->l,P->r);
	P->s = (P->r?P->r->s:0)+1; return P;
}
ph ins(ph p, T v) { return meld(p, new heap(v)); }
ph pop(ph p) { return meld(p->l,p->r); }

int N,M,src,des,K;

ph cand[MX];
vector<array<int,3>> adj[MX], radj[MX];
pi pre[MX];
ll dist[MX];

struct state {
	int vert; ph p; ll cost;
	bool operator<(const state& s) const { return cost > s.cost; }
};

int main() {
	cin.tie(0)->sync_with_stdio(0); cin >> N >> M >> src >> des >> K;
	F0R(i,M) {
		int u,v,w; cin >> u >> v >> w;
		adj[u].pb({v,w,i}); radj[v].pb({u,w,i}); // vert, weight, label
	}
	priority_queue<state> ans;
	{
		F0R(i,N) dist[i] = INF, pre[i] = {-1,-1};
		priority_queue<T,vector<T>,greater<T>> pq;
		auto ad = [&](int a, ll b, pi ind) {
			if (dist[a] <= b) return;
			pre[a] = ind; pq.push({dist[a] = b,a});
		};
		ad(des,0,{-1,-1});
		vi seq;
		while (sz(pq)) {
			auto a = pq.top(); pq.pop(); 
			if (a.f > dist[a.s]) continue;
			seq.pb(a.s); each(t,radj[a.s]) ad(t[0],a.f+t[1],{t[2],a.s}); // edge index, vert
		}
		each(t,seq) {
			each(u,adj[t]) if (u[2] != pre[t].f && dist[u[0]] != INF) {
				ll cost = dist[u[0]]+u[1]-dist[t];
				cand[t] = ins(cand[t],{cost,u[0]});
			}
			if (pre[t].f != -1) cand[t] = meld(cand[t],cand[pre[t].s]);
			if (t == src) {
				cout << dist[t] << "\n"; K --;
				if (cand[t]) ans.push(state{t,cand[t],dist[t]+cand[t]->v.f});
			}
		}
	}
	F0R(i,K) {
		if (!sz(ans)) {
			cout << -1 << "\n";
			continue;
		}
		auto a = ans.top(); ans.pop();
		int vert = a.vert;
		cout << a.cost << "\n";
		if (a.p->l) {
			ans.push(state{vert,a.p->l,a.cost+a.p->l->v.f-a.p->v.f});
		}
		if (a.p->r) {
			ans.push(state{vert,a.p->r,a.cost+a.p->r->v.f-a.p->v.f});
		}
		int V = a.p->v.s;
		if (cand[V]) ans.push(state{V,cand[V],a.cost+cand[V]->v.f});
	}
}