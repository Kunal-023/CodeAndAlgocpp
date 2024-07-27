#include <bits/stdc++.h>
using namespace std;
#define int long long int

void build(int ind,int low,int high,vector<int> &arr,vector<int> &seg){
    if(low==high){
        seg[ind]=arr[low];
        return;
    }

    int mid=(low+high)/2;

    build(2*ind+1,low,mid,arr,seg);
    build(2*ind+2,mid+1,high,arr,seg);
    seg[ind]=(seg[2*ind+1]+seg[2*ind+2]);
}

void RangeUpdate(int ind,int low,int high,int l,int r,int gval,vector<int> &seg,vector<int> &lazy){
    //update previous remaning updates and propagate downwards
    if(lazy[ind]!=0){//means update ramaning
        seg[ind]+=(high-low+1)*lazy[ind];
        //propagate downwards
        if(low!=high){//means there are children
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];
        }
        lazy[ind]=0;//as values are already propagated to child
    }
    //no overlap
    //l r low high or low high l r
    if(r<low || l>high){
        return ;
    }
    //complete overlap
    // l low high r
    if(l<=low && r>=high ){
        seg[ind]+=(high-low+1)*gval;
        if(low!=high){
            lazy[2*ind+1]+=gval;
            lazy[2*ind+2]+=gval;
        }
        return;
    }
    
    int mid=(low+high)/2;
    RangeUpdate(2*ind+1,low,mid,l,r,gval,seg,lazy);
    RangeUpdate(2*ind+2,mid+1,high,l,r,gval,seg,lazy);
    seg[ind]=(seg[2*ind+1]+seg[2*ind+2]);
    
}

int RangeQuery(int ind,int low,int high,int l,int r,vector<int> &seg,vector<int> &lazy){

    //Do previous Updates
    if(lazy[ind]!=0){//means update ramaning
        seg[ind]+=(high-low+1)*lazy[ind];
        //propagate downwards
        if(low!=high){//means there are children
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];
        }
        lazy[ind]=0;//as values are already propagated to child
    }

    //no overlap
    //l r low high or low high l r
    if(r<low || l>high){
        return 0;
    }
    //complete overlap
    // l low high r
    if(l<=low && r>=high ){
        return seg[ind];
    }
    int mid=(low+high)/2;
    int left=RangeQuery(2*ind+1,low,mid,l,r,seg,lazy);
    int right=RangeQuery(2*ind+2,mid+1,high,l,r,seg,lazy);

    return (left+right);
}

int32_t main(){
    
    int n,q;
    cin>>n>>q;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    vector<int> seg(4*n);
    vector<int> lazy(4*n);
    build(0,0,n-1,arr,seg);
    while(q--){
        int t;
        cin>>t;
        if(t==2){
            int x;
            cin>>x;
            x--;
            cout<<RangeQuery(0,0,n-1,x,x,seg,lazy)<<endl;
        }
        else{
            int l,r,gval;
            cin>>l>>r>>gval;
            l--;r--;
            RangeUpdate(0,0,n-1,l,r,gval,seg,lazy);
        }
    }
    

    return 0;
}
