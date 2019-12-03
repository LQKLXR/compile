#include "def.h"
#include "SyntaxAnalysis.tab.h"

struct ASTNode * mknode(int num,int kind,int pos,...){
    struct ASTNode *T=(struct ASTNode *)calloc(sizeof(struct ASTNode),1);
    int i=0;
    T->kind=kind;
    T->pos=pos;
    va_list pArgs = NULL;
    va_start(pArgs, pos);
    for(i=0;i<num;i++)
        T->ptr[i]= va_arg(pArgs, struct ASTNode *);
    while (i<4) T->ptr[i++]=NULL;
    va_end(pArgs);
    return T;
}


void display(struct ASTNode *T,int indent)
{//�Գ����﷨�����ȸ�����
  int i=1;
  struct ASTNode *T0;
  if (T)
	{
	switch (T->kind) {
		//////
	case EXT_DEF_LIST:  
						display(T->ptr[0],indent);    //��ʾ���ⲿ���壨�ⲿ�����ͺ������б��еĵ�һ��
                        display(T->ptr[1],indent);    //��ʾ���ⲿ�����б��е������ⲿ����
                        break;
	case EXT_VAR_DEF:   
						printf("%*c�ⲿ�������壺(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);        //��ʾ�ⲿ��������
                        printf("%*c��������\n",indent+3,' ');
                        display(T->ptr[1],indent+6);        //��ʾ�����б�
                        break;
	case TYPE:          
                        break;
    case EXT_DEC_LIST:  display(T->ptr[0],indent);     //������ʾ�ⲿ��������
                        display(T->ptr[1],indent);     //����������ͬ�ģ�����ʾ�﷨���˴���������Ժ����ƴ���ϲ�
                        break;
	case FUNC_DEF:      printf("%*c�������壺(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);      //��ʾ������������
                        display(T->ptr[1],indent+3);      //��ʾ�������Ͳ���
                        display(T->ptr[2],indent+3);      //��ʾ������
                        break;
	case FUNC_DEC:      printf("%*c��������%s\n",indent,' ',T->type_id);
                        if (T->ptr[0]) {
                                printf("%*c�����βΣ�\n",indent,' ');
                                display(T->ptr[0],indent+3);  //��ʾ���������б�
                                }
                        else printf("%*c�޲κ���\n",indent+3,' ');
                        break;
	case PARAM_LIST:    display(T->ptr[0],indent);     //������ʾȫ���������ͺ����ƣ�
                        display(T->ptr[1],indent);
                        break;
	case PARAM_DEC:     printf("%*c���ͣ�%s, ��������%s\n",indent,' ',T->ptr[0]->type==INT?"int":"float",T->ptr[1]->type_id);
                        break;
	case EXP_STMT:      printf("%*c����ʽ��䣺(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);
                        break;
	case RETURN:        printf("%*c������䣺(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);
                        break;
	case COMP_STM:      printf("%*c������䣺(%d)\n",indent,' ',T->pos);
                        printf("%*c�������ı������岿�֣�\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //��ʾ���岿��
                        printf("%*c����������䲿�֣�\n",indent+3,' ');
                        display(T->ptr[1],indent+6);      //��ʾ��䲿��
                        break;
	case STM_LIST:      display(T->ptr[0],indent);      //��ʾ��һ�����
                        display(T->ptr[1],indent);        //��ʾʣ�����
                        break;
	case WHILE:         printf("%*cWHILEѭ����䣺(%d)\n",indent,' ',T->pos);
                        printf("%*cWHILEѭ��������\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //��ʾѭ������
                        printf("%*cWHILEѭ���壺(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //��ʾѭ����
                        break;
						//FOR��ʼ
	case FOR:			printf("%*cFORѭ����䣺(%d)\n",indent,' ',T->pos);
                        printf("%*cFORѭ������1��\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //��ʾѭ������1
						printf("%*cFORѭ������2��\n",indent+3,' ');
                        display(T->ptr[1],indent+6);      //��ʾѭ������2
						printf("%*cFORѭ������3��\n",indent+3,' ');
                        display(T->ptr[2],indent+6);      //��ʾѭ������3
                        printf("%*cѭ���壺(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[3],indent+6);      //��ʾѭ����
                        break;
						
	case IF_THEN:       printf("%*c�������(IF_THEN)��(%d)\n",indent,' ',T->pos);
                        printf("%*c������\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //��ʾ����
                        printf("%*cIF�Ӿ䣺(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //��ʾif�Ӿ�
                        break;
	case IF_THEN_ELSE:  printf("%*c�������(IF_THEN_ELSE)��(%d)\n",indent,' ',T->pos);
                        printf("%*c������\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //��ʾ����
                        printf("%*cIF�Ӿ䣺(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //��ʾif�Ӿ�
                        printf("%*cELSE�Ӿ䣺(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[2],indent+6);      //��ʾelse�Ӿ�
                        break;
    case DEF_LIST:      display(T->ptr[0],indent);    //��ʾ�þֲ����������б��еĵ�һ��
                        display(T->ptr[1],indent);    //��ʾ�����ֲ���������
                        break;
    case VAR_DEF:       printf("%*c�ֲ��������壺(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);   //��ʾ��������
                        display(T->ptr[1],indent+3);   //��ʾ�ö����ȫ��������
                        break;
    case DEC_LIST:      printf("%*c��������\n",indent,' ');
                        T0=T;
                        while (T0) {
                            if (T0->ptr[0]->kind==ID)
                                printf("%*c %s\n",indent+6,' ',T0->ptr[0]->type_id);
                            else if (T0->ptr[0]->kind==ASSIGNOP)
                                {
                                printf("%*c %s ASSIGNOP\n ",indent+6,' ',T0->ptr[0]->ptr[0]->type_id);
                                display(T0->ptr[0]->ptr[1],indent+strlen(T0->ptr[0]->ptr[0]->type_id)+7);        //��ʾ��ʼ������ʽ
                                }
                            T0=T0->ptr[1];
                            }
                        break;
	case ID:	        printf("%*cID�� %s\n",indent,' ',T->type_id);
                        break;
	case INT:	        printf("%*cINT��%d\n",indent,' ',T->type_int);
                        break;
	case FLOAT:	        printf("%*cFLAOT��%f\n",indent,' ',T->type_float);
                        break;
	//
	case CHAR:			printf("%*cCHAR��%c\n",indent,' ',T->type_char);
	case ASSIGNOP:		printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						display(T->ptr[1],indent+3);
						break;
	case AND:			printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						display(T->ptr[1],indent+3);
						break;
	case OR:			printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						display(T->ptr[1],indent+3);
						break;
	case RELOP:			printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						display(T->ptr[1],indent+3);
						break;
	case PLUS:			printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						display(T->ptr[1],indent+3);
						break;
	case SELFPLUS:		printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						break;
	case MINUS:			printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						display(T->ptr[1],indent+3);
						break;
	case SLEFMINUS:		printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
	case STAR:			printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						display(T->ptr[1],indent+3);
						break;
	case DIV:
                    printf("%*c%s\n",indent,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    display(T->ptr[1],indent+3);
                    break;
	case NOT:		printf("%*c%s\n",indent,' ',T->type_id);
						display(T->ptr[0],indent+3);
						display(T->ptr[1],indent+3);
						break;
	case UMINUS:    printf("%*c%s\n",indent,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    break;
    case FUNC_CALL: printf("%*c�������ã�(%d)\n",indent,' ',T->pos);
                    printf("%*c��������%s\n",indent+3,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    break;
	case ARGS:      i=1;
                    while (T) {  //ARGS��ʾʵ�ʲ�������ʽ���н�㣬���һ������Ϊ��һ��ʵ�ʲ�������ʽ���ڶ�������Ϊʣ�µ�
                        struct ASTNode *T0=T->ptr[0];
                        printf("%*c��%d��ʵ�ʲ�������ʽ��\n",indent,' ',i++);
                        display(T0,indent+3);
                        T=T->ptr[1];
                        }
//                    printf("%*c��%d��ʵ�ʲ�������ʽ��\n",indent,' ',i);
  //                  display(T,indent+3);
                    printf("\n");
                    break;
         }
      }
}