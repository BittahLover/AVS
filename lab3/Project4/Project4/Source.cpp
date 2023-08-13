#include<stdlib.h>
#include<process.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include <clocale>

typedef struct stack
{
	int top;
	int a[100];
}c;

void lshift(c* sq, c* sa);
void comp(c* sm);
void diff(c* sa, c* sm);
void sum(c* sa, c* sm);
void push(int b, c* s);
void bin(int n, c* s);
int convert(c* s);
void display(c* s);
int q1 = 0;

int main()
{
	setlocale(LC_ALL, "Russian");
	c sm, sq, sa, temp;
	int tempm, tempq;
	sm.top = -1;
	sq.top = -1;
	temp.top = -1;
	sa.top = -1;
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		sm.a[i] = 0;
		sq.a[i] = 0;
		sa.a[i] = 0;
	}
	int  q = 0, m = 0, steps;
	printf("Введите M(делитель) и Q(Делимое) ");
	scanf_s("%d%d", &m, &q);
	if (m == 0)
	{
		printf("\nДелить на ноль нельзя\n");
		return 0;
	}
	if (q / m < 0.0000000000000000000000000000000001)
	{
		printf("Число слишком мало");
		printf("\nПотеря значимости.\n\n");
		return 0;
		
	}
	tempm = m;
	tempq = q;
	if (m < 0)
	{
		m = -m;
	}
	if (q < 0)
	{
		q = -q;
	}
	bin(m, &sm);
	bin(q, &sq);
	sm.top += 1;
	sa.top = sm.top;
	steps = sq.top;
	for (i = 0; i <= steps; i++)
	{
		printf("\n.......................................проход %d................................... \n ", i + 1);
		printf("\n");
		lshift(&sq, &sa);
		printf("                                  Sa                                sq");
		printf("\n\nСдвиг влево");
		printf("                      ");
		display(&sa);
		printf("                              ");
		display(&sq);
		diff(&sa, &sm);
		printf("\nРазница ");
		printf("                         ");
		display(&sa);
		printf("                              ");
		display(&sq);
		if (sa.a[sa.top] == 1)
		{
			printf("\n\nЕсли A<0 тогда Q0=0 и a=a+m ");
			sq.a[0] = 0;
			sum(&sa, &sm);
			printf("\n\nПосле операции");
			printf("                   ");
			display(&sa);
			printf("                              ");
			display(&sq);
		}
		else
		{
			printf("\n\nЕсли A>0 тогда Q0=1  ");
			sq.a[0] = 1;
			printf("\nПосле операции");
			printf("                   ");
			display(&sa);
			printf("                              ");
			display(&sq);
		}
		printf("\n");
	}
	printf("\n.......................................Ответ................................... \n ");
	printf("\n\nОстаток = ");
	display(&sa);
	printf("\n\nЧастное = ");
	display(&sq);
	if (tempm < 0 || tempq < 0)
	{
		printf("\n\nЧастное  =  -%d ", convert(&sq));
		printf("\n\nОстаток  =  %d ", convert(&sa));
	}
	else
	{
		printf("\n\nЧастное  =  %d ", convert(&sq));
		printf("\n\nОстаток  =  %d ", convert(&sa));
	}
	return 0;
}
void lshift(c* sq, c* sa)
{
	int i, temp, ta = sa->a[sa->top], tq = sq->a[sq->top];
	for (i = (sq->top); i > 0; i--)
	{
		sq->a[i] = sq->a[i - 1];
	}
	for (i = sa->top; i > 0; i--)
	{
		sa->a[i] = sa->a[i - 1];
	}
	sa->a[i] = tq;
}
void diff(c* sa, c* sm)
{
	c temp;
	temp.top = -1;
	int i;
	temp.top = sm->top;
	for (i = sm->top; i >= 0; i--)
	{
		temp.a[i] = sm->a[i];

	}
	comp(&temp);
	int carry = 0;
	for (i = 0; i <= sm->top; i++)
	{
		if ((sa->a[i] == 0) && temp.a[i] == 0 && carry == 0)
		{
			sa->a[i] = 0;
		}
		else if (((sa->a[i] == 0) && (temp.a[i] == 0)) && carry != 0)
		{
			sa->a[i] = 1;
			carry = 0;
		}
		else if (((sa->a[i] == 0) && carry == 0) && (temp.a[i] != 0))
		{
			sa->a[i] = 1;
		}
		else if (((carry == 0) && (temp.a[i] == 0)) && sa->a[i] != 0)
		{
			sa->a[i] = 1;
		}
		else if ((carry == 0) && ((temp.a[i] != 0) && sa->a[i] != 0))
		{
			sa->a[i] = 0;
			carry = 1;

		}
		else if ((carry != 0) && ((temp.a[i] == 0) && sa->a[i] != 0))
		{
			sa->a[i] = 0;
			carry = 1;
		}
		else if ((carry != 0) && ((temp.a[i] != 0) && sa->a[i] == 0))
		{
			sa->a[i] = 0;
			carry = 1;
		}
		else
		{
			sa->a[i] = 1;
			carry = 1;
		}
	}
}
void comp(c* sm)
{
	int i;
	for (i = 0; i <= sm->top; i++)
	{
		if ((sm->a[i]) == 0)
			sm->a[i] = 1;
		else
			sm->a[i] = 0;
	}
	for (i = 0; i <= sm->top; i++)
	{
		if (sm->a[i] == 0)
		{
			sm->a[i] = 1;
			break;
		}
		else
		{
			sm->a[i] = 0;
		}
	}
}
void sum(c* sa, c* sm)
{
	int carry = 0, i;
	for (i = 0; i <= sm->top; i++)
	{
		if ((sa->a[i] == 0) && sm->a[i] == 0 && carry == 0)
		{
			sa->a[i] = 0;
		}
		else if (((sa->a[i] == 0) && (sm->a[i] == 0)) && carry != 0)
		{
			sa->a[i] = 1;
			carry = 0;
		}
		else if (((sa->a[i] == 0) && carry == 0) && (sm->a[i] != 0))
		{
			sa->a[i] = 1;
		}
		else if (((carry == 0) && (sm->a[i] == 0)) && sa->a[i] != 0)
		{
			sa->a[i] = 1;
		}
		else if ((carry == 0) && ((sm->a[i] != 0) && sa->a[i] != 0))
		{
			sa->a[i] = 0;
			carry = 1;
		}
		else if ((carry != 0) && ((sm->a[i] == 0) && sa->a[i] != 0))
		{
			sa->a[i] = 0;
			carry = 1;
		}
		else if ((carry != 0) && ((sm->a[i] != 0) && sa->a[i] == 0))
		{
			sa->a[i] = 0;
			carry = 1;
		}
		else
		{
			sa->a[i] = 1;
			carry = 1;
		}
	}
}
void push(int b, c* s)
{
	s->a[++(s->top)] = b;
}
void bin(int n, c* s)
{
	int rem;
	for (int i = n; i != 0; i = i / 2)
	{
		rem = i % 2;
		push(rem, s);
	}
}
int convert(c* s)
{
	int i, sum = 0;
	for (i = s->top; i >= 0; i--)
	{
		sum = sum + (s->a[i]) * pow(2, i);
	}
	return sum;
}

void display(c* s)
{
	for (int i = s->top; i >= 0; i--)
	{
		printf("%d", s->a[i]);
	}
}
