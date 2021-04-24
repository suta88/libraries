#include <vector>
using namespace std;

struct HLD{
    vector<int> hld,sz,par,depth,head,ids,pos,ran;
    vector<vector<int>> G,chains;
    int id = -1, num = 0;

    HLD(vector<vector<int>> &g, int root = 0) : G(g){
        int n = g.size();
        hld.resize(n);
        sz.resize(n);
        par.resize(n,-1);
        depth.resize(n,-1);
        pos.resize(n);
        ids.resize(n);
        ran.resize(n);
        depth[root] = 0;
        get_size(root,-1);
        decompose(root,-1,root);
    }

    void get_size(int u, int p){
        sz[u] = 1;
        for(auto v : G[u]){
            if(v == p) continue;
            par[v] = u;
            depth[v] = depth[u] + 1;
            get_size(v,u);
            sz[u] += sz[v];
        }
    };

    void decompose(int u, int p, int h){
        if(u == h){
            chains.push_back({u});
            head.push_back(u);
            id++;
            ran[u] = 1;
        }else{
            ran[u] = ran[p] + 1;
        }
        hld[num] = u;
        pos[u] = num++;
        ids[u] = id;
        int mx = 0;
        int nxt = -1;
        for(auto v : G[u]){
            if(v == p) continue;
            if(mx < sz[v]){
                mx = sz[v];
                nxt = v;
            }
        }
        if(nxt != -1) decompose(nxt,u,h);
        for(auto v : G[u]){
            if(v == p) continue;
            if(v == nxt) continue;
            else decompose(v,u,v);
        }
    }

    int lca(int u, int v){
        while(ids[u] != ids[v]){
            if(depth[head[ids[u]]] > depth[head[ids[v]]]) u = par[head[ids[u]]];
            else v = par[head[ids[v]]];
        }
        return depth[u] < depth[v] ? u : v;
    }
};