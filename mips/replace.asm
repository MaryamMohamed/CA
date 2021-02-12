.data

str: .space 100                 # Pre Allocate space for the input sentence
input: .space 30                # Pre Allocate space for the input sentence 
ins: .asciiz "Please enter a sentence: "    # string to print sentence
seek: .asciiz "Please enter a word: "       # string to print sentence 
nomatch: .asciiz "No Match(es) Found"           
found: .asciiz " Match(es) Found"
newline: .asciiz "\n"               # string to print newline

.text

li $v0, 4       # syscall to print string
la $a0, ins     # move str into a0
syscall         # syscall 

li $a1, 100     # allocate space for the string
la $a0, str     # load address of the input string
li, $v0, 8      # read string input from user
syscall         # issue a system call

move $t9, $a0       # move string to t5

li $v0, 4       # syscall to print string
la $a0, seek        # move str into a0
syscall         # syscall 

la $a0, input       # load address of the input string
li $a2, 30      # allocate space for the string
li, $v0, 8      # read string input from user
syscall         # issue a system call

move $t8, $a0       # move string to t8
la $s5, input       # create space for the input word we are looking for in s5

wloop:          # loop to allocate space for the word we are looking for to a register
lb $t0, 0($t8)      # load first character into t0
beqz $t0, sentence  # branch to sentence loop if null character
sb $t0, 0($s5)      # store the current character into current address of s5
addi $t8, $t8, 1    # add one to t8 to move to next character
addi $s5, $s5, 1    # add one to s5 to move to the next allocated space
j wloop         # jump back to wloop

la $s4, str     # create space for the input sentence

sentence:       # loop to allocate space for the word we are looking for into a register
lb $t0, 0($t9)      # load first character into t0
beqz $t0, resetsen  # branch to check loop if null character
sb $t9, 0($s4)      # store the current character into current address of s4
addi $t9, $t9, 1    # add one to t9 to move to next character
addi $s4, $s4, 1    # add one to s5 to move to the next allocated space
j sentence      # jump back to sentence

resetsen:
li $s4, 0       # reset sentence back to 0 (first character)

resetword:
li $s5, 0       # reset word we are looking for back to 0 (first character)

check:
lb $t1, 0($s4)      # load current character of sentence to t1
beq $t1, 46, quit   # branch to QUIT if period found
bne $t1, 70, nextword   # if t1 != t0 branch to nextword
beq $t1, 70, checkword  # branch to found if t1 = f

nextword:       # loop to get to the next word
lb $t1, 0($s4)      # load current character to t1
beq $t1, 46, quit   # branch to quit if period found
bne $t1, 32, increment  # if current character is not a spaace branch to increment
beq $t1, 32, plusone    # if current character is a space branch to plusone
increment:      # increment procedure
addi $s4, $s4, 1    # add one to s4 to move to next character
j nextword      # jump to nextword
plusone:        # plusone procedure
addi $s4, $s4, 1    # add one to s4 to move to next character
j resetword     # jump to check

checkword:
addi $s4, $s4, 1    # add one to s4 to move to next character
addi $s5, $s5, 1    # add one to s5 to move to next character
lb $t1, 0($s4)      # load current character of sentence to t1
lb $t0, 0($s5)      # load current character of sentence to t0
bne $t1, $t0, increment # if t0 != t1 branch to increment (looking for a)
addi $s4, $s4, 1    # add one to s4 to move to next character
addi $s5, $s5, 1    # add one to s5 to move to next character
lb $t1, 0($s4)      # load current character of sentence to t1
lb $t0, 0($s5)      # load current character of sentence to t0
bne $t1, $t0, increment # if t0 != t1 branch to increment (looking for d)
addi $s4, $s4, 1    # add one to s4 to move to next character
addi $s5, $s5, 1    # add one to s5 to move to next character
lb $t1, 0($s4)      # load current character of sentence to t1
lb $t0, 0($s5)      # load current character of sentence to t0
bne $t1, $t0, increment # if t0 != t1 branch to increment (looking for e)
addi $s4, $s4, 1    # add one to s4 to move to next character
addi $s5, $s5, 1    # add one to s5 to move to next character
lb $t1, 0($s4)      # load current character of sentence to t1
lb $t0, 0($s5)      # load current character of sentence to t0
bne $t1, $t0, increment # if t0 != t1 branch to increment (looking for d)
addi $t2, $t2, 1    # add one to t2 which counts occurences
j resetword

quit:
beqz $t2, exit      # if t2 = 0 branch to exit
li $v0, 1       # syscall to print integer
move $a0, $t2       # move str into a0
syscall         # syscall 
li $v0, 4       # syscall to print string
la $a0, found       # move found into a0
syscall         # syscall 

exit:
    li      $v0,4                   # syscall to print string
    la      $a0,nomatch             # move nomatch into a0
    syscall
