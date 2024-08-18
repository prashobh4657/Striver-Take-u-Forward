// Problem : Minimum Insertions/Deletions to Convert String A to String B
// If minimum not asked ==> Then we just delete all characters of string a and then insert all characters of string b (Ans : A.size()+B.size());
// Clearly characters which are common not need to delete. Since minimum operations required hence try to keep longest common portion intact.
// So let’s convert in this way : a→LCS(min)→b   (It will give minimum operations)
// ===> a → LCS  (do necessary deletions)  = total deletions = length(a)-length(LCS);
// ===> LCS → b (do necessary insertions) = total insertions = length(b) - length (LCS);
// ===> Total operations : (A.size()+B.size())-(2*LCS(A,B));

// Also there is question : If here delete and insert and replace all three operations were given then it will be famous question
// i.e. EDIT DISTANCE  that we will not discuss here now.

// GFG Link : https://practice.geeksforgeeks.org/problems/minimum-number-of-deletions-and-insertions0209/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
// Just see latest submission;
// Leetcode Link : https://leetcode.com/problems/delete-operation-for-two-strings/description/
// Just see latest submission; (Exactly same as GFG submission) (But here insertion not allowed but logic remain same);
