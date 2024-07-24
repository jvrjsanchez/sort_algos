package main

import (
	"context"
	"fmt"
	"sync"
	"time"
)

func main() {
	ctx, cancel := context.WithTimeout(context.Background(), 2000*time.Millisecond)
	defer cancel()
	//context carry timeouts and deadlines
	//have a Done() channel which is closed when timeout or deadline has elapsed.

	// chan string
	// chan struct{}
	ch := make(chan int) // work queue
	n := 100

	var wg sync.WaitGroup
	for id := 0; id < 10; id++ {
		wg.Add(1)
		go func() {
			defer func() {
				fmt.Printf("worker %d done \n", id)
				wg.Done() // happens before end of Wait.
			}()

			for {
				select {
				case msg, ok := <-ch:
					if !ok {
						fmt.Printf("worker %d done; channel closed\n", id)
						return
					}
					DoRPC(ctx, id, msg)
				case <-ctx.Done():
					fmt.Printf("worker %d done; channel cancelled\n", id)
					return
				}
			}
		}()
	}

loop:
	for i := 0; i < n; i++ {
		//context-aware sending to a channel.
		// either send to the channel of stop if context is done.
		select { // allows us to capture race-conditions in code
		case ch <- i:
			// do nothing in response
		case <-ctx.Done():
			fmt.Printf("sender context cancelled")
			break loop
		}
	}
	close(ch) // happens before the end of wait, happens before the end of each worker - close the channel to indicate no more data will be sent
	wg.Wait() // end of Wait
}

func DoRPC(ctx context.Context, workerID int, val int) {
	fmt.Printf("worker: %d, executing RPC with data: %v\n", workerID, val)
	time.Sleep(150 * time.Millisecond)
	// pass context down into the HTTP library
}
