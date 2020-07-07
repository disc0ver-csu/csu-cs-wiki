init_game macro op1,op2,op3,op4,op5,op6		;循环输出用于初始化界面
	;DH行号  DL列号 CX=0
	mov cx,0
	mov dh,op1								;起始行
	mov dl,op2								;起始列
op6:
	mov ah,02h
	mov bh,00h
	int 10h

	push cx
	mov ah,09h
	mov al,op3								;要显示的字符 al=字符的ascii码
	mov cx,01h								;写入字符重复次数
	mov bh,00h								;页号
	mov bl,0afh								;设置颜色
	int 10h
	pop cx

	inc cx
	inc op4									;指出循环输出的是行还是列
	cmp cx,op5								;循环次数
	jne op6
endm

clean macro op1,op2,op3,op4					;用于清屏，分别是起止的行和列号
	;CL左上角行号 CH左上角列号 DL右上角行号 DH右上角列号
	mov ah,06h
	mov al,00h
	mov bh,09h								;改变行属性的色彩，字的色彩 bh表示空白行的属性
	mov ch,op1
	mov cl,op2
	mov dh,op3
	mov dl,op4
	int 10h

	mov ah,02h								;设置光标位置
	mov bh,00h
	mov dh,00h
	mov dl,00h
	int 10h
endm

menu macro op1,op2,op3						;菜单显示宏定义，用于屏幕上方文字的输出
	;DH行号  DL列号
	mov ah,02h
	mov bh,00h
	mov dh,op1
	mov dl,op2
	int 10h
	
	mov ah,09h
	lea dx,op3
	int 21h
endm

DATAS SEGMENT
	;此处输入数据段代码
	fgf db '*******************************************$'
    m1 db 'WELCOME TO PLAY$'
    m2 db 'date:2019/3/22$'
    m3 db 'please press 1 or 2 to continue$'
    menu1 db '1.Start game$'
    menu2 db '2.Exit$'
    menu3 db 'Select number of menu:$'
    menu4 db 'Please input right number$'

    level1 db 'Please choose a level of the new game:$'
    easy   db '1.EASY$'
    hard   db '2.HARD$'
    menu5 db 'Select number of level:$'

    meg db 'Press Enter key to continue *_*$'
    meg1 db 'When a letter is dropping,please hit it!$'
    meg2 db 'Press space key to pause!$'
    meg3 db 'Press ESC key to return to main interface!$'
    meg4 db 'When the game was paused,press ESC to quit!$'
    
    mesmissing db 'MISSING:$'				
    messcore db 'SCORE:$' 					;分数
    meg7 db 'hit the letter num:$'
    meg8 db 'the missing letter num:$'
    meg9 db 'the shooting is:$'

    letter db 0								;随机产生的字母
    speed dw 0                              ;字母下落的速度
    sped1 dw 50000
    position db 0                           ;字母下落的位置（即列号）
    n db 26 								;随机产生的字母要进行转换
    score db 0								;分数
    missing db 0							;错过的字母数
    scoreshi db 0							;分数的十位
	scorege db 0							;分数的个位
    hitshi db 0								;击中率数的十位数
    hitge db 0								;击中率的个位数
    missshi db 0							;错过的十位数
    missge db 0								;错过的个位数
    
    hang db 0
    lie db 0								;记录击中时字母的行列号
    
    string db '100%$'						;初始化的击中率，之后要根据分数和错过数进行转换计算
    
    row db 0
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
;初始化首页
START:
	MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码

index:
	;主界面初始化 置光标类型，隐藏光标
	mov ah,01h
	mov cx,00h
	or ch,00010111b
	int 10h

	clean 0,0,24,80
	;输出非打印控制字符
	init_game 0,0,03h,dl,80,s
	init_game 24,0,03h,dl,80,s1
	;init_game 0,0,03h,dh,25,s2
	;init_game 0,80,03h,dh,25,s3
	;输出字符
	menu 3,15,fgf
	menu 5,25,m1
	menu 7,25,m2
	menu 9,25,m3
	menu 11,25,menu1
	menu 13,25,menu2
	menu 15,15,fgf
	menu 17,25,menu3

;输入选择功能（进入游戏或者退出游戏）
fun_input:
	;放置
	mov ah,2
	mov bh,0
	mov dh,15
	mov dl,47
	int 10h
	
	mov ah,1
	int 21h
	
	cmp al,49                         ;若输入是1，则进入游戏
	je gametip					      ;游戏开始	
   	cmp al,50                         ;若输入是2或者esc则退出程序
   	je exithigh
   	cmp al,1bh
   	je exithigh
   	jmp errortip1


;游戏开始的文字提示
gametip:			
	clean 0,0,24,80						;清屏
	;clean 1,0,23,80					;将除了最上面和最下面的爱心清屏					
	menu 5,15,fgf					;开始的提示语
	menu 7,15,meg
	menu 9,15,meg1
	menu 11,15,meg2
	menu 13,15,meg3
	menu 15,15,meg4
	menu 17,15,fgf
	
	mov ah,07h
	int 21h
	
	cmp al,1bh                        ;按任意键继续，esc除外
	je index	                      ;按esc重新进入主界面（即退出当前游戏）

;进入选择速度界面
choose_speed:
	;clean 1,0,23,80
	clean 0,0,24,80
	menu 7,15,fgf
	menu 9,15,level1
	menu 11,15,easy
	menu 11,40,hard
	menu 13,15,fgf
	menu 15,25,menu5

;速度选择
speed_input:
	mov ah,2
	mov dh,15
	mov dl,49
	int 10h
	mov ah,1
	int 21h
	
	cmp al,49                         ;若输入是1，则选择速度简单
	je speedeasy					 
   	cmp al,50                         ;若输入是2，则选择速度困难
   	je speedhard
   	cmp al,1bh
   	je index
   	jmp errortip2

speedeasy:
	mov speed,10
	jmp play
speedhard:
	mov speed,2  

;开始游戏	
play:
	;clean 1,0,22,80
	clean 0,0,24,80

	call init_score_missing	         ;在游戏界面下显示初始分数score和错过的字母数missing

sub_position:
	sub position,78
	cmp position,0
	jne sub_position_big
	inc position

sub_position_big:
	jmp output_letter

new_position:
	mov ah,2ch                        ;取系统时间产生随机数，确定落下字母的列号
	int 21h
	mov al,dl
	mov position,al                   ;position为字母的列号
	cmp position,0
	jne position_big
	inc position

position_big:
	cmp position,78
	ja sub_position

;在对应的列输出新的字母
output_letter:
	mov dl,position
	mov ah,02h
	mov al,letter
	mov dh,1
	int 10h

;等待输入以及控制下落时间	
temp:
	mov cx,0

nextrow:
	push cx
	mov cx,0

yanchi:
	push cx
	mov cx,0

yanchi1:
	add cx,1
	cmp cx,sped1
	jne yanchi1
	push dx
	mov ah,06h							;直接控制台（输入）
	mov dl,0ffh
	int 21h
	pop dx
	cmp al,0
	int 10h	
	jz pass

;游戏进行中的操作	
action:
	cmp al,32
	je pause                              ;输入空格暂停
	cmp al,1bh
	je exitlow                            ;输入esc退出
	jmp drop

pause:
	push dx
	mov ah,06h
	mov dl,0ffh
	int 21h
	pop dx
	
	cmp al,20h
	jne pause
	jmp pass

;游戏中的退出（得先显示结果）	
exitlow:
	;clean 1,0,23,80
	clean 0,0,24,80
	call result

drop:
	cmp al,letter
	je get_score                       		;若输入与落下字母一样，则高亮后消失并且计分
	jmp pass                              	;若输入与下落字母不一样，则继续下落

get_score:
	;取行列,用于后面高亮之后消失
	mov bh,0
	mov ah,3
	int 10h	
	
	mov hang,dh
	mov lie,dl
	int 10h
	
	call letter_bright

fasheng:	
	call sound
	
letter_disappear:
	call disappear

pass:
	pop cx
	inc cx
	cmp cx,speed                          ;speed为常数
	
	je print
	jmp yanchi

print:
	;当本行输出时没有输入字符时，用空格覆盖原来字符，同时字符下移
	mov ah,0ah
	mov bh,0
	mov al,32
	mov cx,1
	int 10h
	
	inc dh                               ;将光标的位置下移一行，行号加一，下移一行
	mov ah,02h
	mov bh,0
	int 10h	
	
	mov ah,0ah
	mov al,letter
	mov bh,0
	mov cx,1
	int 10h
	
	pop cx
	inc cx
	cmp cx,21
	
	je bottom
	jmp nextrow


bottom:
	;当字母掉到最底下还没有输入则需要重新产生一个字母并且在原来位置并且使错过的字母数+1
	push ax
	mov al,missing
	inc al
	mov missing,al
	pop ax
	
	mov bh,0                                      ;取光标位置
	mov ah,3
	int 10h
	
	mov lie,dl
	int 10h 
	
;输出错过的字母数，进行完此函数后，直接运行new_letter函数，实现又产生字母的功能	
print_missing:
	mov ah,02h
	mov dl,32
	int 21h
	
	;实时输出错过的字母数	
	push ax
	push bx
	mov al,missing
	mov ah,0
	mov bl,10
	div bl
	mov missshi,al
	mov missge,ah
	pop bx
	pop ax
	
	mov ah,2
	mov bh,0
	mov dh,23
	mov dl,60
	int 10h
	
	mov al,missshi
	mov dl,al
	add dl,30h
	mov ah,2
	int 21h
	
	mov dl,missge
	add dl,30h
	mov ah,2
	int 21h

;产生一个新字母
new_letter:
	mov ah,2ch                                    	;取系统时间
	int 21h                        
	mov ah,0                                       
	mov al,dl										;除法商放在al，余数放在al
	div n
	add ah,61h
	mov letter,ah                                   ;产生新的字母
	int 10h
	
	mov ah,02h     									;设置光标位置
	mov bh,00h
	mov dh,hang    
	mov dl,lie
	int 10h
	
	mov ah,09h										;用空格代替原来字母位置的内容
	mov al," "
	mov bh,0
	mov cx,1
	mov bl,00h
	int 10h
	
	jmp new_position

;当选择菜单输入其他键时输出输入错误的提示
errortip1:											
	push ax
	mov ah,1
	int 21h
	menu 17,25,menu4
	mov ah,2
	mov bh,0
	mov bh,0
	mov dh,15
	mov dl,47
	int 10h
	
	mov ah,0ah
	mov al,32
	mov bh,00h
	mov cx,01h
	int 10h
	jmp fun_input

;当选择速度输入其他键时输出输入错误的提示
errortip2:							
	push ax
	mov ah,1
	int 21h
	menu 17,25,menu4
	mov ah,2
	mov bh,0
	mov bh,0
	mov dh,15
	mov dl,47
	int 10h
	
	;移光标
	mov ah,2
	mov bh,0
	mov dh,15
	mov dl,49
	int 10h
	
	mov ah,0ah
	mov al,32
	mov bh,00h
	mov cx,01h
	int 10h
	jmp speed_input

exithigh:							;退出程序
	mov ah,6
	mov bh,7						;清屏
	mov al,0
	mov ch,0
	mov cl,0
	mov dh,24
	mov dl,80
	int 10h
	
	mov ah,2
	mov bh,0
	mov dh,0
	mov dl,0
	int 10h                          
	
	mov ah,4ch
	int 21h

;显示初始分数和错过的个数
init_score_missing proc near

	menu 23,10,messcore
	menu 23,50,mesmissing
	init_game 22,0,' ',dl,80,sk5
	
	push dx
		
	mov ah,2
	mov dh,23
	mov dl,18
	int 10h
	
	mov ah,2
	mov dl,score
	add dl,30h
	int 21h
	
	mov ah,2
	mov dh,23
	mov dl,60
	int 10h
	
	mov ah,02h
	mov dl,missing
	add dl,30h
	int 21h
	
	jmp new_letter
init_score_missing endp

;disappear函数主体（使被击中的字母消失，同时刷新得分）
disappear proc near	
	inc score	
	;实时输出分数	
	push ax
	push bx
	mov al,score
	mov ah,0
	mov bl,10
	div bl
	mov scoreshi,al
	mov scorege,ah
	pop bx
	pop ax	
	
	mov ah,2
	mov bh,0			;覆盖消失的字符
	mov dl,18
	mov dh,23
	int 10h
	
	mov dl,scoreshi
	add dl,30h
	mov ah,2
	int 21h
	
	mov dl,scorege
	add dl,30h
	mov ah,2
	int 21h
	
	jmp new_letter
disappear endp

;letter_bright函数开始
;字母高亮
letter_bright proc near	
	mov ah,09h
	mov al,letter                            ;要显示字符
	mov cx,01h
	mov bh,00h
	mov bl,0a0h                            ;设置颜色
	int 10h
	
	jmp fasheng
letter_bright endp

;sound发声函数
sound proc
	mov al,0b6h                    ;向计数器写控制字
	out 43h,al                     ;方式3、双字节写和二进制计数方式写到控制口
	mov dx,12h                     ;设置搜索被除数
	mov ax,348ch
	mov bx,900
	div bx
	out 42h,al                     ;先送lsb
	mov al,ah
	out 42h,al                     ;后送msb
	;让61端口产生脉冲，打开扬声器
	;读端口原值
	in al,61h                      
	or al,3
	out 61h,al                     ;接通扬声器
	call delay0
	mov al,ah
	out 61h,al
	jmp letter_disappear
sound endp

;发声时间函数
delay0 proc
	push cx
	push ax	
	mov cx,0ffffh
delay1:
	mov ax,0010h
delay2:
	dec ax
	jnz delay2
	loop delay1
	pop ax
	pop cx
	ret
delay0 endp

;result函数，游戏结束后显示得分和命中率
result proc near
	menu 5,15,fgf
	menu 7,25,meg7
	menu 9,25,meg8
	menu 11,25,meg9
	menu 13,15,fgf
	
	push ax
	push bx
	mov al,score
	mov ah,0
	mov bl,10
	div bl
	mov scoreshi,al
	mov scorege,ah
	pop bx
	pop ax
	
	mov ah,2
	mov dl,45
	mov dh,7
	int 10h
	
	mov al,scoreshi
	mov dl,al
	add dl,30h
	mov ah,2
	int 21h
	
	mov dl,scorege
	add dl,30h
	mov ah,2
	int 21h
	
	pop dx
	pop ax
		
	push ax
	push bx
	mov al,missing
	mov ah,0
	mov bl,10
	div bl
	mov missshi,al
	mov missge,ah
	pop bx
	pop ax
	
	mov ah,2
	mov dl,51
	mov dh,9
	int 10h
	
	mov al,missshi
	mov dl,al
	add dl,30h
	mov ah,2
	int 21h
	
	mov dl,missge
	add dl,30h
	mov ah,2
	int 21h
	
	pop dx
	pop ax
	
	push ax
	push bx
	push cx
	push dx
	
	mov ah,2
	mov dl,44
	mov dh,11
	int 10h
	;计算击中率
	mov al,score
	mov dl,missing
	add dl,al
	cmp al,dl
	jne caculate
	
	push dx
	mov ah,09h
	lea dx,string
	int 21h
	pop dx
	
	jmp end_game

caculate:
	mov bl,10
	mul bl
	div dl
	mov hitshi,al
	
	mov al,ah
	mul bl
	div dl
	mov hitge,al
	
hitlv:
	push dx
	mov dl,hitshi
	add dl,30h
	mov ah,2
	int 21h
	
	mov dl,hitge
	add dl,30h
	mov ah,2
	int 21h
	
	mov ah,2
	mov dl,25h                         ;输出%
	int 21h
	pop dx

end_game:
	mov ah,7
	int 21h
	cmp al,1bh
	jne end_game
	
	jmp start
result endp
	
codes ends
	end start




