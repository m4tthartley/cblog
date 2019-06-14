#include <stdio.h>
// #include <dirent.h>
#include <glob.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int globError(const char* epath, int error) {
	printf("error\n");
	return error;
}

int main() {
	// DIR* dir;
	// struct dirent* file;
	// dir = opendir("photos");
	// while(file = readdir(dir)) {
	// 	if (file->d_type == DT_DIR) {
	// 		printf("%s \n", file->d_name);
	// 	}
	// }

	glob_t files;
	glob("photos/*/DSCF0802.jpg", 0, globError, &files);
	for (int i = 0; i < files.gl_pathc; i++) {
		printf("%s \n", files.gl_pathv[i]);

		int w;
		int h;
		int n;
		unsigned char* data = stbi_load(files.gl_pathv[i], &w, &h, &n, 0);

		int w2 = w /*/ 2*/;
		int h2 = h /*/ 2*/;
		printf("%i %i %i \n", w, h, n);
		unsigned char* output = malloc(w2*h2*n);
		for (int y=0; y<h2; y++)
		for (int x=0; x<w2; x++)
		for (int c=0; c<n; c++) {
			output[(y*w2+x)*n + c] = data[(y*w2+x)*n + c];
		}

		char* outputDir = "out/";
		char* outputPath = malloc(strlen(outputDir) + strlen(files.gl_pathv[i]) + 1);
		// outputPath[0] = 0;
		strcat(outputPath, outputDir);
		strcat(outputPath, files.gl_pathv[i]);
		printf("%s\n", outputPath);
		stbi_write_jpg(outputPath, w2, h2, n, output, 50);
	}

	printf("hi\n");
}