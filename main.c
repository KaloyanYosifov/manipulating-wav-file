#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t SAMPLE_BYTES;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./mwav input.wav output.wav 2\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    for (int i = 0; i < HEADER_SIZE; i++) {
        BYTE data;

        fread(&data, sizeof(BYTE), 1, input);
        fwrite(&data, sizeof(BYTE), 1, output);
    }

    SAMPLE_BYTES data;
    unsigned long sizeOfSampleBytes = sizeof(SAMPLE_BYTES);

    while (fread(&data, sizeOfSampleBytes, sizeOfSampleBytes, input) == sizeOfSampleBytes) {
        SAMPLE_BYTES data2 = data * factor;
        fwrite(&(data2), sizeOfSampleBytes, sizeOfSampleBytes, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
