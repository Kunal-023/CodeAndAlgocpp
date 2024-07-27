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
    seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
}

void PointUpdate(int ind,int low,int high,int gind,int gval,vector<int> &seg){
    if(low==high){
        seg[ind]=gval;
        return;
    }
    int mid=(low+high)/2;
    if(gind<=mid){
        PointUpdate(2*ind+1,low,mid,gind,gval,seg);
    }
    else PointUpdate(2*ind+2,mid+1,high,gind,gval,seg);
    seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);

}

int query(int ind,int low,int high,int l,int r,vector<int>&seg){
    //no overlap
    //l r low high or low high l r
    if(r<low || l>high){
        return INT_MAX;
    }
    //complete overlap
    // l low high r
    if(l<=low && r>=high ){
        return seg[ind];
    }
    int mid=(low+high)/2;
    int left=query(2*ind+1,low,mid,l,r,seg);
    int right=query(2*ind+2,mid+1,high,l,r,seg);

    return min(left,right);
}

int32_t main(){
    
    int n,q;
    cin>>n>>q;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    vector<int> seg(4*n);
    build(0,0,n-1,arr,seg);
    while(q--){
        int t;
        cin>>t;
        if(t==2){
            int l,r;
            cin>>l>>r;
            l--;r--;
            cout<<query(0,0,n-1,l,r,seg)<<endl;
        }
        else{
            int gind,gval;
            cin>>gind>>gval;
            gind--;
            PointUpdate(0,0,n-1, gind, gval,seg);
            arr[gind]=gval;
        }
    }
    

    return 0;
}
