title SECOND PROGRAMM
INCLUDE Irvine32.inc

.data



.code
main PROC



main ENDP
foo PROC
	mov eax,1
	mov ebx,1
	add eax,ebx
	sub eax,ebx
	call DumpRegs

	exit
foo ENDP
END foo