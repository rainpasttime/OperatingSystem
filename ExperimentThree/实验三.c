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

//չʾ����Ľ��棬�û�ѡ�������ַ�ʽ������֯
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

    //���û���������ֲ��� 1~4 �ķ�Χ֮�ڵ�ʱ��һֱ��ʾ���룬֪���û�������ȷΪֹ��
    do {
        printf("��ѡ��1~4\n");
        scanf("%s",&select);//ѡ��
    } while( !(49 <= select && select <= 52) );

    //������ѡ�����֯��ʽչʾ��һ����ѡ�����
    switch(select) {
		case '1':
			printf("     �ƥ��\n");
			DisplayInput(1);
			releaseAll();
            initStorage();
            DisplayMain();
			break;
		case '2':
			printf("     ����ƥ��\n");
		    DisplayInput(2);
		    releaseAll();
            initStorage();
            DisplayMain();
			break;
		case '3':
			printf("     ����ƥ��\n");
		    DisplayInput(3);
		    releaseAll();
            initStorage();
            DisplayMain();
            break;
        default:
			break;
    }
    releaseAll();
}

//չʾ��һ���Ľ��棬ѡ����Ҫ���е��ж���
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
		    printf("��ѡ��1~5\n");
            scanf("%s",&select);//ѡ��
		} while( !(49 <= select && select <= 53) );

		 switch(select) {
		     case '1':
		         printf("     �����ڴ����\n");
			     DisplayStorage(idle);
			     DisplayInput(choose);
			     break;
             case '2':
                 printf("     ռ���ڴ����\n");
			     DisplayStorage(occupy);
			     DisplayInput(choose);
                 break;
             case '3':
                 printf("     �����ڴ�\n");
                 printf("�����ڴ��С��\n");
			     scanf("%d",&apply);
			     ApplyStorage(choose,apply);
			     DisplayInput(choose);
			     break;
		     case '4':
			     printf("     �����ڴ�\n");
                 printf("��������ڴ�ı�ţ�\n");
			     scanf("%s",&Number);
		         RecycleStorage(choose,Number);
		         DisplayInput(choose);
			     break;
		     default:
			     break;
    }
}

/*չʾ�ڴ�������
**����Ĳ������Զ�������ݽṹ��ָ�롣
**���������ǿ��п��ָ�룬��չʾ���п������
**����������ռ�ÿ��ָ�룬��չʾռ�ÿ������
*/
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
		printf("|");

		printf("%s",tem->number);
		print_space( 8- strlen(tem->number));
		printf("|\n");

		tem = tem->next;

	}
	 printf("|--------|--------|--------|\n");
	 printf("\n");
}

//����ո��Ա�����ı�
void print_space(int num){
	int i;
	for (i=0; i<num; i++) {
		printf(" ");
	}
}

/*
**��ʼ���ڴ�顣
**mainStorage�Ƕ�����ͷ�ļ������ȫ�ֱ�����
**��ʼ��ַ��0
**��ʼ������32KB
**��ʼ��ռ���ڴ��Ϊ��
*/
void initStorage()
{
    copyChar(ADDRESS,mainStorage.address);          //��ʼ��ַ��0
    copyChar(MAX_LENGTH,mainStorage.length);       //������32KB
    copyChar("1",mainStorage.number);
    mainStorage.next = NULL;
    mainStorage.tag = 0;
    copyChar("1",mainStorage.number);
    idle = &mainStorage;
    occupy = NULL;
}

/*
**�����ڴ�ĺ���
**������������������1����ѡ�����֯��ʽ������2����������ڴ��С
**firstTem�ı���������ָ�򱻷����ڴ�Ŀ��п��ǰһ�����п顣
**newApply��ָ���·����ڴ��ָ�롣
*/
void ApplyStorage(int choose,int apply)
{
    Storage *tem = idle;
    Storage *newApply;
    Storage *firstTem = idle;
    int length;
    int differ;
    char len[5];
    while(tem!=NULL)
    {
        //��ȡ��ǰ���п�ĳ��ȣ���1�ַ���ת����Ϊ����
        length = atoi(tem->length);
        //�����п��С����������ڴ��С��
        if(length>=apply)
        {
            while(firstTem!=NULL && firstTem->next!=tem)
                firstTem = firstTem->next;
            differ = length-apply;
            //���������ʣ��ֵС���ŷ�ֵ
            if(differ<LIMIT)
            {
                //ֱ�Ӱ�tem������
                if(tem!=idle)
                    firstTem->next = tem->next;
                else
                    idle = idle->next;
                tem->next = occupy;
                tem->tag = 1;
                occupy = tem;
                break;
            }
            //�����ʣ���ڴ�����ŷ�ֵ
            else
            {
                newApply = (Storage*)malloc(sizeof(Storage));
                copyChar(tem->address,newApply->address);
                itoa(apply,newApply->length,10);
                newApply->next = occupy;
                newApply->tag = 1;
                occupy = newApply;
                //�������֮��Ŀ��п����ʼ��ַ
                ComputeAddress(apply,tem);
                itoa(differ,tem->length,10);
                break;
            }
        }
        //û���ҵ�length>apply������������ҡ�
        tem = tem->next;
    }
    //û���㹻�ڴ��ʱ��
    if(tem==NULL)
    {
        printf("Don't have enough storage!ERROR!\n");
        return;
    }
    //�������ڴ�֮����Ҫ����ѡ�����֯��ʽ���¸������ڴ������
    Rank(choose);
}

//�������֮����п�ĳ�ʼ��ַ
void ComputeAddress(int apply,Storage *tem)
{
    int address = atoi(tem->address);
    address += apply;
    itoa(address,tem->address,10);
}
/*
**���մ���Ĳ�����������ʲô��������֯��
**���õ���ѡ������
**ite�ǽ��б�����
**firstָ��һ���е�Ӧ��������ǰ��Ľڵ�
**temָ�����first��ǰһ���ڵ�
**firstHeadָ��head��ǰһ���ڵ�
***/
void Rank(int choose)
{
    Storage *tem;
    Storage *head;
    Storage *first;
    Storage *ite;
    Storage *firstHead;
    head = idle;
    while(head!=NULL)
    {
        Storage *firstHead = idle;
        tem = head;
        first = head;
        ite = head->next;
        while(ite!=NULL)
        {
            //�����ڴ��С�Ӵ�С����
            if(choose==1)
            {
                //�Ƚ��ַ���������ַ�������С������������ֿ϶�С�����������ȣ��ٱȽ��ַ�����ֵ
                int flen = strlen(first->length);
                int itlen = strlen(ite->length);
                if(flen<itlen||( flen==itlen && strcmp(first->length,ite->length)<0) )
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            //�����ڴ��С��С��������
            else if(choose==2)
            {
                //�Ƚ��ַ���������ַ�������С������������ֿ϶�С�����������ȣ��ٱȽ��ַ�����ֵ
                int flen = strlen(first->length);
                int itlen = strlen(ite->length);
                if(flen>itlen||( flen==itlen && strcmp(first->length,ite->length)>0) )
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            //�����ڴ��ַ��С��������
            else
            {
                int flen = strlen(first->address);
                int itlen = strlen(ite->address);
                if(flen>itlen||( flen==itlen && strcmp(first->address,ite->address)>0) )
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            ite = ite->next;
        }
        //���ҵ�����Ҫ����ǰ����ڴ�飬�޸�ָ�룬�ı����ǵ�˳��
        if(first!=head)
        {
            tem->next = first->next;
            if(idle==head)
            {
                first->next = head;
                idle = first;
            }
            else
            {
                while(firstHead!=NULL && firstHead->next!=head)
                      firstHead=firstHead->next;
                first->next = head;
                firstHead->next = first;
            }
        }
        else
        {
            head = head->next;
        }
    }
    //������ѡ����㷨�������ڴ��֮����Ҫ���±��
    AllocateNumber();
}

/*�����㷨.
**������������������1����ѡ�����֯��ʽ������2������յ��ڴ���ı��
**tem���б�����ָ����Ҫ�����յ��ڴ�
**firstָ����Ҫ�����յ��ڴ��ǰһ���ڴ�
**
*/
void RecycleStorage(int choose,char *number)
{
    Storage *tem;
    Storage *first;
    tem = occupy;
    first = occupy;
    int num = atoi(number);
    while(tem!=NULL)
    {
        int nu =atoi(tem->number);
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
            break;
        }
        else
        {
            first = tem;
            tem = tem->next;
        }
     }
     //�Ҳ����û���Ҫ���յ��ڴ���
    if(tem==NULL)
    {
        printf("The number is wrong!ERROR!\n");
        return;
    }
    Union(choose);
}

/*�����ж��������ڵĺϲ�
**ʱ�临�Ӷ���O(n^2)
**˫��ѭ������һ��ѭ�������ÿһ��head����ite����һ����п�鿴�Ƿ���head�������ڡ�
*/
void Union(int choose)
{
    Storage *head;
    int j;
    int next;
    Storage *ite;
    head = idle;
    while(head!=NULL)
    {
        ite = idle;
        //��������
        next = atoi(head->address);
        next += atoi(head->length);
        while(ite!=NULL)
        {
            //�����Ƿ��ǵ�ǰ�ڵ��������
            int tem = atoi(ite->address);
            //��ʱiteָ��Ľڵ���headָ��ڵ��������
            if(tem==next)
            {
                //�����Ҫ���ϲ�����idleָ��Ľڵ㣬��Ҫ�ı�idleָ��
                if(ite==idle)
                {
                    idle = idle->next;
                    //����ϲ�֮��Ŀ����ڴ�鳤�ȡ�
                    j = atoi(ite->length)+atoi(head->length);
                    itoa(j,head->length,10);
                    free(ite);
                    ite = idle;
                }
                else
                {
                    Storage *t = idle;
                    while(t!=NULL&&t->next!=ite)
                    {
                        t = t->next;
                    }
                    t->next = ite->next;
                    //����ϲ�֮��Ŀ����ڴ�鳤�ȡ�
                    j = atoi(ite->length)+atoi(head->length);
                    itoa(j,head->length,10);
                    free(ite);
                    ite = t->next;
                }
            }
            else
                ite=ite->next;
        }
        head = head->next;
    }
    Rank(choose);
}

//��a�����е�ֵ������b������ȥ
void copyChar(char *a,char *b)
{
    int i;
    for(i=0;i<strlen(a);i++)
    {
        b[i] = a[i];
    }
    b[i] = '\0';
}
//�û�ѡ���˳�֮���ͷ�ȫ����̬����Ŀռ䡣
void releaseAll()
{
    Storage *tem;
    while(idle!=NULL)
    {
        tem = idle->next;
        free(idle);
        idle = tem;
    }
    while(occupy!=  NULL)
    {
        tem = occupy->next;
        free(tem);
        occupy = tem;
    }
}
//�������֮����ڴ�����±��
void AllocateNumber()
{
    Storage *tem = idle;
    int i = 1;
    while(tem!=NULL)
    {
        itoa(i,tem->number,10);
        i++;
        tem = tem->next;
    }
    tem = occupy;
    i = 1;
    while(tem!=NULL)
    {
        itoa(i,tem->number,10);
        i++;
        tem = tem->next;
    }
}

