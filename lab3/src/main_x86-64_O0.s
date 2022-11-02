MonteCarloAlgorithm:
        pushq   %rbp                    // добавить адрес возврата в стек
        movq    %rsp, %rbp              // запомнить адрес текущего кадра стека
        subq    $48, %rsp               // зарезервировать 48 байт для локальных переменных
        movl    %rdi, -36(%rbp)         // добавить значение rdi (count) в стек
        movl    $0, %edi                // копировать 0 в edi (создание NULL)
        call    time                    // вызвать time
        movl    %eax, %edi              // копировать eax (результат time(NULL)) в edi
        call    srand                   // вызвать srand
        pxor    %xmm0, %xmm0            // исключающее ИЛИ между xmm0 и xmm0 (обнуление xmm0)
        movsd   %xmm0, -8(%rbp)         // добавить значение xmm0 в стек (создание double insideCount)
        movl    $0, -12(%rbp)           // создать i и присвоить 0 
        jmp     .L2                     // безусловный переход в метку .L2                  
.L5:
        call    rand                    // вызов rand
        pxor    %xmm0, %xmm0            // обнулить xmm0
        cvtsi2sdl       %eax, %xmm0     // копировать eax (результат rand()) в xmm0
        movsd   .LC1(%rip), %xmm1       // копировать константу из метки .LC1 (RAND_MAX) в xmm1
        divsd   %xmm1, %xmm0            // разделить rand() на RAND_MAX
        movsd   %xmm0, -24(%rbp)        // копировать rand() / RAND_MAX в стек (создание double x)
        call    rand                    // вызов rand
        pxor    %xmm0, %xmm0            // обнулить xmm0
        cvtsi2sdl       %eax, %xmm0     // копировать eax (результат rand()) в xmm0
        movsd   .LC1(%rip), %xmm1       // копировать константу из метки .LC1 (RAND_MAX) в xmm1
        divsd   %xmm1, %xmm0            // разделить rand() на RAND_MAX
        movsd   %xmm0, -32(%rbp)        // копировать rand() / RAND_MAX в стек (создание double y)
        movsd   -24(%rbp), %xmm0        // копировать x в xmm0
        movapd  %xmm0, %xmm1            // дублировать х 
        mulsd   %xmm0, %xmm1            // умножить х на х
        movsd   -32(%rbp), %xmm0        // копировать у в xmm0
        mulsd   %xmm0, %xmm0            // умножить у на у
        addsd   %xmm0, %xmm1            // сложить х*х и у*у
        movsd   .LC2(%rip), %xmm0       // копировать 1.0 в xmm0
        comisd  %xmm1, %xmm0            // сравнить х*х+у*у и 1.0
        jb      .L3                     // переход в метку .L3, если х*х+у*у < 1.0  
        movsd   -8(%rbp), %xmm1         // копировать insideCount в xmm1
        movsd   .LC3(%rip), %xmm0       // копировать константу из метки .LC3 (4.0) в xmm0
        addsd   %xmm1, %xmm0            // прибавить к 4.0 insideCount
        movsd   %xmm0, -8(%rbp)         // добавить xmm0 в стек (присвоить результат сложения insideCount)
.L3:
        addl    $1, -12(%rbp)           // прибавить 1 к i (++i)
.L2:
        movl    -12(%rbp), %eax         // копировать i в eax
        cmpl    -36(%rbp), %eax         // сравнить i и count
        jl      .L5                     // переход в метку .L5, если i < count
        pxor    %xmm1, %xmm1            // обнулить xmm1
        cvtsi2sdl     -36(%rbp), %xmm1  // копировать count в xmm1
        movsd   -8(%rbp), %xmm0         // копировать insideCount в xmm0
        divsd   %xmm1, %xmm0            // разделить insideCount на count
        movq    %xmm0, %rax             // копировать xmm0 в rax
        movq    %rax, %xmm0             // копировать rax в xmm0
        leave                           // очистить кадр стека
        ret                             // выход из подпрограммы MonteCarloAlgorithm
.LC4:
        .string "PI: %lf\n"
main:
        pushq   %rbp                    // добавить адрес возврата в стек
        movq    %rsp, %rbp              // запомнить адрес текущего кадра стека
        subq    $16, %rsp               // зарезервировать 16 байтов для локальных переменных
        movl    $100000000, -4(%rbp)    // создать count и инциализировать 100000000
        movl    -4(%rbp), %eax          // копировать count в eax
        movl    %eax, %edi              // копировать eax в edi (добавление аргумента MonteCarloAlgorithm)
        call    MonteCarloAlgorithm     // вызов MonteCarloAlgorithm
        movq    %xmm0, %rax             // копироваеть xmm0 (результат MonteCarloAlgorithm) в rax
        movq    %rax, -16(%rbp)         // копировать rax в стек
        movq    -16(%rbp), %rax         // копировать значение из стека в rax
        movq    %rax, %xmm0             // копироваеть rax в xmm0 (второ)
        movl    $.LC4, %edi             // копировать константу из метки .LC4 в edi
        call    printf                  // вызов printf
        movl    $0, %eax                // копировать в eax 0 (код завершения функции main)
        leave                           // очистить кадр стека
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