# Greedy-Algorithms
Authors: Braden Azis (UFID: 20730106) and Brian Delaney (UFID: )

## How to Compile
Compile using make.

## How to Run
Run the program by piping an input file into the executable:
```
    ./main < input/<input_file>
```

### Example:
```
    ./main < input/example.in
```
Can compare output in terminal to expected example output at 
```
    output/example.out
```




## Question 3:
Assume there exists an algorithm A that is offline and optimal, and is not the OPTFF. Because A and OPTFF are not the same, they will
differ their eviction choice at some request. Consider an arbitrary case where A and OPTFF select a different item for eviction in the cache (index i).

Let a represent the item A evicts.
Let b represent the item OPTFF (Beladay's) evicts.

Due to the nature of OPTFF, we know its eviction policy is to evict the item whose request is the furthest in the future. As such,

```
    next_request(b) >= next_request(a)
```

We'll modify A to behave the same way, but instead of evicting a at i it'll evict b. We call this A'.
After this swap at i, A' behaves the exact same as A (A and A' only different at i), and A' will match OPTFF at i ONLY.

Immediately after i, the state of the cache in A is everything except a, and the state of A' is everything except b.
In the requests after this swap the situation plays as follows:

We know the request for a will happen before b, due to the OPTFF policy selecting the furthest request in the future.
When a is requested, A is guaranteed to miss (because it evicted a from the cache) and A' is guaranteed to hit (because it kept a).
Again, this scenario is guaranteed to happen, thus A' is strictly better than A AT THIS CURRENT POINT.

Following this, the requests can be unpredictable and the algorithms will evict based on their respective policies.
It is important to note that b cannot reenter the cache until the next request for b occurs. 

Now let's assume that after the initial request for a we reach the request for b.
At this point we know that A will hit because it kept b at i (choosing to evict a). And A' will miss because it chose to evict b at i.

The total misses between the two algorithms will end up equivalently with 1 miss each. Therefore showing that swapping an eviction of A
to be the eviction of OPTFF at some i does not make A any less optimal because A' could not miss any more than A in that situation.

Because i is arbitrary, this exchange argument can extend for any index in the request sequence, and shows demonstrates that at any
index where A and OPTFF want to select differently that by forcing A to evict OPTFF's item will not increase the number of misses.

Because we assumed A to be optimal, and have expressed that OPTFF cannot have any more misses than that of A, we have shown OPTFF is optimal.

Q.E.D

