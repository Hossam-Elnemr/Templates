function<bool(int)> can = [&](int node) {
                if (vis[node])
                    return false;
 
                vis[node] = true;
                for (auto i: adj[node]) {
                    if (m_to[i] == -1 || can(m_to[i])) {
                        m_to[i] = node;
                        return true;
                    }
                }
                return false;
            };
 
            int cnt = 0;
            for (int i = 1; i<=n; i++) {
                memset(vis, 0, sizeof vis);
                cnt += can(i);
            }
            return cnt == n;
        };
