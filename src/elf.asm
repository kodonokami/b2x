global main
extern system
extern exit

section .text
main:
push kodo
call system

push 0x0
call exit

section .data
db "kodok"
kodo: times 1000000 db 0x90
