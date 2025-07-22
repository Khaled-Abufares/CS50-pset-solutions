//بسم الله الرحمن الرحيم
// This project was completed with assistance from ChatGPT for educational understanding purposes.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#define HEADER_SIZE 44
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }
    FILE *inputFile = fopen(argv[1], "rb");
    if (inputFile == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }
    FILE *outputFile = fopen(argv[2], "wb");
    if (outputFile == NULL)
    {
        printf("Could not open output file.\n");
        fclose(inputFile);
        return 1;
    }
    float volumeFactor = strtof(argv[3], NULL);
    if (volumeFactor < 0.0)
    {
        printf("Volume factor must be non-negative.\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }
    uint8_t waveHeader[HEADER_SIZE];
    fread(waveHeader, sizeof(uint8_t), HEADER_SIZE, inputFile);
    fwrite(waveHeader, sizeof(uint8_t), HEADER_SIZE, outputFile);
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, inputFile) == 1)
    {
        int32_t temp = (int32_t)(sample * volumeFactor);
        if (temp > INT16_MAX) temp = INT16_MAX;
        if (temp < INT16_MIN) temp = INT16_MIN;
        sample = (int16_t)temp;
        fwrite(&sample, sizeof(int16_t), 1, outputFile);
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
