#include <stdio.h>
#include <string.h>

void speaker();
void hearer();
void Srelation();
void Hrelation();
void Sgender();
void Hgender();
void Sstatus();
void Hstatus();
void write();


int L=5000;//作品の本文のSptextあるいはSpStage内の最大文字数
int M=250;//タグ情報の最大文字数
int N=4000;//エクセルの行数(3000あれば足りそう)
char text[5000];
char Spe[4000][100];
char Hea[4000][100];
char Sre[4000][100];
char Hre[4000][100];
char Sge[4000][100];
char Hge[4000][100];
char Sst[4000][100];
char Hst[4000][100];



int main(void)
{
  speaker();
  hearer();
  Srelation();
  Hrelation();
  Sgender();
  Hgender();
  Sstatus();
  Hstatus();
  write();
  return 0;
}


void speaker(){
  int a=0;
  FILE *fa;//ファイルポインタの作成

  //ファイルが開けないことを表す
  if((fa=fopen("speaker.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //fgetsで一行ずつ読み出しSpe配列に保存していく。(M-1)文字まで読み込める
  while(fgets(Spe[a], M, fa) != NULL){
    strtok(Spe[a],"\r\n");//配列の最後に付加する改行をやめさせる(Oxygenの都合上)
    a++;
  }
  fclose(fa);
  a=0;
}


void hearer(){
  int b=0;
  FILE *fb;

  if((fb=fopen("hearer.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出してHea配列に保存してい
  while(fgets(Hea[b], M, fb) != NULL){
    strtok(Hea[b],"\r\n");
    b++;
  }
  fclose(fb);
  b=0;
}


void Srelation(){
  int c=0;
  FILE *fc;

  if((fc=fopen("S-relation.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しSre配列に保存していく。
  while(fgets(Sre[c], M, fc) != NULL){
    strtok(Sre[c],"\r\n");
    c++;
  }
  fclose(fc);
  c=0;
}

void Hrelation(){
  int d=0;
  FILE *fd;

  if((fd=fopen("H-relation.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しHre配列に保存していく。
  while(fgets(Hre[d], M, fd) != NULL){
    strtok(Hre[d],"\r\n");
    d++;
  }
  fclose(fd);
  d=0;
}

void Sgender(){
  int e=0;
  FILE *fe;

  if((fe=fopen("S-gender.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しSge配列に保存していく。
  while(fgets(Sge[e], M, fe) != NULL){
    strtok(Sge[e],"\r\n");
    e++;
  }
  fclose(fe);
  e=0;
}

void Hgender(){
  int f=0;
  FILE *ff;

  if((ff=fopen("H-gender.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しHge配列に保存していく。
  while(fgets(Hge[f], M, ff) != NULL){
    strtok(Hge[f],"\r\n");
    f++;
  }
  fclose(ff);
  f=0;
}

void Sstatus(){
  int g=0;
  FILE *fg;

  if((fg=fopen("S-status.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しSst配列に保存していく。
  while(fgets(Sst[g], M, fg) != NULL){
    strtok(Sst[g],"\r\n");
    g++;
  }
  fclose(fg);
  g=0;
}

void Hstatus(){
  int h=0;
  FILE *fh;

  if((fh=fopen("H-status.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しHst配列に保存していく。
  while(fgets(Hst[h], M, fh) != NULL){
    strtok(Hst[h],"\r\n");
    h++;
  }
  fclose(fh);
  h=0;
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
  fr = fopen("Writing.txt","wt");//wtにしないと\nで改行してくれないためwtにした

  if((fs=fopen("context.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しtext配列に保存していく。
  while(fgets(text, L, fs) != NULL){
    strtok(text,"\r\n");

    //Oxygen用に成型していく
    if(strcmp(Spe[i],"StD")==0){//Spe配列と"StD"という文字列を、strcmpで比較する。イコールならば0をかえす
      fprintf(fr, "<p><stage>%s</stage></p>\n",text);
    }else if(strcmp(Spe[i],"\0")==0){
      break;//終了した場合は抜ける(文末には\0がある)
    }else{
      fprintf(fr, "<sp speaker=\"%s\" hearer=\"%s\" Srelation=\"%s\" Hrelation=\"%s\" Sgender=\"%s\" Hgender=\"%s\" Sstatus=\"%s\" Hstatus=\"%s\">\n   <speaker>%s</speaker>\n   <p>\n",Spe[i], Hea[i], Sre[i], Hre[i], Sge[i], Hge[i], Sst[i], Hst[i], Spe[i]);

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

      if(strncmp(text, "(", 1) == 0){
        while(strcmp(x[j] , "^") != 0){  //文字列比較注意
	         if(strcmp(x[j]," ") != 0 && strcmp(x[j],"  ")){//空白の処理
	            fprintf(fr,"    <Spstage>(%s)</Spstage>\n",x[j]);
	         }
           j++;
           if(strcmp(x[j] , "^") != 0 && strcmp(x[j]," ") != 0 && strcmp(x[j],"  ")){
             fprintf(fr,"     <Sptext>%s</Sptext>\n",x[j]);
	           j++;
	         }
         }
       }else{
         while(strcmp(x[j] , "^") != 0){
           if(strcmp(x[j]," ") != 0 && strcmp(x[j],"  ")){
             fprintf(fr,"    <Sptext>%s</Sptext>\n",x[j]);
           }
           j++;
           if(strcmp(x[j] , "^") != 0 && strcmp(x[j]," ") != 0 && strcmp(x[j],"  ")){
             fprintf(fr,"    <Spstage>(%s)</Spstage>\n",x[j]);
             j++;
           }
         }
       }
       fprintf(fr,"   </p>\n</sp>\n");
     }//elseの閉じ括弧
     i++;
     j=0;
   }
   fclose(fs);
   fclose(fr);
}
