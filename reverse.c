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

    fseek(input, 0L, SEEK_END);
    unsigned long sz = ftell(input);
    rewind(input);

    for (int i = 0; i < HEADER_SIZE; i++) {
        BYTE data;

        fread(&data, sizeof(BYTE), 1, input);
        fwrite(&data, sizeof(BYTE), 1, output);
    }

    unsigned long amountOfSampleBytesToAllocate = (sz - HEADER_SIZE) / sizeof(SAMPLE_BYTES);
    SAMPLE_BYTES data[amountOfSampleBytesToAllocate];
    unsigned int index = 0;
    unsigned long sizeOfSampleBytes = sizeof(SAMPLE_BYTES);

    while (fread(&data[index], sizeOfSampleBytes, 1, input) == 1) {
        index++;
    }

    unsigned int sampleIdentifier = 0;
    for (unsigned int i = 0; i < amountOfSampleBytesToAllocate; i++) {
        fwrite(&(data[amountOfSampleBytesToAllocate - 1 - i]), sizeOfSampleBytes, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
