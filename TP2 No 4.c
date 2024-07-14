#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main() {
    char src_file[256], dest_file[256];
    int src_fd, dest_fd, bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Meminta nama file sumber dan file tujuan dari pengguna
    printf("Masukkan nama file sumber: ");
    scanf("%s", src_file);
    printf("Masukkan nama file tujuan: ");
    scanf("%s", dest_file);

    // Mencoba membuka file sumber
    src_fd = open(src_file, O_RDONLY);
    if (src_fd == -1) {
        printf("Gagal membuka file sumber: %s\n", src_file);
        return 1;
    }

    // Mencoba membuka/membuat file tujuan
    dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (dest_fd == -1) {
        printf("File tujuan sudah ada: %s\n", dest_file);
        close(src_fd);
        return 1;
    }

    // Salin isi file sumber ke file tujuan
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            printf("Gagal menulis ke file tujuan: %s\n", dest_file);
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read < 0) {
        printf("Gagal membaca file sumber: %s\n", src_file);
        close(src_fd);
        close(dest_fd);
        return 1;
    }

    printf("File berhasil disalin: %s -> %s\n", src_file, dest_file);

    close(src_fd);
    close(dest_fd);
    return 0;
}