.data
array: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
length: .word 10
newline: .asciiz " \n"

.text
main:


  la $a0, array                # Load array into $a0
  li $a1, 0                    # Load 0 into a1
  lw $a2, length               # Load length into $a2
  li $a3, 1            # Load item to search for into $a1


  jal linear

  move $a0, $v1
  li $v0,1          #print location of target by linear search
  syscall

  la $a0, newline
  li $v0,4          #new line
  syscall


  li $v0, 10
  syscall

linear:
    li $s4, 0       #index i = 0

    j linearLoop

    linearLoop:
        bge $s4, $a2, linearFailed  #if $t0 > target, it jumps out of loop
        lw $t1, 0($a0)          #load the array into t1
        beq $t1, $a3, linearFound   #if array[element] = target, found target
        addi $a0, $a0, 4        #add 4 to the array size
        addi $s4, $s4, 1        #add one to the index

        j linearLoop        #SOS THIS IS NO FUN !!!!!#

    linearFound:
        move $v1, $s4       #move $t0 into $v1
        j exitLoop

    linearFailed:
        li $v1, -1
        j exitLoop

    exitLoop:
        jr $ra
