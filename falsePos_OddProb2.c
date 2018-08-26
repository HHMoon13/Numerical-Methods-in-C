#include<stdio.h>
#include<math.h>

const double K = 0.016;
const int Ca = 42, Cb = 28, Cc = 4;

double f(double x)
{
    double val = (Cc +x) / (Ca - 2*x);
    val = val / (Ca - 2*x);
    val = val / (Cb - x);
    val = val - K;
    return val;
}

void showValuesInRange(double a,double b, int fileWrite)
{
    char filename[20] = "falsePosFile1.csv";
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

double falsePosMainProc(double xlow, double xhi, double accr, int fileWrite)
{

    ///print iteration number, xlow, xhi, xmid, relative error, f(xmid) in terminal
    ///print iteration number and relative error in file2.csv
    char filename[20] = "falsePosFile2.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter file_2 name: ");
        scanf("%s",filename);
        fp = fopen(filename,"w+");
    }


    ///print headline
    printf("Iteration\tx-low		x-high		x-r\tRelativeError\tf(xr)\n");
    if(fileWrite) fprintf(fp,"Iteration,xlow,xhigh, xr, Rel.Approx.Err., f(xr)\n");

    if(f(xlow)>0) //it is acutally xhi
    {
        double temp = xhi;
        xhi = xlow;
        xlow = temp;
    }

    ///1st iteration

    int iteration = 1;
    //double xmid = (xlow+xhi)/2.0;
    double xr = xhi - f(xhi) * (xhi- xlow) / ( f(xhi) - f(xlow));

    printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xr,f(xr));
    if(fileWrite) fprintf(fp,"%d, %.10lf, %.10lf, %.10lf,---, %.10lf\n",iteration,xlow,xhi,xr,f(xr));

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


        //update oldx;
        oldx = xr;

        //printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xmid,f(xmid));
        printf("%d\t%10lf	%10lf	%10lf	%10lf		%.9lf\n",iteration,xlow,xhi,xr,relErr,f(xr));
        if(fileWrite) fprintf(fp,"%d, %.10lf, %.10lf, %.10lf, %.20lf, %.10lf\n",iteration,xlow,xhi,xr,relErr,f(xr));
    }

    /// updated oldx is the solution now;

    printf("\nTotal iteartions: %d\nApproximate solution: %.10lf\nRelative Approx. Error: %.10lf\n",iteration,oldx,relErr);

    if(fileWrite) fclose(fp);
    return oldx;

}

int main()
{
    //showValuesInRange(0,20,0);  //for part 1;


    printf("Solving f(x) for n = 0, Guess point xlow = 0, xhi = 20\n");

input:
    printf("Enter accepted accuracy separated by space:");

    double xlow, xhi, accr;
    xlow = 0.0;
    xhi = 20.0;

    scanf("%lf", &accr);
    printf("xlo: %lf xhi: %lf accr: %lf\n",xlow,xhi,accr);

    if(f(xlow)*f(xhi)>0)
    {
        printf("Invalid x-low, x-hi\n\n");
        goto input;
    }

    printf("Want to write all data in file? (1 = yes/ 0 = no): ");
    int fileWrite = 0;
    scanf("%d",&fileWrite);

    double soln = falsePosMainProc(xlow,xhi,accr,fileWrite);


    return 0;
}
