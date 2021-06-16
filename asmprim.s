.text
.globl  prime_checker_asm
.type   prime_checker_asm, @function
prime_checker_asm:     # check is contained in %rdi, return is %rax
    cmpq $3, %rdi      # set CC to see if %rdi is <= 3
    jle LessThree      # if so, then jump to another series of checks
    movq $2, %rsi      # move two into the next available param variable
TwoThreeLoop:          # this loop checks whether our input is divisible by 2 or 3
    movq %rdi, %rax    # moves the value of %rdi into %rax for divq
    xorq %rdx, %rdx    # clears %rdx for its transformation in the next line 
    idivq %rsi         # %rdx = %rax mod 2
    cmpq $0, %rdx      # set CC to see if rdi is even
    je RetZero         # if so, return zero
    incq %rsi          # iterate our loop var
    cmpq $4, %rsi      # check to see if we have hit 4 yet
    je TwoThreeLoopEnd # if so, escape
    jmp TwoThreeLoop   # if not, redo the loop
TwoThreeLoopEnd:       # end of two three loop
    movq %rdi, %rsi    # we're done with the previous %rsi. Repurpose it as our orig value
    movq $5, %rdi      # init %rdi to be our iteration value (so we can call a func on it)
WhileSquare:           # this loop runs while the quare of our iterator is less than %rsi
    call square        # %rax now contains the squared value of %rdi
    cmpq %rax, %rsi    # set CC to see if the new squared value <= check
    jl RetOne          # if so return one
    xorq %rcx, %rcx    # initialize %rcx = 0
InWhileDivLoop:        # this loop is for checking modulo values for both iter and iter+2
    movq %rsi, %rax    # set %rax to be our check value for divq
    xorq %rdx, %rdx    # clears %rdx for its transformation in the next line
    idivq %rdi         # %rdx = %rax mod %rdi
    cmpq $0, %rdx      # set CC to see if %rsi is divisible by %rdi
    je RetZero         # If so, return zero
    addq $2, %rdi      # increment %rdi by two
    incq %rcx          # increment our counter, %rcx by one
    cmpq $2, %rcx      # set CC to see if %rcx = 2
    je DivLoopEnd      # If so, end the loop
    jmp InWhileDivLoop # If not, continue
DivLoopEnd:            # end of the iter and iter + 2 loop
    addq $2, %rdi      # reset the value of %rdi (-4) and add 6 (+2)
    jmp WhileSquare    # continue
LessThree:             # if input is less than or equal to 3
    cmpq $1, %rdi      # set CC to see if %rdi is greater than 1
    jg RetOne          # if so, then return 1
    jmp RetZero        # if not, return 0
RetOne:                # returns one
    movq $1, %rax      # move 1 into the return
    jmp End            # terminate
RetZero:               # returns zero
    xorq %rax, %rax    # move 0 into the return
    jmp End            # terminate
End:                   # terminating the function
    ret                # returns to caller
.size   prime_checker_asm, .-prime_checker_asm

.type   square, @function
square:             # input to be squared is input in %rdi, output in %rax
    movq %rdi, %rax # moves %rdi to %rax
    mulq %rax       # multiplies %rax by itself
    ret             # returns to the caller
.size   square, .-square
