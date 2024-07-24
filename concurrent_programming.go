package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup
	for i := 0; i < 10; i++ {
		wg.Add(1) // happens before beggining of Wait.
		go func() {
			defer wg.Done() // happens before end of Wait
			DoRPC(i)
		}()
	}
	wg.Wait() // end of Wait

}

func DoRPC(val int) {
	fmt.Printf("executing RPC with data: %v\n ", val)
	time.Sleep(150 * time.Millisecond)
}
