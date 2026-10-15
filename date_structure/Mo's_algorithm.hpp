struct Mo{
  int N;
  vector<pair<int,int>>query;
  Mo(int _N):N(_N){}
  void add_query(int l,int r){query.emplace_back(make_pair(l,r));}
  template<typename AL,typename AR,typename EL,typename ER,typename O>
  void mo(const AL&add_left,const AR&add_right,const EL&erase_left,const ER&erase_right,const O&out){
    int Q=query.size();
    if(!Q)return;
    int bs=max(1,N/(int)sqrt(Q));
    vector<int>ord(Q);
    for(int i=0;i<Q;i++)ord[i]=i;
    sort(ord.begin(),ord.end(),[&](int&i,int&j){
      if(query[i].first/bs!=query[j].first/bs)return query[i]<query[j];
      if((query[i].first/bs)%2)return query[i].S<query[j].S;
      return query[i].S>query[j].S;
    });
    int l=0,r=0;
    for(int i=0;i<Q;i++){
      int ql=query[ord[i]].first;
      int qr=query[ord[i]].second;
      while(l>ql)add_left(--l);
      while(r<qr)add_right(r++);
      while(l<ql)erase_left(l++);
      while(r>qr)erase_right(--r);
      out(ord[i]);
    }
  }
};