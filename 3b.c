#include &lt;stdio.h&gt;
#include &lt;dirent.h&gt;
int main(int argc, char **argv)
{
DIR *dp;
struct dirent *entry;
// Check if a directory path was provided
if (argc &lt; 2) {
fprintf(stderr, &quot;Usage: %s &lt;directory&gt;\n&quot;, argv[0]);
return 1;
}
// Open the directory
dp = opendir(argv[1]);
if (dp == NULL) {
perror(&quot;opendir&quot;);
return 1;
}
// Print the contents of the directory
printf(&quot;\nContents of the directory %s are:\n&quot;, argv[1]);
while ((entry = readdir(dp)) != NULL) {
printf(&quot;%s\n&quot;, entry-&gt;d_name);
}
// Close the directory
closedir(dp);
return 0;
}
