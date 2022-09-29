DATA SEGMENT
str_A DB 'Input a number (<= 5): $'
str_B DB 0AH,0DH,'Input anotHer number : $'
RES DB 0AH,0DH,'THe finAL result is : $'
Infor DB 0AH,0DH, 'My Information:2012020028_fujingqi$'
;0DH和0AH分别为非显示字符回车和换行的ASCII码值，美国符号"＄"为字符串结束标志，不能省略
DATA ENDS

MYCODE SEGMENT

ASSUME CS:MYCODE,DS:DATA

START:
	MOV AX,DATA
    MOV DS,AX
    ;把data转到DS数据段寄存器,让数据段指向正确的位置,DATA不是指令，而是伪指令
    LEA DX,str_A
    ;DOS功能调用AH 09H显示字符串，DS:DX=串地址
	MOV AH,09H  
	INT 21H
	;DOS功能调用AH 01H键盘输入并回显 AL = 输入的字符串
	
	MOV AH,01H  
	INT 21H
	SUB AL,30H      ;将输入的字符转成对应的数值

	MOV BL,AL       ;再将上方输入的数值字符传入BL

	lea DX,str_B
	MOV AH,09H      ;显示字符串 ds:DX=串地址 '$'结束字符串
	INT 21H

	MOV AH,01H      ;键盘输入并回显 AL=输入字符
	INT 21H
	SUB AL,30H      ;将输入的字符转成对应的数值
	
	ADD BL,AL
	
    lea DX,RES      ;输出字符串3
	MOV AH,09H  
	INT 21H

	MOV DL,BL       ;将最后的结果传入DL
	ADD DL,30H
    ;DOS功能调用AH 02H显示输出 DL=输出字符
	
	MOV AH,02H
	INT 21H

    lea DX,Infor      ;输出个人信息的字符串
	MOV AH,09H  
	INT 21H
	
    MOV  AX , 4C00H ; 程序返回指令
    INT  21H

MYCODE ENDS

END START