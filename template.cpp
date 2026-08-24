#include<bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
using namespace std;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
struct dsu{
	public:
		dsu()=delete;
		dsu(int _n):n(_n),f(_n+1,-1){}
		int merge(int a,int b){int x=find(a),y=find(b);if(x==y)return x;if(-f[x]<-f[y])swap(x,y);return f[x]+=f[y],f[y]=x;}
		bool same(int x,int y){return find(x)==find(y);}
		int find(int x){if(f[x]<0)return x;return f[x]=find(f[x]);}
		int size(int x){return -f[find(x)];}
	private:
		int n;
		vector<int>f;
};
template<class T>struct BIT{
	public:
		BIT()=delete;
		BIT(int _n):n(_n),f(_n+1){};
		BIT(vector<T>a):n(a.size()-1),f(a.size(),0){f=a;for(int i=1;i<=n;i++){int fa=i+(i&-i);if(fa<=n)f[fa]+=f[i];}}
		void add(int p,T x){while(p<=n){f[p]+=x;p+=p&-p;}}
		T sum(int p){T s=0;while(p>0){s+=f[p];p-=p&-p;}return s;}
		T sum(int l,int r){return sum(r)-sum(l-1);}
	private:
		int n;
		vector<T>f;
};
namespace math{
	constexpr ll smod(ll x,ll m)noexcept{x%=m;if(x<0)x+=m;return x;}
	constexpr ll qmi(ll x,ll n,int m){if(m==1)return 0;ui _m=static_cast<ui>(m);ull r=1,y=smod(x,m);while(n){if(n&1)r=(r*y)%_m;y=(y*y)%_m;n>>=1;}return static_cast<ll>(r);}
	constexpr bool isprime(int n)noexcept{if(n<=1)return 0;if(n==2||n==7||n==61)return 1;if(n%2==0)return 0;ll d=n-1;while(d%2==0)d/=2;constexpr ll b[3]={2,7,61};for(ll a:b){ll t=d;ll y=qmi(a,t,n);while(t!=n-1&&y!=1&&y!=n-1){y=(y*y)%n;t<<=1;}if(y!=n-1&&t%2==0)return 0;}return 1;}
	constexpr pair<ll,ll>invgcd(ll a,ll b){a=smod(a,b);if(a==0)return {b,0};ll s=b,t=a,m0=0,m1=1;while(t){ll u=s/t;s-=t*u,m0-=m1*u;swap(s,t),swap(m0,m1);}if(m0<0)m0+=b/s;return {s,m0};}
	constexpr ll invmod(ll x,ll m){return invgcd(x,m).sc;}
	int ceilpow2(int n)noexcept{if(n<=1)return 0;return 32-__builtin_clz(n-1);}
	int bsf(ui n){return __builtin_ctz(n);}
	vector<int>sieve(int n){vector<int>res;vector<bool>isp(n+1,1);isp[0]=isp[1]=false;for(int j=4;j<=n;j+=2)isp[j]=false;for(int i=3;i*i<=n;i+=2)if(isp[i])for(int j=i*i;j<=n;j+=i*2)isp[j]=false;if(n>=2)res.pb(2);for(int j=3;j<=n;j+=2)if(isp[j])res.pb(j);return res;}
	pair<ll,ll> crt(const vector<ll>&r,const vector<ll>&m) {int n=int(r.size());ll r0=0,m0=1;for(int i=0;i<n;i++){ll r1=smod(r[i],m[i]),m1=m[i];if(m0<m1){swap(r0,r1);swap(m0,m1);}if(m0%m1==0){if(r0%m1!=r1)return {0,0};continue;}ll g,im;tie(g,im)=invgcd(m0, m1);ll u1=(m1/g);if((r1-r0)%g)return {0,0};ll x=(r1-r0)/g%u1*im%u1;r0+=x*m0;m0*=u1;if(r0<0)r0+=m0;}return {r0,m0};}
};
struct barrett{
	ui _m;ull im;
	barrett(ui m):_m(m),im((ull)(-1)/m+1){}
	ui umod()const{return _m;}
	ui mul(ui a,ui b)const{ull z=a;z*=b;ull x=(ull)(((unsigned __int128)(z)*im)>>64);ui v=(ui)(z-x*_m);if(_m<=v)v+=_m;return v;}
};
template<int m>struct static_modint{
	using mint=static_modint;
	static constexpr int mod()noexcept{return m;}
	static constexpr ui umod()noexcept{return static_cast<ui>(m);}
	static constexpr bool prime=math::isprime(m);
	static mint raw(int v)noexcept{mint x;x._v=static_cast<ui>(v);return x;}
	static_modint()noexcept:_v(0){}
	template<class T,enable_if_t<is_signed<T>::value,int> =0>
	static_modint(T v)noexcept{ll x=static_cast<ll>(v%static_cast<ll>(umod()));if(x<0)x+=umod();_v=static_cast<ui>(x);}
	template<class T,enable_if_t<is_unsigned<T>::value,int> =0>
	static_modint(T v)noexcept{_v=static_cast<ui>(v%umod());}
	static_modint(bool v)noexcept{_v=static_cast<ui>(v%umod());}
	ui val()const noexcept{return _v;}
	mint&operator++()noexcept{++_v;if(_v==umod())_v=0;return *this;}
	mint&operator--()noexcept{if(_v==0)_v=umod();--_v;return *this;}
	mint operator++(int)noexcept{mint tmp=*this;++*this;return tmp;}
	mint operator--(int)noexcept{mint tmp=*this;--*this;return tmp;}
	mint&operator+=(const mint&rhs)noexcept{_v+=rhs._v;if(_v>=umod())_v-=umod();return *this;}
	mint&operator-=(const mint&rhs)noexcept{if(_v<rhs._v)_v+=umod();_v-=rhs._v;return *this;}
	mint&operator*=(const mint&rhs)noexcept{ull z=_v;z*=rhs._v;_v=static_cast<ui>(z%umod());return *this;}
	mint&operator/=(const mint&rhs){return *this=*this*rhs.inv();}
	mint operator+()const noexcept{return *this;}
	mint operator-()const noexcept{return mint()-*this;}
	mint pow(ll n)const{mint x=*this,r=1;while(n){if(n&1)r*=x;x*=x;n>>=1;}return r;}
	mint inv()const{if constexpr(prime)return pow(umod()-2);else{auto eg=math::invgcd(_v,m);return raw(static_cast<int>(eg.second));}}
	friend mint operator+(const mint& lhs,const mint& rhs)noexcept{return mint(lhs)+=rhs;}
	friend mint operator-(const mint& lhs,const mint& rhs)noexcept{return mint(lhs)-= rhs;}
	friend mint operator*(const mint& lhs,const mint& rhs)noexcept{return mint(lhs)*=rhs;}
	friend mint operator/(const mint& lhs,const mint& rhs){return mint(lhs)/=rhs;}
	friend bool operator==(const mint& lhs,const mint& rhs)noexcept{return lhs._v==rhs._v;}
	friend bool operator!=(const mint& lhs,const mint& rhs)noexcept{return lhs._v!=rhs._v;}
	private:
		ui _v;
};
template<int id>struct dynamic_modint{
	using mint=dynamic_modint;
	static int mod()noexcept{return static_cast<int>(bt.umod());}
	static void set_mod(int m){bt=barrett(m);}
	static mint raw(int v)noexcept{mint x;x._v=static_cast<ui>(v);return x;}
	dynamic_modint()noexcept:_v(0){}
	template<class T,enable_if_t<is_integral<T>::value,int> =0>
	dynamic_modint(T v)noexcept{if constexpr(is_signed<T>::value){ll x=static_cast<ll>(v%static_cast<ll>(mod()));if(x<0)x+=mod();_v=static_cast<ui>(x);}else _v=static_cast<ui>(v%mod());}
	ui val()const noexcept{return _v;}
	mint&operator++()noexcept{if(++_v==umod())_v=0;return *this;}
	mint&operator--()noexcept{if(_v==0)_v=umod();--_v;return *this;}
	mint operator++(int)noexcept{mint t=*this;++*this;return t;}
	mint operator--(int)noexcept{mint t=*this;--*this;return t;}
	mint&operator+=(const mint& rhs)noexcept{_v+=rhs._v;if(_v>=umod())_v-=umod();return *this;}
	mint&operator-=(const mint& rhs) noexcept {if(_v<rhs._v)_v+=umod();_v-=rhs._v;return *this;}
	mint&operator*=(const mint& rhs)noexcept{_v=bt.mul(_v,rhs._v);return *this;}
	mint&operator/=(const mint& rhs){return *this=*this*rhs.inv();}
	mint operator+()const noexcept{return *this;}
	mint operator-()const noexcept{return mint()-*this;}
	mint pow(ll n)const{mint x=*this,r=1;while(n){if(n&1)r*=x;x*=x;n>>=1;}return r;}
	mint inv()const{auto eg=math::invgcd(_v,mod());return raw(static_cast<int>(eg.second));}
	friend mint operator+(const mint& lhs,const mint& rhs)noexcept{return mint(lhs)+=rhs;}
	friend mint operator-(const mint& lhs,const mint& rhs)noexcept{return mint(lhs)-=rhs;}
	friend mint operator*(const mint& lhs,const mint& rhs)noexcept{return mint(lhs)*=rhs;}
	friend mint operator/(const mint& lhs,const mint& rhs){return mint(lhs)/=rhs;}
	friend bool operator==(const mint& lhs,const mint& rhs)noexcept{return lhs._v==rhs._v;}
	friend bool operator!=(const mint& lhs,const mint& rhs)noexcept{return lhs._v!=rhs._v;}
	private:
		ui _v;
		static barrett bt;
		static ui umod()noexcept{return bt.umod();}
};
template<int id>barrett dynamic_modint<id>::bt=998244353;
template<class S,S(*op)(S,S),S(*e)()>struct segtree{
	segtree()=delete;
	explicit segtree(int n):_n(n){log=math::ceilpow2(_n);size=1<<log;d=vector<S>(2*size,e());}
	explicit segtree(const vector<S>&v):_n(static_cast<int>(v.size())-1){log=math::ceilpow2(_n);size=1<<log;d.resize(2*size);if(_n>0){copy(v.begin()+1,v.end(),d.begin()+size);fill(d.begin()+size+_n,d.end(),e());for(int i=size-1;i>=1;i--)update(i);}else fill(d.begin(),d.end(),e());}
	void set(int p,const S& x){p=p+size-1;d[p]=x;for(int i=1;i<=log;i++)update(p>>i);}
	const S& get(int p)const{return d[p+size-1];}
	S prod(int l,int r)const{if(l>r)return e();S sml=e(),smr=e();for(int L=l+size-1,R=r+size;L<R;L>>=1,R>>=1){if(L&1)sml=op(sml,d[L++]);if(R&1)smr=op(d[--R],smr);}return op(sml,smr);}
	const S& all_prod()const{return d[1];}
	template<bool(*f)(const S&)>int max_right(int l)const{return max_right(l,[](const S& x){return f(x);});}
	template<class F>int max_right(int l,F f)const{if(l>_n)return _n;int cur=l+size-1;S sm=e();do{cur>>=math::bsf(static_cast<ui>(cur));if(!f(op(sm,d[cur]))){while(cur<size){cur=(2*cur);if(f(op(sm,d[cur]))){sm=op(sm,d[cur]);cur++;}}return cur-size;}sm=op(sm,d[cur]);cur++;}while((cur&(cur-1)));return _n;}
	template<bool(*f)(const S&)>int min_left(int r)const{return min_left(r,[](const S& x){return f(x);});}
	template<class F>int min_left(int r,F f)const{if(r<1)return 1;int cur=r+size-1;S sm=e();do{while(cur>1&&(cur&1))cur>>=1;if(!f(op(d[cur],sm))){while(cur<size){cur=(2*cur+1);if(f(op(d[cur],sm))){sm=op(d[cur],sm);cur--;}}return cur-size+2;}sm=op(d[cur],sm);cur--;}while((cur&(cur-1)));return 1;}
  	private:
		int _n,size,log;
		vector<S> d;
		void update(int k){d[k]=op(d[2*k],d[2*k+1]);}
};
template<class S,S(*op)(S,S),S(*e)(),class F,S(*mapping)(F,S),F(*composition)(F,F),F(*id)()>struct lazy_segtree{
	lazy_segtree()=delete;
	explicit lazy_segtree(int n):_n(n){log=math::ceilpow2(_n);size=1<<log;d=vector<S>(2*size,e());lz=vector<F>(size,id());}
	explicit lazy_segtree(const vector<S>& v):_n(static_cast<int>(v.size())-1){log=math::ceilpow2(_n);size=1<<log;d.resize(2*size);lz=vector<F>(size,id());if(_n>0){copy(v.begin()+1,v.end(),d.begin()+size);fill(d.begin()+size+_n,d.end(),e());for(int i=size-1;i>=1;i--)update(i);}else fill(d.begin(), d.end(), e());}
	void set(int p,const S& x){p=p+size-1;for(int i=log;i>=1;i--)push(p>>i);d[p]=x;for(int i=1;i<=log;i++)update(p>>i);}
	S get(int p){p=p+size-1;for(int i=log;i>=1;i--)push(p>>i);return d[p];}
	S prod(int l,int r){if(l>r)return e();int L=l+size-1,R=r+size;for(int i=log;i>=1;i--){if(((L>>i)<<i)!=L)push(L>>i);if(((R>>i)<<i)!=R)push((R-1)>>i);}S sml=e(),smr=e();for(;L<R;L>>=1,R>>=1){if(L&1)sml=op(sml,d[L++]);if(R&1)smr=op(d[--R],smr);}return op(sml,smr);}
	const S& all_prod()const{return d[1];}
	void apply(int p,const F& f){p=p+size-1;for(int i=log;i>=1;i--)push(p>>i);d[p]=mapping(f,d[p]);for(int i=1;i<=log;i++)update(p>>i);}
	void apply(int l, int r, const F& f){if(l>r)return;int L=l+size-1,R=r+size;for(int i=log;i>=1;i--){if(((L>>i)<<i)!=L)push(L>>i);if(((R>>i)<<i)!=R)push((R-1)>>i);}{int l2=L,r2=R;for(;L<R;L>>= 1,R>>=1){if(L&1)all_apply(L++,f);if(R&1)all_apply(--R,f);}L=l2;R=r2;}for(int i=1;i<=log;i++){if(((L>>i)<<i)!=L)update(L>>i);if(((R>>i)<<i)!=R)update((R-1)>>i);}}
	template<bool(*f)(const S&)>int max_right(int l){return max_right(l,[](const S& x){return f(x);});}
	template<class G>int max_right(int l,G g){if(l>_n)return _n;int cur=l+size-1;for(int i=log;i>=1;i--)push(cur>>i);S sm=e();do{while((cur&1)==0)cur>>=1;if(!g(op(sm,d[cur]))){while(cur<size){push(cur);cur=(2*cur);if(g(op(sm,d[cur]))){sm=op(sm,d[cur]);cur++;}}return cur-size;}sm=op(sm,d[cur]);cur++;}while(cur&(cur-1));return _n;}
	template<bool(*f)(const S&)>int min_left(int r){return min_left(r,[](const S& x){return f(x);});}
	template<class G> int min_left(int r,G g){if(r<1)return 1;int cur=r+size-1;for(int i=log;i>=1;i--)push(cur>>i);S sm=e();do{while(cur>1&&(cur&1))cur>>=1;if(!g(op(d[cur],sm))){while(cur<size){push(cur);cur=(2*cur+1);if(g(op(d[cur],sm))){sm=op(d[cur],sm);cur--;}}return cur-size+2;}sm=op(d[cur],sm);if((cur&-cur)==cur)break;cur--;}while(1);return 1;}
	private:
		int _n,size,log;
		vector<S> d;
		vector<F> lz;
		void update(int k){d[k]=op(d[2*k],d[2*k+1]);}
		void all_apply(int k,const F& f){d[k]=mapping(f,d[k]);if(k<size)lz[k]=composition(f,lz[k]);}
		void push(int k){all_apply(2*k,lz[k]);all_apply(2*k+1,lz[k]);lz[k]=id();}
};
namespace IO{
	void fastIO(){ios::sync_with_stdio(0);cin.tie(0);}
	void openf(string fileName){freopen((fileName+".in").c_str(),"r",stdin);freopen((fileName+".out").c_str(),"w",stdout);}
	int read(){int x=0;bool flag=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')flag=0;ch=getchar();}while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}if(flag)return x;return x=(~x)+1;}
	template<typename T>void read(T &x){x=0;bool flag=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')flag=0;ch=getchar();}while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}if(flag)return x;return x=(~x)+1;}
	template<typename T>void write(T x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10+'0');}
}
namespace rd{
	mt19937 rand32(chrono::high_resolution_clock::now().time_since_epoch().count());
	int randint(int l,int r){uniform_int_distribution<>dist(l,r);return dist(rand32);}
}
template<const int M>struct Comb_static{
	using mint=static_modint<M>;
	vector<mint>fact,invfact;
	int N=0,unex=0;
	Comb_static()=delete;
	Comb_static(int n,int _unex):N(n),unex(_unex){fact.resize(N+1),invfact.resize(N+1);fact[0]=fact[1]=invfact[0]=1;for(int i=2;i<=N;i++)fact[i]=fact[i-1]*i;invfact[N]=math::invmod(fact[N].val(),M);for(int i=N-1;i>=1;i--)invfact[i]=invfact[i+1]*(i+1);}
	ll comb(ll m,ll n){if(n<0||n>m)return unex;if(n==0||n==m)return 1;return (fact[m]*invfact[n]*invfact[m-n]).val();}
};
template<int id>struct Comb_dynamic{
	using mint=dynamic_modint<id>;
	vector<mint>fact,invfact;
	int N=0,M=0,unex=0;
	Comb_dynamic()=delete;
	Comb_dynamic(int n,int mod,int _unex):N(n),M(mod),unex(_unex){fact.resize(N+1),invfact.resize(N+1);mint::set_mod(M);fact[0]=fact[1]=invfact[0]=1;for(int i=2;i<=N;i++)fact[i]=fact[i-1]*i;invfact[N]=math::invmod(fact[N].val(),M);for(int i=N-1;i>=1;i--)invfact[i]=invfact[i+1]*(i+1);}
	ll comb(ll m,ll n){if(n<0||n>m)return unex;if(n==0||n==m)return 1;return (fact[m]*invfact[n]*invfact[m-n]).val();}
};
namespace str{
	vector<int>kmp(string s){int m=s.length(),p=0;vector<int>nxt(m+1);s=' '+s;nxt[1]=0;for(int i=2;i<=m;i++){while(p&&s[i]!=s[p+1])p=nxt[p];if(s[i]==s[p+1])p++;nxt[i]=p;}return nxt;}
	vector<int>manacher(string st){string s="##";for(char c:st){s+=c;s+='#';}int n=s.size();vector<int>p(n+1);s=' '+s;int mid=0,rgt=-1;for(int i=1;i<=n;i++){if(i>rgt)p[i]=1;else p[i]=min(p[2*mid-i],rgt-i);while(s[i+p[i]]==s[i-p[i]])p[i]++;if(p[i]+i>rgt){rgt=p[i]+i;mid=i;}}return p;}
};
template<class T>struct Matrix{
	ui n,m;
	vector<T>data;
	Matrix()=delete;
	Matrix(ui n,ui m):n(n),m(m),data(n*m,T()){}
	static Matrix I(ui s){Matrix r(s,s);for(ui i=1;i<=s;++i)r[i][i]=T(1);return r;}
	void set(ui i,ui j,const T& k){data[(i-1)*m+j-1]=k;}
	struct P{T* p;T& operator[](ui c){return p[c-1];}};
	struct CP{const T* p;const T& operator[](ui c)const{return p[c-1];}};
	P operator[](ui r){return{data.data()+(r-1)*m};}
	CP operator[](ui r)const{return{data.data()+(r-1)*m};}
	Matrix operator+(const Matrix& o)const{Matrix r(n,m);for(ui i=0;i<n*m;++i)r.data[i]=data[i]+o.data[i];return r;}
	Matrix operator-(const Matrix& o)const{Matrix r(n,m);for(ui i=0;i<n*m;++i)r.data[i]=data[i]-o.data[i];return r;}
	Matrix operator*(const Matrix& o)const{Matrix r(n,o.m);for(ui i=1;i<=n;++i)for(ui k=1;k<=m;++k){T v=(*this)[i][k];if(v!=T())for(ui j=1;j<=o.m;++j)r[i][j]+=v*o[k][j];}return r;}
	Matrix operator^(ull p)const{Matrix r=I(n),b=*this;for(;p;p>>=1,b=b*b)if(p&1)r=r*b;return r;}
	static inline T _inv(const T& x){if constexpr(is_floating_point_v<T>)return T(1)/x;else if constexpr(requires{x.inv();})return x.inv();else{static_assert(!is_integral_v<T>,"Matrix::gauss requires a field-like scalar type (floating point or type with inv()/division)");return T(1)/x;}}
	pair<int,T> gauss(Matrix* B=nullptr){ui r=1;T d=1;for(ui c=1;c<=m&&r<=n;++c){ui p=r;if constexpr(is_floating_point_v<T>){for(ui i=r+1;i<=n;++i)if(abs((*this)[i][c])>abs((*this)[p][c]))p=i;if(abs((*this)[p][c])<1e-9){d=0;continue;}}else{for(ui i=r;i<=n;++i)if((*this)[i][c]!=T()){p=i;break;}if((*this)[p][c]==T()){d=0;continue;}}if(p!=r){d=-d;for(ui j=1;j<=m;++j)swap((*this)[r][j],(*this)[p][j]);if(B)for(ui j=1;j<=B->m;++j)swap((*B)[r][j],(*B)[p][j]);}T iv=_inv((*this)[r][c]);d*=(*this)[r][c];for(ui j=c;j<=m;++j)(*this)[r][j]*=iv;if(B)for(ui j=1;j<=B->m;++j)(*B)[r][j]*=iv;for(ui i=1;i<=n;++i)if(i!=r&&(*this)[i][c]!=T()){T f=(*this)[i][c];for(ui j=c;j<=m;++j)(*this)[i][j]-=f*(*this)[r][j];if(B)for(ui j=1;j<=B->m;++j)(*B)[i][j]-=f*(*B)[r][j];}++r;}return {r-1,(r<=n&&n==m)?T(0):d};}
	T det()const{Matrix a=*this;return a.gauss().sc;}
	pair<int,Matrix> solve(Matrix b)const{
		if(n!=b.n)return {-1,Matrix(0,0)};
		Matrix a=*this;
		auto [r,_]=a.gauss(&b);
		auto is_zero = [](const T& v){
			if constexpr(is_floating_point_v<T>)return std::abs(v)<1e-9;
			else return v==T();
		};
		for(ui i=r+1;i<=n;++i)for(ui j=1;j<=b.m;++j)if(!is_zero(b[i][j]))return {-1,Matrix(0,0)};
		Matrix x(m,b.m);
		for(ui i=1,p=1;i<=n&&p<=(ui)r;++i){
			ui c=1;
			while(c<=m&&is_zero(a[i][c]))++c;
			if(c<=m){
				for(ui j=1;j<=b.m;++j)x[c][j]=b[i][j];
				++p;
			}
		}
		return {r,x};
	}
	pair<int,Matrix> solve(Matrix b)const{if(n!=b.n)return {-1,Matrix(0,0)};Matrix a=*this;auto [r,_]=a.gauss(&b);for(ui i=r+1;i<=n;++i)for(ui j=1;j<=b.m;++j)if(b[i][j]!=T())return {-1,Matrix(0,0)};Matrix x(m,b.m);for(ui i=1,p=1;i<=n&&p<=(ui)r;++i){ui c=1;while(c<=m&&a[i][c]==T())++c;if(c<=m){for(ui j=1;j<=b.m;++j)x[c][j]=b[i][j];++p;}}return {r,x};}
	pair<int,vector<T>> solve(const vector<T>& b)const{if(n!=b.size())return {-1,{}};Matrix B(n,1);for(ui i=0;i<n;++i)B.data[i]=b[i];auto [r,X]=solve(B);if(r==-1)return {-1,{}};return {r,X.data};}
};
template<class S,S(*op)(S,S),S(*e)()>struct ST{
	ST()=delete;
	int n,W;
	vector<S>d;
	ST(vector<S>a){if((n=a.size()-1)<=0)return;W=n+1;int K=__lg(n);d.resize((K+1)*W);copy(a.begin()+1,a.end(),d.begin()+1);for(int i=1;i<=K;++i){const S*p=d.data()+(i-1)*W;S*c=d.data()+i*W;for(int j=1,h=1<<(i-1),lim=n-(1<<i)+1;j<=lim;++j)c[j]=op(p[j],p[j+h]);}}
	inline S prod(int l,int r)const{if(__builtin_expect(l>r,0))return e();int k=__lg(r-l+1);const S*p=d.data()+k*W;return op(p[l],p[r-(1<<k)+1]);}
};
int main(){
	
}
/*

*/
