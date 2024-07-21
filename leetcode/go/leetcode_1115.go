package leetcode

func printFoo() {}
func printBar() {}

type FooBar struct {
	n       int
	fooChan chan struct{}
	barChan chan struct{}
}

func NewFooBar(n int) *FooBar {
	return &FooBar{n: n,
		fooChan: make(chan struct{}, 1),
		barChan: make(chan struct{}),
	}
}

func (fb *FooBar) Foo(printFoo func()) {
	for i := 0; i < fb.n; i++ {
		fb.fooChan <- struct{}{}
		printFoo()
		fb.barChan <- struct{}{}
	}
}

func (fb *FooBar) Bar(printBar func()) {
	for i := 0; i < fb.n; i++ {
		<-fb.barChan
		printBar()
		<-fb.fooChan
	}
}
