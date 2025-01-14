	.intel_syntax noprefix

	#mkmpos.bas' compilation started at 13:06:56 (FreeBASIC 0.90.1)

.section .text
.balign 16

.globl _PARSELIST@4
_PARSELIST@4:
push ebp
mov ebp, esp
sub esp, 36
push ebx
.Lt_0006:
mov dword ptr [ebp-4], 0
mov dword ptr [ebp-8], 0
mov dword ptr [ebp-20], 0
mov dword ptr [ebp-16], 0
mov dword ptr [ebp-12], 0
mov dword ptr [ebp-4], 0
push 0
push -1
push 2
push offset _Lt_0008
push -1
push dword ptr [ebp+8]
mov dword ptr [ebp-32], 0
mov dword ptr [ebp-28], 0
mov dword ptr [ebp-24], 0
lea eax, [ebp-32]
push eax
call _fb_StrConcat@20
push eax
push -1
push dword ptr [ebp+8]
call _fb_StrAssign@20
mov dword ptr [ebp-8], 1
push -1
push dword ptr [ebp+8]
call _fb_StrLen@8
mov dword ptr [ebp-36], eax
jmp .Lt_000B
.Lt_000E:
push 0
push -1
push 1
push dword ptr [ebp-8]
push dword ptr [ebp+8]
call _fb_StrMid@12
push eax
push -1
lea eax, [ebp-20]
push eax
call _fb_StrAssign@20
push 2
push offset _Lt_0008
push -1
lea eax, [ebp-20]
push eax
call _fb_StrCompare@16
test eax, eax
jne .Lt_0010
push 1
push offset _Lt_0000
push -1
mov eax, dword ptr [ebp-4]
imul eax, 12
lea ebx, [_TOKENS+eax]
push ebx
call _fb_StrCompare@16
test eax, eax
jne .Lt_0012
push 0
push 2
push offset _Lt_0013
push -1
mov eax, dword ptr [ebp-4]
imul eax, 12
lea ebx, [_TOKENS+eax]
push ebx
call _fb_StrAssign@20
.Lt_0012:
cmp dword ptr [ebp-4], 15
jge .Lt_0015
inc dword ptr [ebp-4]
push 0
push 1
push offset _Lt_0000
push -1
mov ebx, dword ptr [ebp-4]
imul ebx, 12
lea eax, [_TOKENS+ebx]
push eax
call _fb_StrAssign@20
.Lt_0015:
jmp .Lt_000F
.Lt_0010:
push 0
push -1
lea eax, [ebp-20]
push eax
push -1
mov eax, dword ptr [ebp-4]
imul eax, 12
lea ebx, [_TOKENS+eax]
push ebx
call _fb_StrConcatAssign@20
.Lt_000F:
.Lt_000C:
inc dword ptr [ebp-8]
.Lt_000B:
mov eax, dword ptr [ebp-36]
cmp dword ptr [ebp-8], eax
jle .Lt_000E
.Lt_000D:
lea eax, [ebp-20]
push eax
call _fb_StrDelete@4
.Lt_0007:
pop ebx
mov esp, ebp
pop ebp
ret 4
.balign 16

.globl _main
_main:
push ebp
mov ebp, esp
and esp, 0xFFFFFFF0
sub esp, 32
push ebx
mov dword ptr [ebp-4], 0
call ___main
push 0
push dword ptr [ebp+12]
push dword ptr [ebp+8]
call _fb_Init@12
.Lt_0002:
mov dword ptr [ebp-16], 0
mov dword ptr [ebp-12], 0
mov dword ptr [ebp-8], 0
mov dword ptr [ebp-20], 0
push 1
push 75
push offset _Lt_0017
call _fb_StrAllocTempDescZEx@8
push eax
push 0
call _fb_PrintString@12
push 1
push 47
push offset _Lt_0018
call _fb_StrAllocTempDescZEx@8
push eax
push 0
call _fb_PrintString@12
push 1
push 66
push offset _Lt_001A
call _fb_StrAllocTempDescZEx@8
push eax
push 0
call _fb_PrintString@12
push -1
push 0
push 0
push -1
lea eax, [ebp-16]
push eax
push 0
push offset _Lt_0000
call _fb_StrAllocTempDescZEx@8
push eax
call _fb_LineInput@24
lea eax, [ebp-16]
push eax
call _PARSELIST@4
mov dword ptr [ebp-20], 0
.Lt_001E:
push 0
push -1
push 2
mov eax, dword ptr [ebp-20]
imul eax, 12
lea ebx, [_TOKENS+eax]
push ebx
call _fb_VAL@4
fmul qword ptr [_Lt_0024]
fadd qword ptr [_Lt_0025]
sub esp, 8
mov dword ptr [esp], 0x5F000000
fcom dword ptr [esp]
fnstsw ax
test ah, 1
jz .Lt_0026
fistp qword ptr [esp]
pop eax
pop ebx
jmp .Lt_0027
.Lt_0026:
fsub dword ptr [esp]
fistp qword ptr [esp]
pop eax
pop ebx
xor ebx, 0x80000000
.Lt_0027:
push ebx
push eax
call _fb_HEXEx_l@12
push eax
push 3
push offset _Lt_001F
mov dword ptr [ebp-32], 0
mov dword ptr [ebp-28], 0
mov dword ptr [ebp-24], 0
lea eax, [ebp-32]
push eax
call _fb_StrConcat@20
push eax
push 0
call _fb_PrintString@12
cmp dword ptr [ebp-20], 15
jge .Lt_0022
push 0
push 2
push offset _Lt_0023
call _fb_StrAllocTempDescZEx@8
push eax
push 0
call _fb_PrintString@12
.Lt_0022:
.Lt_001C:
inc dword ptr [ebp-20]
.Lt_001B:
cmp dword ptr [ebp-20], 15
jle .Lt_001E
.Lt_001D:
push 1
push 0
call _fb_PrintVoid@8
lea eax, [ebp-16]
push eax
call _fb_StrDelete@4
.Lt_0003:
push 0
call _fb_End@4
mov eax, dword ptr [ebp-4]
pop ebx
mov esp, ebp
pop ebp
ret
	#mkmpos.bas' compilation took 0.0009776556640304079 secs

.section .data
.balign 4
_Lt_0000:	.ascii	"\0"

.section .bss
.balign 4
	.lcomm	_TOKENS,192

.section .data
.balign 4
_Lt_0008:	.ascii	",\0"
.balign 4
_Lt_0013:	.ascii	"0\0"
.balign 4
_Lt_0017:	.ascii	"This simple program outputs a 16 array of tile offsets from a list of tiles\0"
.balign 4
_Lt_0018:	.ascii	"you enter. Tiles must be 0-47, comma separated.\0"
.balign 4
_Lt_001A:	.ascii	"Copy/Paste the printout, directly usable by the Vostok Engine MK2.\0"
.balign 4
_Lt_001F:	.ascii	"0x\0"
.balign 4
_Lt_0023:	.ascii	", \0"
.balign 8
_Lt_0024:	.quad	0x4010000000000000
.balign 8
_Lt_0025:	.quad	0x4050000000000000
