/******************************
 * The code is for Ch8
 * by Y. Zhai 2013-12-21
 * compiled with MinGW 4.8.1 GCC
 ******************************/
#include<stdio.h>

struct data
{
	int f[3];
	float res;
};

int main()
{
	struct data glue[9]={
		{1,1,1,-7.25},
		{1,2,2,-5.48},
		{1,3,3,-5.35},
		{2,1,2,-5.40},
		{2,2,3,-4.42},
		{2,3,1,-5.90},
		{3,1,3,-4.68},
		{3,2,1,-5.90},
		{3,3,2,-5.63},
	};


	float s[3][3]={0};
	float r[3];
	int idx,tmp;
	float rmax,rmin;
	int i,j ,k;

	int max(float* begin,int total,float *max,int *idx);
	int min(float* begin,int total,float *min,int *idx);
	for(i=0;i<9;++i){
		for(j=0;j<3;++j){
			for(k=0;k<3;++k){
				if(glue[i].f[j]==k+1){
					s[j][k]+=(glue[i].res)/3;
				}
			}
		}
	}


	for(i=0;i<3;++i){
		max(s[i],3,&rmax,&idx);
		min(s[i],3,&rmin,&tmp);
		r[i]=rmax-rmin;
		printf("第%d个因子，最优水平：%d\n",i+1,idx+1);
	}
	max(r,3,&rmax,&idx);
	printf("其中，影响最大的因子为第%d个因子；",idx+1);
	min(r,3,&rmin,&idx);
	printf("影响最小的因子为第%d个因子。\n",idx+1);

	return 0;
}


int max(float* begin,int total,float *max,int *idx)
{
	float *p;
	int j;
	*max=*begin;
	for(p=begin,j=0;p!=begin+total;++p,++j){
		if(*p>=*max){
			*max=*p;
			*idx=j;
		}
	}
	return 0;
}


int min(float* begin,int total,float *min,int *idx)
{
	float *p;
	int j;
	*min=*begin;
	for(p=begin,j=0;p!=begin+total;++p,++j){
		if(*p<=*min){
			*min=*p;
			*idx=j;
		}
	}
	return 0;
}
