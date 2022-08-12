## Control Signal shorthand

PLEASE NOTE: I'm kinda planning to change this a lot soon based on what I've learnt from using it for a while. Watch this space..

You may use a shorthand for control signals. These are made out of a sequence 
of time-steps.

Use `_` to indicate that the signal should remain static for one step.

Use `~` to indicate that the signal should be gliding toward the next value for 
a step.

Use a number to set the value of a step.

Use a colon `:` for tempo indication.

(Maybe,) use `±` for lfo vibrato?


### Examples

Start at `440Hz` for 4 steps, then switch (instantly) to 550Hz
```
440Hz____550Hz____
```

Start at `1` and glide to `0` over 4 seconds

```
1s: 1~~~~0
```

Frequency signal for Twinkle Twinkle Little Star

```
120bpm:
c_ c_ g_ g_ a_ a_ g__  
f_ f_ e_ e_ d_ d_ c__
```


