#include<stdio.h>
#include<math.h>

double f(double x)
{

	double val = exp(x) - 5*x*x;
	return val;
}

void showValuesInRange(double a,double b)
{
	char filename[20] = "file1.csv";
	FILE *fp;
	fp = fopen(filename,"w+");

	printf("	x		f(x)\n\n");
	fprintf(fp,"x,f(x)\n");

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
		fprintf(fp, "%lf, %lf\n",x,f(x));
		x = x+0.1;
	}

	fclose(fp);

}

double bisectionMainProc(double xlow, double xhi, double accr)
{

	///print iteration number, xlow, xhi, xmid, relative error, f(xmid) in terminal
	///print iteration number and relative error in file2.csv

	char filename[20] = "file2.csv";
	FILE *fp;
	fp = fopen(filename,"w+");

	///print headline
	printf("Iteration\tx-low		x-high		x-mid\tRelativeError\tf(xmid)\n");
	fprintf(fp,"Iteration, Relative Aprox. Error\n");

	///check if invalid xlow xhi
	if(f(xlow)*f(xhi)>0)
	{
		printf("Invalid x-low, x-hi");
		return 0;
	}

	if(f(xlow)>0) //it is acutally xhi
	{
		double temp = xhi;
		xhi = xlow;
		xlow = temp;
	}




	///1st iteration

	int iteration = 1;
	double xmid = (xlow+xhi)/2.0;
	printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xmid,f(xmid));
	fprintf(fp,"%d, ---\n",iteration);

	double oldx = xmid;
	double relErr = 100;

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
		//if(relErr<0) relErr = relErr*(-1.0);
		relErr = fabs(relErr)*100.0;
		relErr = relErr/xmid;
		relErr = fabs(relErr);


		//update oldx;
		oldx = xmid;

		//printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xmid,f(xmid));
		printf("%d\t%10lf	%10lf	%10lf	%10lf		%.9lf\n",iteration,xlow,xhi,xmid,relErr,f(xmid));
		fprintf(fp,"%d, %.20lf\n",iteration,relErr);
	}

	/// updated oldx is the solution now;

	printf("\nTotal iteartions: %d\nApproximate solution: %.10lf\nRelative Approx. Error: %.10lf\n",iteration,oldx,relErr);

	fclose(fp);
	return oldx;

}

int main()
{
	showValuesInRange(-1.0,1.0);

input:	printf("Enter x-low, x-high and accepted accuracy separated by space:");

	double xlow, xhi, accr;

	scanf("%lf %lf %lf",&xlow,&xhi, &accr);
	printf("Echo: %lf %lf %lf\n",xlow,xhi,accr);

	if(f(xlow)*f(xhi)>0)
	{
		printf("Invalid x-low, x-hi\n\n");
		goto input;
	}


	double soln = bisectionMainProc(xlow,xhi,accr);


	return 0;
}
