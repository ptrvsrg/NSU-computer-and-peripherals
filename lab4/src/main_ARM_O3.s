MonteCarloAlgorithm:
        push    {r4, r5, r6, r7,        // поместить в стек регистры r4, r5, r6, r7,
                r8, r9, r10, fp, lr}    // r8, r9, r10, fp, lr
        mov     r9, r0                  // переписать count в r9          
        movs    r0, #0                  // обнулить r0 (аргумент time)
        sub     sp, sp, #12             // зарезервировать 12 байтов для локальных переменных
        movs    r4, #0                  // обнулить r4 (младшая часть insideCount)
        bl      time                    // вызвать time (реузьтат в r0)
        bl      srand                   // вызвать srand (r0 аргумент)
        movs    r3, #0                  // обнулить r3 (старшая часть insideCount)
        cmp     r9, #0                  // сравнить count и 0
        strd    r3, [sp]                // записать insideCount в стек
        ble     .L2                     // перейти к метке .L2, если count <= 0
        adr     r10, .L11               // загружает RAND_MAX в r10
        mov     r8, #0                  // обнулить r8 (создание i)
.L5:
        bl      rand                    // вызвать rand
        add     r8, r8, #1              // ++i
        bl      __aeabi_i2d             // конвертировать результат rand() в double
        mov     r2, r10                 // переписать RAND_MAX в r2
        bl      __aeabi_ddiv            // (double)rand() / RAND_MAX (создание x)
        mov     r5, r1                  
        mov     r4, r0                  // переписать х в r4 и r5
        bl      rand                    // вызвать rand
        bl      __aeabi_i2d             // конвертировать результат rand() в double
        mov     r2, r10                 // переписать RAND_MAX в r2
        bl      __aeabi_ddiv            // (double)rand() / RAND_MAX (создание у)
        mov     r6, r0                  
        mov     r7, r1                  // переписать y в r6 и r7
        mov     r2, r4
        mov     r3, r5                  // переписать х в r2 и r3
        mov     r0, r4
        mov     r1, r5                  // переписать х в r0 и r1
        bl      __aeabi_dmul            // x*x                
        mov     r4, r0                  
        mov     r5, r1                  // переписать x*x в r4 и r5
        mov     r2, r6                  
        mov     r3, r7                  // переписать y в r2 и r3
        mov     r0, r6
        mov     r1, r7                  // переписать y в r0 и r1
        bl      __aeabi_dmul            // y*y     
        mov     r2, r0
        mov     r3, r1                  // переписать x*x в r2 и r3
        mov     r0, r4
        mov     r1, r5                  // переписать x*x в r0 и r1
        bl      __aeabi_dadd            // y*y + x*x
        movs    r2, #0                  // обнулить r2
        movs    r3, #0                  // обнулить r3
        movt    r3, 16368               // 0 | (16368 << 16) = 1.0 (в r2 и r3)
        bl      __aeabi_dcmple          // х*х + у*у <= 1.0 (возвращает 0, если ложно, и 1, если истинно)
        movs    r3, #0                  // обнулить r3
        movt    r3, 16400               // 0 | (16400 << 16) = 4.0 (в r2 и r3)
        mov     r4, r0                  // переписать результат х*х + у*у <= 1.0 в r4
        movs    r2, #0                  // обнулить r2
        ldrd    r0, [sp]                // загрузить insideCount в r0, r1
        cbz     r4, .L3                 // перейти к метке .L3, если результат сравнения х*х + у*у <= 1.0 равен 0
        bl      __aeabi_dadd            // insideCount + 4.0
        strd    r0, [sp]                // записать insideCount + 4.0 в стек
.L3:
        cmp     r9, r8                  // сравнить count и i
        bne     .L5                     // перейти к метке .L5, если count != i
.L2:
        mov     r0, r9                  // переписать count в r0
        bl      __aeabi_i2d             // конвертировать count в double
        mov     r2, r0                  
        mov     r3, r1                  // переписать (double)count в r2 и r3
        ldrd    r0, [sp]                // загрузить insideCount в r0, r1
        bl      __aeabi_ddiv            // insideCount / count
        add     sp, sp, #12             // вернуть 12 байтов, зарезервированные для локальныз переменных
        pop     {r4, r5, r6, r7,        // вернуть изначальные значения r4, r5, r6, r7,
                r8, r9, r10, fp, pc}    // r8, r9, r10, fp, lr
.L11:
        .word   -4194304                // RAND_MAX
        .word   1105199103
.LC0:
        .ascii  "PI: %lf\012\000"
main:
        push    {r3, lr}                // поместить в стек регистры r3, lr
        mov     r0, #57600
        movt    r0, 1525                // r0 = 57600 | (1525 << 16) = 1.0
        bl      MonteCarloAlgorithm     // вызвать MonteCarloAlgorithm
        mov     r2, r0                  
        mov     r3, r1                  // переписать pi в r2, r3 (второй аргумент printf)
        movw    r0, #:lower16:.LC0
        movt    r0, #:upper16:.LC0      // поместить указатель на строку из метки .LC0 в r0 (первый аргумент printf)
        bl      printf                  // вызвать MonteCarloAlgorithm
        movs    r0, #0                  // обнулить r0 (результат main)
        pop     {r3, pc}                // вернуть изначальные значения r3, pc