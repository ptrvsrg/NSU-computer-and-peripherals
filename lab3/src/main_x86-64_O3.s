MonteCarloAlgorithm:
        pushq   %r14                    // добавить содержимое регистра r14 в стек
        pushq   %rbp                    // добавить адрес возврата в стек
        movq    %rdi, %rbp              // копировать 100000000 в rbp
        xorl    %edi, %edi              // обнуление ebx (создание NULL)
        pushq   %rbx                    // добавить содержимое регистра rbx в стек
        subq    $16, %rsp               // зарезервировать 16 байтов для локальных переменных
        call    time                    // вызвать time
        movl    %eax, %edi              // копировать eax (результат time(NULL)) в edi
        call    srand                   // вызвать srand
        testq   %rbp, %rbp              // логическое сравнение rbp и rbp (сравнение rbp с 0))
        jle     .L6                     // переход в метку .L6, если rbp <= rbp
        xorl    %ebx, %ebx              // обнуление ebx (создание i)
        xorl    %r14d, %r14d            // обнуление r14d - старшая часть r14 (создание insideCount)
.L5:
        call    rand                    // вызов rand
        pxor    %xmm0, %xmm0            // обнуление xmm0
        cvtsi2sdl       %eax, %xmm0     // копировать eax (результат rand()) в xmm0
        divsd   .LC1(%rip), %xmm0       // разделить rand() на RAND_MAX
        movsd   %xmm0, 8(%rsp)          // копировать rand() / RAND_MAX в стек (создание double x)
        call    rand                    // вызов rand
        movsd   8(%rsp), %xmm0          // копировать х в xmm0
        pxor    %xmm1, %xmm1            // обнуление xmm1
        movsd   .LC2(%rip), %xmm2       // копировать константу из метки .LC2 (1.0) в xmm2
        cvtsi2sdl       %eax, %xmm1     // копировать eax (результат rand()) в xmm1
        divsd   .LC1(%rip), %xmm1       // разделить rand() на RAND_MAX (создание double у)
        mulsd   %xmm1, %xmm1            // умножить у на у
        mulsd   %xmm0, %xmm0            // умножить х на х
        addsd   %xmm1, %xmm0            // сложить х*х и у*у
        comisd  %xmm0, %xmm2            // сравнить х*х+у*у и 1.0
        jb      .L3                     // переход в метку .L3, если х*х+у*у < 1.0  
        movsd   .LC3(%rip), %xmm3       // копировать константу из метки .LC3 (4.0) в xmm3
        movq    %r14, %xmm4             // копировать insideCount в xmm4
        addsd   %xmm4, %xmm3            // прибавить insideCount к 4.0
        movq    %xmm3, %r14             // добавить xmm3 в стек (присвоить результат сложения insideCount)
.L3:
        addq    $1, %rbx                // прибавить 1 к i (++i)
        cmpq    %rbx, %rbp              // сравнить i и count
        jne     .L5                     // переход в метку .L5, если i != count
.L2:
        pxor    %xmm1, %xmm1            // обнуление xmm1
        addq    $16, %rsp               // сместить esp, чтобы исключить локальные переменные
        movq    %r14, %xmm0             // копировать insideCount в xmm0
        cvtsi2sdq       %rbp, %xmm1     // копировать count в xmm1
        popq    %rbx                    // извлечь вершину стека в rbx
        popq    %rbp                    // извлечь вершину стека в rbp
        popq    %r14                    // извлечь вершину стека в r14
        divsd   %xmm1, %xmm0            // разделить insideCount на count
        ret                             // выход из подпрограммы MonteCarloAlgorithm
.L6:
        xorl    %r14d, %r14d            // обнуление r14d - старшая часть r14 (создание insideCount)
        jmp     .L2                     // переход к метке .L2
.LC4:
        .string "PI: %lf\n"
main:                                   
        subq    $8, %rsp                // зарезервировать 8 байтов для локальных переменных
        movl    $100000000, %edi        // поместить 100000000 в edi (аргумент MonteCarloAlgorithm)
        call    MonteCarloAlgorithm     // вызов MonteCarloAlgorithm (результат в xmm0)
        movl    $.LC4, %edi             // поместить строку из метки .LC4 в edi (аргумент printf)
        movl    $1, %eax                // копировать 1 в eax
        call    printf                  // вызов printf
        xorl    %eax, %eax              // обнуление eax (будущий резуьтат main)
        addq    $8, %rsp                // сместить esp, чтобы исключить локальные переменные
        ret                             // выход из подпрограммы main
.LC1:
        .long   -4194304                // RAND_MAX
        .long   1105199103
.LC2:
        .long   0                       // 1.0
        .long   1072693248
.LC3:
        .long   0                       // 4.0
        .long   1074790400