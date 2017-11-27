#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>


#define MAX_LENGTH  20
using namespace std;



int Hit(int *page,int lengthOfP,int numebr);
int Empty(int* page,int lengthOfP);
void Display(int *page,int lengthOfP,int *input,int locate);
void DisplayHeadTitleOne(int i);
void DisplayHeadTitleTwo(int i);
void DisplayHeadTitleThree(int i);
void DisplayHeadTitleFour(int i);
void print_space(int num);
void OPT(int *page,int *input,int lengthOfP,int lengthOfI);
void FIFO(int* page,int* input,int lengthOfP,int lengthOfI);
void LRU(int* page,int* input,int lengthOfP,int lengthOfI);
void initZero(int* arrayT,int length);
int getInputArray(string stringInput);

//下面三个数组分别代表了大小为1,2,3的页框
int smallSize[1]={0};
int mediumSize[2]={0,0};
int bigSize[3]={0,0,0};
int hugeSize[4]={0,0,0,0};
int inputQueue[MAX_LENGTH];

int main()
{
    string stringInput;
    ifstream readfile;
    readfile.open("input.txt", ios::in);
    int lengthOfI;

    //读入文件中第一行输入序列，用1个页面框的时候处理
    getline(readfile,stringInput);
    lengthOfI = getInputArray(stringInput);
    printf("一个页面框，理想算法下的情况：\n");
    OPT(smallSize,inputQueue,1,lengthOfI);
    initZero(smallSize,1);
    printf("同样条件下，最近最少使用算法下的情况：\n");
    LRU(smallSize,inputQueue,1,lengthOfI);
    initZero(inputQueue,lengthOfI);
    printf("同样条件下，先进先出算法下的情况：\n");
    FIFO(smallSize,inputQueue,1,lengthOfI);
    initZero(inputQueue,lengthOfI);

    //读入文件中第二行输入序列，用2个页面框的时候处理
    getline(readfile,stringInput);
    lengthOfI = getInputArray(stringInput);
    printf("两个页面框，理想算法下的情况：\n");
    OPT(mediumSize,inputQueue,2,lengthOfI);
    initZero(mediumSize,2);
    printf("同样条件下，最近最少使用算法下的情况：\n");
    LRU(mediumSize,inputQueue,2,lengthOfI);
    initZero(mediumSize,2);
    printf("同样条件下，先进先出算法下的情况：\n");
    FIFO(mediumSize,inputQueue,2,lengthOfI);
    initZero(inputQueue,lengthOfI);


    //读入文件中第三行输入序列，用3个页面框的时候处理
    getline(readfile,stringInput);
    lengthOfI = getInputArray(stringInput);
    printf("三个页面框，理想算法下的情况：\n");
    OPT(bigSize,inputQueue,3,lengthOfI);
    initZero(bigSize,3);
    printf("同样条件下，最近最少使用算法下的情况：\n");
    LRU(bigSize,inputQueue,3,lengthOfI);
    initZero(bigSize,3);
    printf("同样条件下，先进先出算法下的情况：\n");
    FIFO(bigSize,inputQueue,3,lengthOfI);

    printf("上面同样的输入，分配4个页面框，先进先出的算法“\n");
    FIFO(hugeSize,inputQueue,4,lengthOfI);
    printf("则出现了Belady现象");

    readfile.close();
    return 0;
}



/*判断是否命中，如果当前输入的页面在内存里面，则返回下标，否则返回-1
  参数：page数组是当前内存里面的页面
        lengthOfP整型是page数组的长度
        number是当前输入的页面
*/
int Hit(int *page,int lengthOfP,int number)
{
    int i;
    for(i=0;i<lengthOfP;i++)
    {
        if(page[i]==number)
            return i;
    }
    return (-1);
}

/*
**判断是否有空的页面，是就返回下标，否则返回-1
*/
int Empty(int* page,int lengthOfP)
{
    int i;
    for(i=0;i<lengthOfP;i++)
    {
        if(page[i]==0)
            return i;
    }
    return -1;
}

/*
**最佳页面算法
**参数：
**       page代表当前内存里面的页面
**       input代表输入顺序
**       lengthOfP代表内存可以存储的页面个数
**       lengthOfI代表输入的页面个数
**临时变量：
         farLocate代表最远将来采用到的页面的在page数组里面的下标
         tag数组长度与lengthOfP一样，标记这个页面将来是否用到
         number计算缺页次数
         hitTag标记是否命中
         emptyTag存储-1表示没有空页面，否则里面是空页面的下标
*/
void OPT(int *page,int *input,int lengthOfP,int lengthOfI)
{
    int number=0;
    int i;
    int j;
    int t;
    int tem;
    bool flag;
    int hitTag;
    int emptyTag;
    int *tag;
    int farLocate;

    tag = new int[lengthOfP];
    for(i=0;i<lengthOfP;i++)
    {
        tag[i]=-1;
    }

    //展示表格的头部
    if(lengthOfP==1)
        DisplayHeadTitleOne(1);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(1);
    else
        DisplayHeadTitleThree(1);


    for(i=0;i<lengthOfI;i++)
    {
        tem = input[i];
        flag = true;

        hitTag = Hit(page,lengthOfP,tem);
        emptyTag = Empty(page,lengthOfP);

        //没有命中，但是有空的页面
        if(hitTag==-1 && emptyTag!=-1)
        {
            page[emptyTag] = tem;
            number++;
        }
        //如果没有命中并且没有空的页面
        else if(hitTag==-1 && emptyTag==-1)
        {
            number++;
            for(j=i+1;j<lengthOfI;j++)
            {
                for(t=0;t<lengthOfP;t++)
                {
                    if(page[t]==input[j]&&tag[t]==-1)
                    {
                        tag[t] = j;
                        //cout<<"input "<<tem<<"     farLocate "<<farLocate<<endl;
                    }
                }
            }
            //有页面以后用不到，就淘汰该页面
            for(j=0;j<lengthOfP;j++)
            {
                //flag为true表示目前没有找到不需要用的页面,则j是第一个不用的页面的下标
                if(flag && tag[j]==-1)
                {
                    //cout<<"input "<<tem<<"    page[j] "<<page[j]<<endl;
                    page[j]=tem;
                    //找到一个不需要用的页面
                    flag = false;
                }
                //重新把tag置为0
                tag[j]=-1;
            }
            //淘汰最远将来才用到的页面
            if(flag)
            {
                farLocate = 0;
                //cout<<"input "<<tem<<"    farLocate "<<farLocate<<endl;
                for(j=1;j<lengthOfP;j++)
                {
                    if(tag[j]>tag[farLocate])
                        farLocate = j;
                }
                page[farLocate] = tem;
            }
        }
        Display(page,lengthOfP,input,i);
    }
    //展示表格的尾部
    if(lengthOfP==1)
        DisplayHeadTitleOne(2);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(2);
    else
        DisplayHeadTitleThree(2);

    printf("缺页次数：%d\n",number);
    delete tag;
}

/*
**先进先出页面算法
**参数：
**       page代表当前内存里面的页面
**       input代表输入顺序
**       lengthOfP代表内存可以存储的页面个数
**       lengthOfI代表输入的页面个数
**临时变量：
         number计算缺页次数
         hitTag标记是否命中
         emptyTag存储-1表示没有空页面，否则里面是空页面的下标
*/
void FIFO(int* page,int* input,int lengthOfP,int lengthOfI)
{
    int number=0;
    int i;
    int j;
    int t;
    int tem;
    int hitTag;
    int emptyTag;

    //展示表格的头部
    if(lengthOfP==1)
        DisplayHeadTitleOne(1);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(1);
    else if(lengthOfP==3)
        DisplayHeadTitleThree(1);
    else
        DisplayHeadTitleFour(1);

    for(i=0;i<lengthOfI;i++)
    {
        tem = input[i];
        hitTag = Hit(page,lengthOfP,tem);
        emptyTag = Empty(page,lengthOfP);

        //没有命中，但是有空的页面
        if(hitTag==-1 && emptyTag!=-1)
        {
            page[emptyTag] = tem;
            number++;
        }
        //如果没有命中并且没有空的页面
        else if(hitTag==-1 && emptyTag==-1)
        {
            number++;
            //第1个页面装的是最旧的页面
            for(j=0;j<lengthOfP-1;j++)
            {
                page[j] = page[j+1];
            }
            //最后一个页面装刚刚没有命中的页面
            page[lengthOfP-1] = tem;
        }
        Display(page,lengthOfP,input,i);
    }
    //展示表格的尾部
    if(lengthOfP==1)
        DisplayHeadTitleOne(2);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(2);
    else if(lengthOfP==3)
        DisplayHeadTitleThree(2);
    else
        DisplayHeadTitleFour(2);

    printf("缺页次数：%d\n",number);

}


/*
**最近最少使用页面算法
**参数：
**       page代表当前内存里面的页面
**       input代表输入顺序
**       lengthOfP代表内存可以存储的页面个数
**       lengthOfI代表输入的页面个数
**临时变量：
         number计算缺页次数
         hitTag标记是否命中
         emptyTag存储-1表示没有空页面，否则里面是空页面的下标
*/
void LRU(int* page,int* input,int lengthOfP,int lengthOfI)
{
    int number = 0;
    int i;
    int j;
    int t;
    int tem;
    int change;
    int hitTag;
    int emptyTag;

    //展示表格的头部
    if(lengthOfP==1)
        DisplayHeadTitleOne(1);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(1);
    else
        DisplayHeadTitleThree(1);


    for(i=0;i<lengthOfI;i++)
    {
        tem = input[i];
        hitTag = Hit(page,lengthOfP,tem);
        emptyTag = Empty(page,lengthOfP);

        //没有命中，但是有空的页面
        if(hitTag==-1 && emptyTag!=-1)
        {
            page[emptyTag] = tem;
            number++;
        }
        //如果没有命中并且没有空的页面
        else if(hitTag==-1 && emptyTag==-1)
        {
            number++;
            //第1个页面装的是最旧的页面
            for(j=0;j<lengthOfP-1;j++)
            {
                page[j] = page[j+1];
            }
            //最后一个页面装刚刚没有命中的页面
            page[lengthOfP-1] = tem;
        }
        //当命中的时候，要把这个命中的页面改变位置，当成一个最新的页面
        else if(hitTag!=-1)
        {
            change = page[hitTag];
            for(j=0;j<lengthOfP-1;j++)
            {
                page[j]=page[j+1];
            }
            page[lengthOfP-1] = tem;
        }
        Display(page,lengthOfP,input,i);
    }
    //展示表格的尾部
    if(lengthOfP==1)
        DisplayHeadTitleOne(2);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(2);
    else
        DisplayHeadTitleThree(2);

    printf("缺页次数：%d\n",number);

}


//把数组重新置为0
void initZero(int* arrayT,int length)
{
    int i;
    for(i=0;i<length;i++)
    {
        arrayT[i]=0;
    }
}

//从文件的输入序列的字符串数组转换成为int型数组
int getInputArray(string stringInput)
{
    int lengthOfI = 0;
    int i=0;
    int tag=0;
    int oneNumber;
    while(stringInput[i]==' ')
        i++;
    for(;stringInput[i]!='\0';)
    {
        oneNumber=0;
        while(stringInput[i]!=' '&&stringInput[i]!='\0')
        {
            int tem=stringInput[i]-'0';
            oneNumber = oneNumber*10+(stringInput[i]-'0');
            i++;
        }
        inputQueue[lengthOfI++] = oneNumber;
            while( stringInput[i]==' ')
            {
                i++;
            }
    }
    return lengthOfI;
}

 //输出空格，以便对齐文本
void print_space(int num){
	int i;
	for (i=0; i<num; i++) {
		printf(" ");
	}
}

void DisplayHeadTitleOne(int i)
{
    if(i==1)
    {
        printf("|--------|--------|\n");
	    printf("|  输入  |  页面1 |\n");
        printf("|--------|--------|\n");
        return;
    }
    else
    {
        printf("|--------|--------|\n");
        return;
    }
}

void DisplayHeadTitleTwo(int i)
{
    if(i==1)
    {
        printf("|--------|--------|--------|\n");
	    printf("|  输入  |  页面1 |  页面2 |\n");
        printf("|--------|--------|--------|\n");
        return;
    }
    else
    {
        printf("|--------|--------|--------|\n");
    }
}

void DisplayHeadTitleThree(int i)
{
    if(i==1)
    {
        printf("|--------|--------|--------|--------|\n");
	    printf("|  输入  |  页面1 |  页面2 |  页面3 |\n");
        printf("|--------|--------|--------|--------|\n");
        return;
    }
    else
    {
        printf("|--------|--------|--------|--------|\n");
    }
}

void DisplayHeadTitleFour(int i)
{
    if(i==1)
    {
        printf("|--------|--------|--------|--------|--------|\n");
	    printf("|  输入  |  页面1 |  页面2 |  页面3 |  页面4 |\n");
        printf("|--------|--------|--------|--------|--------|\n");
        return;
    }
    else
    {
        printf("|--------|--------|--------|--------|--------|\n");
    }
}

void Display(int *page,int lengthOfP,int *input,int locate)
{
    int i;
    char tem[3];

    printf("|");

    //打印当前输入的页面
    itoa(input[locate],tem,10);
    printf("%s",tem);
    print_space( 8- strlen(tem));
    printf("|");

    //打印当前内存中页面的状态
    for(i=0;i<lengthOfP;i++)
    {
        if(page[i]!=0)
        {
            itoa(page[i],tem,10);
            printf("%s",tem);
            print_space( 8- strlen(tem));
            printf("|");
        }
        else
        {
            printf("        ");
            printf("|");
        }
    }
    printf("\n");
}




