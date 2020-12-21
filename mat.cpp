struct Mat{
    int m[K][K];
    Mat(int diag = -1){
        ms(m , 0);
        if(diag==0)for(int i = 0 ; i < K ; i ++)m[i][i] = 1;
        if(diag>0)for(int i = 0 ; i < diag ; i ++)m[i][i+1]=1;
    }
    Mat operator* (const Mat &b) const{
        Mat c = Mat();
        for(int i = 0 ; i < K ; i ++)
            for(int k = 0 ; k < K ; k ++)
                for(int j = 0 ; j < K ; j ++)
                    c.m[i][j] = (ll(c.m[i][j]) + ll(m[i][k]) * b.m[k][j])%mod;
        return(c);
    }
};
Mat pw(Mat a, ll b){Mat res(0);while(b){if(b&1){res=(a*res);}a=(a*a);b>>=1;}return(res);}




struct matrix{
	vector < vector < int > > mat;
	int n , m;
	matrix (int N , int M){
		n = N , m = M;
		mat.resize(n);
		for(int i = 0 ; i < n ; i ++)mat[i].resize(m);
		for(int i = 0 ; i < n ; i ++)
			for(int j = 0 ; j < m ; j ++)
				mat[i][j] = 0;
	}
	friend matrix operator * (matrix &A , matrix &B){
		assert(A.m == B.n);
		int &n = A.n , &m = B.m;
		int &K = A.m;
		matrix C(n , m);
		auto &c = C.mat;
		auto &a = A.mat;
		auto &b = B.mat
		for(int i = 0 ; i < n ; i ++)
			for(int k = 0 ; k < K ; k ++)
				for(int j = 0 ; j < m ; j ++)
					c[i][j] = (1LL * c[i][j] + 1LL * a[i][k] * b[k][j])%mod;
		return(C);
	}
	friend matrix operator ^ (matrix a , ll b){
		matrix res(a.n , a.n);
		for(int i = 0 ; i < a.n ; i ++)res.mat[i][i] = 1;
		while(b){
			if(b&1)res = a*res;
			b>>=1;
			a = a * a;
		}
		return(res);
	}
};
