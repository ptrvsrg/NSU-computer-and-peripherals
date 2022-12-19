#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Few args error\n");
        return EXIT_FAILURE;
    }

    FILE * file = fopen("main.c", "w");
    if (!file)
    {
        fprintf(stderr, "File opening error\n");
        return EXIT_FAILURE;
    }

    int dummy_branch_count = atoi(argv[1]);

    // write header
    fprintf(file,
            "#include <stdio.h>\n"
            "#include <stdlib.h>\n\n"
            "int main(int argc, char ** argv)\n"
            "{\n"
            "\tint a = 0, b = 0, c = 0;\n\n"
            "\tfor (int i = 0; i < 10000000; ++i)\n"
            "\t{\n"
            "\t\tif ((i %% 5) == 0) a = 2;\n"
            "\t\telse a = 0;\n"
            "\t\tif ((i %% 4) == 0) b = 2;\n"
            "\t\telse b = 0;\n");

    for (int i = 0; i < dummy_branch_count; ++i)
        fprintf(file, "\t\tif (i < 0) a = 1; // dummy branch #%d\n", i + 1);

    // write tail
    fprintf(file,
            "\t\tif ((a * b) == 1) c = 1; // spy branch\n"
            "\t}\n\n"
            "\t// it is necessary that during optimization\n"
            "\t// it is not deleted as unused variable\n"
            "\tif (a == 12345) printf(\"Wow\");\n"
            "\tif (b == 12345) printf(\"Wow\");\n"
            "\tif (c == 12345) printf(\"Wow\");\n\n"
            "\treturn EXIT_SUCCESS;\n"
            "}");

    return EXIT_SUCCESS;
}