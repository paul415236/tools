#include <stdio.h>
#include <stdlib.h>

void hexDump (void *addr, int len)
{
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}

int main (int argc, char *argv[])
{
	FILE *fptr = NULL;
	long len = 0;
	void *buffer = NULL;

	if (argc < 2)
	{
		printf("./dump filename \n");
		return -1;
	}

	fptr = fopen(argv[1], "rb");
	if (!fptr)
	{
		printf("open file failed \n");
		return -1;
	}

	fseek(fptr, 0L, SEEK_END);
	len = ftell(fptr) + 1;

	if (len == 0)
	{
		printf("empty file \n");
		goto EMPTY_FILE;
	}

	buffer = malloc(len);
	if (!buffer)
	{
		printf("out of memory \n");
		goto EMPTY_FILE;
	}

	fseek(fptr, 0L, SEEK_SET);
	len = fread(buffer, 1, len, fptr);

    hexDump((char *)buffer, len);

	free(buffer);

EMPTY_FILE:
	fclose(fptr);
    return 0;
}
