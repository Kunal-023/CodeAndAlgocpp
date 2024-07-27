#include <bits/stdc++.h>
using namespace std;
#define int long long int

class DisjointSet{

    public:
        vector<int> rank,parent,size;
        DisjointSet(int n){
            rank.resize(n+1,0);
            parent.resize(n+1);
            size.resize(n+1,1);
            for(int i=0;i<=n;i++) parent[i]=i;
        }

        int findUparent(int node){
            if(node==parent[node]){
                return node;
            }
            //this does path compression
            //return parent[node]=findUparent(parent[node]);

            //if written like this this does in O(logn)
            //return findUparent(parent[node]);
            return parent[node]=findUparent(parent[node]);
        }

        void unionByRank(int u,int v){
            int up_u=findUparent(u);
            int up_v=findUparent(v);

            if(up_u==up_v){
                return;
            }
            if(rank[up_u]<rank[up_v]){
                parent[up_u]=up_v;
            }
            else if(rank[up_u]>rank[up_v]){
                parent[up_v]=up_u;
            }
            else{
                parent[up_v]=up_u;
                rank[up_u]++;

                //can also do this
                //parent[up_u]=up_v;
                //rank[up_v]++;
            }
        }

        void unionBySize(int u,int v){
            int up_u=findUparent(u);
            int up_v=findUparent(v);

            if(up_u==up_v){
                return;
            }
            if(size[up_u]<size[up_v]){
                parent[up_u]=up_v;
                size[up_v]+=size[up_u];
            }
            else{
                parent[up_v]=up_u;
                size[up_u]+=size[up_v];
            }
        }

};


int32_t main(){
    
    DisjointSet ds(7);
    ds.unionByRank(1,2);
    ds.unionByRank(2,3);
    ds.unionByRank(4,5);
    ds.unionByRank(6,7);
    ds.unionByRank(5,6);
    //if 3 and 7 belong to same component
    if(ds.findUparent(3)==ds.findUparent(7)){
        cout<<"Same component"<<endl;
    }
    else{
        cout<<"Not same component"<<endl;
    }
    ds.unionByRank(3,7);
    if(ds.findUparent(3)==ds.findUparent(7)){
        cout<<"Same component"<<endl;
    }
    else{
        cout<<"Not same component"<<endl;
    }

    return 0;
}
