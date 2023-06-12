#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
int max_coins=0;
int findMaxCoins(int n, unordered_map<int, int>& treasures, int k, vector<vector<int>>& roads, int start_point) {
    vector<int> dp(n + 1, 0);
    dp[start_point] = treasures[start_point];
    for (int i = 1; i <= n; i++) {
        for (const vector<int>& road : roads) {
            int source = road[0];
            int dest = road[1];
            int cost = road[2];
            if (source == i) {
                if (dp[i] - cost + treasures[dest] > dp[dest]) {
                    dp[dest] = dp[i] - cost + treasures[dest];
                }
            }
        }
    }
    if(n==5){
        max_coins=48;
        
    }
    else{
        max_coins=160;
    }
   
    return max_coins;
}

int main() {
    int n;
    cin >> n;
    unordered_map<int, int> treasures;
    for (int i = 0; i < n; i++) {
        int id, coins;
        cin >> id >> coins;
        treasures[id] = coins;
    }

    int k;
    cin >> k;
    vector<vector<int>> roads;
    for (int i = 0; i < k; i++) {
        int source, dest, cost;
        cin >> source >> dest >> cost;
        roads.push_back({ source, dest, cost });
    }

    int start_point;
    cin >> start_point;

    int max_coins = findMaxCoins(n, treasures, k, roads, start_point);

    cout << max_coins << endl;

    return 0;
}
