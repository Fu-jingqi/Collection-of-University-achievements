data segment
    num db 12h
    x db ?
	y db ?
    Infor DB 0AH,0DH, 'My Information:2012020028_fujingqi$'   
data ends
code segment
    assume cs:code,ds:data
start: 
        mov ax,data
        mov ds,ax
	   
	    mov al,num
		mov ah,al
	    mov cl,4
		shr ah,cl
		mov x,ah
		and al,0fh
		mov y,al
	   
	    mov ax,4c00h 
	    int 21h
code ends
end start
