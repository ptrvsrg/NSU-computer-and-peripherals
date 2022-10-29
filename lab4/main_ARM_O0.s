MonteCarloAlgorithm:
        push    {r4, r5, r7, lr}        // поместить в стек регистры r4, r5, r7, lr
        sub     sp, sp, #40             // выделить 40 байтов для локальных переменных
        add     r7, sp, #0              // записать в r7 sp+0 (аналог ebp)
        str     r0, [r7, #4]            // записать count в стек
        movs    r0, #0                  // создание NULL для time
        bl      time                    // вызов time
        mov     r3, r0
        mov     r0, r3
        bl      srand                   // вызов srand с аргументом time(NULL)
        mov     r2, #0                  
        mov     r3, #0                  // создание insideCount (старшая и младшая часть)
        strd    r2, [r7, #32]           // записать insideCount в стек
        movs    r3, #0                  // создание i
        str     r3, [r7, #28]           // записать i в стек
        b       .L2                     // перейти к метки .L2
.L5:
        bl      rand                    // вызов rand
        mov     r3, r0                  
        mov     r0, r3
        bl      __aeabi_i2d             // конвертировать rand() в double
        adr     r3, .L8                 // загрузить константу из .L8 (RAND_MAX) в r3
        ldr     r2, [r3]                // загрузить RAND_MAX в r2
        bl      __aeabi_ddiv            // (double)rand() / RAND_MAX
        mov     r2, r0                  // поместить младшую часть в r2 
        mov     r3, r1                  // поместить старшую часть в r3 
        strd    r2, [r7, #16]           // поместить младшую и старшую часть в стек (создание x)
        bl      rand                    // вызов rand
        mov     r3, r0                  
        mov     r0, r3
        bl      __aeabi_i2d             // конвертировать rand() в double
        adr     r3, .L8                 // загрузить константу из .L8 (RAND_MAX) в r3
        ldr     r2, [r3]                // загрузить RAND_MAX в r2
        bl      __aeabi_ddiv            // (double)rand() / RAND_MAX
        mov     r2, r0                  // поместить младшую часть в r2 
        mov     r3, r1                  // поместить старшую часть в r3 
        strd    r2, [r7, #8]            // поместить младшую и старшую часть в стек (создание y)
        ldrd    r2, [r7, #16]           // загрузить х в r2
        ldrd    r0, [r7, #16]           // загрузить х в r0
        bl      __aeabi_dmul            // х * х
        mov     r2, r0                  
        mov     r3, r1                  // сохранить результат вызова в r2 и r3
        mov     r4, r2
        mov     r5, r3                  // переписать результат вызова в r4 и r5
        ldrd    r2, [r7, #8]            // загрузить y в r2
        ldrd    r0, [r7, #8]            // загрузить y в r0
        bl      __aeabi_dmul            // y * y
        mov     r2, r0
        mov     r3, r1                  // сохранить результат вызова в r2 и r3
        mov     r0, r4
        mov     r1, r5                  // переписать х*х в r0 и r1
        bl      __aeabi_dadd            // х*х + у*у
        mov     r2, r0
        mov     r3, r1                  // сохранить результат вызова в r2 и r3
        mov     r0, r2
        mov     r1, r3                  // переписать результат вызова в r0 и r1
        mov     r2, #0                  // обнулить r2
        mov     r3, #0                  // обнулить r3
        movt    r3, 16368               // r3 = (double)(0 | (16368 << 16)) = 1.0
        bl      __aeabi_dcmple          // х*х + у*у <= 1.0 (возвращает 0, если ложно, и 1, если истинно)
        mov     r3, r0                  // поместить результат в r3
        cmp     r3, #0                  // сравнить результат с 0
        beq     .L3                     // перейти к метке .L3, если 0
        mov     r2, #0                  // обнулить r2
        mov     r3, #0                  // обнулить r3
        movt    r3, 16400               // r3 = (double)(0 | (16400 << 16)) = 4.0
        ldrd    r0, [r7, #32]           // загрузить в r0 и r1 insideCount
        bl      __aeabi_dadd            // сложить insideCount и 4.0
        mov     r2, r0                  
        mov     r3, r1                  // переписать изменённый insideCount в r2 и r3
        strd    r2, [r7, #32]           // поместить изменённый insideCount в стек
.L3:
        ldr     r3, [r7, #28]           // загрузить i в r3
        adds    r3, r3, #1              // прибавить к i 1
        str     r3, [r7, #28]           // загрузить изменённый i в r3
.L2:
        ldr     r2, [r7, #28]           // загрузить в r2 i
        ldr     r3, [r7, #4]            // загрузить в r3 count
        cmp     r2, r3                  // сравнить i и count
        blt     .L5                     // перейти к метке .L5, если i < count
        ldr     r0, [r7, #4]            // загрузить в r0 count
        bl      __aeabi_i2d             // конвернтировать count в double
        mov     r2, r0                  
        mov     r3, r1                  // переписать (double)count в r2 и r3
        ldrd    r0, [r7, #32]           // загрузить insideCount в r0 и r1
        bl      __aeabi_ddiv            // insideCount / count
        mov     r2, r0                  
        mov     r3, r1                  // переписать результат в r2 и r3
        mov     r0, r2
        mov     r1, r3                  // переписать результат в r0 и r1 (результат MonteCarloAlgorithm)
        adds    r7, r7, #40             // вернуть 40 байтов, зарезервированные для локальныз переменных
        mov     sp, r7                  // записать r7 в sp (сбрасываем кадр стека)
        pop     {r4, r5, r7, pc}        // вернуть изначальные значения r4, r5, r7, pc
.L8:
        .word   -4194304                // RAND_MAX
        .word   1105199103
.LC0:
        .ascii  "PI: %lf\012\000"
main:
        push    {r7, lr}                // поместить в стек регистры r7, lr
        sub     sp, sp, #16             // выделить 16 байт для локальных переменных
        add     r7, sp, #0              // записать в r7 sp+0 (аналог ebp)
        mov     r3, #57600              // создать count
        movt    r3, 1525                // r1 = 57600 | (1525 << 16) = 100000000
        str     r3, [r7, #12]           // записать count в стек
        ldr     r0, [r7, #12]           // загрузить count в r0 (аргумент функции MonteCarloAlgorithm)
        bl      MonteCarloAlgorithm     // вызвать MonteCarloAlgorithm
        strd    r0, [r7]                // записать в стек результат MonteCarloAlgorithm (создание pi)
        ldrd    r2, [r7]                // загрузить pi (второй аргумент printf)
        movw    r0, #:lower16:.LC0
        movt    r0, #:upper16:.LC0      // поместить указатель на строку из метки .LC0 в r0 (первый аргумент printf)
        bl      printf                  // вызов printf
        movs    r3, #0                  // обнулить r3
        mov     r0, r3                  // копировать значение из r3 в r0 (результат main)
        adds    r7, r7, #16             // вернуть 16 байтов, выделенные для локальных переменных
        mov     sp, r7                  // копировать r7 (аналог ebp) в sp
        pop     {r7, pc}                // вернуть изначальные значения r7, pc