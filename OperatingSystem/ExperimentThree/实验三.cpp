/*
*内存动态分区之后三种组织方式：
                              1.从大到小链接则是最坏匹配
                              2.从小到大链接则是最适应匹配
                              3.按地址大小从小到大则是最先匹配
*界面显示：选择匹配方式->输入需要的大小
函数：DisplayMain:显示用户交互主界面

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
    printf("|----------选择匹配方法----------|\n");
    printf("  1.最坏匹配\n");
    printf("  2.最优匹配\n");
    printf("  3.最先匹配\n");
    printf("  4.退出\n");
    printf("|-------------------------|\n");
    printf("请选择1~4\n");
    do {
        scanf("%s",&select);//选项
    } while( !(49 <= select && select <= 52) );

    switch(select) {
		case '1':
			printf("     最坏匹配\n");
			DisplayInput(1);
			break;
		case '2':
			printf("     最优匹配\n");
		    DisplayInput(2);
			break;
		case '3':
			printf("     最先匹配\n");
		    DisplayInput(3);
			break;
		case '4':
			break;
    }
}

void DisplayInput(int choose)
{
        char select;
        printf("|----------菜 单----------|\n");
		printf("  1.显示空闲内存状态\n");
		printf("  2.显示占用内存\n");
		printf("  3.请求内存\n");
		printf("  4.回收内存\n");
		printf("  5.退出\n");
		printf("|-------------------------|\n");
		printf("请选择1~5\n");

		do {
			scanf("%s",&select);//选项
		} while( !(49 <= select && select <= 53) );

		 switch(select) {
		     case '1':
		         printf("     空闲内存情况\n");
			     DisplayStorage(idle);
			     break;
             case '2':
                 printf("     占用内存情况\n");
			     DisplayStorage(occupy);
                 break;
             case '3':
                 printf("     请求内存\n");
                 printf("输入内存大小：\n");
			     scanf("%d",&apply);
			     ApplyStorage(choose,apply);
			     break;
		     case '4':
			     printf("     回收内存\n");
                 printf("输入回收内存的编号：\n");
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
	printf("|  地址  |  长度  |  编号  |\n");
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
    mainStorage.address = ADDRESS;                  //初始地址是0
    mainStorage.length = MAX_LENGTH;               //长度是32KB
    mainStorage.next = NULL;
    mainStorage.tag = 0;
    mainStorage.number = "1";
    idle = &mainStorage;
    occupy = NULL;
}
void print_space(int num){//输出空格，以便对齐文本
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
        //当空闲块大小大于申请的内存大小。
        if(length>apply)
        {
            differ = length-apply;
            //如果申请后的剩余值小于门阀值
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
            //申请后剩余内存大于门阀值
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
                ComputeAddress(apply);  //计算分配之后的空闲块的起始地址
                itoa(differ,idle->length,3);
                break;
            }
        }
        //没有找到继续往后查找。
        tem = tem->next;
    }
    //没有足够内存的时候
    if(tem==NULL)
    {
        printf("Don't have enough storage!ERROR!\n");
        return;
    }
    //分配完内存之后查看空闲块是否有需要上下相邻需要合并的
    Union(choose);
}

//计算分配之后空闲块的初始地址
void ComputeAddress(int apply)
{
    int address = atoi(idle->address);
    address += apply;
    itoa(address,idle->address,5);
}
//按照传入的参数决定按照什么方法进组织。
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
            //按照长度从大到小排序
            if(choose==1)
            {
                if(first->length < ite->length)
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            //按照长度从小到大排序
            else if(choose==2)
            {
                if(first->length > ite->length)
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            //按照地址从小到大排序
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

//回收算法，回收相应编号的内存之后，要根据上下邻整理空闲内存，重新计算大小，并且按照不同的组织形式整理内存。
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
//整理判断是否有上下相邻的部分
void Union(int choose)
{
    Storage *head;
    Storage *ite;
    head = idle;
    while(head!=NULL)
    {
        ite = idle;
        //计算下邻
        int next = atoi(head->address);
        next += atoi(head->length);
        while(ite!=NULL)
        {
            //计算是否是当前节点的下相邻
            int tem = atoi(ite->address);
            if(tem==next)
            {
                Storage *t = idle;
                while(t->next!=ite)
                    t = t->next;
                t->next = ite->next;
                //计算合并之后的空闲内存块长度。
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



/////////////////////////////判断是先整理再排序，还是先排序再整理！！！！！之间的调用关系！！！！！
