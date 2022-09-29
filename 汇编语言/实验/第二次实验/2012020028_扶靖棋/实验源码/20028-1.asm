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
		MOV AH, 9 				;����ַ���str_1,��ʾ����  
		INT 21H  

		LEA DX, BUFF  
		MOV AH, 10 				;�����ַ���  
		INT 21H

		LEA DX, STR_2  
		MOV AH, 9 				;����ַ���str_2,��ʾ��������  
		INT 21H  
	
		MOV AH, 01  
		INT 21H       
		MOV CL, AL 				;����������������������CL  
	        
		LEA SI, BUFF  
		MOV DL, BYTE PTR[SI+1] 	;ȡʵ�ʳ���  
		ADD DL, 30H  			;��ʵ������װ����ascii��

		CMP CL, 30H 			;����С��0  
		JL ERROR
	
		CMP CL, DL  			;�Ƚ�CL��DL
		JGE ERROR  				;CL���ڵ���DL��˵�������������ڵ���ʵ������������תERROR

		LEA DX, STR_3  
		MOV AH, 9 				;����ַ���  
		INT 21H  
	    
		SUB CL, 30H  			;��ʵ������ת����ASCII��
		XOR CH, CH  			;����������
		MOV SI, CX  
		LEA BX, BUFF  
		MOV DL, BYTE PTR[BX + SI + 2]  	
		MOV AH, 2  				;���DL���ַ�
		INT 21H  
		JMP NOR 
	        
ERROR:  LEA DX, STR_4  
		MOV AH, 9 				;����ַ���str_4
		INT 21H

		LEA DX, STR_5  
		MOV AH, 9 				;����ַ���str-5
		INT 21H

		MOV AH, 4CH
		INT 21H         

NOR:  	LEA DX, STR_5  
		MOV AH, 9 				;����ַ���str_5 
		INT 21H

		MOV AH, 4CH
		INT 21H
		  
		
CODE ENDS

END START