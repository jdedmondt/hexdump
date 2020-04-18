#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void die(const char *msg) {
	perror(msg);
	exit(1);
}

int load_rom(const char *path, uint8_t **output) {
	FILE *file = fopen(path, "r");
	
	uint8_t *contents = malloc(1);
	
	if (file == NULL) {
		die("could not load rom\n");
	}
	
	uint8_t temp;
	
	int i = 0;
	while (fread(&temp, 1, 1, file)) {
		contents[i++] = temp;
		contents = realloc(contents, i+1);
	}
	
	*output = contents;
	
	return i;
}

void print_rom(uint8_t *rom, int bytes) {
	for (int i = 1; i <= bytes; i++) {
		printf("%02X ", rom[i-1]);
		if (!(i % 16)) { printf("| 0x%02X - 0x%02X\n", i-16, i); }
		if (!(i % 64)) { putchar('\n'); }
	}
	
	printf("\n\n%d bytes\n", bytes);
}

int main(int argc, char **argv) {
	
	if (argc == 2) {	
	
		uint8_t *rom;
	
		int bytes = load_rom(argv[1], &rom);
	
		print_rom(rom, bytes);
	
	} else {
		printf("invalid agruments\n");
	}
			
	return 0;
}
