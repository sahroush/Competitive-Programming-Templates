struct range{
	set < pii > st;
	void add(int l , int r , vector < pii > &vec){
		vec.clear();
		auto L = st.lower_bound({l , 0});
		auto R = st.upper_bound({r , Inf});
		if(L != st.begin()){
			L --;
			if((*L).second < l)L++;
		}
		vector < pii > v;
		for(auto it = L ; it != R ; it = st.erase(it))v.pb(*it);
		if(v.empty()){
			vec.pb({l , r});
			st.insert({l , r});
			return;
		}
		int cur = l;
		int LL = l , RR = r;
		for(auto ab : v){
			auto a = ab.first;
			auto b = ab.second;
			if(a > cur)
				vec.pb({cur , a-1}), cur = a;
			LL = min(LL , a) , RR = max(RR , b);
			cur = min(r , b) + 1;
			st.erase({a , b});
		}
		if(v.back().second < r)vec.pb({cur , r});
		st.insert({LL , RR});
	}
	void remove(int l , int r , vector < pii > &vec){
		vec.clear();
		auto L = st.lower_bound({l , 0});
		auto R = st.upper_bound({r , Inf});
		if(L != st.begin()){
			L --;
			if((*L).second < l)L++;
		}
		vector < pii > v;
		for(auto it = L ; it != R ; it = st.erase(it))v.pb(*it);
		if(v.empty()){
			return;
		}
		for(auto ab : v){
			auto a = ab.first;
			auto b = ab.second;
			st.erase({a , b});
			vec.pb({max(l , a), min(b , r)});
			if(a < l)
				st.insert({a , l-1});
			if(b > r)
				st.insert({r+1 , b});
		}
	}
};
