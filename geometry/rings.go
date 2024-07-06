package main

import (
	"bufio"
	"fmt"
	"os"
)

var (
	reader *bufio.Reader = bufio.NewReader(os.Stdin)
	writer *bufio.Writer = bufio.NewWriter(os.Stdout)
)

func printf(f string, a ...interface{}) { fmt.Fprintf(writer, f, a...) }
func scanf(f string, a ...interface{})  { fmt.Fscanf(reader, f, a...) }

func Max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

type Point struct {
	x float64
	y float64
}

func (p *Point) Equals(other Point) bool {
	return p.x == other.x && p.y == other.y
}

func (p *Point) Subtract(other Point) Point {
	return Point{
		x: p.x - other.x,
		y: p.y - other.y,
	}
}

func (p *Point) Dist2() float64 {
	return p.x*p.x + p.y*p.y
}

func CircleInter(a Point, b Point, r1 float64, r2 float64) bool {
	if a.Equals(b) {
		return false
	}
	vec := b.Subtract(a)
	d2 := vec.Dist2()
	sum := r1 + r2
	dif := r1 - r2
	if sum*sum < d2 || dif*dif > d2 {
		return false
	}
	return true
}

type DSU struct {
	dsu []int
}

func NewDSU(n int) DSU {
	ret := DSU{
		dsu: make([]int, n),
	}
	for i := 0; i < n; i++ {
		ret.dsu[i] = -1
	}
	return ret
}

func (d *DSU) Find(u int) int {
	if d.dsu[u] < 0 {
		return u
	}
	d.dsu[u] = d.Find(d.dsu[u])
	return d.dsu[u]
}

func (d *DSU) Merge(u, v int) {
	u = d.Find(u)
	v = d.Find(v)
	if u == v {
		return
	}
	if d.dsu[u] > d.dsu[u] {
		u, v = v, u
	}
	d.dsu[u] += d.dsu[v]
	d.dsu[v] = u
}

func prayGod() {
	var n int
	for {
		scanf("%d\n", &n)
		if n == -1 {
			break
		}
		if n == 0 {
			// This shouldn't happen
			os.Exit(1)
		}
		center := make([]Point, n)
		radius := make([]float64, n)
		for i := 0; i < n; i++ {
			scanf("%f %f %f\n", &center[i].x, &center[i].y, &radius[i])
		}
		dsu := NewDSU(n)
		for i := 0; i < n; i++ {
			for j := i + 1; j < n; j++ {
				if CircleInter(center[i], center[j], radius[i], radius[j]) {
					dsu.Merge(i, j)
				}
			}
		}
		ret := 1
		for i := 0; i < n; i++ {
			ret = Max(ret, -dsu.dsu[dsu.Find(i)])
		}
		if ret == 1 {
			printf("The largest component contains 1 ring.\n")
		} else {
			printf("The largest component contains %d rings.\n", ret)
		}
	}
}

func main() {
	defer writer.Flush()
	prayGod()
}
