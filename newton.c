#include<stdio.h>
#include<math.h>

double f(double x)
{
    double fx = (x-4) *(x-4) *(x+2);
    return fx;
}

double ff(double x)
{
    return 2*(x-4)*(x+2) + (x-4)*(x-4);
}

void showValuesInRange(double a,double b, int fileWrite)
{
    char filename[20] = "NewtonFile1.csv";
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

double newtonRaphsonMainProc(double x_init, double accr, int fileWrite)
{

    //print iteration number, xlow, xhi, xmid, relative error, f(xmid) in terminal
    //print iteration number and relative error in file2.csv
    char filename[20] = "NewtonFile2.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter file_2 name: ");
        scanf("%s",filename);
        fp = fopen(filename,"w+");
    }


    ///print headline
    printf("Iteration\tx[i]		f(xi)		f'(xi)\tRelativeError\t x[i+1]\n");
    if(fileWrite) fprintf(fp,"Iteration,x[i],f(xi), f'(xi), Rel.Approx.Err., x[i+1]\n");

    double xi = x_init;

    ///1st iteration
    int iteration = 1;
    double xnew = xi - f(xi)/ff(xi);

    printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xi,f(xi),ff(xi),xnew);
    if(fileWrite) fprintf(fp,"%d, %.10lf, %.10lf, %.10lf,---, %.10lf\n",iteration,xi,f(xi),ff(xi),xnew);

    double oldx = xi;
    double relErr = 100;

    xi = xnew;

    while(relErr>accr)
    {
        iteration++;

        //calcaulting error %
        relErr = xnew - oldx;
        relErr = fabs(relErr)*100.0;
        relErr = relErr/xnew;
        relErr = fabs(relErr);

        xi = xnew;
        xnew = xi - f(xi)/ff(xi); ///this is new x

        //printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xmid,f(xmid));
        printf("%d\t%10lf	%10lf	%10lf	%10lf		%.9lf\n",iteration,xi,f(xi),ff(xi),relErr,xnew);
        if(fileWrite) fprintf(fp,"%d, %.10lf, %.10lf, %.10lf, %.20lf, %.10lf\n",iteration,xi,f(xi),ff(xi),relErr,xnew);

        //update oldx;
        oldx = xi;
    }

    /// updated oldx is the solution now;

    printf("\nTotal iteartions: %d\nApproximate solution: %.10lf\nRelative Approx. Error: %.10lf\n",iteration,oldx,relErr);

    if(fileWrite) fclose(fp);
    return oldx;

}

int main()
{
    showValuesInRange(0,20,1);  //for part 1;

    printf("Enter x_init and accepted accuracy separated by space: ");

    double x_init, accr;
    x_init = -2.3;

    scanf("%lf %lf", &x_init, &accr);
    printf("x_init: %lf accr: %lf\n",x_init,accr);


    printf("Want to write all data in file? (1 = yes/ 0 = no): ");
    int fileWrite = 0;
    scanf("%d",&fileWrite);

    double soln = newtonRaphsonMainProc(x_init,accr,fileWrite);


    return 0;
}
