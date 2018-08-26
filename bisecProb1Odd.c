#include<stdio.h>
#include<math.h>

long long factVals[15];
int n;

void setN(int x)
{
    n = x;
}

double f(double x)
{

    double val = exp(x) - 5*x*x;
    return val;
}

double power(double a,int k) /// a^k
{
    if(k==0) return 1;

    if( k%2 ) // k is odd
        return a * power(a,k-1);
    //else k is even
    double ak = power(a,k/2);
    return ak*ak;
}

long long fact(int k)
{
    if(k==0) return factVals[k] = 1; //0! = 1
    else if(factVals[k]!=0) return factVals[k];
    else return factVals[k] = k*fact(k-1);
}

/// Jn(x) = (x/2)^n SUM(k=0,10) [ { (-1)^k * (x*x/4)^k} / {k! * (n+k)!} ]
double Jn(double x)
{
    double xpart = power( (x/2.0), n);
    double sumpart = 0.0;

    double num, denum, minusOne, newterm;
    for(int k = 0; k<= 10; k++)
    {
        if(k%2) minusOne = -1.0;
        else minusOne = 1.0;

        num = power(x*x/4.0, k);
        denum = fact(k) * fact(n+k);

        newterm = minusOne * num / denum;

        sumpart+= newterm;
    }

    return xpart * sumpart;
}

void showValuesInRange(double a,double b, int fileWrite)
{
    char filename[20] = "OddProb1file1.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter file_1 name: ");
        scanf("%s",filename);
        fp = fopen(filename,"w+");

    }
    printf("	x		Jn(x)\n\n");
    if(fileWrite) fprintf(fp,"x,Jn(x)\n");

    if(a>b)
    {
        double t = a;
        a = b;
        b = t;
    }

    double x = a;

    while(x<=b)
    {
        printf("%10lf	%10lf\n",x,Jn(x));
        if(fileWrite) fprintf(fp, "%lf, %lf\n",x,Jn(x));
        x = x+0.1;
    }

    if(fileWrite) fclose(fp);

}

double bisectionMainProc(double xlow, double xhi, double accr, int fileWrite)
{

    ///print iteration number, xlow, xhi, xmid, relative error, f(xmid) in terminal
    ///print iteration number and relative error in file2.csv
    char filename[20] = "OddProb1file2.csv";
    FILE *fp;

    if(fileWrite)
    {
        printf("Enter file_2 name: ");
        scanf("%s",filename);
        fp = fopen(filename,"w+");
    }


    ///print headline
    printf("Iteration\tx-low		x-high		x-mid\tRelativeError\tf(xmid)\n");
    if(fileWrite) fprintf(fp,"Iteration,xlow,xhigh, xmid, Relative Approx. Error, f(xmid)\n");

    if(Jn(xlow)>0) //it is acutally xhi
    {
        double temp = xhi;
        xhi = xlow;
        xlow = temp;
    }

    ///1st iteration

    int iteration = 1;
    double xmid = (xlow+xhi)/2.0;
    printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xmid,Jn(xmid));
    if(fileWrite) fprintf(fp,"%d, %.10lf, %.10lf, %.10lf,---, %.10lf\n",iteration,xlow,xhi,xmid,Jn(xmid));

    double oldx = xmid;
    double relErr = 100;

    double oldfx;

    while(relErr>=accr)
    {
        iteration++;

        //test sign of fucntion
        oldfx = Jn(oldx);
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


        //update oldx;
        oldx = xmid;

        //printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xmid,f(xmid));
        printf("%d\t%10lf	%10lf	%10lf	%10lf		%.9lf\n",iteration,xlow,xhi,xmid,relErr,Jn(xmid));
        if(fileWrite) fprintf(fp,"%d, %.10lf, %.10lf, %.10lf, %.20lf, %.10lf\n",iteration,xlow,xhi,xmid,relErr,Jn(xmid));
    }

    /// updated oldx is the solution now;

    printf("\nTotal iteartions: %d\nApproximate solution: %.10lf\nRelative Approx. Error: %.10lf\n",iteration,oldx,relErr);

    if(fileWrite) fclose(fp);
    return oldx;

}

int main()
{

    //printf("%lld %lf\n",fact(10),power(2,8));
    /*
    int nn;
    while(1)
    {
        printf("[ Enter -1 to get out of the loop ]");
        printf("Enter value of n: ");
        scanf("%d",&nn);

        if(nn==-1) {
            break;
        }

        setN(nn);
        showValuesInRange(0.0, 10.0);
    }

    ///showValuesInRange(0.0, 10.0,1);  //for part 1;
    */

    printf("Solving Jn(x) for n = 0, Guess point xlow = 1, xhi = 3, increment  = 0.1\n");
    showValuesInRange(1.0,3.0, 0); //0 means no file write

input:
    printf("Enter x-low, x-high and accepted accuracy separated by space:");

    double xlow, xhi, accr;

    scanf("%lf %lf %lf",&xlow,&xhi, &accr);
    printf("Echo: %lf %lf %lf\n",xlow,xhi,accr);

    if(Jn(xlow)*Jn(xhi)>0)
    {
        printf("Invalid x-low, x-hi\n\n");
        goto input;
    }

    printf("Want to write all data in file? (1 = yes/ 0 = no): ");
    int fileWrite = 0;
    scanf("%d",&fileWrite);

    double soln = bisectionMainProc(xlow,xhi,accr,fileWrite);


    return 0;
}

