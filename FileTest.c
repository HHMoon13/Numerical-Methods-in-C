#include<stdio.h>


int main()
{
    FILE *fp, *fpw, *fpr;
    fp = fopen("/home/hhmoon/Desktop/3-2/Numerical/Code Practice/files/test.txt","r+");
    fpw = fopen("/home/hhmoon/Desktop/3-2/Numerical/Code Practice/files/test.txt","a");
    if(fp==NULL || fpw==NULL)
    {
        printf("Can't Open input file\n");
        exit(1);
    }

    char ss[1000];
    int cnt = 1;
    while (!feof(fp))
    {
        if (fscanf(fp, "%s", ss) != 1)
            break;
        fprintf(fpw, "%s %d\n", ss, cnt);
        printf("%s %d\n", ss, cnt++);
    }

    printf("\n\nPrinting is done!\n");

    return 0;
}
