module stackADT
    contains
        !subroutine to set top of stack to 0
        subroutine clear(arr)
            implicit none
            
            integer, intent(inout) :: arr(:)

            !set first value in array to 0
            arr(1) = 0
        end subroutine clear

        !function to check if stack is empty
        logical function isempty(arr)
            implicit none

            integer, intent(in) :: arr(:)

            !check if first value in array is 0
            if (arr(1)==0) then
                isempty = .TRUE.
            else
                isempty = .FALSE.
            end if
        end function isempty
    
        !subroutine to add value to top of stack
        subroutine push(arr, value)
            implicit none

            integer, intent(inout) :: arr(:)
            integer, intent(in) :: value
            integer :: i

            !find last value in array
            i=1
            do while(arr(i)/=0)
                i = i+1
            end do

            !add value to end of array and set new top of stack to 0
            arr(i) = value
            arr(i+1) = 0
        end subroutine push

        !subroutine to remove and return top value of stack
        subroutine pop(arr, topvalue)
            implicit none
            
            integer, intent(inout) :: arr(:)
            integer, intent(out) :: topvalue
            integer :: i

            !find last value in array
            i=1
            do while(arr(i)/=0)
                i = i+1
            end do

            !get last value of array and replace it with 0 in array
            topvalue = arr(i-1)
            arr(i-1) = 0
        end subroutine pop
end module stackADT