// https://github.com/TKTYI/TKTYI-library/blob/main/date_structure/treap.hpp
// PE680
// 反転と sum i*A[i]
mt19937_64 mt(512810410);
struct treap{
  struct Node {
    // 子のindex,0はdummy
    int left=0,right=0;
    // 優先度
    long long pr;
    // 左端の値,右端の値,部分木サイズ,反転の遅延
    // 閉区間
    long long L,R,si=0;
    bool rev=0;
    Node(long long _L,long long _R):si(abs(_R-_L)+1),L(_L),R(_R),rev(0){pr=mt();}
    Node(){}
  };
  int root;
  vector<Node>V;
  treap(long long N):root(1),V(2){V[1]=Node(0,N-1);}
  void update(int t){
    if(!t)return;
    V[t].si=abs(V[t].R-V[t].L)+1;
    V[t].si+=V[V[t].left].si;
    V[t].si+=V[V[t].right].si;
  }
  void push(int t){
    if(!t||!V[t].rev)return; 
    swap(V[t].left,V[t].right);
    if(V[t].left)V[V[t].left].rev^=1,swap(V[V[t].left].L,V[V[t].left].R);
    if(V[t].right)V[V[t].right].rev^=1,swap(V[V[t].right].L,V[V[t].right].R);
    V[t].rev=0;
  }
  void split(int t,long long k,int&l,int&r){
    if(!t){l=r=0;return;}      
    push(t);
    long long L=0;
    if(V[t].left)L=V[V[t].left].si;
    if(k<=L){
      int _l,_r;
      split(V[t].left,k,_l,_r);
      V[t].left=_r;l=_l;r=t;
    }
    else if(k>=L+abs(V[t].R-V[t].L)+1){
      int _l,_r;
      split(V[t].right,k-L-abs(V[t].R-V[t].L)-1,_l,_r);
      V[t].right=_l;l=t;r=_r;
    }
    else{
      k-=L;
      long long M=V[t].L<V[t].R?V[t].L+k:V[t].L-k;
      l=t;r=V.size();
      V.emplace_back(Node(M,V[t].R));
      V[r].right=V[t].right;
      V[t].R=M>V[t].L?M-1:M+1;
      V[t].right=0;
      update(r);
    }
    update(t);
  }
  void merge(int& t,int l,int r){
    if(!l){t=r;return;}
    if(!r){t=l;return;}
    push(l);push(r);  
    if(V[l].pr>V[r].pr){
      int _t;
      merge(_t,V[l].right,r);
      V[l].right=_t;t=l;
    }
    else{
      int _t;
      merge(_t,l,V[r].left);
      V[r].left=_t;t=r;
    }
    update(t);
  }
  void apply(long long l,long long r){
    int t1,t2,t3;
    split(root,r,t1,t3);
    split(t1,l,t1,t2);
    V[t2].rev^=1;
    swap(V[t2].L,V[t2].R);
    merge(t1,t1,t2);
    merge(root,t1,t3);
  }
  mint prod(int t,long long l,long long r){
    mint res=0;
    push(t);
    if(V[t].left)res+=prod(V[t].left,l,l+V[V[t].left].si-1);
    if(V[t].right)res+=prod(V[t].right,r-V[V[t].right].si+1,r);
    l+=V[V[t].left].si;
    r-=V[V[t].right].si;
    long long N=(abs(V[t].L-V[t].R)+1)%2000000000;
    if(V[t].L<V[t].R)res+=mint(l)*V[t].L*N+mint(l+V[t].L)*(N*(N-1)/2)+mint(N*(N-1)/2)*(2*N-1)/3;
    else res+=mint(l)*V[t].L*N+mint(V[t].L-l)*(N*(N-1)/2)-mint(N*(N-1)/2)*(2*N-1)/3;
    return res;
  }
  mint all_prod(){return prod(root,0,V[root].si-1);}
};