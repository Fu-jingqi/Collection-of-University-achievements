.model small
.486
IO_ADDRESS  EQU  200H             ;8254��ֵַ
data   segment
d1   dw  ?
data   ends
CODE   EGMENT
     ASSUME CS:CODE,ds:data
START:        
     mov ax,data
     mov ds,ax
     MOV DX, ***H        ;������               
     MOV AL, **H         ;������0����ʽ3��BCD�����
     OUT DX, AL
     MOV DX, ***H        ;������0���ó�ֵ
     MOV AL, *                  
     OUT DX, AL
     OUT DX, AL          ;д��ֵ10000  ����1S��ʱ��������
				
    ; MOV DX, ***H
    ; MOV AL, **H         ;������1����ʽ3�������Ƽ���
    ; OUT DX, AL
    ; MOV DX, ***H
    ; MOV AL, *           ;д��ֵ
    ; OUT DX, AL          ;����4S��ʱ��������
	
     HLT              
CODE    ENDS
     END   START