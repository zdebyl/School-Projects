Name: Zoe Debyl
Date: 2/7/2023
Assignment: Assignment 3

To compile and run Q1:
make
./q1

- this will run both brute force and presorting algorithm (first brute then presorting)
- brute algorithm takes around 11 seconds to run and presorting algorithm taks around 0.02 seconds to run

To compile and run Q2:
make
./q2

- this will run all 3 algorithms; brute algorithm, then horspool's algorithm, then boyer-moore algorithm
- brute algorithm takes around 7 minutes to run, Horspool's algorithm takes around 1 minute to 4 minutes
  and Boyer-Moore's algorithm takes around 1 minute to 4 minutes


q2.4 analysis:

search pattern; ratio of time (time calculated in seconds); ratio of shifts:
- it; 447.5/225.57 = 1.98; 3296601/1693360 = 1.95
- The; 396.47/147.14 = 2.69; 3296600/1122285 = 2.69
- this; 423.54/116.98 = 3.62; 3296599/897084 = 3.67
- group; 458.17/97.96 = 4.68; 3296598/732869 = 4.5
- reason; 458.92/99.3 = 4.62; 3296597/666755 = 4.94
- student; 461.62/83.79 = 9.76; 3296596/593115 = 5.56
- maintain; 408.28/47.28 = 8.64; 3296595/518568 = 6.36
- disclosed; 431.43/50.23 = 8.59; 3296594/482101 = 6.84
- University; 444.82/62.59 = 7.1; 3296593/454139 = 7.26
- Technilogical; 424.52/39.15 = 10.84; 3296590/351581 = 9.38

average ratios:
- time: 6.25
- shifts: 5.32
performance:
The performance time for Horspool's algorithm is much faster than the brute force algorithm for string search.
In terms of time, it is on average 6.25 times faster and in terms of shifts, it is on average 5.32 faster.
As the length of the word gets longer, the better Horspool's algorithm is in comparison to the brute force algorithm.
