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

List *head;    /* head ��ʾ��Ϊ���ӵ�ͷ��� head��ȫ�ֱ��� ָ��ͷ���*/

int begin=0;	//�Ƿ��ʼ����

/*�������*/
void DeleteList(int i);
int WriteData();
void CreatList()
{
	int z=1;               /*����ѭ��*/
	//ɾ��֮ǰ�ڵ㣨��ֹ�ڴ�й©��
	if(begin)
        while(head->next==NULL)
        {
            DeleteList(1);
        }
    begin=1;
	head=(List *)malloc(sizeof(List));  /* Ϊͷ�����������ڴ� */
	head->next=NULL;
}
int LenList()  //���
{
	int n=0;
    List *p=head;
	int z=1;               /*����ѭ��*/
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
char* GetfromList(int i)//���������еĵڣ��Ԫ�ص�ֵ
{
    List *p=head;
    int index=0;               //��������
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

List* SearchList(char name[])//�������в���ֵΪname������Ԫ��
{
    List *p=head->next;
    int index=1;               //��������
    int length=LenList();
	while(1)
	{
		if(index>length)
		{
			printf("\n\t\t\t�Ҳ�������!");
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

void EditList(char num[],char name[],char sex[],float chinese,float math, float english) //�޸�Ԫ��
{
	List * list=SearchList(name);
	strcpy(list->data.num,num);
	strcpy(list->data.sex,sex);
	list->data.chinese=chinese;
	list->data.math=math;
	list->data.english=english;
}

void DeleteList(int i) //ɾ����i��Ԫ��
{
    List *p=head,*s;
    int index=1;               //��������
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

/*��ʾȫ���˳ɼ�*/
void ShowScore()
{
	List *p=head;
	int i;
	printf("\n\t\t\t��ʾ����ѧ���ɼ�:");
	if(head->next==NULL)
		printf("\n\t\t\t�޼�¼!\n");
	else
	{
		printf("\n");
		i=0;
		while(p->next!=NULL)
		{
			i++;
		    printf("\t\t\t%d.%10s ����:%-8s �Ա�:%s\n\t\t\t����:%5.1f ��ѧ:%5.1f Ӣ��:%5.1f\n\n",i,p->next->data.num,p->next->data.name,p->next->data.sex,p->next->data.chinese,p->next->data.math,p->next->data.english);
			p=p->next;
		}
	}
}

/*��ƽ����*/
void Average()
{
	float ac=0,am=0,ae=0;
    List *p=head;
	int i;
	printf("\n\t\t\t��ʾ����ѧ���ɼ�:");
	if(head->next==NULL)
		printf("\n\t\t\t�޼�¼!\n");
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
	printf("\n\t\t\t����ƽ����:%.2f",ac/i);
	printf("\n\t\t\t��ѧƽ����:%.2f",am/i);
	printf("\n\t\t\tӢ��ƽ����:%.2f",ae/i);
}

/*�����ɼ�*/
void InsertScore(char num[],char name[],char sex[],float chinese,float math, float english)
{
    List *p=head,*s;
    int index=1;               /*��������*/
    int length=LenList();
	while(1)
	{
        if(length+1==index)
        {
            s=(List *)malloc(sizeof(List));  /*Ϊ�����������ڴ�*/
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
		printf("\n\t\t\t%s�ĳɼ���ӳɹ�!\n",name);	
	else
		printf("\n\t\t\t%s�ĳɼ����ʧ��!\n",name);	
}

/*�޸ĳɼ�*/
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
	//�ж�����Ƿ���ȷ
	if( i<1 || i>length)
    {
        printf("\n\t\t\t��������ȷ��ɾ�����!(1~%d��\n",length);
	    return;
    }
	//��ʼ��
	strcpy(name,GetfromList(i));
	list=SearchList(name);
	strcpy(sex,list->data.sex);
	strcpy(num,list->data.num);
	c=list->data.chinese;
	m=list->data.math;
	e=list->data.english;
	//�޸�
	while(1)
	{
		printf("\n\t\t\t���Ƿ�Ҫ�޸�%s�Ļ�����Ϣ��(Y/N):",name);
		scanf("%c",&ch);//��ȡ�س�
		scanf("%c",&ch);
		if(ch=='y'||ch=='Y')
		{
			printf("\n\t\t\t������%s������ѧ�ź��Ա�:\n\t\t\t(�����ʽ:3215008387 Ů):\n\t\t\t",name);
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
		printf("\n\t\t\t���Ƿ�Ҫ�޸�%s�ĳɼ���(Y/N):",name);
		scanf("%c",&ch);//��ȡ�س�
		scanf("%c",&ch);
		if(ch=='y'||ch=='Y')
		{
			printf("\n\t\t\t������%s������Ӣ���Ƴɼ�:\n\t\t\t(�����ʽ:100 100 100):\n\t\t\t",name);
			scanf("%f %f %f",&c,&m,&e);
			break;
		}
		if(ch=='n'||ch=='N')
		{
			count++;
			break;
		}
	}
	if(count==2)	//���ζ���
		return;
	EditList(num,name,sex,c,m,e);
	if(WriteData())
		printf("\n\t\t\t%s�ĳɼ��޸ĳɹ�!\n",name);	
	else
		printf("\n\t\t\t%s�ĳɼ��޸�ʧ��!\n",name);	
}

/*ɾ���ɼ�*/
void DeleteScore(int i) 
{
	char name[20];
    int length=LenList();
	char ch;
	if( i<1 || i>length)
    {
        printf("\n\t\t\t��������ȷ��ɾ�����!(1~%d��\n",length);
	    return;
    }
	strcpy(name,GetfromList(i));
	while(1)
	{
		printf("\n\t\t\t���Ƿ�Ҫɾ��%s�ĳɼ���(Y/N):",name);
		scanf("%c",&ch);//��ȡ�س�
		scanf("%c",&ch);
		if(ch=='y'||ch=='Y')
			break;
		if(ch=='n'||ch=='N')
			return;
	}
	DeleteList(i);
	if(WriteData())
		printf("\n\t\t\t%s�ĳɼ�ɾ���ɹ�!\n",name);	
	else
		printf("\n\t\t\t%s�ĳɼ�ɾ��ʧ��!\n",name);	
}




/*�ļ� ����*/

void ReadData()//�������ļ�
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

int WriteData()//д�������ļ�
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

int Enter(char str[]){	//��½��֤
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

int EditPassword(char password[]){	//�޸�����
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


/* ������ */
void main()
{
	int choice;
	int i;
	char num[20];
	char str[20];
	char sex[5];
	float c,m,e;
	//�����ʼ��
	printf("\n\t\t\t-------ѧ���ɼ�����ϵͳ��ʼ��-------\n");
	CreatList();
	ReadData();
	system("cls");	//����
	while(1)
	{
		printf("\n\t\t\t----------ѧ���ɼ�����ϵͳ----------\n");
		printf("\n\t\t\t����������:");	
		scanf("%s",&str);
		if(Enter(str))
			break;
	}
	while(1)
	{
		system("cls");	//����
		printf("\n\t\t\t----------ѧ���ɼ�����ϵͳ----------\n");
		printf("\n\t\t\t************************************");
		printf("\n\t\t\t*       1-------��ʾ������Ϣ       *");
		printf("\n\t\t\t*       2-------�� ƽ �� ��        *");
		printf("\n\t\t\t*       3-------����ѧ����Ϣ       *");
		printf("\n\t\t\t*       4-------�޸�ѧ����Ϣ       *");
		printf("\n\t\t\t*       5-------ɾ��ѧ����Ϣ       *");
		printf("\n\t\t\t*       6-------�� �� �� ��        *");
		printf("\n\t\t\t*       0-------��      ��         *");
		printf("\n\t\t\t************************************\n");
		printf("\t\t\t��ѡ��˵���(0--6):");
		scanf("%d",&choice);getchar();
		if (choice==0)
		{
			printf("\t\t\t�������!\n");
			return;
		}
		else if(choice==1)
		{
			ShowScore();
			while(1)
			{
				printf("\n\t\t\t����0����:");
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
				printf("\n\t\t\t����0����:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if (choice==3)
		{
			printf("\n\t\t\t������ѧ��������(����0����)(�����ʽ:��˼�):\n\t\t\t");
			scanf("%s",str);
			if(str[0]=='0')
				continue;	
			printf("\n\t\t\t������%s������ѧ�ź��Ա�:\n\t\t\t(�����ʽ:3215008387 Ů):\n\t\t\t",str);
			scanf("%s %s",num,sex);
			printf("\n\t\t\t������%s������Ӣ���Ƴɼ�:\n\t\t\t(�����ʽ:100 100 100):\n\t\t\t",str);
			scanf("%f %f %f",&c,&m,&e);
			InsertScore(num,str,sex,c,m,e);
			while(1)
			{
				printf("\n\t\t\t����0����:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if (choice==4)
		{
			ShowScore();
			printf("\n\t\t\t������Ҫ�޸�ѧ�������(����0����):");
			scanf("%d",&i);
			if(i==0)
				continue;
			EditScore(i);
			while(1)
			{
				printf("\n\t\t\t����0����:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if (choice==5)
		{
			ShowScore();
			printf("\n\t\t\t������Ҫɾ��ѧ�������(����0����):");
			scanf("%d",&i);
			if(i==0)
				continue;
			DeleteScore(i);
			while(1)
			{
				printf("\n\t\t\t����0����:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
		else if (choice==6)
		{
			printf("\n\t\t\t������ԭ����:");
			scanf("%s",str);
			if(!Enter(str))
			{
				printf("\n\t\t\t�������!");//����ȷ
				while(1)
				{
					printf("\n\t\t\t����0����:");
					scanf("%d",&choice);
					if(choice==0)
						break;
				}
				if(choice==0)
					continue;
			}
			printf("\n\t\t\t������������(6-20λ):");
			scanf("%s",str);
			if(strlen(str)<6||strlen(str)>20)//���볤�Ȳ���ȷ
			{
				while(1)
				{
					printf("\n\t\t\t���볤�Ȳ���ȷ!");
					printf("\n\t\t\t����0����:");
					scanf("%d",&choice);
					if(choice==0)
						break;
				}
				if(choice==0)
					continue;
			}
			if(EditPassword(str))
				printf("\n\t\t\t�����޸ĳɹ�!");
			else
				printf("\n\t\t\t�����޸�ʧ��!");

			
			while(1)
			{
				printf("\n\t\t\t����0����:");
				scanf("%d",&choice);
				if(choice==0)
					break;
			}
		}
	}
}