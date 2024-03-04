package main

import (
	"bufio"
	"fmt"
	"os"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)

func printf(f string, a ...interface{}) { fmt.Fprintf(writer, f, a...) }
func scanf(f string, a ...interface{})  { fmt.Fscanf(reader, f, a...) }

type Position struct {
	x int
	y int
}

type Direction struct {
	name string
	dx   int
	dy   int
}

func main() {
	var dfs func(Position)
	var res string
	moveDir := func(dirName string) {
		printf("%s\n", dirName)
		writer.Flush()
		scanf("%s\n", &res)
	}
	seen := make(map[Position]struct{})
	directions := []Direction{
		{"up", -1, 0},
		{"down", 1, 0},
		{"left", 0, -1},
		{"right", 0, 1},
	}
	dfs = func(curr Position) {
		seen[curr] = struct{}{}
		for i, dir := range directions {
			nxt := Position{curr.x + dir.dx, curr.y + dir.dy}
			if _, ok := seen[nxt]; !ok {
				moveDir(dir.name)
				if res == "ok" {
					dfs(nxt)
					moveDir(directions[i^1].name)
				} else if res != "wall" {
					os.Exit(0)
				}
			}
		}
	}
	dfs(Position{0, 0})
	printf("no way out\n")
	writer.Flush()
	scanf("%s\n", &res)
}
