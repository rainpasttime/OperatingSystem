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

//������������ֱ�����˴�СΪ1,2,3��ҳ��
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

    //�����ļ��е�һ���������У���1��ҳ����ʱ����
    getline(readfile,stringInput);
    lengthOfI = getInputArray(stringInput);
    printf("һ��ҳ��������㷨�µ������\n");
    OPT(smallSize,inputQueue,1,lengthOfI);
    initZero(smallSize,1);
    printf("ͬ�������£��������ʹ���㷨�µ������\n");
    LRU(smallSize,inputQueue,1,lengthOfI);
    initZero(inputQueue,lengthOfI);
    printf("ͬ�������£��Ƚ��ȳ��㷨�µ������\n");
    FIFO(smallSize,inputQueue,1,lengthOfI);
    initZero(inputQueue,lengthOfI);

    //�����ļ��еڶ����������У���2��ҳ����ʱ����
    getline(readfile,stringInput);
    lengthOfI = getInputArray(stringInput);
    printf("����ҳ��������㷨�µ������\n");
    OPT(mediumSize,inputQueue,2,lengthOfI);
    initZero(mediumSize,2);
    printf("ͬ�������£��������ʹ���㷨�µ������\n");
    LRU(mediumSize,inputQueue,2,lengthOfI);
    initZero(mediumSize,2);
    printf("ͬ�������£��Ƚ��ȳ��㷨�µ������\n");
    FIFO(mediumSize,inputQueue,2,lengthOfI);
    initZero(inputQueue,lengthOfI);


    //�����ļ��е������������У���3��ҳ����ʱ����
    getline(readfile,stringInput);
    lengthOfI = getInputArray(stringInput);
    printf("����ҳ��������㷨�µ������\n");
    OPT(bigSize,inputQueue,3,lengthOfI);
    initZero(bigSize,3);
    printf("ͬ�������£��������ʹ���㷨�µ������\n");
    LRU(bigSize,inputQueue,3,lengthOfI);
    initZero(bigSize,3);
    printf("ͬ�������£��Ƚ��ȳ��㷨�µ������\n");
    FIFO(bigSize,inputQueue,3,lengthOfI);

    printf("����ͬ�������룬����4��ҳ����Ƚ��ȳ����㷨��\n");
    FIFO(hugeSize,inputQueue,4,lengthOfI);
    printf("�������Belady����");

    readfile.close();
    return 0;
}



/*�ж��Ƿ����У������ǰ�����ҳ�����ڴ����棬�򷵻��±꣬���򷵻�-1
  ������page�����ǵ�ǰ�ڴ������ҳ��
        lengthOfP������page����ĳ���
        number�ǵ�ǰ�����ҳ��
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
**�ж��Ƿ��пյ�ҳ�棬�Ǿͷ����±꣬���򷵻�-1
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
**���ҳ���㷨
**������
**       page����ǰ�ڴ������ҳ��
**       input��������˳��
**       lengthOfP�����ڴ���Դ洢��ҳ�����
**       lengthOfI���������ҳ�����
**��ʱ������
         farLocate������Զ�������õ���ҳ�����page����������±�
         tag���鳤����lengthOfPһ����������ҳ�潫���Ƿ��õ�
         number����ȱҳ����
         hitTag����Ƿ�����
         emptyTag�洢-1��ʾû�п�ҳ�棬���������ǿ�ҳ����±�
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

    //չʾ����ͷ��
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

        //û�����У������пյ�ҳ��
        if(hitTag==-1 && emptyTag!=-1)
        {
            page[emptyTag] = tem;
            number++;
        }
        //���û�����в���û�пյ�ҳ��
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
            //��ҳ���Ժ��ò���������̭��ҳ��
            for(j=0;j<lengthOfP;j++)
            {
                //flagΪtrue��ʾĿǰû���ҵ�����Ҫ�õ�ҳ��,��j�ǵ�һ�����õ�ҳ����±�
                if(flag && tag[j]==-1)
                {
                    //cout<<"input "<<tem<<"    page[j] "<<page[j]<<endl;
                    page[j]=tem;
                    //�ҵ�һ������Ҫ�õ�ҳ��
                    flag = false;
                }
                //���°�tag��Ϊ0
                tag[j]=-1;
            }
            //��̭��Զ�������õ���ҳ��
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
    //չʾ����β��
    if(lengthOfP==1)
        DisplayHeadTitleOne(2);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(2);
    else
        DisplayHeadTitleThree(2);

    printf("ȱҳ������%d\n",number);
    delete tag;
}

/*
**�Ƚ��ȳ�ҳ���㷨
**������
**       page����ǰ�ڴ������ҳ��
**       input��������˳��
**       lengthOfP�����ڴ���Դ洢��ҳ�����
**       lengthOfI���������ҳ�����
**��ʱ������
         number����ȱҳ����
         hitTag����Ƿ�����
         emptyTag�洢-1��ʾû�п�ҳ�棬���������ǿ�ҳ����±�
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

    //չʾ����ͷ��
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

        //û�����У������пյ�ҳ��
        if(hitTag==-1 && emptyTag!=-1)
        {
            page[emptyTag] = tem;
            number++;
        }
        //���û�����в���û�пյ�ҳ��
        else if(hitTag==-1 && emptyTag==-1)
        {
            number++;
            //��1��ҳ��װ������ɵ�ҳ��
            for(j=0;j<lengthOfP-1;j++)
            {
                page[j] = page[j+1];
            }
            //���һ��ҳ��װ�ո�û�����е�ҳ��
            page[lengthOfP-1] = tem;
        }
        Display(page,lengthOfP,input,i);
    }
    //չʾ����β��
    if(lengthOfP==1)
        DisplayHeadTitleOne(2);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(2);
    else if(lengthOfP==3)
        DisplayHeadTitleThree(2);
    else
        DisplayHeadTitleFour(2);

    printf("ȱҳ������%d\n",number);

}


/*
**�������ʹ��ҳ���㷨
**������
**       page����ǰ�ڴ������ҳ��
**       input��������˳��
**       lengthOfP�����ڴ���Դ洢��ҳ�����
**       lengthOfI���������ҳ�����
**��ʱ������
         number����ȱҳ����
         hitTag����Ƿ�����
         emptyTag�洢-1��ʾû�п�ҳ�棬���������ǿ�ҳ����±�
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

    //չʾ����ͷ��
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

        //û�����У������пյ�ҳ��
        if(hitTag==-1 && emptyTag!=-1)
        {
            page[emptyTag] = tem;
            number++;
        }
        //���û�����в���û�пյ�ҳ��
        else if(hitTag==-1 && emptyTag==-1)
        {
            number++;
            //��1��ҳ��װ������ɵ�ҳ��
            for(j=0;j<lengthOfP-1;j++)
            {
                page[j] = page[j+1];
            }
            //���һ��ҳ��װ�ո�û�����е�ҳ��
            page[lengthOfP-1] = tem;
        }
        //�����е�ʱ��Ҫ��������е�ҳ��ı�λ�ã�����һ�����µ�ҳ��
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
    //չʾ����β��
    if(lengthOfP==1)
        DisplayHeadTitleOne(2);
    else if(lengthOfP==2)
        DisplayHeadTitleTwo(2);
    else
        DisplayHeadTitleThree(2);

    printf("ȱҳ������%d\n",number);

}


//������������Ϊ0
void initZero(int* arrayT,int length)
{
    int i;
    for(i=0;i<length;i++)
    {
        arrayT[i]=0;
    }
}

//���ļ����������е��ַ�������ת����Ϊint������
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

 //����ո��Ա�����ı�
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
	    printf("|  ����  |  ҳ��1 |\n");
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
	    printf("|  ����  |  ҳ��1 |  ҳ��2 |\n");
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
	    printf("|  ����  |  ҳ��1 |  ҳ��2 |  ҳ��3 |\n");
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
	    printf("|  ����  |  ҳ��1 |  ҳ��2 |  ҳ��3 |  ҳ��4 |\n");
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

    //��ӡ��ǰ�����ҳ��
    itoa(input[locate],tem,10);
    printf("%s",tem);
    print_space( 8- strlen(tem));
    printf("|");

    //��ӡ��ǰ�ڴ���ҳ���״̬
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




