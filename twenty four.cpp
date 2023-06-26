#include<bits/stdc++.h>
using namespace std; 
char cf;
int top,te;
struct node
{
	int fl,fr;
	char c;
	int fz,fm;
	int step;
}f[4],t,V[4];
string to__string(int x)
{
	string s;
	if(x>=10)
	{
		s+=(x/10)+'0';
		x%=10;
	}
	s+=x+'0';
	return s;
}
node calculation(node x,node y,char c)
{
	switch(c)
	{
		case '+':case '-':
			x.fz*=y.fm;
			y.fz*=x.fm;
			x.fm*=y.fm;
			if(c=='+')	x.fz+=y.fz;
			else	x.fz-=y.fz;
			break;
		case '*':
			x.fz*=y.fz;
			x.fm*=y.fm;
			break;
		case '/':
			x.fz*=y.fm;
			x.fm*=y.fz;
			break;
	}
	if(x.step<y.step)	x.step=y.step;
	return x;
}
node calculation_formula(int l,int q)
{
	for(int i=l;i<4;i++)
	{
		if(f[i].fr)
		{
			f[i].fr--;
			break;
		}
		if(f[i].fl)
		{
			f[i].fl--;
			if(i==l || f[i].c=='+' || f[i].c=='-')
			{
				t=calculation_formula(i,top);
				V[top++]=t;
			}
			else
			{
				t=calculation_formula(i,top);
				V[top-1]=calculation(V[top-1],t,t.c);
			}
			i=V[top-1].step;
			continue;
		}
		if(i==l)
		{
			V[top++]=f[i];
			continue;
		}
		switch(f[i].c)
		{
			case '+':case '-':
				V[top++]=f[i];
				break;
			case '*':case '/':
				V[top-1]=calculation(V[top-1],f[i],f[i].c);
				break;
		}
	}
	for(int i=q+1;i<top;i++)	V[q]=calculation(V[q],V[i],V[i].c);
	top=q; 
	return V[q];
}
void determine_24()
{
	string s;
	top=0;
	for(int i=0;i<4;i++)
	{
		for(int j=1;j<=f[i].fr;j++)	{s+=')';top--;}
		if(i>0)	s+=f[i].c;
		for(int j=1;j<=f[i].fl;j++)	{s+='(';top++;}
		s+=to__string(f[i].fz);
	}
	while(top--)	s+=')';
	top=0;
	node w;
	w=calculation_formula(0,0);
	if(24*w.fm==w.fz)	cout<<s<<"=24\n";
}
void choose_brackets()
{
	for(int i=1;i<=5;i++)
	{
		for(int j=0;j<4;j++)
		{
			f[j].fl=0;
			f[j].fr=0;
			f[j].step=j;
		}
		switch(i)
		{
			case 1:f[0].fl=2;f[2].fr=1;f[3].fr=1;break;
			case 2:f[0].fl=1;f[1].fl=1;f[3].fr=2;break;
			case 3:f[1].fl=2;f[3].fr=1;break;
			case 4:f[1].fl=1;f[2].fl=1;break;
			case 5:f[0].fl=1;f[2].fr=1;f[2].fl=1;break;
		}
		determine_24();
	}
}
void select_operator(int num)
{
	if(num==4)
	{
		choose_brackets();
		return;
	}
	for(int i=1;i<=4;i++)
	{
		switch(i)
		{
			case 1:f[num].c='+';break;
			case 2:f[num].c='-';break;
			case 3:f[num].c='*';break;
			case 4:f[num].c='/';break;
		}
		select_operator(num+1);
	}
}
int main()
{
	srand(time(NULL));
	while(1)
	{
		for(int i=0;i<4;i++)
		{
			f[i].fz=1+rand()%13;
			cout<<f[i].fz<<" ";
			f[i].fm=1;
		}
		cout<<endl;
		cout<<"Should I output all the answers?(y/n)";
		cin>>cf;
		if(cf=='y')
		{
			for(int i=0;i<4;i++)
			{
				swap(f[0],f[i]);
				for(int j=1;j<4;j++)
				{
					swap(f[1],f[j]);
					for(int z=2;z<4;z++)
					{
						swap(f[2],f[z]);
						select_operator(1);
						swap(f[2],f[z]);
					}
					swap(f[1],f[j]);
				}
				swap(f[0],f[i]);
			}
			cout<<"end"<<endl;
		}
		system("pause");
	}
}
