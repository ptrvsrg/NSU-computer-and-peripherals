#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Few args error\n");
        return EXIT_FAILURE;
    }

    FILE * file = fopen("branches.h", "w");
    if (!file)
    {
        fprintf(stderr, "File opening error\n");
        return EXIT_FAILURE;
    }

    int count_branches = atoi(argv[1]);
    int offset = atoi(argv[2]);
    if (offset < 2)
        offset = 2;
    int power = log2(offset);

    // write header
    fprintf(file,
            "#ifndef BRANCHES_H\n"
            "#define BRANCHES_H\n\n"
            "void RunBranches(void) {\n"
            "\tasm volatile (\n"
            "\t\t\"mov $10, %%eax;\\n\"\n"
            "\t\t\"cmp $15, %%eax;\\n\"\n"
            "\t\t\".p2align %d;\\n\"\n",
            power
    );

    for (int i = 0; i < count_branches; ++i)
    {
        fprintf(file,
                "\t\t\"jle label_%d;\\n\"\n"
                "\t\t\"nop;\\n\"\n",
                i);

        for (int j = 0; j < offset - 2; ++j)
            fprintf(file, "\t\t\"nop;\\n\"\n");

        fprintf(file, "\t\t\"label_%d:\\n\"\n", i);
    }

    // write tail
    fprintf(file,
            "\t);\n"
            "}\n\n"
            "#endif //BRANCHES_H"
    );

    fclose(file);

    return EXIT_SUCCESS;
}