#include <bits/stdc++.h>
using namespace std;
#define directed false
#define Set unordered_set<int>
#define Dict unordered_map
#define contains(x) count(x)
#define foreach(exp) for (const int& exp)

int C(int n, int k) {
    int res = 1;
    if (k > n - k) k = n - k;

    for (int i = 0; i < k; ++i){
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

vector<Set> G;

void edge(int u, int v){
    G[u].insert(v);
    if(!directed) G[v].insert(u);
}

template <typename Type>
int random(Type &S){
    int randomVal = rand() % S.size();
    auto it = S.begin();
    advance(it, randomVal);
    return *it;
}

double E(Set &S){
    double e = 0;
    auto i = S.begin(); ++i;
    for (; i != S.end(); ++i) {
        for (auto j = S.begin(); j != i; ++j) {
            if(G[*i].find(*j) != G[*i].end() || G[*j].find(*i) != G[*j].end()) e++;
        }
    }
    return e;
}

bool isConnected(Set &S){
    stack<int> pilha;
    Dict<int, bool> mark;

    pilha.push(*S.begin());

    while(!pilha.empty()){
        int u = pilha.top();
        pilha.pop();

        mark[u] = true;

        foreach (v: G[u]) {
            if(S.contains(v) && !mark[v]){
                pilha.push(v);
            }
        }
    }

    for (const int& u: S) if(!mark[u]) return false;
    return true;
}

int numberOfEdges(Set &S){
    int ans = 0;
    foreach(u : S){
        foreach(v : G[u]){
            if(S.contains(u)) ans++;
        }
    }
    return ans / 2;
}

bool isGamaDense(Set &S, double gama){
    double lhs = numberOfEdges(S);
    double rhs = C(S.size(), 2);
    return lhs >= (gama * rhs);
}

bool isGamaClique(Set &S, double gama){
    if(!isConnected(S)) return false;
    return isGamaDense(S, gama);
}

double PHI(Set &R, double gama){
    //  PHI(R) = |E(R)| - gama C(|R|, 2)
    double e = E(R);
    return e - (gama * C(R.size(), 2));
}

double PHIs(Set S, Set &R){
    //  PHIs(R) = PHI(S u R)
    foreach(u : S) R.insert(u);
    return PHI(R, 1);   //here should be gama instead of 1
}

double DELTAsx(Set S, int x, int y){
    // DELTAsx = PHIsu{x}({y}) - PHIs ({y}).
    Set Y; Y.insert(y);
    double rhs = PHIs(S, Y);
    S.insert(x);
    return PHIs(S, Y) - rhs;
}


bool isGamaVertex(Set &S, int v, double gama){
    S.insert(v);
    bool ans = isGamaClique(S, gama);
    S.erase(v);
    return ans;
}

Set N(Set &S){
    Set NS;
    foreach(u : S){
        foreach(v : G[u]){
            if(!S.contains(v)){
                NS.insert(v);
            }
        }
    }
    return NS;
}

Set Ngama(Set S, double gama){
    Dict<int, bool> used;
    Set Ny;
    foreach (u : S) {
        if(used.contains(u)) continue;
        foreach(v : G[u]){
            if(!S.contains(v)){
                if(used[v]) continue;
                used[v] = true;
                if(isGamaVertex(S, v, gama)){
                    Ny.insert(v);
                }
            }
        }
    }
    return Ny;
}

Set construct_dsubg(double gama){
    double gama_star = 1;
    Set S, S_star;
    S_star.insert(rand() % G.size());   //here it should be a random vertex from G
                                        //but for testing, it could be a choice
    while(gama_star >= gama){
        S = S_star;
        Set Ny_star = Ngama(S, gama_star);
        int x = -1;
        if(Ny_star.size() > 0){
            x = random(Ny_star);
        }
        else{
            Set NS = N(S);
            if(NS.empty()) return S;
            x = random(NS);
        }
        S_star = S; S_star.insert(x);
        gama_star = numberOfEdges(S_star) / C(S_star.size(), 2);
    }
    return S;
}

void readGraph(){
    freopen("adj_list.txt", "r", stdin);
    int gsize; cin>>gsize; getchar();
    G = vector<Set>(gsize);
    string line;
    int vertex = 0;
    while( getline( cin, line ) ){
        istringstream iss( line );
        int number;
        while( iss >> number ) G[vertex].insert(number);
        vertex++;
    }
}

void showGraph(){
    for(int i = 0; i < G.size(); i++){
        foreach(u : G[i]){
            cout<<u<<" ";
        }
        cout<<endl;
    }
}

int main(){
    srand(time(0));
    readGraph();


}
