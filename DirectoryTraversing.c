#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

void fileLineCounter(const char *file, int *line_count){
	FILE *fptr = fopen(file, "r");
	if (!fptr){
		printf("Cannot open file, bye \n");
		return;
	}
	int lineCount = 0;
	char buffer[4096];
	while (fgets(buffer, sizeof(buffer), fptr)){
		lineCount++;
	}
	fclose(fptr);
	*line_count += lineCount;
}

void traverse(const char *directory, int *line_count){
	DIR *d = opendir(directory);
	if (!d){
		printf("Cannot open directory, bye \n");
		return;
	}
	struct dirent *entry;
	char path[4096];

	while ((entry = readdir(d)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
			continue;
		}

		snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
		if (entry->d_type == DT_DIR){
			traverse(path, line_count);
		}
		else if (entry->d_type == DT_REG && strstr(entry->d_name, ".txt")){
			fileLineCounter(path, line_count);
		}
	}
	closedir(d);
}


int main(){
	char dirpath[4096];
	printf("Enter a directory: ");
	scanf("%s", dirpath);
	int line_count = 0;
	traverse(dirpath, &line_count);
	printf("Amount of lines in all files: %d\n", line_count);
	return 0;
}
