gcc -DNDEBUG math.c
------------------------------------------

Read in 2 floats:
7   0
when divided x/y = inf


Read in 2 floats:
0   0
when divided x/y = nan

------------------------------------------
With an effect and NDEBUG flag. 
And we can see how to do that with our GNU compiler. 
We do a -DNDEBUG as part of the compilation.
And that's telling us turn off the asserts.

And now let's run the same program except that the asserts have been turned off.
And now, we can read in, let's say, 3 and 4, sure enough, 2 and 1, sure enough.
But now, when we read 7 over 0, instead of getting an assertion era, we get 1 divided x over y is inf and that's the system provided infinity. 
Now it's sort of interesting, what if you divide 0 by 0?
It also doesn't abort. 
Instead, it just says not a number.
So these are two interesting constructs when we get some mathematical operation that can't be interpreted in the normal set of reals. 
And now because we can't, we're in the infinite loop and its waiting for floats. 
And we don't have the ability to write in a 0, which we used before to create both. 
We will just do Ctrl+C, and get out of there. 