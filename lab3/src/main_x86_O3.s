MonteCarloAlgorithm:
        pushl   %esi                   // добавить в стек содержимое esi
        pushl   %ebx                   // добавить в стек содержимое ebx
        subl    $48, %esp              // зарезервировать 48 байт для локальных переменных
        movl    60(%esp), %esi         // копировать в esi 100000000
        pushl   $0                     // добавить в стек 0 (NULL)
        call    time                   // вызов time
        movl    %eax, (%esp)           // копировать eax (результат time(NULL)) в вершину стека
        call    srand                  // вызов srand
        addl    $16, %esp              // сместить esp, чтобы исключить значение eax и NULL
        testl   %esi, %esi             // логическое И между esi и esi (проверка esi на ноль)
        jle     .L6                    // переход в метку .L6, если esi == 0
        fldz                           // загрузить 0 в стек сопроцессора (создание insideCount)
        xorl    %ebx, %ebx             // обнулить ebx (создание i)
        fstpl   24(%esp)               // извлечь st(0) в стек
.L5:
        call    rand                   // вызов rand
        movl    %eax, 12(%ebp)         // копировать eax(результат rand()) в стек
        fildl   12(%esp)               // загрузить результат rand() в стек сопроцессора
        fdivl   .LC1                   // разделить вершину стека сопроцессора на константу из метки .LC1 (rand() / RAND_MAX)
        fstpl   16(%esp)               // извлечь st(0) в стек (double x)
        call    rand                   // вызов rand
        movl    %eax, 12(%ebp)         // копировать eax(результат rand()) в стек
        fildl   12(%esp)               // загрузить результат rand() в стек сопроцессора
        fdivl   .LC1                   // разделить вершину стека сопроцессора на константу из метки .LC1 (rand() / RAND_MAX)
        fldl    16(%esp)               // загрузить х в стек сопроцессора
        fmul    %st(0), %st            // умножить х на х
        fxch    %st(1)                 // поменять местами st(0) и st(1)
        fmul    %st(0), %st            // умножить у на у
        faddp   %st, %st(1)            // сложить х*х с у*у и вытолкнуть st(0)
        fld1                           // загрузить 1 в стек сопроцессора
        fcomip  %st(1), %st            // сравнить st(1) и st(0) ((х*х + у*у) и 1.0)
        fstp    %st(0)                 // сохранить вершину стека сопроцессора в st(0)
        jb      .L3                    // переход в метку .L3, если (х*х + у*у) < 1.0 
        fldl    24(%esp)               // загрузить insideCount в стек сопроцессора
        fadds   .LC3                   // прибавить к st(0) (insideCount) константу из метки .LC3 (4.0)
        fstpl   24(%esp)               // извлечь st(0) в стек (присвоить результат сложения insideCount)
.L3:
        addl    $1, %ebx               // прибавить 1 к i
        cmpl    %ebx, %esi             // сравнить i и count
        jne     .L5                    // переход в метку .L5, если i != count
.L2:
        movl    %esi, 12(%esp)         // копировать count в стек
        fildl   12(%esp)               // загрузить count в стек сопроцессора
        fdivrl  24(%esp)               // разделить insideCount на count
        addl    $36, %esp              // сместить esp, чтобы исключить локальные переменные
        popl    %ebx                   
        popl    %esi
        ret                            // выход из подпрограммы MonteCarloAlgorithm
.L6:
        fldz                           // загрузить 0 в стек сопроцессора
        fstpl   24(%esp)               // извлечь st(0) в стек (обнулить insideCount)
        jmp     .L2                    // безусловный переход в метку .L2
.LC5:
        .string "PI: %lf\n"
main:
        leal    4(%esp), %ecx          // вычислить эффективный адрес 4(%esp) и поместить в ecx
        andl    $-16, %esp             // логическое и -16 & %esp
        pushl   -4(%ecx)               // добавить в стек содержимое -4(%ecx)
        pushl   %ebp                   // добавить адрес возврата в стек
        movl    %esp, %ebp             // запомнить адрес текущего кадра стека
        pushl   %ecx                   // добавить в стек содержимое %ecx
        subl    $16, %esp              // зарезервировать 16 байтов для локальных переменных
        pushl   $100000000             // добавить в стек значение 100000000
        call    MonteCarloAlgorithm    // вызов MonteCarloAlgorithm
        movl    $.LC5, (%esp)          // копировать в стек строку из метки .LC5, как первый аргумент для вызова printf 
        fstpl   4(%esp)                // извлечь вершину st(0) (результат MonteCarloAlgorithm) в стек до вершины, как второй аргумент для вызова printf 
        call    printf                 // вызов printf
        movl    -4(%ebp), %ecx         // копировать в ecx -4(%ebp)
        addl    $16, %esp              // вернуть 16 байт, использованные при вызове printf         
        xorl    %eax, %eax             // обнулить eax (код завершения функции main)
        leave                          // сбросить кадр стека
        leal    -4(%ecx), %esp         // вычислить эффективный адрес -4(%ecx) и поместить в esp
        ret                            // выход из подпрограммы main
.LC1:
        .long   -4194304               // RAND_MAX
        .long   1105199103
.LC3:
        .long   1082130432             // 4.0