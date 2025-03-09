#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/* Symmetric encryption function */
int encrypt_file(const char *filename, int key) {
    FILE *input_file, *output_file;
    char output_filename[256];
    char *dot_position;
    int c;
    
    /* Open the input file for reading */
    input_file = fopen(filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s for reading\n", filename);
        return 1;
    }
    
    /* Create the output filename by appending _enc before the extension */
    strcpy(output_filename, filename);
    dot_position = strrchr(output_filename, '.');
    
    if (dot_position != NULL) {
        char extension[32];
        strcpy(extension, dot_position);
        *dot_position = '\0';
        strcat(output_filename, "_enc");
        strcat(output_filename, extension);
    } else {
        strcat(output_filename, "_enc");
    }
    
    /* Open the output file for writing */
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s for writing\n", output_filename);
        fclose(input_file);
        return 1;
    }
    
    /* Read each character from the input file, encrypt it, and write to the output file */
    while ((c = fgetc(input_file)) != EOF) {
        /* Simple symmetric encryption: add the key value to each character */
        fputc(c + key, output_file);
    }
    
    /* Close the files */
    fclose(input_file);
    fclose(output_file);
    
    printf("Encrypted %s to %s (key = %d)\n", filename, output_filename, key);
    return 0;
}

/* Symmetric decryption function */
int decrypt_file(const char *filename, int key) {
    FILE *input_file, *output_file;
    char output_filename[256];
    char *dot_position;
    int c;
    
    /* Open the input file for reading */
    input_file = fopen(filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s for reading\n", filename);
        return 1;
    }
    
    /* Create the output filename by appending _dec before the extension */
    strcpy(output_filename, filename);
    dot_position = strrchr(output_filename, '.');
    
    if (dot_position != NULL) {
        char extension[32];
        strcpy(extension, dot_position);
        *dot_position = '\0';
        strcat(output_filename, "_dec");
        strcat(output_filename, extension);
    } else {
        strcat(output_filename, "_dec");
    }
    
    /* Open the output file for writing */
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s for writing\n", output_filename);
        fclose(input_file);
        return 1;
    }
    
    /* Read each character from the input file, decrypt it, and write to the output file */
    while ((c = fgetc(input_file)) != EOF) {
        /* Simple symmetric decryption: subtract the key value from each character */
        fputc(c - key, output_file);
    }
    
    /* Close the files */
    fclose(input_file);
    fclose(output_file);
    
    printf("Decrypted %s to %s (key = %d)\n", filename, output_filename, key);
    return 0;
}

/* Function to check if a file has a specific extension */
int has_extension(const char *filename, const char *extension) {
    size_t filename_len = strlen(filename);
    size_t extension_len = strlen(extension);
    
    if (filename_len < extension_len) {
        return 0;
    }
    
    return strcmp(filename + filename_len - extension_len, extension) == 0;
}

/* Process files in the current directory */
void process_directory(int key) {
    DIR *dir;
    struct dirent *entry;
    int files_processed = 0;
    
    /* Open the current directory */
    dir = opendir(".");
    if (dir == NULL) {
        fprintf(stderr, "Error: Unable to open current directory\n");
        return;
    }
    
    printf("Processing files in the current directory...\n");
    
    /* Read directory entries */
    while ((entry = readdir(dir)) != NULL) {
        /* Process only regular files with .txt extension */
        if (entry->d_type == DT_REG && has_extension(entry->d_name, ".txt")) {
            /* Skip files that are already encrypted or decrypted */
            if (strstr(entry->d_name, "_enc") == NULL && 
                strstr(entry->d_name, "_dec") == NULL) {
                
                printf("Found text file: %s\n", entry->d_name);
                
                /* Encrypt the file */
                if (encrypt_file(entry->d_name, key) == 0) {
                    files_processed++;
                    
                    /* Create the encrypted filename to decrypt it */
                    char enc_filename[256];
                    char *dot_position = strrchr(entry->d_name, '.');
                    
                    if (dot_position != NULL) {
                        strncpy(enc_filename, entry->d_name, dot_position - entry->d_name);
                        enc_filename[dot_position - entry->d_name] = '\0';
                        strcat(enc_filename, "_enc");
                        strcat(enc_filename, dot_position);
                    } else {
                        strcpy(enc_filename, entry->d_name);
                        strcat(enc_filename, "_enc");
                    }
                    
                    /* Decrypt the encrypted file */
                    decrypt_file(enc_filename, key);
                }
            }
        }
    }
    
    closedir(dir);
    
    printf("\nProcess completed. %d file(s) processed.\n", files_processed);
    if (files_processed < 2) {
        printf("Warning: Less than two text files were processed.\n");
        printf("Please make sure there are at least two plain text files in the current directory.\n");
    }
}

int main() {
    const int ENCRYPTION_KEY = 4;
    
    printf("Encryption/Decryption System\n");
    printf("Using symmetric key approach with key = %d\n\n", ENCRYPTION_KEY);
    
    process_directory(ENCRYPTION_KEY);
    
    return 0;
}