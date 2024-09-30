class Solution{
    LongestRepeatingSubsequence(str){
        var n = str.length
        var dp = new Array(n+1);
        for (var i = 0; i <= n; i++){
            dp[i] = new Array(n+1)
            for (var j = 0; j <= n; j++){
                dp[i][j] = 0;
            }
        }
        for (i = 1; i <= n; i++){
            for (j = 1; j <= n; j++){
                if ((str(i - 1) === str(j - 1) && i != j)
                    dp[i][j] = 1 + dp[i-1][j-1]
                else
                    dp[i][j] = Math.max(dp[i][j-1], dp[i-1][j])
            }
        }
        return dp[n][n]
    }
}
