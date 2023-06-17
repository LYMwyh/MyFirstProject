#include<bits/stdc++.h>
using namespace std; 
char cf;
int q;
struct node
{
	int fl,fr;
	char c;
	int fz,fm;
	int step;
	int check_l,check_r;
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
node calculation_formula(int l,int top)
{
	t;
	q=top;
	for(int i=l;i<4;i++)
	{
		if(f[i].fr && f[i].fr-f[i].check_r>0)
		{
			f[i].check_r++;
			break;
		}
		if(f[i].fl && f[i].fl-f[i].check_l>0)
		{
			f[i].check_l++;
			if(f[i].c=='+' || f[i].c=='-' || i==l)
			{
				V[top]=calculation_formula(i,top);
				top++;
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
	return V[q];
}
void determine_24()
{
	node t=calculation_formula(0,0);
	if(t.fz%t.fm==0 && t.fz/t.fm==24)
	{
		string s;
		int top=0;
		for(int i=0;i<4;i++)
		{
			for(int j=1;j<=f[i].fr;j++)	{s+=')';top--;}
			if(i>0)	s+=f[i].c;
			for(int j=1;j<=f[i].fl;j++)	{s+='(';top++;}
			s+=to__string(f[i].fz);
		}
		for(int i=1;i<=top;i++)	s+=')';
		s+="=24";
		cout<<s<<endl;
	}
}
void choose_brackets()
{
	for(int i=1;i<=5;i++)
	{
		for(int j=0;j<4;j++)
		{
			f[j].fl=0;
			f[j].fr=0;
			f[j].check_l=0;
			f[j].check_r=0;
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
	while(true)
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
			
		}
		system("pause");
	}
	return 0;
}
