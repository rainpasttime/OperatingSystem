/*
*�ڴ涯̬����֮��������֯��ʽ��
                              1.�Ӵ�С���������ƥ��
                              2.��С����������������Ӧƥ��
                              3.����ַ��С��С������������ƥ��
*������ʾ��ѡ��ƥ�䷽ʽ->������Ҫ�Ĵ�С
������DisplayMain:��ʾ�û�����������

*/
#include"Storage.h"

int main()
{
    initStorage();
    DisplayMain();
    return 0;
}

void DisplayMain()
{
    char select;
    printf("|----------ѡ��ƥ�䷽��----------|\n");
    printf("  1.�ƥ��\n");
    printf("  2.����ƥ��\n");
    printf("  3.����ƥ��\n");
    printf("  4.�˳�\n");
    printf("|-------------------------|\n");
    printf("��ѡ��1~4\n");
    do {
        scanf("%s",&select);//ѡ��
    } while( !(49 <= select && select <= 52) );

    switch(select) {
		case '1':
			printf("     �ƥ��\n");
			DisplayInput(1);
			break;
		case '2':
			printf("     ����ƥ��\n");
		    DisplayInput(2);
			break;
		case '3':
			printf("     ����ƥ��\n");
		    DisplayInput(3);
			break;
		case '4':
			break;
    }
}

void DisplayInput(int choose)
{
        char select;
        printf("|----------�� ��----------|\n");
		printf("  1.��ʾ�����ڴ�״̬\n");
		printf("  2.��ʾռ���ڴ�\n");
		printf("  3.�����ڴ�\n");
		printf("  4.�����ڴ�\n");
		printf("  5.�˳�\n");
		printf("|-------------------------|\n");
		printf("��ѡ��1~5\n");

		do {
			scanf("%s",&select);//ѡ��
		} while( !(49 <= select && select <= 53) );

		 switch(select) {
		     case '1':
		         printf("     �����ڴ����\n");
			     DisplayStorage(idle);
			     break;
             case '2':
                 printf("     ռ���ڴ����\n");
			     DisplayStorage(occupy);
                 break;
             case '3':
                 printf("     �����ڴ�\n");
                 printf("�����ڴ��С��\n");
			     scanf("%d",&apply);
			     ApplyStorage(choose,apply);
			     break;
		     case '4':
			     printf("     �����ڴ�\n");
                 printf("��������ڴ�ı�ţ�\n");
			     scanf("%s",&Number);
		         RecycleStorage(choose,Number);
			     break;
		     case '5':
			     break;
    }
}

void DisplayStorage(Storage *head)
{
	Storage *tem = head;
	printf("|--------|--------|--------|\n");
	printf("|  ��ַ  |  ����  |  ���  |\n");
    printf("|--------|--------|--------|\n");
	while (tem != NULL) {
		printf("|");

		printf("%s",tem->address);
		print_space( 8- strlen(tem->address));
		printf("|");

		printf("%s",tem->length);
		print_space(8 - strlen(tem->length));
		printf("|\n");

		printf("%s",tem->number);
		print_space( 8- strlen(tem->number));
		printf("|");

		tem = tem->next;

	}
	 printf("|--------|--------|\n");
	 printf("\n");
}

void initStorage()
{
    mainStorage.address = ADDRESS;                  //��ʼ��ַ��0
    mainStorage.length = MAX_LENGTH;               //������32KB
    mainStorage.next = NULL;
    mainStorage.tag = 0;
    mainStorage.number = "1";
    idle = &mainStorage;
    occupy = NULL;
}
void print_space(int num){//����ո��Ա�����ı�
	int i;
	for (i=0; i<num; i++) {
		printf(" ");
	}
}

void ApplyStorage(int choose,int apply)
{
    Storage *tem = idle;
    Storage *newApply;
    newApply = new Storage;
    int length;
    int differ;
    char len[5];
    while(tem!=NULL)
    {
        length = atoi(tem->length);
        //�����п��С����������ڴ��С��
        if(length>apply)
        {
            differ = length-apply;
            //���������ʣ��ֵС���ŷ�ֵ
            if(differ<LIMIT)
            {
                copyChar(idle->address,newApply->address);
                copyChar(idle->length,newApply->length);
                newApply->next = occupy;
                if(occupy!=NULL)
                {
                    int a = atoi(occupy->number)+1;
                    char b[5];
                    itoa(a,b,5);
                    newApply->number = b;
                }
                else
                    newApply->number = "1";
                occupy = newApply;
                idle = idle->next;
                break;
            }
            //�����ʣ���ڴ�����ŷ�ֵ
            else
            {
                copyChar(idle->address,newApply->address);
                itoa(apply,newApply->length,3);
                newApply->next = occupy;
                newApply->tag = 1;
                if(occupy!=NULL)
                {
                    int a = atoi(occupy->number)+1;
                    itoa(a,newApply->number,MAX_LENGTH);
                }
                else
                    copyChar("1",newApply->number);
                occupy = newApply;
                ComputeAddress(apply);  //�������֮��Ŀ��п����ʼ��ַ
                itoa(differ,idle->length,3);
                break;
            }
        }
        //û���ҵ�����������ҡ�
        tem = tem->next;
    }
    //û���㹻�ڴ��ʱ��
    if(tem==NULL)
    {
        printf("Don't have enough storage!ERROR!\n");
        return;
    }
    //�������ڴ�֮��鿴���п��Ƿ�����Ҫ����������Ҫ�ϲ���
    Union(choose);
}

//�������֮����п�ĳ�ʼ��ַ
void ComputeAddress(int apply)
{
    int address = atoi(idle->address);
    address += apply;
    itoa(address,idle->address,5);
}
//���մ���Ĳ�����������ʲô��������֯��
void Rank(int choose)
{
    Storage *tem;
    Storage *head;
    Storage *first;
    Storage *ite;
    head = idle;
    while(head!=NULL)
    {
        tem = head;
        first = head;
        ite = head->next;
        while(ite!=NULL)
        {
            //���ճ��ȴӴ�С����
            if(choose==1)
            {
                if(first->length < ite->length)
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            //���ճ��ȴ�С��������
            else if(choose==2)
            {
                if(first->length > ite->length)
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            //���յ�ַ��С��������
            else
            {
                if(first->address > ite->address)
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            ite = ite->next;
        }
        if(first!=head)
        {
            tem->next = first->next;
            first->next = head;
            if(idle==head)
                idle = first;
        }
        else
        {
            head = head->next;
        }
    }
}

//�����㷨��������Ӧ��ŵ��ڴ�֮��Ҫ������������������ڴ棬���¼����С�����Ұ��ղ�ͬ����֯��ʽ�����ڴ档
void RecycleStorage(int choose,char *number)
{
    Storage *tem;
    Storage *first;
    tem = occupy;
    first = occupy;
    int num = getInteger(number);
    while(tem!=NULL)
    {
        int nu = getInteger(tem->number);
        if(num==nu)
        {
            if(tem==occupy)
            {
                occupy = occupy->next;
                tem->tag = 0;
                tem->next = idle;
                idle = tem;
            }
            else
            {
                first->next = tem->next;
                tem->tag = 0;
                tem->next = idle;
                idle = tem;
            }
        }
        else
        {
            first = tem;
            tem = tem->next;
        }
    }
    if(tem==NULL)
    {
        printf("The number is wrong!ERROR!\n");
        return;
    }
    Union(choose);
}
//�����ж��Ƿ����������ڵĲ���
void Union(int choose)
{
    Storage *head;
    Storage *ite;
    head = idle;
    while(head!=NULL)
    {
        ite = idle;
        //��������
        int next = atoi(head->address);
        next += atoi(head->length);
        while(ite!=NULL)
        {
            //�����Ƿ��ǵ�ǰ�ڵ��������
            int tem = atoi(ite->address);
            if(tem==next)
            {
                Storage *t = idle;
                while(t->next!=ite)
                    t = t->next;
                t->next = ite->next;
                //����ϲ�֮��Ŀ����ڴ�鳤�ȡ�
                next = atoi(ite->length)+atoi(head->length);
                itoa(next,head->length,3);
                if(ite==idle)
                    idle = head;
                delete ite;
                ite = t->next;
            }
        }
        head = head->next;
    }
    Rank(choose);
}

void copyChar(char *a,char *b)
{
    int i;
    for(i=0;i<strlen(a);i++)
    {
        b[i] = a[i];
    }
    b[i] = '\0';
}

int getInteger(char *a)
{
    int i=0;
    int sum = 0;
    for(;i<strlen(a);i++)
    {
        int j = a[i]-'0';
        sum = sum*10+j;
    }
    return sum;
}



/////////////////////////////�ж��������������򣬻�����������������������֮��ĵ��ù�ϵ����������
