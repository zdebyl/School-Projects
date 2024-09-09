program sortrecursive
    use intIO

    implicit none

    !declare variables
    integer, dimension(:), allocatable :: numbers
    integer :: readcheck
    real :: startTime, endTime, time

    !read file
    write(*,*) "Reading numbers from file."
    call readUnsorted(numbers, readcheck)

    !check if file read properly
    if (readcheck==0) then
        write(*,*) "Error with file. Exiting program."
    else
        !call sort function
        write(*,*) "Sorting numbers."
        call cpu_time(startTime)
        call recursiveQsort(numbers, 1, size(numbers))
        call cpu_time(endTime)
        time = endTime - startTime

        write(*,*) "Time to sort:", time, "seconds"

        !check that file works and write to file
        write(*,*) "Writing to file 'sortedNUM.txt'."
        if(writeSorted(numbers)) then
            write(*,*) "Sorted numbers written to file 'sortedNUM.txt'"
        else
            write(*,*) "Error with file."
        end if

        !deallocate array
        deallocate(numbers)
    end if
    
    contains
        !subroutine to iteratively sort numbers
        recursive subroutine recursiveQsort(numbers, leftIndex, rightIndex)
            implicit none

            !declare and initialize variables
            integer, intent(inout) :: numbers(:)
            integer, intent(in) :: leftIndex
            integer, intent(in) :: rightIndex
            integer :: partitionIndex, partitionValue, i, temp, j
            
            if (leftIndex < rightIndex) then
                !use the rightmost value as the partition value
                partitionValue = numbers(rightIndex)
                i = leftIndex - 1

                !sort values using partition
                do j = leftIndex, rightIndex-1, 1
                    if (numbers(j)<=partitionValue) then
                        i = i + 1
                        temp = numbers(i)
                        numbers(i) = numbers(j)
                        numbers(j) = temp
                    end if
                end do

                !put partition value in correct spot
                temp = numbers(i+1)
                numbers(i+1) = numbers(rightIndex)
                numbers(rightIndex) = temp

                partitionIndex = i+1

                !recursively call function for values left of pivot
                call recursiveQsort(numbers, leftIndex, partitionIndex-1)

                !recursively call function for values right of pivot
                call recursiveQsort(numbers, partitionIndex+1, rightIndex)
            end if
        end subroutine recursiveQsort
end program sortrecursive