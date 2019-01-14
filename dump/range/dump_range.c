#include <stdio.h>
#include <stdlib.h>


#define BUFFER_SIZE (0x800000)

int main(int argc, char *argv[])
{
    unsigned char buffer[BUFFER_SIZE];

    unsigned int start_addr;
    unsigned int size = 0;

    if (argc < 4)
    {
        printf("dump_range <filename> <start addr> <size> \n");
        return -1;
    }

    printf("FILE: %s \n", argv[1]);

    FILE *pFile = NULL;
    FILE *dst   = NULL;

    pFile = fopen(argv[1], "rb");
    if (!pFile)
    {
        printf("fopen src fail \n");
        return -1;
    }

    dst = fopen("out", "wb");
    if (!dst)
    {
        fclose(pFile);
        printf("fopen dst fail \n");
        return -1;
    }

    start_addr = strtol(argv[2], NULL, 16);
    size       = strtol(argv[3], NULL, 16);
    if (size > BUFFER_SIZE)
    {
        printf("file size is larger than buffer \n");
        goto FAIL;
    }

    printf("start: 0x%x , size: 0x%x \n", start_addr, size);
    fseek(pFile, start_addr, SEEK_SET);

    fread(buffer, 1, size, pFile);
    fwrite(buffer , 1, size, dst);

FAIL:
    fclose(pFile);
    fclose(dst);
}
