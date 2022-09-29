.model small
.486
IO_ADDRESS EQU 200H
data segment
d1 dw ?
data ends
CODE SEGMENT
ASSUME CS:CODE, ds:data
START:
	mov ax, data
	mov ds, ax
	MOV DX, 203H
	MOV AL, 37H
	OUT DX, AL
	MOV DX, 200H
	MOV AL, 0
	OUT DX, AL
	OUT DX, AL

	MOV DX, 203H
	MOV AL, 55H
	OUT DX, AL
	MOV DX, 201H
	MOV AL, 10
	OUT DX, AL

	HLT
CODE ENDS
	END START
