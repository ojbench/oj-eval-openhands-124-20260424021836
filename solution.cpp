#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

struct SegmentTree {
    int tree[MAXN * 4];
    int lazy[MAXN * 4];
    int n;
    
    void init(int size) {
        n = size;
        for (int i = 0; i < n * 4; i++) {
            tree[i] = 0;
            lazy[i] = 0;
        }
    }
    
    void pushDown(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    void update(int node, int l, int r, int ql, int qr, int val) {
        pushDown(node, l, r);
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            pushDown(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
        pushDown(node * 2, l, mid);
        pushDown(node * 2 + 1, mid + 1, r);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
    
    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        pushDown(node, l, r);
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int mid = (l + r) / 2;
        return max(query(node * 2, l, mid, ql, qr), 
                   query(node * 2 + 1, mid + 1, r, ql, qr));
    }
    
    void rangeUpdate(int l, int r, int val) {
        update(1, 1, n, l, r, val);
    }
    
    int rangeMax(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

SegmentTree st;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    st.init(x);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if we can fulfill this order
        // We need to check segments [u, v-1]
        int maxOccupied = st.rangeMax(u, v - 1);
        
        if (maxOccupied + n <= k) {
            // Can fulfill the order
            printf("T\n");
            // Update the segments
            st.rangeUpdate(u, v - 1, n);
        } else {
            // Cannot fulfill the order
            printf("N\n");
        }
    }
    
    return 0;
}
