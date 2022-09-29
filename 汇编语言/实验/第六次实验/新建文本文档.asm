.model small       
.486 
data  segment
  ioM8259E     equ 230H
  ioM8259O     equ 231H
  ioport		equ 210H
  io8255c		equ ioport+2
  io8255k		equ ioport+3
  io8255a		equ ioport
  led      db   3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh,77h,7ch,39h,5eh,79h,71h,73h,0ffh,00h ;段码0～F P 全亮，灭
  BUFF  db 00H   
data ends
STACKS SEGMENT PARA STACK 'STACK'
   DW 200 DUP(?)
STACKS ENDS
code  segment
	assume cs:code,ds:data,ss:STACKS
	start:MOV AX, data
	      MOV DS, AX
	      MOV AL, 80H
	      MOV DX, io8255k
	      OUT DX, AL
	      ; initiallize 8259A
	      CLI
	      MOV DX, ioM8259E
	      MOV AL, 13H
	      OUT DX, AL        ;ICW1
	      
	      MOV DX, ioM8259O
	      MOV AL, 08H
	      OUT DX, AL       ;ICW2
	      
	      MOV AL, 01H
	      OUT DX,AL        ;ICW4
	      
	      MOV AL, 0FFH 
	      OUT DX, AL       ; Write OCW1
	      
	      CALL SToreV   ; Store interupt vector
	      
	      MOV DX, ioM8259O
	      IN AL, DX        ; Read IMR
	      AND AL, 0FBH
	      OUT DX, AL       ; Open IR2
		  STI
	      
	 AG:  MOV BX, OFFSET led
	      MOV AL, BYTE PTR BUFF
	      XLAT
	      MOV DX, io8255a
	      OUT DX, AL
	      MOV DX, io8255c
	      MOV AL,01H
	      OUT DX, AL
	      MOV CX, 00FFH
	 DELAY:loop DELAY
	      JMP AG
	      mov ah, 4ch
	      int 21h
	      
	      InterF PROC    ;Interrupt Service Routine
	         STI
	         PUSH DX
	         PUSH AX
	        
	         MOV AL, BYTE PTR BUFF
			 INC AL
			 CMP AL, 0AH
	         JB IAA
	         MOV AL, 00H
	     IAA:MOV BYTE PTR BUFF, AL
	         MOV AL,20H
	         MOV DX, ioM8259E
	         OUT DX, AL          ;EOI operation
	         POP AX
	         POP DX
	         IRET
	      InterF ENDP
	      
	      SToreV PROC
	         ;store vector
			
	         push DS
	         push SI
	         PUSH AX
			 
	         MOV AX,0
	         MOV DS, AX
	         MOV SI, 0AH
	         mov ah,25h
	         mov al,0ah
	         mov dx,SEG InterF
	         MOV DS,DX
	         MOV DX, OFFSET InterF
	         INT 21H
	         
	         POP AX
	         POP SI
	         POP DS
	         RET
	      SToreV ENDP
    
code ends
	end start
