#include<stdio.h>
#include<math.h>

double f(double x)
{
    double fx = (x-4) *(x-4) *(x+2);
    return fx;
}

void showValuesInRange(double a,double b, int fileWrite)
{
    char filename[] = "SecantFile1.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter file_1 name: ");
        scanf("%s",filename);
        fp = fopen(filename,"w+");

    }
    printf("	x		f(x)\n\n");
    if(fileWrite) fprintf(fp,"x,f(x)\n");

    if(a>b)
    {
        double t = a;
        a = b;
        b = t;
    }

    double x = a;

    while(x<=b)
    {
        printf("%10lf	%10lf\n",x,f(x));
        if(fileWrite) fprintf(fp, "%lf, %lf\n",x,f(x));
        x = x+1.0;
    }

    if(fileWrite) fclose(fp);

}

double secantMainProc(double xlo, double xh, double accr, int fileWrite)
{

    //print iteration number, xlow, xhi, xmid, relative error, f(xmid) in terminal
    //print iteration number and relative error in file2.csv
    char filename[20] = "SecantFile2.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter file_2 name: ");
        scanf("%s",filename);
        fp = fopen(filename,"w+");
    }

    ///print headline
    printf("Iteration\tx[i-1]\tx[i]		f(x[i-1])		f(x[i])\tRelativeError\t x[i+1]\n");
    if(fileWrite) fprintf(fp,"Iteration,x[i-1],x[i],f(x[i-1]), f(x[i]), Rel.Approx.Err., x[i+1]\n");

    double xlow = xlo;
    double xhi = xh;

    ///1st iteration
    int iteration = 1;
    double xnew = xhi - ( f(xhi)*(xhi-xlo)/(f(xhi)-f(xlow))  );

    printf("%d\t%10lf\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,f(xlow),f(xhi),xnew);
    if(fileWrite) fprintf(fp,"%d, %.10lf,%.10lf, %.10lf, %.10lf,---, %.10lf\n",iteration,xlow,xhi,f(xlow),f(xhi),xnew);

    double relErr = 100;

    xlow = xhi;
    xhi = xnew;

    while(relErr>accr)
    {
        iteration++;

        xnew = xhi - (f(xhi)*(xhi-xlow)/(f(xhi)-f(xlow)));

        //calcaulting error %
        relErr = xnew - xhi;
        relErr = fabs(relErr)*100.0;
        relErr = relErr/xnew;
        relErr = fabs(relErr);

        //printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xmid,f(xmid));
        printf("%d\t%10lf\t%10lf	%10lf	%10lf	%10lf		%.9lf\n",iteration,xlow,xhi,f(xlow),f(xhi),relErr,xnew);
        if(fileWrite) fprintf(fp,"%d, %.10lf,%.10lf, %.10lf, %.10lf, %.20lf, %.10lf\n",iteration,xlow,xhi,f(xlow),f(xhi),relErr,xnew);

        //update oldx;
        xlow = xhi;
        xhi = xnew;
    }

    /// updated oldx is the solution now;

    printf("\nTotal iteartions: %d\nApproximate solution: %.10lf\nRelative Approx. Error: %.10lf\n",iteration,xnew,relErr);

    if(fileWrite) fclose(fp);
    return xnew;

}

int main()
{
    //showValuesInRange(0,20,0);  //for part 1;

    printf("Enter xlo, xhi and accepted accuracy separated by space: ");
    double xlo, xhi, accr;
    scanf("%lf %lf %lf", &xlo, &xhi, &accr);

    printf("Want to write all data in file? (1 = yes/ 0 = no): ");
    int fileWrite = 0;
    scanf("%d",&fileWrite);

    double soln = secantMainProc(xlo,xhi,accr,fileWrite);


    return 0;
}

