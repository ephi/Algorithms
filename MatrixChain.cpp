#define MAX_SIZE 100
/*
Given P = {a1,a2,a3,...,an} s.t a_i,a_(i+1) are the dimenssions of matrix mi(ex dimenssion of matrix m1 is a1 X a2, dimenssion of m2 is a2 X a3)
find the minimal number of operations to get product: m1 * m2 * m3 * ... * m_n-1
the problem is in fact to find the correct order of multications to get the least number of operations.
e.x: if P = { 10, 20 , 30 } -> m1 is of size 10 X 20, m2 is of size 20 X 30 there is only one way with 10 X 20 X 30 operations
     if p = { 10, 20, 30, 20 } -> m1 is of size 10 X 20, m2 is of size 20 X 30, m3 is of size 30 X 20 and there are 
                                  2 ways to calculate the product: (m1 * m2) * m3 or m1 * ( m2 *  m3)
                                  --> number of operations of first is: 10X20X30 (for m1 * m2 -size 10X30) + 10X30X20( t*m3, t=m1*m2 )
                                      number of operations of second is: 20X30X20 (m2 * m3 = t size 20X20) + 10X20X20(m1 * t)
                                      --> minimal number of operations is:   10X20X30 (for m1 * m2 -size 10X30) + 10X30X20( t*m3, t=m1*m2 )
 1) this problem has optimal substrucre: i.e every instance of the problem can be expressed of the same subproblems.
 let mc(i,j) - least number of operations in order to get the product of mi,mi+1,...,mj
 then: mc(i,j) = 0 <---> i = j  , 0 <= i, j < n-1
       mc(i,j) = min( mc(i,k) + mc(k+1,j) + p[i]*p[k+1]*p[j+1] ), i <= k < j 
       infact any least number of operations to get product of mi,mi+1,...,mj
       is really to find out the least number of operations for mi,mi+1,...,mk and for mk+1,mk+2,...,mj
       and then find out the number of operations to get A1*A2 where (mi * mi+1 * ... * mk)=A1  (mk+1 * ... * mj)=A2
       which expressed in the dimenssion array where dim(A1) = p[i] X p[k+1], dim(A2) = p[k+1] X p[j+1]
       therefore the number of operations if indeed: p[i] * p[k+1] * p[j+1].
  2) this problem has overlapping subproblems: because calculating mc(i,j) will require to calculate the solution to all sub problems in reapting manner.
  because of 2) an attempt to directly implement the recursive solution displayed in 1) will result in an exponential run time complexiy.
  using DP paradigm the problem is solved with run time complexiy O(n^3) and space complexit of O(n^2).
*/
int sol(int p[MAX_SIZE],int n){
    int mc[MAX_SIZE][MAX_SIZE];
    int t = n - 1;
    for(int i = 0; i < t;i++){
        mc[i][i] = 0;
    }
    //printarr(p,n);
    for(int r = 1; r < t;r++){
      for(int i = 0; i < t - r;i++){
          int j = i + r;
          int product = p[i]*p[j+1];
          int minima = INT_MAX;
          for(int k = i; k < j;k++){
              int p2 = product * p[k+1];
              //cout << k+1 << endl;
              int canidate = mc[i][k] + mc[k+1][j] + p2;
              if(canidate < minima) minima = canidate;
          }
          mc[i][j] = minima;
          //printf("mc[%d][%d]: ",i,j);
          // << mc[i][j] << endl;
      }
    }
    return mc[0][t-1];
}
