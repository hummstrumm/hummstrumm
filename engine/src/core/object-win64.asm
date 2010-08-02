PUBLIC  _GetCurrentProcessor_asmforwin64_
_TEXT   SEGMENT
_GetCurrentProcessor_asmforwin64_ PROC NEAR
    push ebp
    mov ebp, esp
    
    mov eax, 1
    cpuid
    shr ebx, 24
    mov eax, ebx
    
    pop ebp
    ret
_GetCurrentProcessor_asmforwin64_ ENDP
_TEXT ENDS
END