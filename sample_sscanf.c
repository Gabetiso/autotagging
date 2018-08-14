#include <stdio.h>
#include <string.h>

int j=0;
int M=5000;//読み込みできる最大文字数
//char s1[5000];
//char s2[4000][1000];

int main(void){
  FILE *fp;
  //char *p;
  //char text[4000][1000];
  char line[5000];
  char Spe[4000][100];
//  char Hea[4000][1000];
  //char Sre[4000][1000];
  //char Hre[4000][1000];
  char Sge[4000][100];
  //char Hge[4000][1000];
  char Sst[4000][100];
  //char Hst[4000][1000];


  if((fp=fopen("sample_human.txt","r"))==NULL){
    printf("Can't open¥n");
  }
  while(fgets(line, M, fp) != NULL){
  //while(fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", Spe[j], Sge[j], Sst[j], Sre[j], text[j], Hea[j], Hge[j], Hst[j], Hre[j])!=EOF){
  sscanf(line, "%s\t%s\t%s", Spe[j], Sge[j], Sst[j]);
    // タブ区切りに文字列を分割
    //p = strtok(s1, "\t");
    //strcpy(s2[j],p);

    //while(p != NULL){//NULLのデータがあるのが問題
      j++;
      //p = strtok(NULL, "\t");
      //if(p!=NULL){
        //strcpy(s2[j],p);
      //}else{
        //strcpy(s2[j],"^");
      //}
    //}
    //ここまで分割処理
    printf("%s",line);
    //printf("%s\n",Spe[j]);
  }
  //for(j=0;j<5;j++){
    //printf("%s%s%s\n",Spe[j],Sge[j],Sst[j]);
  //}
  fclose(fp);
  return 0;
}
