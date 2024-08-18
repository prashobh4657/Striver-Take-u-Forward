/*
Similar to MCM :
because in that also we have series of matrices like ABCD (let say first parition we did at B then (AB)(CD) means proper order that
has to be followed to minimize cost.
Here also that order is required.


b1 b2 b3 b4 b5 b6
Let burst b4
ans = b3*b4*b5
Subproblem remaining [b1,b2,b3] [b5,b6]
total answer would be : [b3*b4*b5] + ans([b1,b2,b3]) + ans([b5,b6]) ==> THIS IS WRONG...
becuase [b1,b2,b3] or [b5 b6] can't be solved individually.

Here main concept of this problem lies in this concept only that these two subproblems can't be solved independently.

Why can't be solved independently?
1. Reality : Because in reality after bursting b4 ===> [b1 b2 b3 b5 b6].
   Now let say b3 is to be bursted then its cost included should be b2*b3*b5. (Level 1)
   let's say at next step b5 is to bursted then cost included should be [b3*b5*b6]. (Level 2)

2. Virtuality : But virtually after bursting b4 if we split subproblems like [b1,b2,b3] and [b5,b6].
   Bursting b3 in 1st subproblem would have cost only b2*b3*1 (right doesn't exist) and that would not be reality. (See reality case);
   ==> you might argue that just take corner element other subproblem but that will not work always (see level2)
   ==>Level 1 (adjusted) by argument :  [b1 b2 b3] [b5 b6]    ===> b3 bursting ===> b2*b3*b5(corner element of another subproblem) (Clearly adjusted as per reality level 1);
   ==>Level 2 : subproblems generated from [b1 b2 b3] ==> [b1 b2] and [b5,b6](already there)
                now burst b5 will give cost : b2(corner element of another subproblem)*b5*b6 (which is clearly not as per reality);
    Clearly adjustment is also wrong.

    In short these two subproblems can't be solved independently.
Let's think different way....
*/
/*
If we keep on bursting ==> no. of balloons will go from n to 0. We will think in direction from 0 to n.
Consider [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
==> Instead of thinking who should be bursted first, we will think who should be at the last.


1 3 1 5 8 1 ==> (1 is applied at both ends)
0 1 2 3 4 5
let's say 8 is at last cost : 1*8*1  (range is [0-5])
at stage [3,8] ==> since 3 is new hence 3 would be bursted at this step ==> cost : 3*8*1
at stage [3,5,8] ==> since 5 is new hence 5 would be bursted at this step ==> cost : [3*5*8]
He doing something related to range (Not understood by me);

In reverse direction ==> the subproblems are independent.
you have subproblem {b1,b2,.........b6} ==> (basically from i to j)
let you burst idx ballon from this range
then return a[i-1]*a[idx]*a[j+1] + solve(i,idx-1) ==>z1 + solve(idx+1,j) ==> z2; (Here z1 and z2 are independent);


Proof : why it is  independent in reverse direction ? 

{b1,b2,b3,b4,b5,b6}


Let say last balloon b4 ==> then its cost will be 1*b4*1 ===> This is sure.
2nd last stage could be [b1,b4] [b2,b4] [b3,b4] [b4,b5] [b4,b6]  (b4 definitely exist in 2nd last stage tabhi toh wo last stage mein burst hua) (and b4 ke saath one more ballon will be there
any one ====> Now no matter who is with b4 whether b1,b2,b3,b5,b6 answer of that pair see carefully let say [b4,b6 was pair] ===> its answer only depend on b4 which is leftmost guy of the range (idx-1) is used in recurrence that's why.
for further stages also you can verify. 
*/

/*
// Leetcode Link : https://leetcode.com/problems/burst-balloons/
==> Submission 1 : May 25, 2023 13:44 ==> (Recursion + Memoization) ()
    Memoization : TC : O(n^3), SC : O(n^2) + O(n) (auxiliary stack space);
==> Submission 2 :  May 25, 2023 13:57 ==> (Tabulation);
    Since we call for (1,n) (i,j) hence i should go from n to 1 and j should go from 1 to n in tabulation 
    just apply loop and copy paste the recurrence in it.
    Rest see code and its comments. 
    
 // GFG Link : https://practice.geeksforgeeks.org/problems/7ae455e552dc4e07f76bbe2adc4d4207ce1ff16e/1
    ==> Just see latest submission (same as leetcode (memoized submitted))
*/
