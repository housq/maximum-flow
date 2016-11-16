#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define INF (1<<30)


int src,dst;
int n;
int e;


struct edge{
	int i;
	int j;
	int c;
	int cf;
	struct edge *next;
	struct edge *reverse;
};

struct edge *adj[MAXN];
//struct edge *adjr[MAXN];

struct edge *find(int i, int j){
	struct edge *p = adj[i];
	while(p){
		if(p->j == j)
			return p;
		p = p->next;
	}
	return NULL;
}

struct edge *insert_edge(int i, int j, int c){
	struct edge *p = (struct edge *) malloc(sizeof(struct edge));
	p->i = i;
	p->j = j;
	p->c = c;
	p->cf = c;
	p->next = adj[i];
	adj[i] = p;
	return p;
}

void insert(int i, int j, int c){
	struct edge *p = find(i,j);
	struct edge *q;
	if(p){
		p->c = p->cf = c;
	}else{
		p = insert_edge(i,j,c);
		q = insert_edge(j,i,0);
		p->reverse = q;
		q->reverse = p;
	}
}

void readdata(){
	char buf[200];
	char *line = buf;
	size_t len = 200;
	char opr,pro[10];
	int d1,d2,d3,d4,d5;
	int i;
	do{
		getline(&line,&len,stdin);
	}while(line[0]=='c');
	sscanf(line,"%c %s %d %d",&opr,pro,&n,&e);
	src = 0;
	dst = n+1;
	n = n+2;
	while(1){
		getline(&line,&len,stdin);
		if(line[0]!='n')
			break;
		sscanf(line,"%c %d %d", &opr, &d1, &d2);
		if(d2>0)
			insert(src,d1,INF);
		else
			insert(d1,dst,INF);
	}
	for(i=0;i<e;i++){
		sscanf(line,"%c %d %d %d %d %d",&opr, &d1, &d2, &d3, &d4, &d5);
		insert(d1,d2,d4);
		getline(&line,&len,stdin);
	}
}

void init(){
	int i=0;
	for(i=0;i<MAXN;i++){
		adj[i] = NULL;
//		adjr[i] = NULL;
	}
}

int head,tail;
int queue[MAXN];
struct edge *prev[MAXN];

int ekrun(){
	int i,j;
	struct edge *p;
	int found = 0;
	int deltac;
	head = tail = 0;
	queue[tail++] = src;
	for(i=0;i<n;i++){
		prev[i] = NULL;
	}

	while(head!=tail){
		i = queue[head++];
		p = adj[i];
		while(p) if((p->cf>0) && (p->j!=src) && (prev[p->j]==NULL)){
			prev[p->j] = p;
			queue[tail++] = p->j;
			if(p->j == dst)
				found = 1;
			p = p->next;
		}else{
			p = p->next;
		}
		if(found) break;
	}
	if(!found){
		return 0;
	}
	deltac = INF;
	j = dst;
	while(j!=src){
		p = prev[j];
		i = p->i;
		if(p->cf < deltac)
			deltac = p->cf;
		j = i;
	}
	
	
	j = dst;
	while(j!=src){
		p = prev[j];
		p->cf-=deltac;
		p->reverse->cf+=deltac;
		j = p->i;
	}
	return deltac;
}

int ek(){
	int f;
	struct edge *p;
	while(f = ekrun()){
			}
	f = 0;
	p = adj[src];
	while(p){
		f+= p->c - p->cf;
		p = p->next;
	}
	return f;

}
int main(){
	init();
	readdata();
	printf("%d\n",ek());
	return 0;
}


