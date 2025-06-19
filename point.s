.text
move_point: .global move_point
    @struct : int x 4byte, int y 4byte, char dir 1byte
    @r0 : point struct : pointer
    @r1 : dir : char
    @r2 : tmp, x or y value
    push    {lr}
    ldrb    r1, [r0, #8]

    cmp     r1, #'w'    @ case : w
    beq     case_w
    cmp     r1, #'s'    @ case : s
    beq     case_s
    cmp     r1, #'a'    @case : a
    beq     case_a
    cmp     r1, #'d'    @case : d
    beq     case_d
    b       ret         @case : default

case_w:
    ldr   r2, [r0, #4]
    sub   r2, r2, #1
    str   r2, [r0, #4]
    b     ret
case_s:
    ldr   r2, [r0, #4]
    add   r2, r2, #1
    str   r2, [r0, #4]  
    b     ret  
case_a:
    ldr   r2, [r0]
    sub   r2, r2, #1
    str   r2, [r0]
    b     ret
case_d:
    ldr   r2, [r0]
    add   r2, r2, #1
    str   r2, [r0]
    b     ret

ret:
    pop     {pc}

    