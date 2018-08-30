#include <iostream>
using namespace std;

int max_three(int a, int b, int c){
    int m = max(a,b);
    return max(m,c);
}
int max(int a, int b){
    if(a < b) return b;
    return a;
}
/* Given Matrix with size n X m, find maximal sum of any path starting from row 0 and ending in row n-1
   constrainment on path, one can reach cell c[i,j] only from c[i-1,j], c[i-1,j-1] or c[i-1,j+1].
   1) this problem has optimal substructre: maximal sum path from any cell c at row 0  to any cell t in row i (0<=i<=n-1)
      must be composed of maximal sum path from c to one of the cells at row i-1 which obey the constrainment i.e
      maxsum(t) = maxsum from c to ck + value(t), where ck is a cell at row i-1 with col belonging to col(t), col(t) - 1,colt(t) +1
   2) this problem has overlapping subproblems: trying to directly implementing this solution as reucrsive one which result in an exponantial run time
      which is why one can try and solve the problem with DP.
      
   additonaly one can notice that for matrix n X 1 there is only one possible path from row 0 to row n-1, therefore one can sum the colnum which will be the result
   formally the recursive formula for matrix M can be described as: 
   maximal path from row 0 to cell(i,j) - c(i,j) = max(c[i-1,j],c[i-1,j-1],c[i-1,j+1]) + M[i,j]
   maximal sum of any path from row 0 to row n-1 is:  max(c[n-1,k]), where 0<=k<=m-1
*/
int algo_two(int ** Mat,int m, int n){
    if(m == 1){
        int sum = 0;
        for(int i = 0; i < n;++i){
            sum += Mat[i][0];
        }
        return sum;
    }
    int ** profit = new int*[n];
    for(int i = 0; i < n;++i){
        profit[i] = new int[m];
    }
    for(int j = 0; j < m;++j)
        profit[0][j] = Mat[0][j];
    
    for(int i =1;i<n;++i){
        for(int j = 0; j < m;++j){
            int a = profit[i-1][j];
            int b = 0;
            int c = 0;
            if(j > 0 ) b = profit[i-1][j-1];
            if(j < m - 1) c = profit[i-1][j+1];
            profit[i][j] = max_three(a,b,c) + Mat[i][j];
        }
    }
    int result = profit[n-1][0];
    for(int i = 1; i < m;++i){
         result = max(result,profit[n-1][i]);
    }
    for(int i = 0; i < n;++i){
        delete profit[i];
    }
    delete profit;
    return result;
}

int main() {
	//code
	int T;
	cin >> T;
	for(int t = 0; t < T;++t){
	  int N;
	  cin >> N;
	  int ** Mat = new int*[N];
	  for(int i = 0;i < N;++i){
	      Mat[i] = new int[N];
	  }
	  for(int i = 0; i < N;i++){
	      for(int j = 0; j < N;j++){
	          cin >> Mat[i][j]; 
	      }
	  }
	  cout << algo_two(Mat,N,N) << endl;
	   for(int i = 0;i < N;++i){
	      delete Mat[i];
	  }
	  delete Mat;
	}
	return 0;
}
