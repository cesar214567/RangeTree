#include <bits/stdc++.h>
using namespace std;

struct node{
    node *left=nullptr;
    node *right=nullptr;
    node *subtree=nullptr;
    node *next = nullptr;
    int value=-1; 
    pair<int,int> point;
};

node * pibot = nullptr;
node * pibot2= nullptr;

void create_simple (node* &st,vector<pair<int,int>> &v,int low,int high ){
    st = new node();
    cout<<low<<" "<<high<<endl;
    if(low==high){
        if(pibot2)
            pibot2->next = st;
        vector<pair<int,int>> ret;
        st->point=v[low];
        st->value = v[low].second;
        ret.push_back(v[low]);
        pibot2 = st;
        return ;
    }
    int mid = (high+low)/2;
    create_simple(st->left,v,low,mid);
    create_simple(st->right,v,mid+1,high);
    st->value=(st->left->value+st->right->value)/2;
    return;
}


bool comp (pair<int,int> a,pair<int,int> b){
    return a.second<b.second;
}


vector<pair<int,int>> create (node* &st,vector<pair<int,int>> &v,int low,int high){
    st = new node();
    cout<<low<<" "<<high<<endl;
    if(low==high){
        if(pibot)
            pibot->next = st;
        vector<pair<int,int>> ret;
        st->point=v[low];
        st->value = v[low].first;
        ret.push_back(v[low]);
        pibot = st;
        return ret;
    }
    int mid = (high+low)/2;
    auto vector1 = create(st->left,v,low,mid);
    auto vector2 = create(st->right,v,mid+1,high);
    vector1.insert(vector1.end(),vector2.begin(),vector2.end());
    sort(vector1.begin(),vector1.end(),comp);
    create_simple(st->subtree,vector1,0,vector1.size()-1);
    st->value=(st->left->value+st->right->value)/2;
    return vector1;
}
    
void dfs(node* temp){
    if(!temp)
        return;
    dfs(temp->left);
    cout << temp->value<<" ";
    dfs(temp->right);
}

vector<pair<int,int>> range_min_query2(node* &st, int valuemin,int valuehigh){
    vector<pair <int,int>> ret;
    auto temp = st;
    //logica
    while(temp->left){
        if(valuemin < temp->value){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }

    while (temp){
        if(temp->value<=valuehigh ){
            if(temp->value >valuemin) ret.push_back(temp->point);
        }else{
            break;
        }
        temp = temp->next;
    }
    return ret;
}

vector<pair<int,int>> range_min_query(node* &st, int valueminX,int valuehighX, int valueminY,int valuehighY){
    auto temp = st;
    while(temp->left){
        if(valueminX < temp->value && valuehighX > temp->value){
            return range_min_query2(temp->subtree,valueminY,valuehighY); 
        }
        else if(valueminX < temp->value && valuehighX < temp->value){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    vector <pair<int, int>>vacio;
    return vacio;
}



int main(){
    vector<pair<int,int>> v;
    v.push_back({2,10});
    v.push_back({5,11});
    v.push_back({9,13});
    v.push_back({0,5});
    sort(v.begin(),v.end());
    node *tree = nullptr;
    create(tree,v,0,v.size()-1);

    for (auto it:range_min_query(tree,0,3,4,6)){
        cout<<"punto: x = "  << it.first << " y =  "<< it.second << endl;
    }
}


