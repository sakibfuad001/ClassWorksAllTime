.model small
.stack 100h
.data 
kk dw 10    
counter dw 0 
filename2 db "b.txt",0
numbers db 0ah,0dh,"numbers:$"
letters db 0ah,0dh,"letters:$"
output_letters db "letters:$"
output_numbers  db "numbers:$"
result db 512 dup (0)  
letter dw 0  
output db 50 dup (0)
number dw 0
prompt db "filename:$"
ff db 0ah,0dh,"enter the filename where to write:$"
filename db 30 dup(0)

buffer db 512 dup(0)
handle dw ?
opener db 0dh,0ah,'open error-code$'
errcode db 30h,'$'
.code        
main proc
    mov ax,@data
    mov ds,ax
    mov es,ax
    call getname_
    lea dx,filename
    mov al,0
    call open_
    jc open_error
    mov handle,ax
 read_loop:
    lea dx,buffer
    mov bx,handle
    call read_
    or ax,ax
    je exit
    mov cx,ax
    call display_
    jmp read_loop
 open_error:
    lea dx,opener
    add errcode,al
    mov ah,9
    int 21h 
    mov ah,4ch
    int 21h
exit: 
mov bx,handle
call close_
  mov ah,2
  mov dl,0ah
  int 21h
  mov dl,0dh
  int 21h
    lea si,output_letters
    lea di,output
    mov cx,8
    cld
    rep movsb  
    add counter,8
    mov ax,letter 
    call include_    
   
    lea si,output_numbers
    mov cx,8
    cld
    rep movsb  
   add counter,8
    mov ax,number
    call include_ 
    mov [di],'$' 
   ; inc counter
      mov  ax,@data
  mov  ds,ax


  mov  ah, 3ch
  mov  cx, 0
  mov  dx, offset filename2
  int  21h  


  mov  handle, ax


  mov  ah, 40h
  mov  bx, handle
  mov  cx, counter 
  mov  dx, offset output
  int  21h
    jc open_error_2
    
          

  mov  ah, 3eh
  mov  bx, handle
  int  21h  
  
  lea dx,filename2
    mov al,0
    call open_
    jc open_error_
    mov handle,ax
 read_loop_:
    lea dx,result
    mov bx,handle
    call read_
    or ax,ax
    je exit2
    mov cx,ax
    call display_2
    jmp read_loop_
 open_error_:
    lea dx,opener
    add errcode,al
    mov ah,9
    int 21h 
    mov ah,4ch
    int 21h    
   
exit2:
    mov bx,handle
    call close_
        
   
    mov ah,4ch
    int 21h
main endp    

open_error_2 proc near:
    mov dx,ax
    add dx,30h
    mov ah,2
    int 21h
    mov ah,4ch
    int 21h
    ret
open_error_2 endp 
display_2 proc near   
    push bx
    mov ah,40h
    mov bx,1
    int 21h
    pop bx
    ret
display_2 endp
include_ proc near
    mov cx,0
    
loops:
    mov dx,0
     div kk
     inc cx
     push dx
     cmp ax,0
     jne loops
sesh:
   pop dx
   add dl,30h
   mov [di],dl
   inc counter
   inc di
   dec cx
   jne sesh
   ret
include_ endp 
getname_ proc near
    push ax
    push dx
    push di
    mov ah,9
    lea dx,prompt
    int 21h
    cld
    lea di,filename
    mov ah,1
 read_name:
    int 21h
    cmp al,0dh
    je done
    stosb
    jmp read_name
done:
    mov al,0
    stosb
    pop di
    pop dx
    pop ax
    ret
getname_ endp
open_ proc near
    mov ah,3dh
    mov al,0
    int 21h
    ret
open_ endp
read_ proc near
    push cx
    mov ah,3fh
    mov cx,512
    int 21h
    pop cx
    ret
read_ endp 

display_ proc near
    push di   
    push bx
    mov bx,0
    mov di,dx
counting_loop:
    cmp [di+bx],48
    jl abar
    cmp [di+bx],57
    jle number_found 
    cmp [di+bx],65
    jl abar
    cmp [di+bx],90
    jle letter_found
    cmp [di+bx],97
    jl abar
    cmp [di+bx],122
    jle letter_found
    jmp abar
letter_found:
    inc letter 
    jmp abar
number_found:
    inc number
    jmp abar
abar:
    dec cx
   
    inc bx    
     cmp cx,0
    jne counting_loop
    pop di
    pop bx
    ret   
display_ endp
close_ proc near
    mov ah,3fh
    int 21h
    ret
close_ endp

end main