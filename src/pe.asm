global _main
extern _system
extern _exit

section .text
_main:
push kodo
call _system

push 0x0
call _exit

section .data
db "kodok"
kodo: times 1000000 db 0x90
