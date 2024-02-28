package main

import (
	"fmt"
)

const INF int64 = 1000000000000000000

func max(a, b int64) int64 {
    if a > b { 
        return a 
    }
    return b
}

func main() {
	var n int
	fmt.Scan(&n)
	a := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}
	for l, r := 0, n-1; l < r; l, r = l+1, r-1 {
		a[l], a[r] = a[r], a[l]
	}
	dp := make([][]int64, n)
	for i := 0; i < n; i++ {
		dp[i] = make([]int64, n)
		for j := 0; j < n; j++ {
			dp[i][j] = -INF
		}
	}
	for i := 1; i < n; i++ {
		dp[0][i] = a[0] + a[i]
	}
	ret := dp[0][n-1]
	for i := 1; i < n; i++ {
		curr_max := -INF
		for j := i + 1; j < n; j++ {
			if i*2-j >= 0 {
				curr_max = max(curr_max, dp[i*2-j][i])
			}
			dp[i][j] = max(dp[i][j], curr_max+a[j])
			if j == n-1 {
				ret = max(ret, dp[i][j])
			}
		}
	}
	fmt.Println(ret)
}
