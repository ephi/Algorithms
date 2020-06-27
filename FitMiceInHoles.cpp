/*
There are N Mice and N holes are placed in a straight line. 
Each hole can accommodate only 1 mouse. A mouse can stay at his position, move one step right from x to x + 1, or move one step left from x to x -1. 
Any of these moves consumes 1 minute. 
Assign mice to holes so that the time when the last mouse gets inside a hole is minimized.
Solution: 
if M_p = mouse postions = { m_pos1, m_pos2, ... , m_pos_N}
if H_p = hole postions = { h_pos1, h_pos2, ... , h_pos_N}
then in the time it takes for mouse i at position m_pos_i to enter hole j at position h_pos_j
every other mouse k at position m_pos_k can enter hole t at position h_pos_t( k != i, j != t) if the distance of mouse i to hole j is greater or equal then the distance of mouse k to hole t. 
That is |m_pos_k - h_pos_t| <= |m_pos_i - h_pos_j| for all 1 <=k != i,t != j <= N, then the optimal solution would be available when |m_pos_i - h_pos_j| is also minimal
this is because mouse k will enter hole t while mouse i is progressing towards/entering (if the distances are equal) hole j.
so we would want to order the positions such that each mouse position will correspond to its nearest hole position. that is, sort M_p and sort H_p.

this will hold true if and only if for m1 - mouse1 ,m2 - mouse2 ,h1 - hole 1,h2 - hole 2 such that pos_m1 < pos_m2 and pos_h1 < pos_h2 then the following holds true max(|pos_m1 - pos_h1|,|pos_m2 - pos_h2|) <= max(|pos_m1 - pos_h2|,|pos_m2 - pos_h1|)
we will show this by induction on the number of swaps in the array sorting does on M_p and H_p.
I.H: when swap changes the mouse positions and hole postions for m1,m2,h1,h2 to pos_m1 < pos_m2 and pos_h1 < pos_h2 then the following holds true max(|pos_m1 - pos_h1|,|pos_m2 - pos_h2|) <= max(|pos_m1 - pos_h2|,|pos_m2 - pos_h1|)
base case: no swap has been occured in either M_p or H_p, 
then, for m1,m2,h1,h2 if pos_m1 < pos_m2 and pos_h1 < pos_h2 then max(|pos_m1 - pos_h1|,|pos_m2 - pos_h2|) <= max(|pos_m1 - pos_h2|,|pos_m2 - pos_h1|)
without the generalliy restriction assume that |pos_m1 - pos_h1| > |pos_m2 - pos_h2| and that |pos_m1 - pos_h2| > |pos_m2 - pos_h1|
so we need to show that |pos_m1 - pos_h1| <= |pos_m1 - pos_h2|. pos_h1 < pos_h2 --> |pos_m1 - pos_h1| <= |pos_m1 - pos_h2| in a trival manner (that is pos_m1 is the same and pos_h1 reduces the total distance).
(same process will holds true for any max choice).
by induction let us assume this will hold true for k-1 swaps we are doing in both M_p and H_p
we will show this also holds true for the k'th swap.
let h_pos_a, h_pos_b, m_pos_a, m_pos_b be the positions which are swapped in H_p and M_p respectivly.
after this swap it now holds true that h_pos_a < h_pos_b , m_pos_a < m_pos_b. We need to show that:
max(|m_pos_a_1-h_pos_a_1|,|m_pos_b_1 -  h_pos_b_1|) <= max(|m_pos_a_1 - h_pos_b_1|,|m_pos_b_1 - h_pos_a_1|) <= ... <= max(|m_pos_a_k-1-h_pos_a_k-1|,|m_pos_b_k-1 -  h_pos_b_k-1|) <= max(|m_pos_a_k-1 - h_pos_b_k-1|,|m_pos_b_k-1 - h_pos_a_k-1|) <= max(|m_pos_a  - h_pos_a|,|m_pos_b -  h_pos_b|) <= max(|m_pos_a - h_pos_b|,|m_pos_b - h_pos_a|)
First we will show that max(|m_pos_a  - h_pos_a|,|m_pos_b -  h_pos_b|) <= max(|m_pos_a - h_pos_b|,|m_pos_b - h_pos_a|)
without generality restriction assume that |m_pos_a  - h_pos_a| > |m_pos_b -  h_pos_b| and that |m_pos_b - h_pos_a| > |m_pos_a - h_pos_b|
so we need to show that |m_pos_a  - h_pos_a| <= |m_pos_b - h_pos_a| because m_pos_a < m_pos_b it trivally holds that |m_pos_a  - h_pos_a| <= |m_pos_b - h_pos_a|
now we will show that max(|m_pos_a_k-1 - h_pos_b_k-1|,|m_pos_b_k-1 - h_pos_a_k-1|) <= max(|m_pos_a  - h_pos_a|,|m_pos_b -  h_pos_b|)
this term: max(|m_pos_a_k-1 - h_pos_b_k-1|,|m_pos_b_k-1 - h_pos_a_k-1|) <= max(|m_pos_a  - h_pos_a|,|m_pos_b -  h_pos_b|) was considered in swap k-1
so it holds by the I.H that if swapping maintained m_pos_a_k-1 < m_pos_a and h_pos_a_k-1 < h_pos_b then indeed max(|m_pos_a_k-1 - h_pos_b_k-1|,|m_pos_b_k-1 - h_pos_a_k-1|) <= max(|m_pos_a  - h_pos_a|,|m_pos_b -  h_pos_b|)
the reset of the inequalities need to be considered in the same way. thus this claim holds true.
                              
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int absVal(int v){
    if( v < 0) return -1 * v;
    return v;
}
int miceToHoleDiff(int a, int b){
    if (a < 0 && b < 0) return absVal((-a)-(-b));
    if (a < 0 && b > 0) return absVal(b-a);
    return absVal(a-b);
}
int bestTimeMiceInHolesByPositions(vector<int> &H_poses, vector<int> &M_poses){
    int n = M_poses.size();
    sort(H_poses.begin(), H_poses.end());
    sort(M_poses.begin(), M_poses.end());
    for(int i = 0;i < n;++i){
        printf("H_poses[%d] = %d, ",i,H_poses[i]);
    }
    printf("\n");
    for(int i = 0;i < n;++i){
        printf("M_poses[%d] = %d, ",i,M_poses[i]);
    }
    printf("\n");
    int max_time = miceToHoleDiff(H_poses[0],M_poses[0]);
    for(int i = 1;i < n;++i){
        int canidate_time = miceToHoleDiff(H_poses[i],M_poses[i]);
        printf("max_time = %d; canidate_time = %d\n",max_time,canidate_time);
        if(canidate_time > max_time) max_time = canidate_time;
    }
    return max_time;
}
int main() {

    vector<int> h_poses = { -2, 9, 69, 11,25, -31, 23, 50, 78 };
    vector<int> m_poses = { -10, -79, -79,5, 67, 93, -85, -28, -94 };
    int min_time_till_last_mouse_in_hole = bestTimeMiceInHolesByPositions(h_poses,m_poses);
    printf("best time = %d minutes\n",min_time_till_last_mouse_in_hole);
   
  	return 0;
}
