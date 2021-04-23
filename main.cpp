#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH "data.txt"
#define PASSWORD_PATH "password.txt"

typedef  struct
{
	char num[20];
	char name[20];
	char sex[5];
	float chinese;
	float math;
	float english;
} DataType;

typedef struct node
{
    DataType data;
	struct node *next;
}List;

List *head;    /* head 表示人为增加的头结点 head是全局变量 指向头结点*/

int begin=0;	//是否初始化过

/*链表操作*/
void DeleteList(int i);
int WriteData();
void CreatList()
{
	int z=1;               /*控制循环*/
	//删除之前节点（防止内存泄漏）
	if(begin)
        while(head->next==NULL)
        {
            DeleteList(1);
        }
    begin=1;
	head=(List *)malloc(sizeof(List));  /* 为头结点申请分配内存 */
	head->next=NULL;
}
int LenList()  //求表长
{
	int n=0;
    List *p=head;
	int z=1;               /*控制循环*/
	while(z)
	{
	    if(p->next!=NULL)
        {
            p=p->next;
            n++;
        }
        else
            z=0;
	}
	return n;
}
char* GetfromList(int i)//返回链表中的第ｉ个元素的值
{
    List *p=head;
    int index=0;               //控制引索
    int length=LenList();
    if( i<1 || i>length)
    {
	    return p->data.name;
    }
	while(1)
	{
        if(index==i)
        {
            return p->data.name;
        }
        p=p->next;
        index++;
	}
}

List* SearchList(char name[])//在链表中查找值为name的数据元素
{
    List *p=head->next;
    int index=1;               //控制引索
    int length=LenList();
	while(1)
	{
		if(index>length)
		{
			printf("\n\t\t\t找不到该人!");
            return NULL;
		}
        if(!strcmp(p->data.name,name))
		{
            return p;
		}
        p=p->next;
        index++;        
	}
}

void EditList(char num[],char name[],char sex[],float chinese,float math, float english) //修改元素
{
	List * list=SearchList(name);
	strcpy(list->data.num,num);
	strcpy(list->data.sex,sex);
	list->data.chinese=chinese;
	list->data.math=math;
	list->data.english=english;
}

void DeleteList(int i) //删除第i个元素
{
    List *p=head,*s;
    int index=1;               //控制引索
    int length=LenList();
    
	while(1)
	{
        if(i==index)
        {
            s=p->next;
            p->next=s->next;
            free(s);
	        return;
        }
        p=p->next;
        index++;
	}
}

/*显示全部人成绩*/
void ShowScore()
{
	List *p=head;
	int i;
	printf("\n\t\t\t显示所有学生成绩:");
	if(head->next==NULL)
		printf("\n\t\t\t无记录!\n");
	else
	{
		printf("\n");
		i=0;
		while(p->next!=NULL)
		{
			i++;
		    printf("\t\t\t%d.%10s 姓名:%-8s 性别:%s\n\t\t\t语文:%5.1f 数学:%5.1f 英语:%5.1f\n\n",i,p->next->data.num,p->next->data.name,p->next->data.sex,p->next->data.chinese,p->next->data.math,p->next->data.english);
			p=p->next;
		}
	}
}

/*求平均分*/
void Average()
{
	float ac=0,am=0,ae=0;
    List *p=head;
	int i;
	printf("\n\t\t\t显示所有学生成绩:");
	if(head->next==NULL)
		printf("\n\t\t\t无记录!\n");
	else
	{
		printf("\n");
		i=0;
		while(p->next!=NULL)
		{
			i++;
			ac+=p->next->data.chinese;
			am+=p->next->data.math;
			ae+=p->next->data.english;
			p=p->next;
		}
	}
	printf("\n\t\t\t语文平均分:%.2f",ac/i);
	printf("\n\t\t\t数学平均分:%.2f",am/i);
	printf("\n\t\t\t英语平均分:%.2f",ae/i);
}

/*新增成绩*/
void InsertScore(char num[],char name[],char sex[],float chinese,float math, float english)
{
    List *p=head,*s;
    int index=1;               /*控制引索*/
    int length=LenList();
	while(1)
	{
        if(length+1==index)
        {
            s=(List *)malloc(sizeof(List));  /*为结点申请分配内存*/
            strcpy(s->data.num,num);
            strcpy(s->data.name,name);
            strcpy(s->data.sex,sex);
            s->data.chinese=chinese;
            s->data.math=math;
            s->data.english=english;
            s->next=p->next;
            p->next=s;
            p=s;
			break;
        }
        p=p->next;
        index++;
	}
	if(WriteData())
		printf("\n\t\t\t%s的成绩添加成功!\n",name);	
	else
		printf("\n\t\t\t%s的成绩添加失败!\n",name);	
}

/*修改成绩*/
void EditScore(int i) 
{
	char name[20];
    int length=LenList();
	char ch;
	char num[20];
	char sex[5];
	float c,m,e;
	List *list;
	int count=0;
	//判断序号是否正确
	if( i<1 || i>length)
    {
        printf("\n\t\t\t请输入正确的删除序号!(1~%d）\n",length);
	    return;
    }
	//初始化
	strcpy(name,GetfromList(i));
	list=SearchList(name);
	strcpy(sex,list->data.sex);
	strcpy(num,list->data.num);
	c=list->data.chinese;
	m=list->data.math;
	e=list->data.english;
	//修改
	while(1)
	{
		printf("\n\t\t\t你是否要修改%s的基本信息？(Y/N):",name);
		scanf("%c",&ch);//读取回车
		scanf("%c",&ch);
		if(ch=='y'||ch=='Y')
		{
			printf("\n\t\t\t请输入%s的语数学号和性别:\n\t\t\t(输入格式:3215008387 女):\n\t\t\t",name);
			scanf("%s %s",num,sex);
			break;
		}
		if(ch=='n'||ch=='N')
		{
			count++;
			break;
		}
	}
	while(1)
	{
		printf("\n\t\t\t你是否要修改%s的成绩？(Y/N):",name);
		scanf("%c",&ch);//读取回车
		scanf("%c",&ch);
		if(ch=='y'||ch=='Y')
		{
			printf("\n\t\t\t请输入%s的语数英三科成绩:\n\t\t\t(输入格式:100 100 100):\n\t\t\t",name);
			scanf("%f %f %f",&c,&m,&e);
			break;
		}
		if(ch=='n'||ch=='N')
		{
			count++;
			break;
		}
	}
	if(count==2)	//两次都否
		return;
	EditList(num,name,sex,c,m,e);
	if(WriteData())
		printf("\n\t\t\t%s的成绩修改成功!\n",name);	
	else
		printf("\n\t\t\t%s的成绩修改失败!\n",name);	
}

/*删除成绩*/
void DeleteScore(int i) 
{
	char name[20];
    int length=LenList();
	char ch;
	if( i<1 || i>length)
    {
        printf("\n\t\t\t请输入正确的删除序号!(1~%d）\n",length);
	    return;
    }
	strcpy(name,GetfromList(i));
	while(1)
	{
		printf("\n\t\t\t你是否要删除%s的成绩？(Y/N):",name);
		scanf("%c",&ch);//读取回车
		scanf("%c",&ch);
		if(ch=='y'||ch=='Y')
			break;
		if(ch=='n'||ch=='N')
			return;
	}
	DeleteList(i);
	if(WriteData())
		printf("\n\t\t\t%s的成绩删除成功!\n",name);	
	else
		printf("\n\t\t\t%s的成绩删除失败!\n",name);	
}




/*文件 密码*/

void ReadData()//读数据文件
{
	FILE *fp;
	char ch;
	char num[20];
	char name[20];
	char sex[5];
	float c,m,e;

	fp=fopen(PATH,"r+");
	if(fp==NULL)
	{
		fp=fopen(PATH,"w+");
		if(fp==NULL)
		{
			printf("can not open '%s'",PATH);
			exit(1);
		}
	}
	else
	{
		ch=fgetc(fp);
		if(ch!=EOF)
		{
			fseek(fp,0,SEEK_SET);
			while(!feof(fp))
			{
				fscanf(fp,"%s %s %s %f %f %f\n",num,name,sex,&c,&m,&e);
					InsertScore(num,name,sex,c,m,e);
			}
		}
	}
	fclose(fp);
	return;
}

int WriteData()//写入数据文件
{
	FILE *fp;
	List *p=head;
	int i=0;
	fp=fopen(PATH,"w+");
	if(fp==NULL)
	{
		printf("can not open '%s'",PATH);
		return 0;
	}
	while(p->next!=NULL)
	{
		i++;
		fprintf(fp,"%s %s %s %f %f %f\n",p->next->data.num,p->next->data.name,p->next->data.sex,p->next->data.chinese,p->next->data.math,p->next->data.english);
		p=p->next;
	}

	fclose(fp);
	return 1;
}

int Enter(char str[]){	//登陆验证
	FILE *fp;
	char password[20];
	fp=fopen(PASSWORD_PATH,"r+");
	if(fp==NULL)
	{
		fp=fopen(PASSWORD_PATH,"w+");
		if(fp==NULL)
		{
			printf("can not open '%s'",PASSWORD_PATH);
			exit(1);
		}
		fprintf(fp,"%s","123456");
		strcpy(password,"123456");
	}
	else
		fscanf(fp,"%s",password);
	fclose(fp);
	if(strcmp(password,str))
		return 0;
	else
		return 1;
}

int EditPassword(char password[]){	//修改密码
	FILE *fp;
	fp=fopen(PASSWORD_PATH,"w+");
	if(fp==NULL)
	{
		printf("can not open '%s'",PASSWORD_PATH);
		return 0;
	}
	fprintf(fp,"%s",password);
	fclose(fp);
	return 1;
}


/* 主函数 */
void main()
{
	int choice;
	int i;
	char num[20];
	char str[20];
	char sex[5];
	float c,m,e;
	//链表初始化
	printf("\n\t\t\t-------学生成绩管理系统初始化-------\n");
	CreatList();
	ReadData();
	system("cls");	//清屏
	while(1)
	{
		printf("\n\t\t\t----------学生成绩管理系统----------\n");
		printf("\n\t\t\t请输入密码:");	
		scanf("%s",&str);
		if(Enter(str))
			break;
	}
	while(1)
	{
		system("cls");	//清屏
		printf("\n\t\t\t----------学生成绩管理系统----------\n");
		printf("\n\t\t\t************************************");
		printf("\n\t\t\t*       1-------显示所有信息       *");
		printf("\n\t\t\t*       2-------求 平 均 分        *");
		printf("\n\t\t\t*       3-------新增学生信息       *");
		printf("\n\t\t\t*       4-------修改学生信息       *");
		printf("\n\t\t\t*       5-------删除学生信息       *");
		printf("\n\t\t\t*       6-------修 改 密 码        *");
		printf("\n\t\t\t*       0-------退      出         *");
		printf("\n\t\t\t************************************\n");
		printf("\t\t\t请选择菜单号(0--6):");
		scanf("%d",&choice);getchar();
		if (choice==0)
		{
			printf("\t\t\t程序结束!\n");
			return;
		}
		else if(choice==1)
		{
			ShowScore();
			while(1)
			{
				printf("\n\t\t\t输入0返回:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if(choice==2)
		{ 
			Average();	
			while(1)
			{
				printf("\n\t\t\t输入0返回:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if (choice==3)
		{
			printf("\n\t\t\t请输入学生的姓名(输入0返回)(输入格式:徐思娴):\n\t\t\t");
			scanf("%s",str);
			if(str[0]=='0')
				continue;	
			printf("\n\t\t\t请输入%s的语数学号和性别:\n\t\t\t(输入格式:3215008387 女):\n\t\t\t",str);
			scanf("%s %s",num,sex);
			printf("\n\t\t\t请输入%s的语数英三科成绩:\n\t\t\t(输入格式:100 100 100):\n\t\t\t",str);
			scanf("%f %f %f",&c,&m,&e);
			InsertScore(num,str,sex,c,m,e);
			while(1)
			{
				printf("\n\t\t\t输入0返回:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if (choice==4)
		{
			ShowScore();
			printf("\n\t\t\t请输入要修改学生的序号(输入0返回):");
			scanf("%d",&i);
			if(i==0)
				continue;
			EditScore(i);
			while(1)
			{
				printf("\n\t\t\t输入0返回:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if (choice==5)
		{
			ShowScore();
			printf("\n\t\t\t请输入要删除学生的序号(输入0返回):");
			scanf("%d",&i);
			if(i==0)
				continue;
			DeleteScore(i);
			while(1)
			{
				printf("\n\t\t\t输入0返回:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if (choice==6)
		{
			printf("\n\t\t\t请输入原密码:");
			scanf("%s",str);
			if(!Enter(str))
			{
				printf("\n\t\t\t密码错误!");//不正确
				while(1)
				{
					printf("\n\t\t\t输入0返回:");
					scanf("%d",&choice);
					if(choice==0)
						break;
				}
				if(choice==0)
					continue;
			}
			printf("\n\t\t\t请输入新密码(6-20位):");
			scanf("%s",str);
			if(strlen(str)<6||strlen(str)>20)//密码长度不正确
			{
				while(1)
				{
					printf("\n\t\t\t密码长度不正确!");
					printf("\n\t\t\t输入0返回:");
					scanf("%d",&choice);
					if(choice==0)
						break;
				}
				if(choice==0)
					continue;
			}
			if(EditPassword(str))
				printf("\n\t\t\t密码修改成功!");
			else
				printf("\n\t\t\t密码修改失败!");

			
			while(1)
			{
				printf("\n\t\t\t输入0返回:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
	}
}