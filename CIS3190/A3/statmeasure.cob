identification division.
program-id. stat.

environment division.
input-output section.
file-control.

*> select file for input
select input-file assign to dynamic ws-fname
   organization is line sequential.

data division.
file section.

*> define input file structure
fd input-file.
01 input-line.
   02 in-num pic x(32767).

working-storage section.

*> define variables
77 sum-of-x-sqrd           pic 9(14)v9(7).
77 sum-of-sqr-diff         pic 9(14)v9(7).
77 sum-of-x                pic s9(14)v9(7).
77 mult-of-x               pic 9(14)v9(7).
77 sum-of-x-div            pic 9(14)v9(7).
77 n                       pic s9(4).
77 mean                    pic s9(6)v9(2).
77 i                       pic s9(4).
77 ws-fname                pic x(30).
77 feof                    pic A(1).

01 array-area.
   02 x                    pic s9(6)v9(2) occurs 1000 times usage display.
01 input-value-record.
   02 in-x                 pic s9(6)v9(2).
   02 filler               pic x(32765).
01 output-title-line.
   02 filler               pic x(31) value "      Statistical Measures".
01 output-underline.
   02 filler               pic x(31) value "-------------------------------".
01 output-col-heads.
   02 filler               pic x(31) value "          Data Values".
01 output-data-line.
   02 filler               pic x(20) value spaces.
   02 out-x                pic -(6)9.9(2).
01 output-results-line-1.
   02 filler               pic x(20) value " mean".
   02 out-mean             pic -(6)9.9(2).
01 output-results-line-2.
   02 filler               pic x(20) value " standard deviation".
   02 std-deviation        pic -(6)9.9(2).
01 output-results-line-3.
   02 filler               pic x(20) value " root mean square".
   02 root-mean-square     pic -(6)9.9(2).
01 output-results-line-4.
   02 filler               pic x(20) value " geometric mean".
   02 geometric-mean       pic -(6)9.9(2).
01 output-results-line-5.
   02 filler               pic x(20) value " harmonic mean".
   02 harmonic-mean        pic -(6)9.9(2).

procedure division.
   *> get file name
   display "Filename containing book information? ".
   accept ws-fname.
   
   *> open file
   open input input-file.

   *> write output formatting
   display output-title-line
   display output-underline
   display output-col-heads
   display output-underline.

   *> get values from file
   move 1 to n.
   perform read-file until feof='Y'.
   compute n = n - 1.

   *> calculate statistics
   perform calculate-mean.
   perform calculate-standard-deviation.
   perform calculate-root-mean-square.
   perform calculate-geometric-mean.
   perform calculate-harmonic-mean.

   *> display output
   display output-underline
   move mean to out-mean.
   display output-results-line-1
   display output-results-line-2
   display output-results-line-3
   display output-results-line-4
   display output-results-line-5.
   
   *> end program
   perform end-of-job.

*> read input file
read-file.
   read input-file into input-value-record
      at end move 'Y' to feof
      not at end perform input-loop
   end-read.

*> store data from the input file
input-loop.
   move in-x to x(n), out-x.
   display output-data-line.
   compute n = n + 1.
  
*> calculate mean
calculate-mean.
   move zero to sum-of-x.
   perform varying i from 1 by 1 until i is greater than n
      compute sum-of-x = sum-of-x + x(i)
   end-perform.

   compute mean rounded = sum-of-x / n.

*> calculate standard deviation
calculate-standard-deviation.
   move zero to sum-of-sqr-diff.
   perform varying i from 1 by 1 until i is greater than n
      compute sum-of-sqr-diff = sum-of-sqr-diff + (x(i) - mean) ** 2
   end-perform.
   
   compute std-deviation rounded = (sum-of-sqr-diff / n) ** 0.5.

*> calculate root mean square
calculate-root-mean-square.
   move zero to sum-of-x-sqrd.
   perform varying i from 1 by 1 until i is greater than n
      compute sum-of-x-sqrd = sum-of-x-sqrd + x(i) * x(i)
   end-perform.
   
   compute root-mean-square = (sum-of-x-sqrd / n) ** (1/2).

*> calculate geometric mean
calculate-geometric-mean.
   move 1 to mult-of-x.
   perform varying i from 1 by 1 until i is greater than n
      compute mult-of-x = mult-of-x * (x(i) ** (1/n))
   end-perform.
   
   compute geometric-mean = mult-of-x.

*> calculate harmonic mean
calculate-harmonic-mean.
   move zero to sum-of-x-div.
   perform varying i from 1 by 1 until i is greater than n
      compute sum-of-x-div = sum-of-x-div + (1 / x(i))
   end-perform.
   
   compute harmonic-mean = n / sum-of-x-div.

*> ending program
end-of-job.
   *> close files
   close input-file.

   stop run.
