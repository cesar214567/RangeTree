#include <bits/stdc++.h>
using namespace std;

void create (vector<int> &st,vector<int> &v,int low,int high, int pos ){
    cout<<low<<" "<<high<<endl;
    if(low==high){
        st[pos]=v[low];
        return;
    }
    int mid = (high+low)/2;
    create(st,v,low,mid,pos*2+1);
    create(st,v,mid+1,high,pos*2+2);
    st[pos]=(st[pos*2+1]+st[pos*2+2])/2;
        

}
// low = 0 high =3
vector<int> range_min_query(vector<int> st,int pos,int high,int valuemin,int valuehigh){
    vector<int> retorno; 
    while(pos<=high){
        if (valuemin<st[pos]){
            pos = pos*2+1;
        }else{
            pos = pos*2+2;
        }
    }
    while (pos<st.size()){
        if(st[pos]<=valuehigh ){
            if(st[pos]>valuemin)retorno.push_back(st[pos]);
            
        }else{
            break;
        }
        pos++;
    }
    return retorno;

}

//       8
//   4
// 1   7        
int main(){
    vector<int> v={2,5,9,0};
    vector<int> st(7,0);   //1 0 2 -1 0 2 4
    sort(v.begin(),v.end());
    create(st,v,0,3,0);
    for(int i=0;i<7;i++){
        cout<<st[i]<<" ";
    }cout<<endl;
    for (auto it:range_min_query(st,0,3,1,11)){
        cout<<it<<" ";
    }
}


