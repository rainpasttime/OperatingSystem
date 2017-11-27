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

//展示最初的界面，用户选择用哪种方式进行组织
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

    //当用户输入的数字不在 1~4 的范围之内的时候，一直提示输入，知道用户输入正确为止。
    do {
        printf("请选择1~4\n");
        scanf("%s",&select);//选项
    } while( !(49 <= select && select <= 52) );

    //根据所选择的组织方式展示下一步的选择界面
    switch(select) {
		case '1':
			printf("     最坏匹配\n");
			DisplayInput(1);
			releaseAll();
            initStorage();
            DisplayMain();
			break;
		case '2':
			printf("     最优匹配\n");
		    DisplayInput(2);
		    releaseAll();
            initStorage();
            DisplayMain();
			break;
		case '3':
			printf("     最先匹配\n");
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

//展示下一级的界面，选择索要进行的行动。
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
		    printf("请选择1~5\n");
            scanf("%s",&select);//选项
		} while( !(49 <= select && select <= 53) );

		 switch(select) {
		     case '1':
		         printf("     空闲内存情况\n");
			     DisplayStorage(idle);
			     DisplayInput(choose);
			     break;
             case '2':
                 printf("     占用内存情况\n");
			     DisplayStorage(occupy);
			     DisplayInput(choose);
                 break;
             case '3':
                 printf("     请求内存\n");
                 printf("输入内存大小：\n");
			     scanf("%d",&apply);
			     ApplyStorage(choose,apply);
			     DisplayInput(choose);
			     break;
		     case '4':
			     printf("     回收内存\n");
                 printf("输入回收内存的编号：\n");
			     scanf("%s",&Number);
		         RecycleStorage(choose,Number);
		         DisplayInput(choose);
			     break;
		     default:
			     break;
    }
}

/*展示内存的情况。
**传入的参数是自定义的数据结构的指针。
**如果传入的是空闲块的指针，则展示空闲块情况。
**如果传入的是占用块的指针，则展示占用块情况。
*/
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
		printf("|");

		printf("%s",tem->number);
		print_space( 8- strlen(tem->number));
		printf("|\n");

		tem = tem->next;

	}
	 printf("|--------|--------|--------|\n");
	 printf("\n");
}

//输出空格，以便对齐文本
void print_space(int num){
	int i;
	for (i=0; i<num; i++) {
		printf(" ");
	}
}

/*
**初始化内存块。
**mainStorage是定义在头文件里面的全局变量。
**初始地址是0
**初始长度是32KB
**初始的占用内存块为空
*/
void initStorage()
{
    copyChar(ADDRESS,mainStorage.address);          //初始地址是0
    copyChar(MAX_LENGTH,mainStorage.length);       //长度是32KB
    copyChar("1",mainStorage.number);
    mainStorage.next = NULL;
    mainStorage.tag = 0;
    copyChar("1",mainStorage.number);
    idle = &mainStorage;
    occupy = NULL;
}

/*
**申请内存的函数
**传入两个参数，参数1代表选择的组织方式，参数2代表申请的内存大小
**firstTem的变量是用来指向被分配内存的空闲块的前一个空闲块。
**newApply是指向新分配内存的指针。
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
        //获取当前空闲块的长度，从1字符串转化成为整型
        length = atoi(tem->length);
        //当空闲块大小大于申请的内存大小。
        if(length>=apply)
        {
            while(firstTem!=NULL && firstTem->next!=tem)
                firstTem = firstTem->next;
            differ = length-apply;
            //如果申请后的剩余值小于门阀值
            if(differ<LIMIT)
            {
                //直接把tem拆下来
                if(tem!=idle)
                    firstTem->next = tem->next;
                else
                    idle = idle->next;
                tem->next = occupy;
                tem->tag = 1;
                occupy = tem;
                break;
            }
            //申请后剩余内存大于门阀值
            else
            {
                newApply = (Storage*)malloc(sizeof(Storage));
                copyChar(tem->address,newApply->address);
                itoa(apply,newApply->length,10);
                newApply->next = occupy;
                newApply->tag = 1;
                occupy = newApply;
                //计算分配之后的空闲块的起始地址
                ComputeAddress(apply,tem);
                itoa(differ,tem->length,10);
                break;
            }
        }
        //没有找到length>apply，继续往后查找。
        tem = tem->next;
    }
    //没有足够内存的时候
    if(tem==NULL)
    {
        printf("Don't have enough storage!ERROR!\n");
        return;
    }
    //分配完内存之后，需要按照选择的组织方式重新给空闲内存块排序
    Rank(choose);
}

//计算分配之后空闲块的初始地址
void ComputeAddress(int apply,Storage *tem)
{
    int address = atoi(tem->address);
    address += apply;
    itoa(address,tem->address,10);
}
/*
**按照传入的参数决定按照什么方法进组织。
**采用的是选择排序。
**ite是进行遍历的
**first指向一轮中的应当排在最前面的节点
**tem指向的是first的前一个节点
**firstHead指向head的前一个节点
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
            //按照内存大小从大到小排序
            if(choose==1)
            {
                //比较字符串，如果字符串长度小，则里面的数字肯定小，如果长度相等，再比较字符串的值
                int flen = strlen(first->length);
                int itlen = strlen(ite->length);
                if(flen<itlen||( flen==itlen && strcmp(first->length,ite->length)<0) )
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            //按照内存大小从小到大排序
            else if(choose==2)
            {
                //比较字符串，如果字符串长度小，则里面的数字肯定小，如果长度相等，再比较字符串的值
                int flen = strlen(first->length);
                int itlen = strlen(ite->length);
                if(flen>itlen||( flen==itlen && strcmp(first->length,ite->length)>0) )
                {
                    first = ite;
                    while(tem->next!=ite)
                        tem = tem->next;
                }
            }
            //按照内存地址从小到大排序
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
        //当找到了需要排在前面的内存块，修改指针，改变他们的顺序。
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
    //按照所选择的算法整理了内存块之后需要重新编号
    AllocateNumber();
}

/*回收算法.
**传入两个参数，参数1代表选择的组织方式，参数2代表回收的内存你的编号
**tem进行遍历，指向需要被回收的内存
**first指向需要被回收的内存的前一个内存
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
     //找不到用户想要回收的内存编号
    if(tem==NULL)
    {
        printf("The number is wrong!ERROR!\n");
        return;
    }
    Union(choose);
}

/*整理判断上下相邻的合并
**时间复杂度是O(n^2)
**双重循环，第一重循环，针对每一个head，用ite遍历一遍空闲块查看是否有head的下相邻。
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
        //计算下邻
        next = atoi(head->address);
        next += atoi(head->length);
        while(ite!=NULL)
        {
            //计算是否是当前节点的下相邻
            int tem = atoi(ite->address);
            //此时ite指向的节点是head指向节点的下相邻
            if(tem==next)
            {
                //如果需要被合并的是idle指向的节点，需要改变idle指针
                if(ite==idle)
                {
                    idle = idle->next;
                    //计算合并之后的空闲内存块长度。
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
                    //计算合并之后的空闲内存块长度。
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

//把a数组中的值拷贝到b数组中去
void copyChar(char *a,char *b)
{
    int i;
    for(i=0;i<strlen(a);i++)
    {
        b[i] = a[i];
    }
    b[i] = '\0';
}
//用户选择退出之后，释放全部动态申请的空间。
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
//分配回收之后给内存块重新编号
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

