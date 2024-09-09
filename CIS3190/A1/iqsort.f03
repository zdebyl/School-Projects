program sort
    use stackADT
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
        call iterativeQsort(numbers)
        call cpu_time(endTime)
        time = endTime - startTime

        write(*,*) "Time to sort:", time, "seconds."

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
        subroutine iterativeQsort(numbers)
            implicit none

            !declare and initialize variables
            integer, intent(inout) :: numbers(:)
            integer :: stack(10000)
            integer :: leftIndex, rightIndex, partitionIndex, partitionValue, i, temp, j

            leftIndex = 1
            rightIndex = size(numbers)

            !clear the stack
            call clear(stack)
            
            !push initial indices on the stack
            call push(stack, leftIndex)
            call push(stack, rightIndex)


            do while (.NOT. isempty(stack))
                !get indices from stack
                call pop(stack, rightIndex)
                call pop(stack, leftIndex)

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

                !add indices of values to left of partition if there are any
                if (partitionIndex-1 > leftIndex) then
                    call push(stack, leftIndex)
                    call push(stack, partitionIndex-1)
                end if

                !add indices of values to right of partition if there are any
                if (partitionIndex+1 < rightIndex) then
                    call push(stack, partitionIndex+1)
                    call push(stack, rightIndex)
                end if
            end do
        end subroutine iterativeQsort
end program sort