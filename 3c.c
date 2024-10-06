#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#define MAX 1024
void usage() {
printf(&quot;Usage: ./a.out filename word\n&quot;);
}
int main(int argc, char *argv[]) {
FILE *fp;
if (argc != 3) {
usage();
exit(1);

}

if (!(fp = fopen(argv[1], &quot;r&quot;))) {
printf(&quot;grep: could not open file: %s\n&quot;, argv[1]);
exit(1);
}

while (fgets(fline, MAX, fp) != NULL) {
count++;

if ((newline = strchr(fline, &#39;\n&#39;)) != NULL) {
*newline = &#39;\0&#39;;
}

if (strstr(fline, argv[2]) != NULL) {
printf(&quot;%s: %d %s\n&quot;, argv[1], count, fline);
occurrences++;
}
}

fclose(fp);

if (occurrences == 0) {
printf(&quot;No occurrences found for &#39;%s&#39; in %s\n&quot;, argv[2], argv[1]);
}
return 0;
}
