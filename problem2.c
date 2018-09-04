#include<stdio.h>
#include<math.h>

const double eps = 1e-9;


double bigPower(double a, int n)
{
    if(n==0) return 1.0;
    if(n%2) return a*bigPower(a,n-1);
    double x = bigPower(a,n/2);
    return x*x;
}

double f(double x, int functionChoice)
{
    if(functionChoice==0) ///question (a)
    {
        double fx = bigPower(x,100);
        return fx;
    }
    else if(functionChoice==1) ///question (b)
    {
        double fx = 3*pow(fabs(x),1.0/3);
        if(x<0) fx *= -1.0;
        return fx;
    }
}

double ff(double x, int functionChoice)
{
    if(functionChoice==0)
    {
        double ffx = 100.0 * bigPower(x,99);
        return ffx;
    }
    else if(functionChoice==1)
    {
        double ffx = f(x,functionChoice)/(3.0*x);
        return ffx;
    }
}

double newtonRaphsonMainProc(double x_init, int iterCount,int functionChoice, int fileWrite)
{
    char filename[20] = "NewtonOutput.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter Newton-Raphson output file name: ");
        scanf("%s",filename);
        char fileLoc[] = "/home/hhmoon/Desktop/3-2/Numerical/CodePractice/files/lab2/";
        strcat(fileLoc,filename);
        fp = fopen(fileLoc,"w+");
    }

    ///print headline
    puts("--------------------------------------------");
    puts("--------------Newton-Raphson----------------");
    printf("Iteration    x[i]     f(xi)      f'(xi)     x[i+1]    Rel. Approx. Err. %%\n");
    if(fileWrite) fprintf(fp,"Iteration,x[i],f(xi), f'(xi), x[i+1], Rel.Approx.Err.%%\n");

    double xi = x_init;

    ///1st iteration
    int iteration = 0;
    double xnew = xi - f(xi,functionChoice)/ff(xi,functionChoice);

    printf("%3d",iteration);
    printf("         % -7.4lf    % -7.4lf    % -7.4lf    % -7.4lf     ---\n",xi,f(xi,functionChoice),ff(xi,functionChoice),xnew);
    if(fileWrite) fprintf(fp,"%d, %.4lf, %.4lf, %.4lf, %.4lf,---\n",iteration,xi,f(xi,functionChoice),ff(xi,functionChoice),xnew);

    double oldx = xi;
    double relErr = 100;

    xi = xnew;

    while(iteration<iterCount)
    {
        iteration++;

        //calcaulting error %
        relErr = xnew - oldx;
        relErr = fabs(relErr)*100.0;
        relErr = relErr/xnew;
        relErr = fabs(relErr);

        xi = xnew;
        xnew = xi - f(xi,functionChoice)/ff(xi,functionChoice); ///this is new x

        printf("%3d",iteration);
        printf("         % -7.4lf    % -7.4lf    % -7.4lf    % -7.4lf     % -8.5lf\n",xi,f(xi,functionChoice),ff(xi,functionChoice),xnew,relErr);
        if(fileWrite) fprintf(fp,"%d, %.4lf, %.4lf, %.4lf, %.4lf, %.6lf\n",iteration,xi,f(xi,functionChoice),ff(xi,functionChoice),xnew,relErr);

        //update oldx;
        oldx = xi;
    }

    /// updated oldx is the solution now;

    printf("SUMMARY: Total iteartions: %d\tApproximate solution: %.10lf\n\n",iteration,oldx);

    if(fileWrite) fclose(fp);
    return oldx;

}

int main()
{
    //printf("%6.3lf\n",-1.0*pow(fabs(-5.0),1.0/3));

    printf("Enter x_init and number_of_iterations_desired separated by space: ");

    double x_init, iterCount;
    x_init = -2.3;

    scanf("%lf %lf", &x_init, &iterCount);

    printf("Want to write all data in file? 0: No , 1: Yes. ");
    int fileWrite = 0;
    scanf("%d",&fileWrite);

    printf("Choose the part of the given problem to solve. 0: (a) , 1: (b) ");
    int functionChoice = 0;
    scanf("%d",&functionChoice);


    double soln = newtonRaphsonMainProc(x_init,iterCount,functionChoice,fileWrite);


    puts("\n\nRunning Again...\n\n");
    main();

    return 0;
}
