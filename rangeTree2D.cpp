#include <bits/stdc++.h>
using namespace std;
map<pair<int,int>,int> results;


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
   // cout<<low<<" "<<high<<endl;
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
   // cout<<low<<" "<<high<<endl;
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

vector<pair<int,int>> range_min_query2(node* &st, int valuemin,int valuehigh, int valueminX, int valuemaxX){
    vector<pair <int,int>> ret;
    auto temp = st;
    //logica
    while(temp->left){
        if(valuemin <= temp->value){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }

    while (temp){
        if(temp->value<=valuehigh ){
            if(temp->value >= valuemin && temp->point.first >= valueminX && temp->point.first <= valuemaxX){
                ret.push_back(temp->point);
            }
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
        if(valueminX <= temp->value && valuehighX >= temp->value){
            return range_min_query2(temp->subtree,valueminY,valuehighY, valueminX, valuehighX); 
        }
        else if(valueminX <= temp->value && valuehighX <= temp->value){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    vector <pair<int, int>>vacio;
    return vacio;
}


vector<pair<int,int>> insertRandomPoints(){
    vector<pair<int,int>> v;
    for(int i = 0; i < 100; i++){
        auto x  = rand()%100;
        auto y = rand()%100;
        cout << "insert: x: " << x << " y: " << y <<endl;
        v.push_back({x,y});
    }    
    return v;
}

bool validate(vector<pair<int,int>> p,int minX,int maxX,int minY,int maxY){
    cout << "Validando: " << endl;
    for(size_t i = 0; i < p.size(); i++){
        if(p[i].first >= minX && p[i].first <= maxX && p[i].second >= minY && p[i].second <= maxY){
            cout << "x: " << p[i].first << " y: " << p[i].second << endl;
            if(results[p[i]] == 0){
               return false;
            }
            else{
                results[p[i]]--;
            }
        }
        else{
            if(results[p[i]]!=0)
                return false;
        }
    }
    return true;
}


int main(){
    srand(time(NULL));

    vector<pair<int,int>> v= insertRandomPoints();
    sort(v.begin(),v.end());
    node *tree = nullptr;
    create(tree,v,0,v.size()-1);

    // 0 1
    // 2 6
    for (auto it:range_min_query(tree,6,70,5,30)){
       // cout<<"punto: x = "  << it.first << " y =  "<< it.second << endl;
        results[{it.first,it.second}]++;
    }
    cout << "MAPA " << endl;
    for(auto it:results){
        cout << "x: " << it.first.first << " y: " << it.first.second << " num: " << it.second << endl;
    }
    cout << "_--------------------" << endl;
     if(!validate(v,6,70,5,30)){
        cout << "MAL RESULTADO" << endl;
    }
     else
         cout << "RESULTADO CORRECTO" << endl;

}


