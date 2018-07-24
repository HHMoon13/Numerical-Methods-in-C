#include<stdio.h>
#include<math.h>

int osf;
const double TempKelvin = 273.15;

void setOsf(int x)
{
	osf = x;
}

double f(double t)
{
	double ta = t+TempKelvin;
	///ln osf = -139.34411 + (1.575701* 10^5)/ta - (6.642308* 10^7)/(ta*ta) + (1.243800 * 10^10 )/(ta*ta*ta) - (8.621949* 10^11)/(ta*ta*ta*ta)
	double fx = log(osf);
	fx += 139.34411 - (1.575701*100000)/ta + (6.642308*10000000)/(ta*ta) - (1.243800 *10000000000)/(ta*ta*ta) + (8.621949*100000000000)/(ta*ta*ta*ta);

	return fx;
}

void showValuesInRange(double a,double b)
{
	char filename[35] = "Prob2file1osf12.csv";
	FILE *fp;
	fp = fopen(filename,"w+");

	printf("\tT		f(T)\n\n");
	fprintf(fp,"Osf value =, %d\nT,f(T)\n",osf);

	if(a>b)
	{
		double tmp = a;
		a = b;
		b = tmp;
	}

	double t = a;

	while(t<=b)
	{
		printf("\t%.2lf	%10lf\n",t,f(t));
		fprintf(fp, "%.2lf, %lf\n",t,f(t));
		t = t+1;
	}

	fclose(fp);

}

double bisectionMainProc(double xlow, double xhi, double accr)
{

	///print iteration number, xlow, xhi, xmid, relative error, f(xmid) in terminal
	///print iteration number and relative error in file2.csv

	char filename[35] = "Prob2file2_osf12.csv";
	FILE *fp;
	fp = fopen(filename,"w+");

	///print headline
	printf("Iteration\tx-low		x-high		x-mid\tRelativeError\tf(xmid)\n");
	fprintf(fp,"Iteration, Relative Aproximate Error\n");

	///check if invalid xlow xhi
	if(f(xlow)*f(xhi)>0)
	{
		printf("Invalid x-low, x-hi\n\n");
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
	double relErr = 100.0;

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

		xmid = (xlow+xhi)/2.0; ///this is new x

		///calcaulting error %
		relErr = xmid - oldx;
		//if(relErr<0) relErr = relErr*(-1.0);
		relErr = fabs(relErr)*100.0;
		relErr = relErr/xmid;
		relErr = fabs(relErr);

		//printf("%d\t%10lf	%10lf	%10lf	---		%.9lf\n",iteration,xlow,xhi,xmid,f(xmid));
		printf("%d\t%10lf	%10lf	%10lf	%10lf		%.9lf\n",iteration,xlow,xhi,xmid,relErr,f(xmid));
		fprintf(fp,"%d, %.20lf\n",iteration,relErr);

		//update oldx;
		oldx = xmid;
	}

	/// updated oldx is the solution now;

	printf("\nTotal iteartions: %d\nApproximate solution: %.10lf\nRelative Approx. Error: %.10lf\n",iteration,oldx,relErr);

	fclose(fp);
	return oldx;

}

int main()
{
	setOsf(12);
	showValuesInRange(0,40);

input:	printf("Enter x-low, x-high and accepted error %% separated by space:");

	double xlow, xhi, accr;

	scanf("%lf %lf %lf",&xlow,&xhi, &accr);
	printf("Echo: %lf %lf %lf\n",xlow,xhi,accr);

	if(f(xlow)*f(xhi)>0)
	{
		printf("Invalid x-low, x-hi");
		goto input;
	}


	double soln = bisectionMainProc(xlow,xhi,accr);


	return 0;
}
