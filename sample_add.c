#include <stdio.h>
#include <string.h>

int j=0;
char s1[10000];
char s2[100][3000];

int main(void){
  FILE *fp;
  char *p;

  if((fp=fopen("sample.txt","r"))==NULL){
    printf("Can't open¥n");
  }
  while(fgets(s1, 10000, fp) != NULL){
    // ()を区切りに文字列を分割
    // 1回目
    p = strtok(s1, "  ");
    strcpy(s2[j],p);
    // 2回目以降
    while(p != NULL) {//NULLのデータがあるのが問題
      j++;
      // strtok関数により変更されたNULLのポインタが先頭
      p = strtok(NULL, "  ");
      if(p!=NULL){
        strcpy(s2[j],p);
      }else{
        strcpy(s2[j],"^");
      }
    }
    j++;
    //ここまで分割処理
    printf("%s",s1);
  }
  for(j=0;j<10;j++){
    printf("%s\n",s2[j]);
  }
  fclose(fp);
  return 0;
}
