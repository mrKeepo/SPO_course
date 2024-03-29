%define BUFFER_SIZE 32

section .data
	char_diff: db 0x00
	buf : times 256 db 0

section .text

string_length:
    xor rax, rax
    .loop:
      cmp  byte[rdi + rax], 0 
      je   .exit 
      inc  rax 
      jmp  .loop
    .exit:
    ret

print_string:
    call string_length 
    mov rsi, rdi 
    mov rdi, 1 
    mov rdx, rax 
    mov rax, 1 
    syscall
    ret

print_char:
    push rdi 
    mov rsi, rsp 
    mov rdi, 1 
    mov rdx, 1 
    mov rax, 1 
    syscall
    pop rdi 
    ret

print_newline:
    mov rdi, 10 
    jmp print_char

string_copy:
    call string_length
    mov  rcx, rax 
    inc  rcx 
    xchg rsi, rdi 
    mov  byte[rdi + rax], 0 
    rep  movsb 
    ret

print_uint:
    push rbp 
    mov  rbp, rsp 
    mov  rax, rdi 
    mov  rdi, 10 
    sub  rsp, BUFFER_SIZE 
    dec  rbp
    mov  byte[rbp], 0 
      .loop:
        dec  rbp
        xor  rdx, rdx 
        div  rdi 
        add  rdx, '0' 
        mov  byte[rbp], dl 
        test rax, rax 
        jnz  .loop 
    mov rdi, rbp 
    call print_string 
    add rsp, BUFFER_SIZE 
    pop rbp
    ret

print_int:
  test rdi, rdi
  jns  .unsigned
  push rdi
  mov  rdi, '-' 
  call print_char
  pop  rdi 
  neg  rdi
  .unsigned:
  jmp  print_uint

string_equals:
  call string_length
  mov  rcx, rax
  xchg rdi, rsi 
  call string_length
  cmp  rax, rcx 
  jne  .not_equals 
  repe cmpsb 
  jne  .not_equals
  mov rax, 1 
  ret
  .not_equals:
    mov rax, 0
    ret

read_char:
	push 0
	mov rsi, rsp
	mov rdx, 1
	xor rdi, rdi
	xor rax, rax
	syscall
	pop rax
	ret

read_word:
	push r14
  push r15
  xor r14, r14
  mov r15, rsi
  dec r15

  .read_first:
	  push rdi
	  call read_char
	  pop rdi
	  cmp al, ' '
	  je .read_first
	  cmp al, 10
	  je .read_first
	  cmp al, 13
	  je .read_first
	  cmp al, 9
	  je .read_first
	  test al, al
	  jz .read_success

  .read_next:
	  mov byte [rdi + r14], al
	  inc r14

	  push rdi
	  call read_char
	  pop rdi
	  cmp al, ' '
	  je .read_success
	  cmp al, 10
	  je .read_success
	  cmp al, 13
	  je .read_success
	  cmp al, 9
	  je .read_success
	  test al, al
	  jz .read_success
	  cmp r14, r15
	  je .read_err
	  jmp .read_next

  .read_success:
	  mov byte [rdi + r14], 0
	  mov rax, rdi
	  mov rdx, r14
	  pop r15
	  pop r14
	  ret

  .read_err:
	  xor rax, rax
		xor rdx, rdx
	  pop r15
	  pop r14
	  ret

parse_uint:
  call string_length
  mov rcx, rax
  mov rsi, rdi 
  xor rdx, rdx 
  xor rax, rax 
  .pars:
    xor  rdi, rdi 
    mov  dil, byte[rsi + rdx] 
    cmp  dil, '0' 
    jb   .exit
    cmp  dil, '9' 
    ja   .exit
    sub  dil, '0'
    imul rax, 10 
    add  rax, rdi 
    inc  rdx 
    dec  rcx 
    jnz  .pars
  .exit:
  ret

parse_int:
  cmp byte[rdi], '-' 
  je .minus 
  jmp parse_uint
  .minus:
    inc rdi 
    call parse_uint 
    test rdx, rdx 
    jz .null 
    neg rax 
    inc rdx
    ret
  .null:
    xor eax, eax 
    ret
