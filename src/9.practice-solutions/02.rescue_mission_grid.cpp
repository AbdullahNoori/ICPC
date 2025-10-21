/**
 * @file 02.rescue_mission_grid.cpp
 * @brief Rescue mission with portals on a grid (0-1 BFS).
 * @complexity O(N * M).
 * @related 3.graphs/05.zero_one_bfs.cpp
 * @related 7.dynamic-programming/05.grid_paths_dp.cpp
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) cin >> grid[i];

    pair<int, int> start{-1, -1}, target{-1, -1};
    vector<pair<int, int>> portals;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'S') start = {i, j};
            if (grid[i][j] == 'T') target = {i, j};
            if (grid[i][j] == 'P') portals.push_back({i, j});
        }
    }

    const int INF = 1e9;
    vector<vector<int>> dist(N, vector<int>(M, INF));
    deque<pair<int, int>> dq;
    dist[start.first][start.second] = 0;
    dq.push_back(start);

    bool teleports_built = false;
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    while (!dq.empty()) {
        auto [x, y] = dq.front();
        dq.pop_front();
        int d = dist[x][y];
        if (make_pair(x, y) == target) {
            cout << d << "\n";
            return 0;
        }
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (0 <= nx && nx < N && 0 <= ny && ny < M && grid[nx][ny] != '#') {
                if (dist[nx][ny] > d + 1) {
                    dist[nx][ny] = d + 1;
                    dq.push_back({nx, ny});
                }
            }
        }
        if (!teleports_built && grid[x][y] == 'P') {
            for (auto [px, py] : portals) {
                if (dist[px][py] > d) {
                    dist[px][py] = d;
                    dq.push_front({px, py});
                }
            }
            teleports_built = true;
        }
    }

    cout << -1 << "\n";
    return 0;
}
