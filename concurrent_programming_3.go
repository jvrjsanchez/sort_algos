package main

import (
	"fmt"
	"sync"
)

// TODO: start 10 'producer' goroutines
// Each producer should generate and send 10 integers to the consumer using fanInChan.

// TODO: start 1 consumer goroutine
// The consumer should receive all of the integers from fanInChan and print them out.

// Challenge: Use wait-groups to ensure that every goroutine returns before the main() func stops.

func main() {
	ch := make(chan int)
	var wg1 sync.WaitGroup

	for i := 0; i < 10; i++ {
		wg1.Add(1)
		go func() {
			for j := 0; j < 10; j++ {
				ch <- j
			}
			wg1.Done()
			if i == 0 {
				wg1.Wait()
				close(ch)
			}
		}()
	}

	var wg2 sync.WaitGroup
	wg2.Add(1)
	go func() {
		defer wg2.Done()
		for x := range ch {
			fmt.Printf("received: %d\n", x)
		}
	}()

	wg2.Wait() // waiting!
}
