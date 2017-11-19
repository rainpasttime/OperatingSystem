#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define LIMIT 1                //定义门阀值是1
#define ADDRESS "0"            //定义初始地址是0
#define MAX_LENGTH "32"        //定义内存大小是32KB

//内存块结构体1的定义
typedef struct Storage{
    char number[32];              //编号，方便回收内存
    char address[32];            //这个内存的起始地址
    char length[3];             //这个内存的长度（单位KB）
	struct Storage *next;      //下一个内存块的指针
    int tag;                   //是否空闲的标志
}Storage;

Storage *idle;
Storage *occupy;
int apply;                    //记录申请内存的大小
char Number[32];      //记录要回收的内存的编号
Storage mainStorage;          //刚开始还没有分配时的内存。
void DisplayMain();
void DisplayInput(int choose);
void DisplayStorage(Storage *head);
void initStorage();
void ApplyStorage(int choose,int apply);
void ComputeAddress(int apply,Storage *tem);
void Rank(int choose);
void RecycleStorage(int choose,char *snumber);
void Union(int choose);
void print_space(int num);
void copyChar(char *a,char *b);
