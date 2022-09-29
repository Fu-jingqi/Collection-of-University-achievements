DATA	SEGMENT
	str_A DB 'X=12341234H,Y=78955678H,Z=5432H $'
	str_B DB 0AH,0DH,'式子的商为 $'
	str_C DB 0AH,0DH,'式子的余数为 $'
	X	DD	12341234H	;四个字节存储
	Y	DD	78955678H	
	Z	DW	5432H		;两个字节存储	
	A	DW	?			;存放整数
	B	DW	?			;存放小数
	Infor DB 0AH,0DH, 'My Information:2012020028_fujingqi$'		
DATA	ENDS

CODE	SEGMENT
	ASSUME CS:CODE,DS:DATA
START:	
	MOV	AX,DATA
	MOV	DS,AX

	MOV	AX,WORD PTR X	
	SUB	AX,WORD	PTR	Y

	MOV	DX,WORD	PTR	X+2	
	SBB	DX,WORD	PTR	Y+2	

	ADD	AX,24			
	ADC	DX,0			
	DIV	Z				
	MOV	A,AX			
	MOV	B,DX

	; LEA DX,str_A;DOS功能调用AH 09H显示字符串，DS:DX=串地址
	; MOV AH,09H  
	; INT 21H

	; LEA DX,str_B;DOS功能调用AH 09H显示字符串，DS:DX=串地址
	; MOV AH,09H  
	; INT 21H

	; LEA DX,str_C;DOS功能调用AH 09H显示字符串，DS:DX=串地址
	; MOV AH,09H  
	; INT 21H

	MOV	AX,4C00H	
	INT	21H		

CODE	ENDS
	END	START
