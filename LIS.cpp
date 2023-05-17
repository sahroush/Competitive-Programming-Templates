#include <bits/stdc++.h>

using namespace std;

int LIS(vector <int> &vec){
    multiset <int> st;
    for(int x : vec){
        st.insert(x);
        auto it = st.lower_bound(x);
        it++;
        if(it != st.end())
            st.erase(it);
    }
    return st.size();
}

int n;
vector <int> vec;

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i = 0 ; i < n ; i ++){
        int x;
        cin >> x;
        vec.push_back(x);
    }   
    cout << LIS(vec);
    return 0;
}