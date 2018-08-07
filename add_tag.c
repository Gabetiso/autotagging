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


int i=0;
int j=0;
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
char x[50][3000];//配列長さ合計に限界あるっぽい



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
  FILE *fp;

  //ファイルが開けないことを表す
  if((fp=fopen("speaker.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しspe配列に保存していく。
  while(fgets(Spe[a], 256, fp) != NULL){
    strtok(Spe[a],"\r\n");//配列の最後に付加する改行をやめさせる
    a++;
  }
  fclose(fp);
  a=0;
}


void hearer(){
  int b=0;
  FILE *fq;

  if((fq=fopen("hearer.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しhea配列に保存していく
  while(fgets(Hea[b], 256, fq) != NULL){
    strtok(Hea[b],"\r\n");
    b++;
  }
  fclose(fq);
  b=0;
}


void Srelation(){
  int c=0;
  FILE *ft;

  if((ft=fopen("S-relation.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しSre配列に保存していく。
  while(fgets(Sre[c], 256, ft) != NULL){
    strtok(Sre[c],"\r\n");
    c++;
  }
  fclose(ft);
  c=0;
}

void Hrelation(){
  int d=0;
  FILE *fu;

  if((fu=fopen("H-relation.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しHre配列に保存していく。
  while(fgets(Hre[d], 256, fu) != NULL){
    strtok(Hre[d],"\r\n");
    d++;
  }
  fclose(fu);
  d=0;
}

void Sgender(){
  int e=0;
  FILE *fv;

  if((fv=fopen("S-gender.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しSge配列に保存していく。
  while(fgets(Sge[e], 256, fv) != NULL){
    strtok(Sge[e],"\r\n");
    e++;
  }
  fclose(fv);
  e=0;
}

void Hgender(){
  int f=0;
  FILE *fw;

  if((fw=fopen("H-gender.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しHge配列に保存していく。
  while(fgets(Hge[f], 256, fw) != NULL){
    strtok(Hge[f],"\r\n");
    f++;
  }
  fclose(fw);
  f=0;
}

void Sstatus(){
  int g=0;
  FILE *fx;

  if((fx=fopen("S-status.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しSst配列に保存していく。
  while(fgets(Sst[g], 256, fx) != NULL){
    strtok(Sst[g],"\r\n");
    g++;
  }
  fclose(fx);
  g=0;
}

void Hstatus(){
  int h=0;
  FILE *fy;

  if((fy=fopen("H-status.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しHst配列に保存していく。
  while(fgets(Hst[h], 256, fy) != NULL){
    strtok(Hst[h],"\r\n");
    h++;
  }
  fclose(fy);
  h=0;
}


void write(){
  FILE *fr;
  FILE *fs;
  char *p;

  fr = fopen("Writing.txt","wt");//wtにしないと\nで改行してくれない
  i=0;
  j=0;
  if((fs=fopen("context.txt","r"))==NULL){
    printf("Can't open\n");
  }
  //一行ずつ読み出しtext配列に保存していく。
  while(fgets(text, 5000, fs) != NULL){
    strtok(text,"\r\n");

    if(strcmp(Spe[i],"StD")==0){
      fprintf(fr, "<p><stage>%s</stage></p>\n",text);
    }else if(strcmp(Spe[i],"\0")==0){//終了した場合
      break;
    }else{
      fprintf(fr, "<sp speaker=\"%s\" hearer=\"%s\" Srelation=\"%s\" Hrelation=\"%s\" Sgender=\"%s\" Hgender=\"%s\" Sstatus=\"%s\" Hstatus=\"%s\">\n   <speaker>%s</speaker>\n   <p>\n",Spe[i], Hea[i], Sre[i], Hre[i], Sge[i], Hge[i], Sst[i], Hst[i], Spe[i]);
      // ()を区切りに文字列を分割
      // 1回目
      p = strtok(text, "()");
      strcpy(x[j],p);
      // 2回目以降
      while(p != NULL) {
	j++;
	// strtok関数により変更されたNULLのポインタが先頭
	p = strtok(NULL, "()");
	if(p!=NULL){
	  strcpy(x[j],p);
	}else{
	  strcpy(x[j],"^");
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
