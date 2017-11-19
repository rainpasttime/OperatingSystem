#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define LIMIT 1                //�����ŷ�ֵ��1
#define ADDRESS "0"            //�����ʼ��ַ��0
#define MAX_LENGTH "32"        //�����ڴ��С��32KB

//�ڴ��ṹ��1�Ķ���
typedef struct Storage{
    char number[32];              //��ţ���������ڴ�
    char address[32];            //����ڴ����ʼ��ַ
    char length[3];             //����ڴ�ĳ��ȣ���λKB��
	struct Storage *next;      //��һ���ڴ���ָ��
    int tag;                   //�Ƿ���еı�־
}Storage;

Storage *idle;
Storage *occupy;
int apply;                    //��¼�����ڴ�Ĵ�С
char Number[32];      //��¼Ҫ���յ��ڴ�ı��
Storage mainStorage;          //�տ�ʼ��û�з���ʱ���ڴ档
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
