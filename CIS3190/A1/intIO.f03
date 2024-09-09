module intIO
    contains
        !subroutine to read in a file
        subroutine readUnsorted(arr, continue)
            implicit none

            !declare and initialize variables
            integer, dimension(:), allocatable, intent(out) :: arr
            integer, intent(out) :: continue
            character (len=100) :: filename
            logical :: fileexist
            character :: newfilename = 'Y'
            integer :: error, numValues, i

            !get name of file
            do while (newfilename .EQ. 'Y')
                write(*,*) 'Enter the file name: '
                read(*,'(A)') filename

                !check if file exists
                inquire(file=filename, exist=fileexist)
                if(.not. fileexist) then
                    !file doesn't exist, prompt user if they want to try a different file
                    write(*,*) "This file does not exist. Enter 'Y' to try another filename or enter any key to exit: "
                    read(*,'(A)') newfilename
                else
                    !file does exist, open file for reading
                    open(unit=9, file=filename, status='old', action='read')
                    exit
                end if
            end do

            !check if file was opened
            if (newfilename .EQ. 'Y') then
                continue = 1

                !get size of file
                numValues = 0

                do
                    !read line
                    read(9, *, iostat=error)
                    
                    !reached end of the file
                    if (error<0) then
                        exit
                    !error reading file
                    else if (error>0) then
                        write(*,*) "There was an error reading the file."
                        continue = 0
                        exit
                    !read line
                    else
                        numValues = numValues + 1
                    end if
                end do

                !go to start of file
                rewind(9)

                !allocate array
                allocate(arr(numValues))

                !read file
                do i=1, numValues
                    read(9, *) arr(i)
                end do
            else
                continue = 0
            end if

            !close file
            close(9)
        end subroutine readUnsorted

        !function to write an array to a file
        logical function writeSorted(arr)
            implicit none

            !declare and initialize variables
            integer, intent(in) :: arr(:)
            character (len=30) :: filename = "sortedNUM.txt"
            logical :: fileexist
            character :: overwrite
            integer :: i
            character (len=1000) :: value

            !check if file exists
            inquire(file=filename, exist=fileexist)
            if(.not. fileexist) then
                !file doesn't exist, create new file and open
                open(unit=10, file=filename, status='new', action='write')
                writeSorted = .TRUE.
            else
                !file does exist, check if user wants to overwrite file
                write(*,*) "This file already exists. Enter 'Y' to try overwrite or enter any key to exit: "
                read(*,'(A)') overwrite

                if (overwrite .EQ. 'Y') then
                    !open file that already exists
                    open(unit=10, file=filename, status='old', action='write')
                    writeSorted = .TRUE.
                else
                    writeSorted = .FALSE.
                end if
            end if

            !write to file
            if (writeSorted) then
                do i=1, size(arr)
                    write(value, *) int(arr(i))
                    write(10, '(a)') adjustl(trim(value))
                end do
            end if

            !close file
            close(10)
        end function writeSorted
end module intIO