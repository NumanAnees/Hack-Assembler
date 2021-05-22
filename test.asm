//Storing 8 in a
@8
D=A
@A
M=D
//storing 9 in b
@9
D=A
@B
M=D
//Now for x = a+b
//store a in x 
@A
D=M
@X
M=D
//and add 1 to x,(b times)
@B
D=M
@Temp //variable for counting
M=D
//LOOP
(LOOP)
@Temp
D=M
@PART2
D;JEQ
@X
M=M+1
@Temp
M=M-1
@LOOP
0;JMP
//x=a+b part is done Now
//Add a in x and store in y
(PART2)
@A
D=M
@Temp2 //2nd variable for counting
M=D
@X
D=M
@Y
M=D
(LOOP2)
@Temp2
D=M
@PART3
D;JEQ
@Y
M=M+1
@Temp2
M=M-1
@LOOP2
0;JMP
//multiply y with b
//for multiplying add y to y b for b times
(PART3)
@B
D=M
@Temp3 //3rd variable for counting
M=D
M=M-1 //decreasing it for 1 time because 1 25 is already present,so we will add 8 times 25  
@Y
D=M
@New
M=D
(LOOP3)
@Temp3
D=M
@End
D;JEQ
@New
D=M
@Y
M=M+D
@Temp3
M=M-1
@LOOP3
0;JMP
(End)
@End
0;JMP

