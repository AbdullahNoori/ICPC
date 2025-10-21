/**
 * @file 05.airport_reinforcement_scc.cpp
 * @brief Determine minimal new routes needed to reach all airports.
 * @solution Tarjan SCC -> condensation DAG -> count sources in unreachable subgraph.
 * @complexity O(N + M) per test case (excluding parsing).
 * @related 3.graphs/03.tarjan_strongly_connected_components.cpp
 * @related 3.graphs/02.topological_sort_kahn.cpp
 */

#include <bits/stdc++.h>
using namespace std;

struct Tarjan {
    int n;
    vector<vector<int>> g;
    vector<int> disc, low, comp, st;
    vector<char> in_st;
    int timer = 0, comp_cnt = 0;

    explicit Tarjan(vector<vector<int>> g)
        : n(static_cast<int>(g.size())), g(move(g)),
          disc(n, -1), low(n), comp(n, -1), in_st(n, 0) {
        st.reserve(n);
        for (int v = 0; v < n; ++v)
            if (disc[v] == -1)
                dfs(v);
    }

    void dfs(int u) {
        disc[u] = low[u] = timer++;
        st.push_back(u);
        in_st[u] = 1;
        for (int v : g[u]) {
            if (disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (in_st[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }
        if (low[u] == disc[u]) {
            while (true) {
                int v = st.back();
                st.pop_back();
                in_st[v] = 0;
                comp[v] = comp_cnt;
                if (v == u) break;
            }
            ++comp_cnt;
        }
    }
};

static string trim(string s) {
    auto is_space = [](unsigned char ch) { return isspace(ch); };
    s.erase(s.begin(), find_if_not(s.begin(), s.end(), is_space));
    s.erase(find_if_not(s.rbegin(), s.rend(), is_space).base(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    string dummy;
    getline(cin, dummy); // consume endline

    while (T--) {
        string airports_line;
        getline(cin, airports_line);
        airports_line = trim(airports_line);
        vector<string> airports;
        string cur;
        for (char ch : airports_line) {
            if (ch == ',') {
                if (!cur.empty()) {
                    airports.push_back(trim(cur));
                    cur.clear();
                }
            } else {
                cur.push_back(ch);
            }
        }
        if (!cur.empty()) airports.push_back(trim(cur));

        int n = static_cast<int>(airports.size());
        unordered_map<string, int> id;
        id.reserve(n * 2);
        for (int i = 0; i < n; ++i) id[airports[i]] = i;

        int m;
        cin >> m;
        getline(cin, dummy);
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i) {
            string route;
            getline(cin, route);
            route = trim(route);
            size_t pos = route.find(',');
            if (pos == string::npos) continue;
            string a = trim(route.substr(0, pos));
            string b = trim(route.substr(pos + 1));
            if (id.count(a) && id.count(b)) {
                g[id[a]].push_back(id[b]);
            }
        }

        string start_line;
        getline(cin, start_line);
        string start_code = trim(start_line);
        if (!id.count(start_code)) {
            cout << 0 << "\n";
            continue;
        }
        int start = id[start_code];

        Tarjan tarjan(g);
        int comp_cnt = tarjan.comp_cnt;
        auto comp = tarjan.comp;

        vector<vector<int>> dag(comp_cnt);
        for (int u = 0; u < n; ++u) {
            for (int v : g[u]) {
                if (comp[u] != comp[v]) {
                    dag[comp[u]].push_back(comp[v]);
                }
            }
        }
        for (auto& edges : dag) {
            sort(edges.begin(), edges.end());
            edges.erase(unique(edges.begin(), edges.end()), edges.end());
        }

        int start_comp = comp[start];
        vector<char> reach(comp_cnt, 0);
        stack<int> st;
        st.push(start_comp);
        reach[start_comp] = 1;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            for (int v : dag[u])
                if (!reach[v]) {
                    reach[v] = 1;
                    st.push(v);
                }
        }

        vector<int> indeg(comp_cnt, 0);
        for (int u = 0; u < comp_cnt; ++u)
            for (int v : dag[u])
                if (!reach[v])
                    ++indeg[v];

        int answer = 0;
        for (int u = 0; u < comp_cnt; ++u)
            if (!reach[u] && indeg[u] == 0)
                ++answer;

        cout << answer << "\n";
    }
    return 0;
}
