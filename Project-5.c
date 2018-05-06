#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define true 1
#define false 0
#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"
#define RED   "\x1b[31m"

char *getcwd(char *buf, size_t size);
void print(char*);
bool pathIsRelative(char*);
char* getFullPath(char*);

int main(int argc, char **argv) {
	struct dirent *direntPtr;
	char cwd[1024];
	int k;

	if(argc == 1) {
   		if (getcwd(cwd, sizeof(cwd)) != NULL) { print(cwd); }
		else { return 0; }
	}

	else {		
		for (k = 1; k < argc; k++) { 

			if(pathIsRelative(argv[k])) { 
				argv[k] = getFullPath(argv[k]); 
			}

			print(argv[k]); 
		}
	}

	return 0;
}

void print(char* path) {
	
	char dpathArr[256];
	struct dirent *direntPtr;

	DIR *dirPtr = opendir(path);

	if(dirPtr == NULL) { return; }

	printf("\n");

	while ((direntPtr = readdir(dirPtr)) != NULL) {

		char* completePath;

		if (direntPtr->d_type != DT_DIR) { printf("%s%s\n", RED, direntPtr->d_name); }
		
		else if(direntPtr->d_type == DT_DIR && strcmp(direntPtr->d_name, ".") != 0 && strcmp(direntPtr->d_name, "..") != 0) {

			printf("\nDirectory: %s%s\n", BLUE, direntPtr->d_name);			

			sprintf(dpathArr, "%s/%s", path, direntPtr->d_name); 
				 
			print(dpathArr); 
		} 
	}

	printf("\n");

	printf("%s", NORMAL_COLOR);
	
	closedir(dirPtr);
} 

bool pathIsRelative(char* target) {
	struct dirent *direntPtr;

	if(target[0] == '/') { return false; }

	return true;
}

char* getFullPath(char* target) {

	char *filePath, *homePath, *completePath;

	homePath = getenv("HOME");

	strcat(homePath, "/");				

	strcat(homePath, target);
				
	completePath = homePath; // strcat concatenates strings into first parameter so reassignment is done for clarity.

	return completePath;
}


