#include <stdio.h>
#include <string.h>


void write();

int L=5000;//作品の本文のSptextあるいはSpStage内の最大文字数
int M=250;//タグ情報の最大文字数
int N=4000;//エクセルの行数(3000あれば足りそう)
char text[5000];

int main(void)
{
  write();
  return 0;
}


//記述部分
void write(){
  int i=0;
  int j=0;
  FILE *fr;
  FILE *fs;
  char x[50][3000];//配列長さ合計に限界あるので調整注意
  char *p;

  //Writing.txtは出力ファイル名になる
  fr = fopen("sample_out.txt","wt");//wtにしないと\nで改行してくれないためwtにした

  if((fs=fopen("sample_in.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しtext配列に保存していく。
  while(fgets(text, L, fs) != NULL){
    strtok(text,"\r\n");

      // ()を区切りに文字列を分割(SptextとSpstageに分ける)
      // 1回目
      p = strtok(text, "()");//"("あるいは")"を区切りにしてtext配列内の文字列を分割する。区切り文字はNULLに変更される。
      strcpy(x[j],p);//pに格納された文字列をx配列にコピーする
      // 2回目以降
      while(p != NULL) {
	       j++;
	       // strtokによって変更されたNULLポインタが先頭
	       p = strtok(NULL, "()");
         if(p!=NULL){
	         strcpy(x[j],p);
	       }else{
	         strcpy(x[j],"^");//分割が終わった地点のx[j]に"^"という楔を打つ
	       }
      }
      j=0;
      //ここまで分割処理

      //その文章が"("から文字が始まっていた場合
      if(strncmp(text, "(", 1) == 0){
        while(strcmp(x[j] , "^") != 0){//分割終了の楔が見つかるまで繰り返す
	         if(strcmp(x[j]," ") != 0 && strcmp(x[j],"  ")!=0){//空白の処理
	            fprintf(fr,"    <Spstage>(%s)</Spstage>\n",x[j]);
}
           j++;
           if(strcmp(x[j] , "^") != 0 && strcmp(x[j]," ") != 0 && strcmp(x[j],"  ")!=0){
             fprintf(fr,"     <Sptext>%s</Sptext>\n",x[j]);
	           j++;
	         }
        }
      }else{
         while(strcmp(x[j] , "^") != 0){
           if(strcmp(x[j]," ") != 0 && strcmp(x[j],"  ")!=0){
             fprintf(fr,"    <Sptext>%s</Sptext>\n",x[j]);
           }
           j++;
           if(strcmp(x[j] , "^") != 0 && strcmp(x[j]," ") != 0 && strcmp(x[j],"  ")!=0){
             fprintf(fr,"    <Spstage>(%s)</Spstage>\n",x[j]);
             j++;
           }
         }
      }
      fprintf(fr,"   </p>\n</sp>\n");
    //elseの閉じ括弧
    i++;
    j=0;
  }
  fclose(fs);
  fclose(fr);
}
