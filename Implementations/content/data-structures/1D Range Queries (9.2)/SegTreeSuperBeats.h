/**
 * Description: Lazy SegTree supports modifications of the form 
    * range min max and sum updates and queries. 
 * Time: O(\log N)?
 */

struct Info {
    ll sum, num;
    void adv(ll inc) {
        sum += num*inc;
    }
};
bool operator==(const Info& a, const Info& b) {
    return a.sum == b.sum && a.num == b.num; }
Info& operator+=(Info& a, const Info& b) {
    a.sum += b.sum, a.num += b.num;
    return a; }
Info operator+(Info a, const Info& b) {
    return a += b; }

struct Node {
    AR<ll,2> mx; // max, second max
    AR<ll,2> mn; // min, second min
    AR<Info,3> info; // sum of each, # of each
    AR<ll,3> lazy; // lazy increments for min, middle, max
    Node() {}
    Node(ll x) { // OK
        mx = {x,-BIG};
        mn = {x,BIG};
        info = {}; info[1] = {x,1};
        lazy = {};
    }
    bool all_equal() const { return mx[0] == mn[0]; } // true if min of range = max of range
    Info get_sum() const { return info[0]+info[1]+info[2]; }
    ll get_min() {
        if (all_equal()) return mn[0]+lazy[1];
        return mn[0]+lazy[0]; }
    ll get_max() {
        if (all_equal()) return mn[0]+lazy[1];
        return mx[0]+lazy[2]; }
};

Node seg[1<<19];

AR<ll,2> comb_mx(const AR<ll,2>& a, const AR<ll,2>& b) {
    ll mx = max(a[0],b[0]);
    ll second_mx = max(a[0] == mx ? a[1] : a[0],b[0] == mx ? b[1] : b[0]);
    return {mx,second_mx};
}

AR<ll,2> comb_mn(const AR<ll,2>& a, const AR<ll,2>& b) {
    ll mn = min(a[0],b[0]);
    ll second_mn = min(a[0] == mn ? a[1] : a[0],b[0] == mn ? b[1] : b[0]);
    return {mn,second_mn};
}

void comb(Node& res, const Node& l, const Node& r) {
    res.mx = comb_mx(l.mx,r.mx);
    res.mn = comb_mn(l.mn,r.mn);
    res.info = {};
    auto deal = [&](const Node& x) {
        if (x.all_equal()) { // case 1: same value
            ll v = x.mn[0]; Info info = x.info[1];
            assert(res.mn[0] <= v && v <= res.mx[0]);
            if (res.all_equal()) {
                res.info[1] += info;
            } else {
                if (res.mn[0] == v) {
                    res.info[0] += info;
                } else if (res.mx[0] == v) {
                    res.info[2] += info;
                } else {
                    res.info[1] += info;
                }
            }
        } else {
            res.info[x.mn[0] == res.mn[0] ? 0 : 1] += x.info[0];
            res.info[1] += x.info[1];
            res.info[x.mx[0] == res.mx[0] ? 2 : 1] += x.info[2];
        }
    };
    assert(res.mn[0] <= res.mx[0]);
    deal(l); deal(r);
}

void push(int ind, int L, int R) {
    if (seg[ind].all_equal()) {
        assert(seg[ind].lazy[0] == 0 && seg[ind].lazy[2] == 0);
        seg[ind].lazy[0] = seg[ind].lazy[2] = seg[ind].lazy[1];
    }
    if (L != R) {
        auto pushdown = [&](Node& node) {
            if (node.all_equal()) {
                if (seg[ind].mn[0] == node.get_min()) {
                    node.lazy[1] += seg[ind].lazy[0];
                } else if (seg[ind].mx[0] == node.get_max()) {
                    node.lazy[1] += seg[ind].lazy[2];
                } else {
                    node.lazy[1] += seg[ind].lazy[1];
                }
            } else {
                node.lazy[0] += seg[ind].lazy[seg[ind].mn[0] == node.get_min() ? 0 : 1];
                node.lazy[1] += seg[ind].lazy[1];
                node.lazy[2] += seg[ind].lazy[seg[ind].mx[0] == node.get_max() ? 2 : 1];
            }
        };
        pushdown(seg[2*ind]);
        pushdown(seg[2*ind+1]);
    }
    F0R(i,3) seg[ind].info[i].adv(seg[ind].lazy[i]);
    bool two_valued = (seg[ind].mn[1] == seg[ind].mx[0]);
    seg[ind].mn[0] += seg[ind].lazy[0];
    seg[ind].mx[0] += seg[ind].lazy[2];
    if (two_valued) {
        seg[ind].mn[1] = seg[ind].mx[0];
        seg[ind].mx[1] = seg[ind].mn[0];
    } else {
        if (seg[ind].mn[1] != BIG)
            seg[ind].mn[1] += seg[ind].lazy[1];
        if (seg[ind].mx[1] != -BIG) 
            seg[ind].mx[1] += seg[ind].lazy[1];
    }
    seg[ind].lazy = {};
    assert(seg[ind].mn[0] <= seg[ind].mx[0]);
}

void pull(int ind, int L, int R) {
    assert(L < R);
    comb(seg[ind],seg[2*ind],seg[2*ind+1]);
}

void build(int ind, int L, int R, const vl& A) {
    if (L == R) {
        seg[ind] = Node(A[L]);
        return;
    }
    int M = (L+R)/2;
    build(2*ind,L,M,A); build(2*ind+1,M+1,R,A);
    pull(ind,L,R);
}

Info query_sum(int lo, int hi, int ind, int L, int R) {
    if (R < lo || hi < L) return {};
    push(ind,L,R);
    if (lo <= L && R <= hi) return seg[ind].get_sum();
    int M = (L+R)/2;
    return query_sum(lo,hi,2*ind,L,M)+query_sum(lo,hi,2*ind+1,M+1,R);
}

void upd_min(int lo, int hi, ll B, int ind, int L, int R) {
    push(ind,L,R);
    ll dif = B-seg[ind].mx[0];
    if (R < lo || hi < L || dif >= 0) return;
    if (lo <= L && R <= hi) {
        if (seg[ind].all_equal()) {
            seg[ind].lazy[1] = dif;
            push(ind,L,R);
            return;
        } else if (B > seg[ind].mx[1]) {
            seg[ind].lazy[2] = dif;
            push(ind,L,R);
            return;
        }
    }
    int M = (L+R)/2;
    upd_min(lo,hi,B,2*ind,L,M);
    upd_min(lo,hi,B,2*ind+1,M+1,R);
    pull(ind,L,R);
}

void upd_max(int lo, int hi, ll B, int ind, int L, int R) {
    push(ind,L,R);
    ll dif = B-seg[ind].mn[0];
    if (R < lo || hi < L || dif <= 0) return;
    if (lo <= L && R <= hi) {
        if (seg[ind].all_equal()) {
            seg[ind].lazy[1] = dif;
            push(ind,L,R);
            return;
        } else if (B < seg[ind].mn[1]) {
            seg[ind].lazy[0] = dif;
            push(ind,L,R);
            return;
        }
    }
    int M = (L+R)/2;
    upd_max(lo,hi,B,2*ind,L,M);
    upd_max(lo,hi,B,2*ind+1,M+1,R);
    pull(ind,L,R);
}

void upd_ad(int lo, int hi, ll B, int ind, int L, int R) {
    push(ind,L,R);
    if (R < lo || hi < L) return;
    if (lo <= L && R <= hi) {
        if (seg[ind].all_equal()) {
            seg[ind].lazy[1] = B;
        } else {
            F0R(i,3) seg[ind].lazy[i] = B;
        }
        push(ind,L,R);
        return;
    }
    int M = (L+R)/2;
    upd_ad(lo,hi,B,2*ind,L,M);
    upd_ad(lo,hi,B,2*ind+1,M+1,R);
    pull(ind,L,R);
}