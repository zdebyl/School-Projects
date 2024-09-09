identification division.
program-id. stat.

environment division.
input-output section.
file-control.

*> select files for input and output
select input-file assign to "nums.txt"
   organization is line sequential.
select output-file assign to "output.txt"
   organization is line sequential.

data division.
file section.

*> define input file structure
fd input-file.
01 input-line.
   02 in-num pic x(80).

*> define ouput file structure
fd output-file.
01 output-line.
   02 out-num pic x(80).

working-storage section.

*> define variables
77 sum-of-x-sqr         pic 9(14)v9(2).
77 sum-of-x             pic s9(10)v9(2).
77 n                    pic s9(4).
77 mean                 pic s9(6)v9(2).
77 i                    pic s9(4).

01 array-area.
   02 x                 pic s9(6)v9(2) occurs 1000 times.
01 input-value-record.
   02 in-x              pic s9(6)v9(2).
   02 filler            pic x(72).
01 output-title-line.
   02 filler            pic x(28) value " mean and standard deviation".
01 output-underline.
   02 filler            pic x(28) value "----------------------------".
01 output-col-heads.
   02 filler            pic x(10) value spaces.
   02 filler            pic x(11) value "data values".
01 output-data-line.
   02 filler            pic x(10) value spaces.
   02 out-x             pic -(6)9.9(2).
01 output-results-line-1.
   02 filler            pic x(9) value " mean=   ".
   02 out-mean          pic -(6)9.9(2).
01 output-results-line-2.
   02 filler            pic x(9) value " std dev=".
   02 std-deviation     pic -(6)9.9(2).

procedure division.
   *> open files
   open input input-file, output output-file.

   *> perform procedure body until the file reads a number greater than 999999.98
   move zero to in-x.
   perform proc-body
      until in-x is not less than 999999.98.
   perform end-of-job.

proc-body.
   *> write output formatting
   write output-line from output-title-line
      after advancing 0 lines.
   write output-line from output-underline
      after advancing 1 line.
   write output-line from output-col-heads
      after advancing 1 line.
   write output-line from output-underline
      after advancing 1 line.

   *> read input file
   move zero to sum-of-x.
   read input-file into input-value-record
      at end perform end-of-job.
   perform input-loop
      varying n from 1 by 1
      until n is greater than 1000 or in-x is not less than 999999.98.
   subtract 1 from n.

   *> calculate mean
   divide n into sum-of-x giving mean rounded.

   *> calculate standard deviation
   move zero to sum-of-x-sqr.
   perform sum-loop
      varying i from 1 by 1
      until i is greater than n.
   compute std-deviation rounded = (sum-of-x-sqr / n) ** 0.5.

   *> write to output
   write output-line from output-underline
      after advancing 1 line.
   move mean to out-mean.
   write output-line from output-results-line-1
      after advancing 1 line.
   write output-line from output-results-line-2
      after advancing 1 line.

*> store and display data from the input file
input-loop.
   move in-x to x(n), out-x.
   write output-line from output-data-line
      after advancing 1 line.
   add x(n) to sum-of-x.
   read input-file into input-value-record
      at end perform end-of-job.

*> calculate sum of squares of deviations from the mean
sum-loop.
   compute sum-of-x-sqr = sum-of-x-sqr + (x(i) - mean) ** 2.

end-of-job.
   *> close files
   close input-file, output-file.

   stop run.
