# Assembler Project

## About

I made this program to translate a bare bones assembly language that I designed for my custom-built 8-bit breadboard computer. I would write code in the input.txt file and then run the program and it would dump the resulting machine code as C++ for my arduino. The arduino would then write the machine code onto an EEPROM (non-volatile memory) that my computer used for reading instructions and storing data.


<img width="500" alt="Screenshot 2024-09-07 at 11 50 50 AM" src="https://github.com/user-attachments/assets/82f86077-9ae6-4e45-85ed-91bb27c46ca3">

*Breadboard Computer*

## Example Assembly Program

Here is a program for multiplying two numbers.

```
; Multiply Program

section.data
    m_result 0
    m_input1 null 
    m_input2 null 

section.code
    multiply:
        m_calc:
            lda m_input1
            add m_result
            sta m_result
            lda m_input2
            dec
            jz m_finish
            sta m_input2
            jmp m_calc
        
        m_finish:
            ret
```

The first section is defining the variables that will be used throughout the program. In this case they are prefixed with "m" which stands for multiply to prevent collsion with other names in the main program. Each of these labels now refers to the memory address for each of these variables.

Here each of the inputs are numbers to be multiplied and the result variable stores their product. The inputs must be given values by the code that imports this code, so here we do not assign them values.

```
section.data
    m_result 0
    m_input1 null 
    m_input2 null 
```

This next section is the bulk of the code. the lines with a colon at the end (eg. "multiply:", "m_calc:") are simply labels for lines in the program. Under the hood, they are assigned the addresses of the next line of code. So, both "multiply" and "m_calc" refer to the memory address that stores the code "lda m_input1".

The lines of code that are preceeded by 3 letter codes (eg. "dec") are instructions for the computer. For example, "lda" stands for "Load the A register". It takes the memory address it is given and loads the "A" register in the computer with the data at that memory address.

```
section.code
    multiply:
        m_calc:
            lda m_input1
            add m_result
            sta m_result
            lda m_input2
            dec
            jz m_finish
            sta m_input2
            jmp m_calc
        
        m_finish:
            ret
```

Translating the above code into english would be something like this:

>Load the value from **input1** into the A register <br>
>Add the A register with **result** <br>
>Store the sum in **result** <br>
>Load the value from **input2** into the A register <br>
>Decrement the value in the A register by 1 <br>
>If the value in the A register is zero, jump to a line of code the returns from the subroute <br>
>Store the value in the A register in **input2** <br>
>Jump to the begining of the program<br>

If someone wanted to use this code, they would have to import this file, load values into the m_input1 and m_input2 variables, and then use "call multiply" to call the multiply subroutine. The answer would be available to them in m_result.