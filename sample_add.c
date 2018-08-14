#include <stdio.h>
#include <string.h>

int j=0;
int M=5000;//読み込みできる最大文字数
char s1[5000];
char s2[4000][1000];

int main(void){
  FILE *fp;
  char *p;

  if((fp=fopen("sample_human.txt","r"))==NULL){
    printf("Can't open¥n");
  }
  while(fgets(s1, M, fp) != "\t"){//タブがnull？
    // タブ区切りに文字列を分割
    p = strtok(s1, "\t");
    strcpy(s2[j],p);

    while(p != NULL){//NULLのデータがあるのが問題
      j++;
      p = strtok(NULL, "\t");
      if(p!=NULL){
        strcpy(s2[j],p);
      }else{
        strcpy(s2[j],"^");
      }
    }
    //ここまで分割処理
    printf("%s",s1);
  }
  //for(j=0;j<35;j++){
    //printf("%s\n",s2[j]);
  //}
  fclose(fp);
  return 0;
}
