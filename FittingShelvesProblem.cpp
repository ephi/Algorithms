/*
  FittingShelvesProblem
  Given a wall W with length w, and 2 types of shelves: A with length n, B with length m
  1) find the amount of A and B such that thier length will fill as much as possible from the length of W
  2) the solution will use as many as possible larger shelves (if n > m, then A should be used the most).
  3) if 1) & 2) are contradicting prefer 1) (that is, if a better fill is found when using smaller shelves then large shelves prefer it)
  idea: look at wall W of length w: |___________w____________| = W
  then, observe that every W can be split in 2 in the following way:
  |_______sm_space_____|___rm_space_______| = W
  where in some stage we consider up to i = w/n,w/n-1, ..., 0 large shelves (every division is rounded down in this algorithm if not an integer)
  sm_space = (n*i)+(w/n-i)*(n/m)*m = the maximal amount of large shevels to take when using upto i large shelves, 
  if i < w/n, then we consider all (=maximal amount) of the smaller shelves which may fit instead of w/n-i large shelves 
  (it as if we replaced w/n-i large shelves with as many as possible small shelves without exceeding the use of w/n large shelves)
  rm_space =  m*((w-sm_space)/m)    = the maximal amount of small shelves which combined with sm_space will fill up as much as possible in W
  now consider x = w - (sm_space+rm_space), obvisouly the objective is to minimize x with respect to all i's from w/n to 0 (inclusive).
  if in any iteration i x was 0, then that is the best possible solution which will contain as many as possible larger shelves and the algorithm should halt.
  if not, then, we should maintain the minimal x found until iteration i.
  Also it's clear that the best case will occur when |___________sm_space__________| = W and sm_space = w when i=w/n, so we can directly consider it first.
  
  now, consider this example:
  w=29 ; m = 3; n = 7
  for iteration i = w/n = 29/7 = 4 the following is considered:
  |______________________n*4__________________________| = 28 = w - 1, min_d = 1
  |_____sm_space=7*4+0___|___rm_space=3((29-28)/3)=0__| = 28 = w - 1, x = 1  
  since there is still distance to be filled between n*4 to w (mind_d > 0) and i >= 0 then we may try to improve min_d by x.
  since they are the same, no improvment should be made, i decreases by one and the following is considered for i = w/n - 1 = 3
  |_____sm_space=7*3+(4-3)*(7/3)*3=27___|___rm_space=3((29-27)/3)=0__| = 27 = w - 2, x = 2 
  since i >= 0 and min_d is not optimal (that is greater then 0), we try to improve min_d with x, since 2 = x > min_d = 1 no improvment can be made.
  i decreases by one and the following is considered for i = w/n - 2 = 2
  |_____sm_space=7*2+(4-2)*(7/3)*3=26___|___rm_space=3((29-26)/3)=3__| = 29 = w - 0, x = 0, 
  since i >= 0 and min_d is not optimal (that is greater then 0), we try to improve min_d with x, since 0 = x < min_d = 1 the improvment can be made
  so min_d becomes 0, i decreases by one, another calculation is made for sm_space and rm_space and x, but since min_d is now 0 the process is halted for i = w/n - 2.
  the dimenssions (small sheveles amount, large shelves amount, fill distance from w) which were calculated in iteration i = w/n - 2 were also saved
  and are now returned.
  
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct WallAnswer {
    int big_shelf_amount;
    int small_shelf_amount;
    int empty_wall_remains;
};

WallAnswer calculate_shelves_for_wall_work(int w, int m, int n){
    WallAnswer wAnswer = {0};
#ifdef DEBUG_CODE
    printf("w=%d ; m = %d; n = %d\n",w,m,n);
#endif
    int i = w/n;
    int d = w % n;
    wAnswer.empty_wall_remains = d;
    wAnswer.big_shelf_amount = w/n;
    if(m == 0) return wAnswer;
    int sm_space = (n*i) + ((w/n) - i)*(n/m)*m;
    int rm_space = m*((w-sm_space)/m);
    int x = w - (sm_space + rm_space);
    int min_d = d;
#ifdef DEBUG_CODE
    printf("d=%d; big = %d; small = %d\n",d,wAnswer.big_shelf_amount,  wAnswer.small_shelf_amount);
#endif
    while(i >=  0 && min_d > 0){
#ifdef DEBUG_CODE
        printf("sm_space = %d; rm_space = %d; min_d=%d ; x = %d; i = %d; big = %d; small = %d\n",sm_space,rm_space,min_d,x,i, wAnswer.big_shelf_amount,  wAnswer.small_shelf_amount);
#endif
        if(x< min_d && x >= 0){
             wAnswer.empty_wall_remains = x;
             wAnswer.big_shelf_amount = i;
             wAnswer.small_shelf_amount = ((w-sm_space)/m)+((w/n) - i)*(n/m);
             min_d = x;
        }
        i--;
        sm_space = (n*i) + ((w/n) - i)*(n/m)*m;
        rm_space = m*((w-sm_space)/m);
        x = w - (sm_space + rm_space);
       
    }
    return wAnswer;
}
WallAnswer calculate_shelves_for_wall(int w, int m, int n){
    if(n >= m) return calculate_shelves_for_wall_work(w,m,n);
    return calculate_shelves_for_wall_work(w,n,m);
}

int main(){
  WallAnswer wa = calculate_shelves_for_wall(129,5,22);
  printf("(small=%d,big=%d,remains=%d)\n",wa.small_shelf_amount,wa.big_shelf_amount,wa.empty_wall_remains);
  return 0;
}
