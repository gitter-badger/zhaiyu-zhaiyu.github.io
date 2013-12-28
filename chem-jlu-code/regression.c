#include<stdio.h>
#include<stdlib.h>

int main()
{
	double fsum(double*,int);
	double fave(double*,int);

	double dat[3][29]=
	{
		{15.58,10.68,15.62,15.78,13.22,16.44,11.40,16.17,14.03,15.67,
			12.74,11.93,14.84,13.73,15.12,17.88,13.38,14.21,16.80,16.38,
			10.81,17.28,14.92,18.14,18.15,10.31,11.40,12.57,17.61},
		{1.95,1.37,2.39,1.14,1.85,1.32,2.05,1.11,1.47,1.38,
			1.35,1.33,1.09,1.27,1.78,2.52,1.43,2.27,1.41,1.78,
			1.32,1.31,1.42,2.31,1.20,0.98,1.27,0.87,1.21},
		{1.34,1.27,1.56,1.48,1.40,1.82,0.85,1.40,1.15,1.89,
			0.87,1.53,1.25,2.47,1.83,2.41,1.69,1.59,1.19,2.44,
			1.35,1.57,1.64,1.64,2.34,0.65,1.19,2.06,1.57}
	};
	double l11,l12,l22,l1y,l2y,lyy;
	double b0,b1,b2,r2;
	double tmp[29];
	double *p1,*p2,*p3,*p4;

	for(p1=dat[0],p2=tmp;p2<=&(tmp[28]);++p1,++p2){
		*p2=(*p1)*(*p1);
	}
	l11=fsum(tmp,29)-fsum(dat[0],29)*fsum(dat[0],29)/29;
	printf("%lf\n",l11);

	for(p1=dat[1],p2=tmp;p2<=&(tmp[28]);++p1,++p2){
		*p2=(*p1)*(*p1);
	}
	l22=fsum(tmp,29)-fsum(dat[1],29)*fsum(dat[1],29)/29;

	for(p1=dat[0],p2=dat[1],p3=tmp;p3<=&(tmp[28]);++p1,++p2,++p3){
		*p3=(*p1)*(*p2);
	}
	l12=fsum(tmp,29)-fsum(dat[0],29)*fsum(dat[1],29)/29;

	for(p1=dat[0],p2=dat[2],p3=tmp;p3<=&(tmp[28]);++p1,++p2,++p3){
		*p3=(*p1)*(*p2);
	}
	l1y=fsum(tmp,29)-fsum(dat[0],29)*fsum(dat[2],29)/29;

	for(p1=dat[1],p2=dat[2],p3=tmp;p3<=&(tmp[28]);++p1,++p2,++p3){
		*p3=(*p1)*(*p2);
	}
	l2y=fsum(tmp,29)-fsum(dat[1],29)*fsum(dat[2],29)/29;

	for(p1=dat[2],p2=tmp;p2<=&(tmp[28]);++p1,++p2){
		*p2=(*p1)*(*p1);
	}
	lyy=fsum(tmp,29)-fsum(dat[2],29)*fsum(dat[2],29)/29;


	b1=(l1y*l22-l2y*l12)/(l11*l22-l12*l12);
	b2=(l2y*l11-l1y*l12)/(l11*l22-l12*l12);

	b0=fave(dat[2],29)-fave(dat[0],29)*b1-fave(dat[1],29)*b2;

	for(p1=dat[0],p2=dat[1],p3=tmp;p3<=&(tmp[28]);++p1,++p2,++p3){
		*p3=(b0+b1*(*p1)+b2*(*p2)-fave(dat[2],29))*(b0+b1*(*p1)+b2*(*p2)-fave(dat[2],29));
	}

	//r2=fsum(tmp,29)/lyy;
	//r2=b1*l1y+b2*l2y;
	//r2/=lyy;
	
	for(p1=dat[0],p2=dat[1],p3=dat[2],p4=tmp;p4!=tmp+29;++p1,++p2,++p3,++p4){
		*p4=(b0+b1*(*p1)+b2*(*p2)-(*p3))*(b0+b1*(*p1)+b2*(*p2)-(*p3));
	}
	r2=1-fsum(tmp,29)/lyy;

	printf("result:\ny=%lf+%lf*x1+%lf*x2\tr^2=%lf\n",b0,b1,b2,r2);

	return 0;
}

double fsum(double* dat,int total)
{
	double * p;
	double x=0;
	for(p=dat;p!=dat+total;++p){
		x+=*p;
	}
	return x;
}

double fave(double * dat,int total)
{
	double* p;
	double x;
	x=fsum(dat,total);
	x/=total;
	return x;
}




//Mathematica mathod:
//lm = NonlinearModelFit[{{15.58, 1.95, 1.34}, {10.68, 1.37, 1.27}, {15.62, 2.39, 1.56}, {15.78, 1.14, 1.48}, {13.22, 1.85, 1.40}, {16.44, 1.32, 1.82}, {11.40, 2.05, 0.85}, {16.17, 1.11, 1.40}, {14.03, 1.47, 1.15}, {15.67, 1.38, 1.89}, {12.74, 1.35, 0.87}, {11.93, 1.33, 1.53}, {14.84, 1.09, 1.25}, {13.73, 1.27, 2.47}, {15.12, 1.78, 1.83}, {17.88, 2.52, 2.41}, {13.38, 1.43, 1.69}, {14.21, 2.27, 1.59}, {16.80, 1.41, 1.19}, {16.38, 1.78, 2.44}, {10.81, 1.32, 1.35}, {17.28, 1.31, 1.57}, {14.92, 1.42, 1.64}, {18.14, 2.31, 1.64}, {18.15, 1.20, 2.34}, {10.31, 0.98, 0.65}, {11.40, 1.27, 1.19}, {12.57, 0.87, 2.06}, {17.61, 1.21, 1.57}} , b0 + b1*x1 + b2*x2, {b0, b1, b2}, {x1, x2}]
