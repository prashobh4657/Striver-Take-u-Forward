/* Minimum insertion to make a string palindrome;
==> Any character can be inserted anywhere.
==> If minimum constraint not given : then e.g. abcd ==> just you can just rev(s) and append to it ==> abcd dbca (Total insertion = length of string);
==> Since a portion in the string is already a palindrome, keep it intact
==> Since minimum portions are required hence we will try to keep longest palindrome intact.
==> Just make other portion of string palindrome (by inserting suitable character at suitable position (it is always possible verified through several examples));
==> Hence Answer : n - (LPS.size()) ==> n-LCS(s,rev(s));



Leetcode Link : https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/ 
Just see latest submission; 
GFG Link : https://practice.geeksforgeeks.org/problems/form-a-palindrome1455/1
Just see latest submission; (Exactly same as Leetcode);
GFG Link 2 : https://practice.geeksforgeeks.org/problems/form-a-palindrome2544/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article 
Just see latest submission; (Exactly same as Leetcode);
GFG Link 3 (Minimum deletions) = minimum insertions.
Just see latest submission; (Exactly same as Leetcode);
*/
