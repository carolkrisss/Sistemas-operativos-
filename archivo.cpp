#include <fcntl.h>
#include <unistd.h>
#include <cstring>
int main() {
int fd = open("ej.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
write (fd, "Hola hola\n", strlen("Hola hola\n"));
close(fd);
return 0; 
} 

