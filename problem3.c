#include<stdio.h>
#include<math.h>

const double eps = 1e-9;

double f(double x, int functionChoice)
{
    double fx;

    if(functionChoice==0) ///question (a)
        fx = exp(0.5*x) -5 + 5*x;

    else if(functionChoice==1) ///question (b)
        fx = sin(x) + cos(1+x*x) -1;

    return fx;
}


double secantMainProc(double xlo, double xh, double accr,int functionChoice, int fileWrite)
{

    char filename[20] = "SecantOutput.csv";
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
    puts("--------------Secant Method-----------------");
    printf("Iteration    x[i-1]     x[i]      f(x[i-1])     f(x[i])    x[i+1]    Rel.Approx.Err.%%\n");
    if(fileWrite) fprintf(fp,"Iteration,x[i-1],x[i],f(x[i-1]), f(x[i]), x[i+1],  Rel.Approx.Err.%%\n");

    double xlow = xlo;
    double xhi = xh;

    ///1st iteration
    int iteration = 0;
    double xnew = xhi - ( f(xhi,functionChoice)*(xhi-xlo)/(f(xhi,functionChoice)-f(xlow,functionChoice))  );


    printf("%3d",iteration);
    printf("         % -7.4lf    % -7.4lf    % -8.5lf    % -8.5lf     % -7.4lf   ---\n",xlow,xhi,f(xlow,functionChoice),f(xhi,functionChoice),xnew);
    if(fileWrite) fprintf(fp,"%d, %.4lf,%.4lf, %.6lf, %.6lf, %.4lf,---\n",iteration,xlow,xhi,f(xlow,functionChoice),f(xhi,functionChoice),xnew);

    double relErr = 100;

    xlow = xhi;
    xhi = xnew;

    while(relErr>accr)
    {
        iteration++;

        xnew = xhi - ( f(xhi,functionChoice)*(xhi-xlo)/(f(xhi,functionChoice)-f(xlow,functionChoice))  );

        //calcaulting error %
        relErr = xnew - xhi;
        relErr = fabs(relErr)*100.0;
        relErr = relErr/xnew;
        relErr = fabs(relErr);

        printf("%3d",iteration);
        printf("         % -7.4lf    % -7.4lf    % -8.5lf    % -8.5lf     % -7.4lf   %8.5lf\n",xlow,xhi,f(xlow,functionChoice),f(xhi,functionChoice),xnew,relErr);
        if(fileWrite) fprintf(fp,"%d, %.4lf,%.4lf, %.6lf, %.6lf, %.4lf,%8.5lf\n",iteration,xlow,xhi,f(xlow,functionChoice),f(xhi,functionChoice),xnew,relErr);

        //update oldx;
        xlow = xhi;
        xhi = xnew;
    }

    /// updated oldx is the solution now;

    printf("SUMMARY: Total iteartions: %d\tApproximate solution: %.4lf\n\n",iteration,xnew);

    if(fileWrite) fclose(fp);

    return xnew;

}

int main()
{

    printf("Choose the part of the given problem to solve. 0: (a) , 1: (b) ");
    int functionChoice = 0;
    scanf("%d",&functionChoice);

    printf("Want to write all data in file? 0: NO , 1: YES ");
    int fileWrite = 0;
    scanf("%d",&fileWrite);

    double xlo, xhi, accr,soln;

    if(functionChoice==1) /// 3times input
    {
        for(int i=1; i<=3; i++)
        {
            printf("Solving of %d th query:\n",i);
            printf("%d). Enter x[i-1], x[i] and accepted relative approximate error%% separated by space: ",i);
            scanf("%lf %lf %lf", &xlo, &xhi, &accr);

            soln = secantMainProc(xlo,xhi,accr,functionChoice,fileWrite);
        }
    }

    else if(functionChoice==0) ///once input
    {
        printf("Enter x[i-1], x[i] and accepted relative approximate error%% separated by space: ");
        scanf("%lf %lf %lf", &xlo, &xhi, &accr);

        soln = secantMainProc(xlo,xhi,accr,functionChoice,fileWrite);
    }


    puts("\n\nRunning Again...\n\n");
    main();

    return 0;
}

