data segment
	str_1 db 'Please input a string(length<9):$'
	str_2 db 0ah,0dh,'The length of the string is:$'
	str_3 db 0ah,0dh,'The small string is:$'
	Infor DB 0AH,0DH, 'My Information:2012020028_fujingqi$'
	instring db 10,?,10 dup(?);为输入的字符串开辟了空间，将保存于instring
data ends

code segment

	assume cs:code,ds:data

start: 
	mov ax,data
    mov ds,ax
       
    lea dx,str_1 	;显示提示信息
    mov ah,09h		;输出DX
    int 21h
  
    lea dx,instring 
    mov ah,0ah   	; ds:dx = 缓冲区首地址; (ds:dx)=缓冲区最大字符数，DS:DX+1)=实际输入的字符数
    int 21h      	; 返回参数：(ds:dx+1)=实际输入的字符数

    lea dx,str_2  	;显示提示信息
    mov ah,09h      ;显示字符串 ds:dx=串地址 '$'结束字符串
    int 21h

    lea bx,instring ;获取输入字符串的长度值，并显示
    inc bx			;加一
    mov dl,[bx]
    add dl,30h
    mov ah,02h  	; 显示输出 dl = 输出字符
    int 21h

    lea dx,str_3 	;显示提示信息
    mov ah,09h      ;显示字符串 ds:dx=串地址
    int 21h

    mov dl,[bx+2] 	;显示字符串中的第二个字符
    mov ah,02h    	
    int 21h

	mov dl,[bx+3] 	;显示字符串中的第三个字符
    mov ah,02h    	
    int 21h
     
    mov ax,4c00h ;程序返回
    int 21h
code ends
end start       
