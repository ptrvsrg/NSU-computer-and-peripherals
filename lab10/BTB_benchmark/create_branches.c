#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if (argc < 2)
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

    int branch_count = atoi(argv[1]);

    // write header
    fprintf(file,
        "#ifndef BRANCHES_H\n"
        "#define BRANCHES_H\n\n"
        "void RunBranches(void) {\n"
        "\tasm volatile (\n"
        "\t\t\"mov $10, %%eax;\\n\"\n"
        "\t\t\"cmp $15, %%eax;\\n\"\n"
        "\t\t\".p2align 1\\n\"\n"
    );

    for (int i = 0; i < branch_count; ++i)
        fprintf(file,
                "\t\t\"jle label_%d;\\n\"\n"
                "\t\t\"label_%d:\\n\"\n",
                i, i);

    // write tail
    fprintf(file,
            "\t);\n"
            "}\n\n"
            "#endif //BRANCHES_H"
    );

    fclose(file);
    return EXIT_SUCCESS;
}