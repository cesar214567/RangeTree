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
    if (a.second==b.second){
        return a.first<b.first;
    } else{
        return a.second<b.second;
    }
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
    while(temp && temp->left && temp->right){
        if(valuemin <= temp->value){
            temp = temp->left;
        }
        else{
            if(valuemin>=temp->left->value && valuemin<= temp->right->value){
                temp =temp->left;
            }else{
                temp = temp->right;

            }
        }
    }
    
    while (temp){
        if(temp->point.second<=valuehigh ){
            if(temp->point.second >= valuemin  && temp->point.first >= valueminX && temp->point.first <= valuemaxX){
                ret.push_back(temp->point);
            }
        }else{
            break;
        }
        temp = temp->next;
    }
    return ret;
}
void print(node* root){
    auto temp = root->subtree;
    while(temp->left){
        temp =temp->left;
    }
    cout<<endl;
    while(temp){
        temp= temp->next;
    }
}


vector<pair<int,int>> range_min_query(node* &st, int valueminX,int valuehighX, int valueminY,int valuehighY){
    auto temp = st;
    while(temp->left){
        if( (valueminX <= temp->value && valuehighX >= temp->value) || valueminX == temp->value || valuehighX == temp->value){
        //if(valueminX <= temp->value && valuehighX >= temp->value){
            return range_min_query2(temp->subtree,valueminY,valuehighY, valueminX, valuehighX); 
        }
        else if(valueminX <= temp->value && valuehighX <= temp->value){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return vector <pair <int, int>>();
}


vector<pair<int,int>> insertRandomPoints(int num_elements){
    vector<pair<int,int>> v;
    for(int i = 0; i < num_elements; i++){
        auto x  = rand()%100;
        auto y = rand()%100;
        v.push_back({x,y});
    }    
    return v;
}


bool create_map(vector<pair<int,int>> p,int minX,int maxX,int minY,int maxY){
    results.clear();
    for(size_t i = 0; i < p.size(); i++){
        if(p[i].first >= minX && p[i].first <= maxX && p[i].second >= minY && p[i].second <= maxY){
            results[p[i]]++;
        }
    }
    return true;
}
bool validate(vector<pair<int,int>> p,int minX,int maxX,int minY,int maxY){
    //cout << "Validando...(brute force) " << endl;
    for(size_t i = 0; i < p.size(); i++){
        if(p[i].first >= minX && p[i].first <= maxX && p[i].second >= minY && p[i].second <= maxY){
            results[p[i]]--;
        }else{
            return false;
        }
    }
    bool funciono = true;
    for(auto it:results){
        if(it.second != 0){
            //cout << "(" << it.first.first << ", "<< it.first.second << ")" << "*:" << it.second << "\n";
            funciono = false;
        }
    }
    if(!funciono){
        //cout<<"Resultado incorrecto"<<endl;
        return false;
    }
    return true;
}

void stress_testing(vector<int>& num_queries){
    cout << "** Stress Testing **\n";
    vector<pair<int,int>> v= insertRandomPoints(100000);
    //vector<pair<int,int>> v = {{20,1}, {40,97}, {49,54}, {52,2}, {67,91}, {71,72}, {71,77},{73,69}, {74,2},{99,22}};
    sort(v.begin(),v.end());
    node *tree = nullptr;
    create(tree,v,0,v.size()-1);
    for(auto num_elements : num_queries){
        cout << "\nTesting: " << num_elements << " elementos\n";
        //print(tree);
        // Start Test
        int timeExecution = 0;
        int x1, x2, y1, y2;
        int queriesOK = 0;
        for(int i = 0; i < num_elements; i++){
            x1 = rand()%100;
            x2 = rand()%100;
            y1 = rand()%100;
            y2 = rand()%100;
            //cout << x1 << " " << x2 << " " << y1 << " " << y2 << "\n";
            auto t1 = std::chrono::high_resolution_clock::now();
            auto result_query = range_min_query(tree, min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2));
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            //cout << "Tiempo de ejecución: " << duration << " milliseconds\n";
            /*for(auto it:result_query){
                cout<<it.first<<" "<<it.second<<endl;
            }*/
            // Validacion Brute Force
            create_map(v,min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2));
            if(!validate(result_query, min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2))){
                //cout<<"Validacion fallida: devolvio un resultado erroneo"<<endl;
            }
            else{
                //cout << "Validacion exitosa.\n";
                queriesOK++;
                timeExecution += duration;
            }
        }
        cout << "Queries OK: " << queriesOK << "\n";
        cout << "Tiempo promedio de ejecución: " << timeExecution/queriesOK << " microsegundos\n";
    }
}

int main(){
    srand(time(NULL));
    vector<int> num_queries = {10, 100, 1000, 10000};
    stress_testing(num_queries);
    return 0;
}


