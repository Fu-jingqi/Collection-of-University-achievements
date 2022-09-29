.model small
.486
IO_ADDRESS  EQU  200H             ;8254基址值
data   segment
d1   dw  ?
data   ends
CODE   EGMENT
     ASSUME CS:CODE,ds:data
START:        
     mov ax,data
     mov ds,ax
     MOV DX, ***H        ;控制字               
     MOV AL, **H         ;计数器0，方式3，BCD码计数
     OUT DX, AL
     MOV DX, ***H        ;计数器0设置初值
     MOV AL, *                  
     OUT DX, AL
     OUT DX, AL          ;写初值10000  产生1S定时周期脉冲
				
    ; MOV DX, ***H
    ; MOV AL, **H         ;计数器1，方式3，二进制计数
    ; OUT DX, AL
    ; MOV DX, ***H
    ; MOV AL, *           ;写初值
    ; OUT DX, AL          ;产生4S定时周期脉冲
	
     HLT              
CODE    ENDS
     END   START