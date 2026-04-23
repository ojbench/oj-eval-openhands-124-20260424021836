#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;
int occupied[MAXN];

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if we can fulfill this order
        // We need to check segments [u, v-1]
        int maxOccupied = 0;
        for (int j = u; j < v; j++) {
            maxOccupied = max(maxOccupied, occupied[j]);
        }
        
        if (maxOccupied + n <= k) {
            // Can fulfill the order
            printf("T\n");
            // Update the segments
            for (int j = u; j < v; j++) {
                occupied[j] += n;
            }
        } else {
            // Cannot fulfill the order
            printf("N\n");
        }
    }
    
    return 0;
}
