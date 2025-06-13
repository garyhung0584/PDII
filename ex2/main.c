#include <stdio.h>
#include <stdlib.h>
void fun(char fileName1[], char fileName2[]) {
FILE *fp1, *fp2;
char ch,full[20];
if ((fp1=fopen(fileName1,"r"))==NULL) {
printf("cannot open file %s",fileName1);
exit(0);
}
fp2=fopen(fileName2,"w");
do {
if ((ch=fgetc(fp1))=='a') ch='@';
printf("%c",ch);
fputc(ch,fp2);
} while (ch!=EOF);
fclose(fp1);
fclose(fp2);
}
int main(void) {
fun("a.txt", "b.txt");
return 0;
}
