#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
FILE *srcFile, *destFile;
char buffer[BUFFER_SIZE];
size_t bytesRead;
// Check if the correct number of arguments is provided
if (argc != 3) {
fprintf(stderr, &quot;Usage: %s &lt;source_file&gt; &lt;destination_file&gt;\n&quot;, argv[0]);
return 1;
}
// Open the source file for reading
srcFile = fopen(argv[1], &quot;rb&quot;);
if (srcFile == NULL) {
perror(&quot;Error opening source file&quot;);
return 1;
}
// Open the destination file for writing
destFile = fopen(argv[2], &quot;wb&quot;);
if (destFile == NULL) {
perror(&quot;Error opening destination file&quot;);
fclose(srcFile);
return 1;
}

// Copy the content from source file to destination file
while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, srcFile)) &gt; 0) {
if (fwrite(buffer, 1, bytesRead, destFile) != bytesRead) {
perror(&quot;Error writing to destination file&quot;);
fclose(srcFile);
fclose(destFile);
return 1;
}
}
// Check for read errors
if (ferror(srcFile)) {
perror(&quot;Error reading from source file&quot;);
}
// Close the files
fclose(srcFile);
fclose(destFile);
printf(&quot;File copied successfully from &#39;%s&#39; to &#39;%s&#39;.\n&quot;, argv[1], argv[2]);
return 0;
}
