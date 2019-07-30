#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "ctime"

#define N printf("\n");
#define V printf("\nsravneniy: %d  peresilki: %d" , sr, pr); N; 
#define VM printf("max sr: %d  max per: %d" , msr, mpr); N; N;
#define P(x) printf("-------"x); N;
const int n=20 , r=50; 
int	m[n], c[n];
int sr=0, pr=0;
int msr=0, mpr=0;

void vivod(){
	for (int i=0 ; i <n ; i++)
		printf("%d " , m[i]);
}
void kopi(){
	for( int i=0; i<n ; i++)
		m[i]=c[i];
}

void vklychenie(){
	P("vklychenie");
	int	i,j,t;
	sr=0, pr=0; msr=0; mpr=0;

    for(i=1; i<n; i++){
		t=m[i];
		j = i; 
		while ((j > 0) && (t < m[j-1])) {
			m[j] = m[j-1]; pr++; sr++;
			j--;
		}
		sr+=2;
	m[j] = t; pr++;
	}
	msr=(((n*n)-n)/(2))-1;
	mpr=((n*n)+(3*n)-4)/(2);
	vivod();
	V; VM;
}

void popolam(){
	P("popolam");
	int i,j,x,b,l,r; 
	sr=0, pr=0;
	for (i=1 ;i<n; i++) {
		x = m[i];
		l = 0;
		r = i;
		while(l<r){
			b = (l+r)/2;
			sr++;
			if (m[b] <= x) {
				l = b+1; sr++;
			}
			else r = b;
		}
		for (j=i; j>=r; j--) {
			m[j] = m[j-1]; pr++;
		}
		m[r] = x; pr++;
	}
	vivod();
	V; N;
}

void vstavka(){
	P("vstavka");
	int i,j,min,k;
	sr=0, pr=0;
	for (i = 0; i < n-1; i++) {
		min = i;
		for (j = i+1; j < n; j++) {
			sr++;
			if (m[j] < m[min])
				min = j; 
		}
		k = m[i];
		m[i] = m[min];
		m[min] = k;
		pr++;
	}
	msr=((n*n)-n);
	mpr=(((n*n)/(4))+(3*(n-1)));
	vivod();
	V; VM;
}

void puzir(){

	P("puzir");
	sr=0, pr=0;
	int i,j,y;
	for( i=0; i<n; i++)
		for( j=0; j<(n-i-1); j++){
			sr++;
			if(m[j] > m[j+1]){
				y = m[j];
				m[j] = m[j+1];
				m[j+1] = y;
				pr++;
			}
		}
	msr=(n-1)*(n/2);
	mpr=(n-1)*(n/2);
	vivod();
	V; VM;
}

void shaker(){
	P("shaker");
	sr=0, pr=0;
	int k, L, R, x;
	L = 0; R = n-1; 
	k = 1;  
	while((L < R) && k > 0){
		k = 0;
		for (int i=L; i<R; i++) {
			sr++;
			if (m[i] > m[i+1]) {
				x = m[i];
				m[i] = m[i+1];
				m[i+1] = x; pr++;
				k = 1;
			}
		}
    R--;
		for (int i=R; i>L; i--) { 
			sr++;
			if (m[i-1] > m[i]) {
				x = m[i];
				m[i] = m[i-1];
				m[i-1] = x; pr++;
				k = 1;
			}
		}
    L++;
	}
	vivod();
	V; N;
}

void sort(int l, int r) {
	int k, ls, rs;
	ls = l;
	rs = r;
	k = m[l];
	while (l < r) {
		while ((m[r] >= k) && (l < r)){
			r--; sr++;
		} sr++;
		sr++;
		if (l != r) {
			m[l] = m[r];
			l++; pr++;
		}
		while ((m[l] <= k) && (l < r)){
			l++; sr++;
		} sr++;
		sr++;
		if (l != r) {
			m[r] = m[l];
			r--; pr++;
		}
	}
	m[l] = k;
	k = l;
	l = ls;
	r = rs; pr++;
	if (l < k)
		sort(l, k-1);
	if (r > k)
		sort(k+1, r);
}

void shell() {
	P("shell");
	sr=0, pr=0;
	int i, j, k, x;
	k = 3;
	while (k > 0) {
		for (i=0; i < n; i++) {
			j = i;
			x = m[i];
			while((j>=k) && (m[j-k]>x)) {
				m[j] = m[j - k];
				j = j - k; pr++; sr++;
			} sr++;
			m[j] = x; pr++;
		}
		if (k/2 != 0)
			k = k/2;
		else if (k == 1)
			k = 0;
			else
				k = 1;
	}
	vivod();
	V; N;
}


void main() {
	srand(time(NULL));

	for(int i=0; i<n; i++){
		 m[i]=rand()%r;
		 c[i]= m[i];
	}
	vivod();
	N; N;
	//------------
	vklychenie();
	//------------
	kopi();
	popolam();
	//------------
	kopi();
	vstavka();
	//------------
	kopi();
	puzir();
	//------------
	kopi();
	shaker();
	//------------
	kopi();
	P("sort");
	sr=0, pr=0;
	sort(0,19);
	vivod();
	V; N;
	//------------
	kopi();
	shell();
	N;
}