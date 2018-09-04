#include<stdio.h>
#include<math.h>
#include<string.h>

const double eps = 1e-9;

const double Q = 20.0;
const double g = 9.8;

double f(double x)
{
    double A = (3*x + (x*x)/2.0);
    double B = 3 + x;
    double val = 1 - (Q*Q/ (g* A*A*A) * B);
    return val;
}

void showValuesInRange(double a,double b, int fileWrite)
{
    printf("Showing values for x = %.3lf to x = %.3lf\n",a,b);

    char filename[20] = "File1.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter func values file name: ");
        scanf("%s",filename);
        char fileLoc[] = "/home/hhmoon/Desktop/3-2/Numerical/CodePractice/files/lab2/";
        strcat(fileLoc,filename);
        fp = fopen(fileLoc,"w+");

    }
    printf(" x     f(x)\n\n");
    if(fileWrite) fprintf(fp,"x,f(x)\n");

    if(a>b)
    {
        double t = a;
        a = b;
        b = t;
    }

    double x = a;

    while(x<=b+eps)
    {
        printf("%.3lf	%.5lf\n",x,f(x));
        if(fileWrite) fprintf(fp, "%.3lf, %.5lf\n",x,f(x));
        x = x+0.1;
    }

    if(fileWrite) fclose(fp);

}

double bisectionMainProc(double xlow, double xhi, double accr,int fileWrite)
{
    char filename[20] = "bisectionOutput.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter bisection output file name: ");
        scanf("%s",filename);
        char fileLoc[] = "/home/hhmoon/Desktop/3-2/Numerical/CodePractice/files/lab2/";
        strcat(fileLoc,filename);
        fp = fopen(fileLoc,"w+");
    }

    ///print headline
    puts("--------------------------------------------");
    puts("---------------Bisection--------------------");
    printf("Iteration    x-high     x-low      x-mid     f(xmid)    Rel. Apprx. Err. %%\n");
    if(fileWrite) fprintf(fp,"Iteration, x-hi, x-low, x-mid,  Relative Approx. Error%%\n");


    if(f(xlow)>0) //it is acutally xhi
    {
        double temp = xhi;
        xhi = xlow;
        xlow = temp;
    }

    ///1st iteration
    int iteration = 1;
    double xmid = (xlow+xhi)/2.0;
    printf("%3d",iteration);
    printf("         % -7.4lf    % -7.4lf    % -7.4lf    % -8.5lf     ---\n",xhi,xlow,xmid,f(xmid));
    if(fileWrite) fprintf(fp,"%d, %.4lf, %.4lf, %.4lf, ---\n",iteration,xhi,xlow,xmid);

    double oldx = xmid;
    double relErr = 100.0;
    double oldfx;

    while(relErr>=accr)
    {
        iteration++;

        //test sign of fucntion
        oldfx = f(oldx);
        if(oldfx>=0)
        {
            xhi = oldx;
        }
        else
        {
            xlow = oldx;
        }

        xmid = (xlow+xhi)/2.0; ///this is new x

        //calcaulting error %
        relErr = xmid - oldx;
        relErr = fabs(relErr)*100.0;
        relErr = relErr/xmid;
        relErr = fabs(relErr);

        printf("%3d",iteration);
        printf("         % -7.4lf    % -7.4lf    % -7.4lf    % -8.5lf   % -9.6lf\n",xhi,xlow,xmid,f(xmid),relErr);
        if(fileWrite) fprintf(fp,"%d, %.4lf, %.4lf, %.4lf, %.6lf\n",iteration,xhi,xlow,xmid,relErr);

        //update oldx;
        oldx = xmid;
    }

    /// updated oldx is the solution now;

    printf("Summary:\nTotal iteartions: %d\nApproximate solution: %.4lf\nRelative Approx. Error%%: %.6lf\n",iteration,oldx,relErr);

    fclose(fp);
    return oldx;

}

double falsePosMainProc(double xlow, double xhi, double accr, int fileWrite)
{
    char filename[20] = "falsePosOutput.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter False Position Output file name: ");
        scanf("%s",filename);
        char fileLoc[] = "/home/hhmoon/Desktop/3-2/Numerical/CodePractice/files/lab2/";
        strcat(fileLoc,filename);
        fp = fopen(fileLoc,"w+");
    }

    ///print headline
    puts("--------------------------------------------");
    puts("------------False Position------------------");
    printf("Iteration    x-high     x-low      x-r     f(xr)    Rel. Apprx. Err. %%\n");
    if(fileWrite) fprintf(fp,"Iteration,xhigh,xlow, xr, Rel.Approx.Err.%%\n");

    if(f(xlow)>0) //it is acutally xhi
    {
        double temp = xhi;
        xhi = xlow;
        xlow = temp;
    }

    ///1st iteration
    int iteration = 1;
    double xr = xhi - f(xhi) * (xhi- xlow) / ( f(xhi) - f(xlow));

    printf("%3d",iteration);
    printf("         % -7.4lf    % -7.4lf    % -7.4lf    % -8.5lf     ---\n",xhi,xlow,xr,f(xr));
    if(fileWrite) fprintf(fp,"%d, %.4lf, %.4lf, %.4lf,---\n",iteration,xhi,xlow,xr);

    double oldx = xr;
    double relErr = 100;

    double oldfx;

    while(relErr>accr)
    {
        iteration++;

        //test sign of fucntion
        oldfx = f(oldx);
        if(oldfx>=0)
        {
            xhi = oldx;
        }
        else
        {
            xlow = oldx;
        }

        xr = xr = xhi - f(xhi) * (xhi- xlow) / ( f(xhi) - f(xlow)); ///this is new x

        //calcaulting error %
        relErr = xr - oldx;
        relErr = fabs(relErr)*100.0;
        relErr = relErr/xr;
        relErr = fabs(relErr);

        printf("%3d",iteration);
        printf("         % -7.4lf    % -7.4lf    % -7.4lf    % -8.5lf   % -9.6lf\n",xhi,xlow,xr,f(xr),relErr);
        if(fileWrite) fprintf(fp,"%d, %.4lf, %.4lf, %.4lf, %.6lf\n",iteration,xhi,xlow,xr,relErr);

        //update oldx;
        oldx = xr;
    }

    /// updated oldx is the solution now;

    printf("Summary:\nTotal iteartions: %d\nApproximate solution: %.4lf\nRelative Approx. Error: %.10e\n",iteration,oldx,relErr);

    if(fileWrite) fclose(fp);
    return oldx;

}


int main()
{

    showValuesInRange(0.5,2.5,0);  /// showing values of the function

    printf("\nSolving f(x)....\n\n");
    printf("Enter upper_bound, lower_bound and accepted accuracy separated by space: \n");

    double xlow, xhi, accr;

    while (1)
    {
        scanf("%lf %lf %lf",&xlow,&xhi, &accr);

        if(f(xlow)*f(xhi)>0)  printf("No root found. Invalid x-low, x-hi. Try Again.\n\n");
        else break;
    }

    puts("Want to write all data in file? 0: No, 1: Yes");
    int fileWrite = 0;
    scanf("%d",&fileWrite);

    double soln;

    soln = bisectionMainProc(xlow,xhi,accr,fileWrite);

    soln = falsePosMainProc(xlow,xhi,accr,fileWrite);

    puts("");
    printf("Root : %.4lf\n",soln);

    return 0;
}

