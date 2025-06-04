.text
move_point: .global move_point
    @struct : int x 4byte, int y 4byte, char dir 1byte
    @r0 : point struct : pointer
    @r1 : dir : char
    @r2 : tmp
    push    {lr}
    ldrb    r1, [r0, #8]

    cmp     r1, #'w'    @ case : w
    ldreq   r2, [r0, #4]
    subeq   r2, r2, #1
    streq   r2, [r0, #4]
    beq     ret

    cmp     r1, #'s'    @ case : w
    ldreq   r2, [r0, #4]
    addeq   r2, r2, #1
    streq   r2, [r0, #4]  
    beq     ret  

    cmp     r1, #'a'    @case : a
    ldreq   r2, [r0]
    subeq   r2, r2, #1
    streq   r2, [r0]
    beq     ret

    cmp     r1, #'d'    @case : d
    ldreq   r2, [r0]
    addeq   r2, r2, #1
    streq   r2, [r0]
    beq     ret
    
ret:
    pop     {pc}

    