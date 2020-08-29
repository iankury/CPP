#include <bits/stdc++.h>

const double eps = 1e-8;
const int oo = 0x3f3f3f3f;

typedef long long ll;
using namespace std;

#define fr(a,b,c) for(int a = b; a < c; a++)
#define rep(a,b) fr(a,0,b)
#define ln printf("\n")
#define db if(0)
#define dbs(x) db rep(i,x) printf(" "); db
#define pb push_back

#define sarr(r,n) rep(zi,n) scanf("%d", &r[zi])
#define parr(r,n) printf("%d", r[0]); fr(zi,1,n) printf(" %d", r[zi]);  ln; 
#define mem(r,v) memset(r, v, sizeof r)

int d, n, m;

int px[111];
int py[111];

bool read(){
    if(scanf("%d%d%d", &n, &d, &m) == EOF) return false;    
    
    rep(i,m){
      scanf("%d%d", &px[i], &py[i]);
    }
    
    return true;
}

bool inside(int x, int y){
  int yy = x-d;  
  if(y < yy) return false;  
  yy = x+d;  
  if(y > yy) return false;  
  yy = d-x;
  if (y < yy) return false;  
  yy = n - (x-(n-d));
  if (y > yy) return false;
  
  return true;  
}

void process(){
  rep(i,m){
    if(inside(px[i], py[i])){
      printf("YES\n");
    }    
    else{
      printf("NO\n");
    }
  }

}

int main(){ 
    int t = -1;
    //scanf("%d", &t);

    while(t-- && read()){       
        process();
    }
    
    return 0;
}
