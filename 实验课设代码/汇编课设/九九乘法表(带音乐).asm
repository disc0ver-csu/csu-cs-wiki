.MODEL SMALL
.DATA
	SOUND dw 138,147,165,175,196,220,247,262,294,330,349,392,440,494,524,587,587,659,698,784,880,988
	MSG1 DB 'Multiplication table:', 0DH, 0AH, '$'
	MSG2 DB 0DH,0AH,'$'
	
.CODE
	START: CALL MAIN
	
	MAIN PROC FAR
   		MOV AX, @DATA
		MOV DS, AX
		
		LEA SI, SOUND
		MOV DI, 0
		CALL SHOW
		

		MOV AX, 4C00H
		INT 21H
			
	MAIN ENDP

				
		;----------------------发出声音----------------------
		DISPLAY_MUSIC PROC NEAR
		    PUSH AX
		    PUSH DX
		    PUSH CX
		
		    ;8253 芯片(定时/计数器)的设置
		    MOV AL,0B6H    ;8253初始化
		    OUT 43H,AL     ;43H是8253芯片控制口的端口地址
		    MOV DX,12H
		    MOV AX,34DCH
		    DIV WORD PTR [SI] ;计算分频值,赋给AX。[SI]中存放声音的频率值。
		    OUT 42H, AL       ;先送低8位到计数器，42H是8253芯片通道2的端口地址
		    MOV AL, AH
		    OUT 42H, AL       ;后送高8位计数器
		
		    ;设置8255芯片, 控制扬声器的开/关
		    IN AL,61H   ;读取8255 B端口原值
		    MOV AH,AL   ;保存原值
		    OR AL,3     ;使低两位置1，以便打开开关
		    OUT 61H,AL  ;开扬声器, 发声
		
		    MOV DX, 12       ;保持[DI]时长
		
			WAIT1:
			    MOV CX, 28000
			DELAY:
			    NOP
			    LOOP DELAY
			    DEC DX
			    JNZ WAIT1
			
			    MOV AL, AH         ;恢复扬声器端口原值
			    OUT 61H, AL
			
			MOV AX, [SI]
			
			CMP AX, 138
			JNZ NEXT
			MOV DI, 1
			
			NEXT:
			
			CMP AX, 988
			JNZ CONTINUE
			MOV DI, 0
			
			CONTINUE:
			CMP DI, 0
			JZ SUB_
			
			ADD_:
			ADD SI, 2
			JMP END_
			
			SUB_:
			SUB SI, 2
		
		END_:
		    POP CX
		    POP DX
		    POP AX
		    RET
		 DISPLAY_MUSIC ENDP
		;----------------------------------------------------
		
		;--------------------九九乘法表封装------------------
		SHOW PROC NEAR
			PUSH DX
			PUSH CX
			PUSH BX
			PUSH AX
			
			;MOV DX, OFFSET MSG1
		 	;MOV AH, 9H
		 	;INT 21H
		 	
		 	;CX存储a,BX存储b
		 	MOV CX, 1
		 	MOV BX, 1
		 	L1:
		 		MOV DX, 10
		 		CMP CX, DX
		 		JZ END_
		 		
			 	L2:
			 		CALL CALC
			 		CALL DISPLAY_MUSIC
			 		
			 		CMP BX, CX
			 		JZ ENDL2
			 		
			 		INC BX
			 		JMP L2
			 		
			 		ENDL2:
			 			MOV DX, OFFSET MSG2
			 			MOV AH, 9H
			 			INT 21H
			 		
			 			MOV BX, 1
			 			INC CX
			 			JMP L1
			 END_:
			 	POP AX
			 	POP BX
			 	POP CX
			 	POP DX
			 	RET
			 
		 SHOW ENDP
		;----------------------------------------------------
	
	
		;--------------------计算乘法并显示------------------
		CALC PROC NEAR
			PUSH DX
			PUSH AX
		
			MOV AX, CX
	 		CALL OUTPUT
	 		
	 		MOV DL, 'x'
	 		MOV AH, 02H
	 		INT 21H
	 		
	 		MOV AX, BX
	 		CALL OUTPUT
	 		
	 		MOV DL, '='
	 		MOV AH, 02H
	 		INT 21H
	 		
	 		MOV AL, CL
			MUL BL
			CALL OUTPUT
			
			MOV DL, ' '
			MOV AH, 02H
			INT 21H
			
			POP AX
			POP DX
			RET
		CALC ENDP
		;----------------------------------------------------
			
			
			
		;-----------------------显示数值---------------------
		OUTPUT PROC NEAR	;显示的数存储在AX中
			PUSH DX
			PUSH BX
			PUSH CX
			
			START_:
			MOV CX, 0
			L1:
			  MOV DX,0
			  MOV BX,10
			  DIV BX
			  ADD DX,30H
			  PUSH DX
			  INC CX
			  CWD
			  CMP AX,0
			  JZ L2
			  JMP L1
	
			L2:
			  POP AX
			  MOV DL,AL
			  MOV AH,02H
			  INT 21H
			  LOOP L2
			 
			POP CX
			POP BX
			POP DX
			RET
		OUTPUT ENDP
		;----------------------------------------------------
		
		END START

