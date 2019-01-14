#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_byte = 0;
unsigned char search_ch[30];

int find_count = 0;
unsigned int find_addr[64];
unsigned int previous_row[64] = {0};

void hexDump (void *addr, int len)
{
    int i, preRow = 0;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    int offset  = 0;

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
    //for (i = 0x58a810; i < 0x58a810 + 10; i++) {
    #if 1
        if (search_byte)
        {
            //printf("pc[%x] = %x cur_check = %x \n", i, pc[i], search_ch[offset]);

            if (pc[i] == search_ch[offset])
            {
                if (offset < (search_byte -1))
                {
                    offset ++;
                }
                else
                {
                    find_addr[find_count] = i - search_byte;
                    previous_row[find_count] = preRow;
                    find_count++; 
                    offset = 0;
                }
            }
            else
            {
                offset = 0;
            }
        }
    #endif
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
            preRow = i;
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

    if (find_count)
    {
        find_count --;

        for (; find_count >= 0; find_count --)
            printf("find[%d]0x%x at row: 0x%x \n", find_count, find_addr[find_count], previous_row[find_count]);
    }
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

    if (argc > 2)
    {
        memset(search_ch, 0, sizeof(search_ch));
        search_byte = atoi(argv[2]);
        printf("search %d bytes \n", search_byte);

        int i = 0;
        for (; i < search_byte; i++)
        {
            search_ch[i] = strtol(argv[2+i+1], NULL, 16);
            printf("%x ", search_ch[i]);
            if ((i+1)&16)
                printf("\n");
        }
        if (i)
        {
            printf("\n");
        }
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
