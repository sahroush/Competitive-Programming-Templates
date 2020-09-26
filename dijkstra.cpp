void djk(int start){
    for (int i = 0  ; i <= n ; i ++){
        dist[i] = INF;
    }
    dist[start] = 0;
    st.insert(pii(start , dist[start]));
    while (!st.empty()){
        pii v = *st.begin();
        st.erase(st.begin());
        if(mark[v.first]){
            continue;
        }
        mark[v.first] = 1;
        for (auto u : adj[v.first]){
            if(!mark[u.first] and dist[u.first] > dist[v.first] + u.second){
                dist[u.first] =  dist[v.first] + u.second;
                st.insert(pii(u.first , dist[u.first]));
            }
        }
    }
}