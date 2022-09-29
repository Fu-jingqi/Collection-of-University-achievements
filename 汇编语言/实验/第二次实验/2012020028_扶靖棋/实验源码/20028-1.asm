DATA SEGMENT  
STR_1 DB 'Please input a string(length<=9): $'  
STR_2 DB 0DH, 0AH,'Please input the index of the char to display: $'  
STR_3 DB 0DH, 0AH,'The char is: $'  
STR_4 DB 0DH, 0AH,'The index is invalid!$' 
STR_5 DB 0DH, 0AH,'MyInformation:2012020028_fujingqi$' 
BUFF DB 20, ?, 20 DUP(?)  
DATA ENDS

CODE SEGMENT  
ASSUME CS:CODE, DS:DATA  
START: 	MOV AX, DATA
		MOV DS, AX

		LEA DX, STR_1  
		MOV AH, 9 				;输出字符串str_1,提示输入  
		INT 21H  

		LEA DX, BUFF  
		MOV AH, 10 				;输入字符串  
		INT 21H

		LEA DX, STR_2  
		MOV AH, 9 				;输出字符串str_2,提示输入索引  
		INT 21H  
	
		MOV AH, 01  
		INT 21H       
		MOV CL, AL 				;输入索引，并将索引存入CL  
	        
		LEA SI, BUFF  
		MOV DL, BYTE PTR[SI+1] 	;取实际长度  
		ADD DL, 30H  			;将实际索引装化成ascii码

		CMP CL, 30H 			;索引小于0  
		JL ERROR
	
		CMP CL, DL  			;比较CL与DL
		JGE ERROR  				;CL大于等于DL，说明输入索引大于等于实际索引，则跳转ERROR

		LEA DX, STR_3  
		MOV AH, 9 				;输出字符串  
		INT 21H  
	    
		SUB CL, 30H  			;将实际索引转化成ASCII码
		XOR CH, CH  			;将自身清零
		MOV SI, CX  
		LEA BX, BUFF  
		MOV DL, BYTE PTR[BX + SI + 2]  	
		MOV AH, 2  				;输出DL的字符
		INT 21H  
		JMP NOR 
	        
ERROR:  LEA DX, STR_4  
		MOV AH, 9 				;输出字符串str_4
		INT 21H

		LEA DX, STR_5  
		MOV AH, 9 				;输出字符串str-5
		INT 21H

		MOV AH, 4CH
		INT 21H         

NOR:  	LEA DX, STR_5  
		MOV AH, 9 				;输出字符串str_5 
		INT 21H

		MOV AH, 4CH
		INT 21H
		  
		
CODE ENDS

END START