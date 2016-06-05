
#include "includes.h"

#define  TASK_STK_SIZE   512			//�����ջ����

OS_STK   TaskStartStk[TASK_STK_SIZE];		//���������ջ��
INT16S   key;					//�����˳�uCOS_II�ļ�	
INT8U	 x=0,y=0;				//�ַ���ʾλ��

#define key_up 119
#define key_down 115
#define key_left 97 
#define key_right 102

#define up 1
#define down 2
#define left 3
#define right 4
INT8U state=right;


void  MyTask(void *data);			//����һ������
/************************������*********************************************/
void  main (void)
{
    char* s="M";				//����Ҫ��ʾ���ַ�

    OSInit();					//��ʼ��uCOS_II

    PC_DOSSaveReturn();				//����Dos����
    PC_VectSet(uCOS, OSCtxSw);			//��װuCOS_II�ж�

    OSTaskCreate(MyTask,			//��������MyTask
		s,				//�����񴫵ݲ���
		&TaskStartStk[TASK_STK_SIZE - 1],//���������ջջ��ָ��
		0);				//ʹ����MyTask�����ȼ���Ϊ0
    OSStart();					//����uCOS_II�Ķ��������
}


void  MyTask (void *pdata)
{
  
char s[5];
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;
#endif

    pdata = pdata; 

    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);	//��װuCOS_IIʱ���ж�����
    PC_SetTickRate(OS_TICKS_PER_SEC*3);	//����uCOS_IIʱ��Ƶ��
    OS_EXIT_CRITICAL();

    OSStatInit();			//��ʼ��uCOS_II��ͳ������

    for (;;) 
	{        

               if (key == key_down) 
	       {
                  state=down;
               }
		else if(key == key_up)
		{
               
                  state=up;
                }
		else if(key == key_left)
		{
               
                  state=left;
                }
		else if(key == key_right)
		{
               
                  state=right;
                }
              }     
               if(state==right)
              {                                  
                PC_DispChar(x, y,		//��x��yλ����ʾs�е��ַ�
		*(char*)pdata, 
		DISP_BGND_BLACK+DISP_FGND_WHITE );
       		x += 1;                         
              }
              else if(state==down)
              {                                  
                PC_DispChar(x, y,		//��x��yλ����ʾs�е��ַ�
		*(char*)pdata, 
		DISP_BGND_BLACK+DISP_FGND_WHITE );
       		y += 1;                         
              }
              else if(state==up)
              {                                  
                PC_DispChar(x, y,		//��x��yλ����ʾs�е��ַ�
		*(char*)pdata, 
		DISP_BGND_BLACK+DISP_FGND_WHITE );
       		y -= 1;                         
              }
              else if(state==left)
              {                                  
                PC_DispChar(x, y,		//��x��yλ����ʾs�е��ַ�
		*(char*)pdata, 
		DISP_BGND_BLACK+DISP_FGND_WHITE );
       		x -= 1;                         
              }

        OSTimeDlyHMSM(0, 0, 1, 0);	//�ȴ�
    }
}
