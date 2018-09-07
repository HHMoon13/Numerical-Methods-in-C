#include<stdio.h>
#include<math.h>

const double eps = 1e-9;

double f(double x, int fCh)
{
    double fx;
    if(fCh==0) ///question (a)
        fx = exp(0.5*x) -5 + 5*x;
    else if(fCh==1) ///question (b)
        fx = sin(x) + cos(1+x*x) -1;
    return fx;
}


double secantMainProc(double x0, double x1, double accr, int iterMax, int fCh, int fileWrite)
{
    /// fCh indicates function choice: which function has been chosen by user to solve
    char filename[20] = "SecantOutput.csv";
    FILE *fp;
    if(fileWrite)
    {
        printf("Enter problem 3 output file name: ");
        scanf("%s",filename);
        char fileLoc[] = "/home/hhmoon/Desktop/3-2/Numerical/CodePractice/files/lab2/";
        strcat(fileLoc,filename);
        fp = fopen(fileLoc,"w+");
    }
    ///print headline
    puts("------------------Secant Method---------------------");
    printf("Iteration    x[i-1]     x[i]      f(x[i-1])     f(x[i])    x[i+1]    Rel.Approx.Err.%%\n");
    if(fileWrite) fprintf(fp,"Iteration,x[i-1],x[i],f(x[i-1]), f(x[i]), x[i+1],  Rel.Approx.Err.%%\n");

    double xlow = x0;
    double xhi = x1;

    ///1st iteration
    int iteration = 0;
    double xnew = xhi -(  ( f(xhi,fCh)*(xhi-xlow)  )/( f(xhi,fCh)-f(xlow,fCh)  ) );

    printf("%3d         % -7.4lf    % -7.4lf    % -8.5lf    % -8.5lf     % -7.4lf   ---\n",iteration,xlow,xhi,f(xlow,fCh),f(xhi,fCh),xnew);
    if(fileWrite) fprintf(fp,"%d, %.4lf,%.4lf, %.6lf, %.6lf, %.4lf,---\n",iteration,xlow,xhi,f(xlow,fCh),f(xhi,fCh),xnew);

    double relErr = 100;

    xlow = xhi;
    xhi = xnew;

    while(1)
    {
        iteration++;
        xnew = xhi -(  ( f(xhi,fCh)*(xhi-xlow)  )/( f(xhi,fCh)-f(xlow,fCh)  ) );
        ///calcaulting error %
        relErr = fabs(xnew - xhi)*100.0;
        relErr = fabs(relErr/xnew);

        printf("%3d         % -7.4lf    % -7.4lf    % -8.5lf    % -8.5lf     % -7.4lf   %8.5lf\n",iteration,xlow,xhi,f(xlow,fCh),f(xhi,fCh),xnew,relErr);
        if(fileWrite) fprintf(fp,"%d, %.4lf,%.4lf, %.6lf, %.6lf, %.4lf,%8.5lf\n",iteration,xlow,xhi,f(xlow,fCh),f(xhi,fCh),xnew,relErr);

        ///update oldx;
        xlow = xhi;
        xhi = xnew;

        ///breaking condition
        if(fCh==0) {
            if(relErr>accr) break;
        }
        else if(fCh==1) {
            if(iteration>=iterMax) break;
        }
    }
    /// updated oldx is the solution now;
    printf("SUMMARY: Total iteartions: %d\tApproximate solution: %.4lf\n\n",iteration,xnew);
    if(fileWrite) fclose(fp);
    return xnew;
}

int main()
{
    printf("Choose the part of the given problem to solve. 0: (a) , 1: (b) ");
    int fCh = 0;
    scanf("%d",&fCh);

    printf("Want to write all data in file? 0: NO , 1: YES ");
    int fileWrite = 0;
    scanf("%d",&fileWrite);

    double xlo, xhi, accr,soln;
    int iterMax;
    ///fCh means fCh
    if(fCh==1) /// 3times input
    {
        for(int i=1; i<=3; i++)
        {
            printf("Solving of %d th query:\n",i);
            printf("%d). Enter x[i-1], x[i] and number_of_iterations_desired separated by space: ",i);
            scanf("%lf %lf %d", &xlo, &xhi, &iterMax);

            soln = secantMainProc(xlo,xhi,100,iterMax,fCh,fileWrite);
        }
    }

    else if(fCh==0) ///once input
    {
        printf("Enter x[i-1], x[i] and accepted relative approximate error%% separated by space: ");
        scanf("%lf %lf %lf", &xlo, &xhi, &accr);

        soln = secantMainProc(xlo,xhi,accr,100,fCh,fileWrite);
    }


    puts("\nRunning Again...\n");
    main();

    return 0;
}
