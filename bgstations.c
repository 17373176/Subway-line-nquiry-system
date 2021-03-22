#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 9999
#define N 20    /*�վ��*/
#define NUM 599 /*���վ��*/

/*---------------------------------------------------*/
/*--------------��������������·��ѯ-----------------*/
/*---------------------------------------------------*/


typedef struct{      /*��վ��Ϣ*/
    char station[N]; /*վ����*/
    int change;      /*����״̬,1Ϊ��,0Ϊ��*/
}sta;

typedef struct{      /*������վ��Ϣ*/
    int weight;      /*��վ֮��ľ���Ϊ1*/
    int L;           /*��վ���ڵ��ߺ�*/
}G;

sta vertex[NUM];     /*����ͼ��������*/
G graph[NUM][NUM];   /*ͼȨ������*/

int Vsum;            /*ʵ�ʵ���վ��*/
int path[NUM];       /*����·��*/
int s[NUM];          /*��ʼվ������վ���·�Ƿ��ҵ�*/
int dis[NUM];        /*��ʼվ������վ����̾���*/

int cout[NUM];       /*�洢·����ջ*/
int top=-1;


/*---------------------------------------------------*/
void push(int v);
int empty();
int pop();
int search(char *s);
void create(int LINE);
void dijkstra(int V1,int V2);
void floyd(int V1,int V2);
void print(int V1,int V2);
void make();
void program();
/*---------------------------------------------------*/


void push(int v){/*��ջ*/
    if(top==NUM) return;
    cout[++top]=v;
}

int empty(){/*ջ�Ƿ�Ϊ��*/
    if(top<0) return 1;
    return 0;
}

int pop(){/*��ջ*/
    if(empty())return -1;
    return cout[top--];
}

int search(char *s){/*����վ�Ƿ����*/
    int i;
    for(i=0;i<Vsum;i++)
        if(!strcmp(vertex[i].station,s))
            return i;
    return -1;
}

void create(int LINE){/*��ͼ*/
    while(LINE--){
        int no,sum;            /*ÿ����·�ı�ź�վ��*/
        scanf("%d %d ",&no,&sum);
        printf("%d %d\n",no,sum);
        int last=-1;                         /*��һվ*/
        while(sum--){            /*�洢ʱע��վ���ظ�*/
            char name[N];
            int is;
            scanf("%s %d ",name,&is);
            printf("%s %d\n",name,is);
            /*���Ҹ�վ�Ƿ��Ѵ���*/
            int index=search(name);
            if(index==-1){                   /*������*/
                strcpy(vertex[Vsum].station, name);
                vertex[Vsum].change=is;
                if(last!=-1){
                    graph[last][Vsum].L=graph[Vsum][last].L=no;
                    graph[last][Vsum].weight=graph[Vsum][last].weight=1;
                }
                last=Vsum;               /*������һվ*/
                Vsum++;                    /*���¶���*/
            }else{                             /*����*/
                if(last!=-1){
                    graph[last][index].L=graph[index][last].L=no;
                    graph[last][index].weight=graph[index][last].weight=1;
                }
                last=index;              /*������һվ*/
            }
        }
    }
}

void dijkstra(int V1,int V2){
    int i;
    /*��ʼ��*/
    for(i=0;i<Vsum;i++){
        dis[i]=graph[V1][i].weight;
        s[i]=0;
        path[i]=V1;
    }
    dis[V1]=0;
    s[V1]=1;
    int minweight,v=-1,j;
    for(i=0;i<Vsum-1;i++){
        minweight=MAX;
        /*�ҵ�δ��ǵ���СȨ��ֵ���� */
        for(j=0;j<Vsum;j++){
            if(!s[j]&&dis[j]<minweight){
                v=j;
                minweight=dis[v];
            }
        }
        s[v]=1;                /*��Ƕ������ҵ����·*/
        if(v==V2) return;          /*�յ��ѱ���򷵻�*/
        for(j=0;j<Vsum;j++){
            if(!s[j]&&graph[v][j].L&&minweight+graph[v][j].weight<dis[j]){
                dis[j]=minweight+graph[v][j].weight;
                path[j]=v;       /*��¼·����ǰ������*/
            }
        }
    }
}

void floyd(int V1,int V2){
    int i,j,k;
    int p_ath[NUM][NUM];
    /*��ʼ��·��*/
    for(i=0;i<Vsum;i++)
        for(j=0;j<Vsum;j++)
            if(i!=j&&graph[i][j].weight<MAX)
                p_ath[i][j]=i;
    for(k=0;k<Vsum;k++)
        for(i=0;i<Vsum;i++)
            for(j=0;j<Vsum;j++)
                if(graph[i][j].weight>graph[i][k].weight+graph[k][j].weight){
                    graph[i][j].weight=graph[i][k].weight+graph[k][j].weight;
                    p_ath[i][j]=p_ath[k][j];
                }
    int t=V2;
    for(;t!=V1;t=p_ath[V1][t])              /*·��׷��*/
        push(t);
}

void print(int V1,int V2){
    int last=V1;                            /*������һվ*/
    int k=1;                               /*����վ��*/
    int u=pop();                             /*��һվ*/
    int L=graph[last][u].L;                /*������·*/
    printf("%s-%d(",vertex[V1].station,L);
    last=u;                              /*������һվ*/
    while(!empty()){
        u=pop();
        if(L!=graph[last][u].L){           /*��Ҫ����*/
            L=graph[last][u].L;
            /*��ӡ����վ���ʹ˻���վ*/
            printf("%d)-%s-%d(",k,vertex[last].station,L);
            k=0;
        }
        k++;
        last=u;                      /*������һվ*/
    }
    printf("%d)-%s",k,vertex[V2].station);
}

void dp(int V1,int V2){
    int f[NUM]={MAX},p_ath[NUM]={V1};
    f[Vsum-1]=0;
    int i,j;
    for(i=Vsum-2;i>=0;i--){
        for(j=i+1;j<Vsum;j++){
            if(f[j]<MAX&&graph[i][j].weight+f[j]<f[i]){
                f[i]=graph[i][j].weight+f[j];
                p_ath[i]=j;
            }
        }
    }
    int t=V2;
    for(;t!=V1;t=p_ath[t])  push(t);
}

/*---------------------------------------------------*/

void make(){
    printf("\n1.��ʼ��ѯ\n");
    printf("2.exit\n");
    int op;
    scanf("%d",&op);
    if(op==1) program();
    else return;
}

void program(){
    int V1,V2;
    printf("��������ʼվ�����յ�վ������վ֮���ûس��ֿ�\n");
    /*������ʼվ���յ�վ*/
    char name_start[N],name_end[N];
    scanf("%s %s",name_start,name_end);
    V1=search(name_start);
    V2=search(name_end);
/*---------------------------------------------------*/
    /*��ѯ����*/
    dijkstra(V1,V2);
    int t=V2;
    for(;t!=V1;t=path[t])  push(t);       /*·��׷��*/
    //floyd(V1,V2);
    //dp(V1,V2);
    /*��ӡ���*/
    print(V1,V2);
    make();
}

int main(){

    printf("��������������·��ѯϵͳ\n");
/*---------------------------------------------------*/

/*---------------------------------------------------*/
    freopen("bgstations.txt","r",stdin);
    int LINE;                            /*����������*/
    scanf("%d ",&LINE);
    int i,j;
    /*��ʼ��*/
    for(i=0;i<NUM;i++)
        for(j=0;j<NUM;j++){
            graph[i][j].weight=graph[j][i].weight=MAX;
            graph[i][j].L=graph[j][i].L=0;
        }
/*---------------------------------------------------*/
    /*��ͼ*/
    create(LINE);
    freopen("CON", "r", stdin);
/*--------------------------------------------------*/
    /*������ʼվ���յ�վ��Ӧ�Ķ�����*/
    make();
    system("pause");
    return 0;
}
