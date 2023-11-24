#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
typedef long long ll;
using namespace std;
const int MAXN = 1e5;
bool primeArr[MAXN];	//用于朴素筛和埃氏筛

//用于欧拉筛
int minP[MAXN];//minP[i] 为i的最小素因子 
int prime[MAXN];//prime[i] 代表n以内从小到大，第i个质数 
int cnt;//素数计数 

//用于区间筛
bool isPrime[MAXN]; //isPrime[i-a]=true 表示i是素数（下标偏移了a）
bool isSqrtPrime[MAXN];

//朴素筛选n以内的素数
//判断k是不是素数
bool Judge(int k)
{
	if (k == 2)return true;
	if (k < 2 || k%2==0)return false;
	for (int i = 3; i <= sqrt(k); i += 2)
	{
		if (k%i == 0)return false;
	}
	return true;
}
//朴素筛
void PurifiedSieve(int n)
{
	for (int i = 0; i <= n; i++)
	{
		primeArr[i] = Judge(i);
	}
}

//埃氏筛
void EraSieve(int n)
{
	for (int i = 0; i < n; i++)
		primeArr[i] = true; //初始化每个数都为素数
	primeArr[0] = primeArr[1] = false;	//初始化0和1不是素数
	for (int i = 2; i <= sqrt(n); i++)	//从i从2到根号n作为质数，依次剔除它的2、3、4……倍
		if (primeArr[i])	//若这个数是素数则剔除它的整数倍
			for (int j = i*2; j <= n; j += i)	//剔除整数倍，上限是n（这里会有重复剔除的数，欧拉筛可优化）
				primeArr[j] = false;
}

//欧拉筛
void EulerSieve(int n)
{
	for (int i = 2; i <= n; i++)
	{
		//从2开始，若i不为0，则表示i为质数，eg:2、3(质数)、4（循环体内被2筛除，minP[4]=2）
		if (!minP[i])prime[cnt++] = minP[i] = i;
		for (int j = 0; j < cnt&&i*prime[j] <= n; j++)
		{
			minP[i*prime[j]] = prime[j]; //分别筛除 i*prime[j],即将当前已知质数乘以i倍筛去
			if (i%prime[j] == 0)break;	//等价于//if(prime[j]>minP[i])break;
			//这一步是保证每个合数仅被其最小因子筛选一次的关键
		}
	}
}

//区间筛
void SegmentSieve(ll a, ll b)	//对区间[a,b)进行筛选 
{
	for (ll i = 0; i * i < b; i++) //初始化[2,sqrt(b))的全为质数
		isSqrtPrime[i] = true;
	for (ll i = 0; i < b - a; i++) //初始化偏移后的[a,b)全为质数
		isPrime[i] = true;

	for (ll i = 2; i * i < b; i++) //埃氏筛选
	{ 
		if (isSqrtPrime[i]) {
			for (ll j = 2 * i; j  <= sqrt(b); j += i)//筛选上限变为sqrt(b)
				isSqrtPrime[j] = false;
			//筛除[a,b)里的非素数
			//(a+i-1)/i 得到最接近（a/i）这个数，也即（a的i倍数)，最低是2LL是表示最低2倍
			for (ll j = max(2LL, (a + i - 1) / i) * i; j < b; j += i)
				isPrime[j - a] = false;
		}
	}
}

//打印primeArr[],即打印朴素筛和埃氏筛的结果
void PrintPrime(int n)
{
	int count = 0;
	for (int i = 0; i <= n; i++)
	{
		if (primeArr[i]) {
			count++;
			printf("%5d ", i);
			if (count % 10 == 0)printf("\n");
		}	
	}
}

//主函数，测试
int main()
{
	printf("\n=============================朴素筛=========================\n");
	PurifiedSieve(200);
	PrintPrime(200);
	printf("\n=============================埃氏筛=========================\n");
	EraSieve(200);
	PrintPrime(200);
	printf("\n=============================欧拉筛=========================\n");
	EulerSieve(200);
	for (int i = 0; i < cnt; i++)
	{
		printf("%5d ", prime[i]);
		if ((i + 1) % 10 == 0)printf("\n");
	}
	printf("\n=============================区间筛=========================\n");
	SegmentSieve(100, 200);
	for (ll i = 0,cnt = 0; i < 200 - 100; i++)
		if (isPrime[i])
		{
			printf("%5lld ", i + 100);
			if ((cnt++ + 1) % 10 == 0)printf("\n");
		}   
	return 0;
}

