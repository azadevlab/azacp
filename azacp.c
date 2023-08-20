#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

typedef struct{
	unsigned long offset;
}PART;

char file_src[79];
char files_dst[79];

void* aza_copy(void *arg);

int main(int argc, char *argv[]){
	struct stat f_stat;
	int file_descr_input, file_descr_output, x, chk, i = 0;
	PART file_part1, file_part2, file_part3;
	pthread_t t1, t2;

	strncpy(file_src, argv[1], sizeof(file_src) - 1);
	file_src[sizeof(file_src) - 1] = '\0';


	strncpy(files_dst, argv[2], sizeof(files_dst) - 1);
	files_dst[sizeof(files_dst) - 1] = '\0';

	file_part1.offset = 0;
	file_part1.size = f_stat.st_size / 3;
	file_part2.offset = file_part1.size;
	file_part2.size = file_part1.size;
	file_part3.offset = file_part2.offset + file_part2.size;
	file_part3.size = f_stat.st_size - file_part3.offset;

	file_descr_input = open(file_src, O_RDONLY);
	file_descr_output = open(files_dst, O_WRONLY|O_CREAT, 0666);

	pthread_create(&t1, NULL, aza_copy, &file_part2);
	pthread_create(&t2, NULL, aza_copy, &file_part3);

	while(i < file_part1.size){
		x = read(file_descr_input, data);
		write(file_descr_output, data, x);
		i += x;
	}

    for (i = 0; i < 3; i++){
        pthread_join(*(threads + i), NULL);
    }
	return 0;
}

void* aza_copy(void *arg){
	int file_input, file_out, x, i = 0;
	PART *file_part;

	file_part = (PART *)arg;
	file_input = open(file_src, O_RDONLY);
    file_out = open(files_dst, O_WRONLY);
    lseek(file_input, file_part->offset, SEEK_SET);
	lseek(file_out, file_part->offset, SEEK_SET);

    while(i < file_part->size){
            x = read(file_input, data);
            write(file_out, data, x);
            i += x;
    }
    close(file_out);
    close(file_input);
	return NULL;
}