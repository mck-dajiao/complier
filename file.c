#include <stdio.h>
#include <stdlib.h>
/**
 *读文件
 */
int rFile(){    
    FILE *fp;
    int flen;
    char *p;
    /* 以只读方式打开文件 */
    if((fp = fopen ("e:\\1.txt","r"))==NULL)
    {
        printf("\nfile open error\n");
        exit(0);
    }
    fseek(fp,0L,SEEK_END); /* 定位到文件末尾 */
    flen=ftell(fp); /* 得到文件大小 */
    p=(char *)malloc(flen+1); /* 根据文件大小动态分配内存空间 */
    if(p==NULL){
        fclose(fp);
        return 0;
    }
    fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */
    fread(p,flen,1,fp); /* 一次性读取全部文件内容 */
    p[flen]=0; /* 字符串结束标志 */
    printf("%s",p);
    fclose(fp);
    free(p);
    getch();
    return 0;
}
/**
 *写文件
 */
int wFile(){
    FILE *stream;
    stream = fopen("e:\\1.txt", "w+");
    fprintf(stream, "hello world!");
    printf("The file pointer is at byte \%ld\n", ftell(stream));
    fclose(stream);
    getch();
    return 0;
}

int main(void){
    /*rFile();*/
    wFile();
    return 0;
}
