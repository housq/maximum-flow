#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
	struct edge *rnext;
	struct edge *reverse;
};

struct edge *adj[MAXN];
struct edge *adjr[MAXN];

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
	p->rnext = adjr[j];
	adjr[j] = p;
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
		adjr[i] = NULL;
	}
}

int head,tail;
int queue[MAXN];
int d[MAXN];

int numiter = 0;
int numaug = 0;


int cfp[MAXN];
struct edge *prev[MAXN];

int min(int a, int b){
	return a<b? a:b;
}

void dinicdfs(int i, int depth, struct edge *link){
	struct edge *p = adj[i];
	if(depth == 0){
		cfp[depth] = INF;
	}else{
		cfp[depth] = min(cfp[depth-1],link->cf);
	}
	prev[depth] = link;
	if(i == dst){
		int deltac = cfp[depth];
		int k;
		for(k=depth;k>=0;k--){
			cfp[k] -= deltac;
			if(k>0){
				prev[k]->cf -= deltac;
				prev[k]->reverse->cf +=deltac;
			}
		}
		numaug++;
		return;
	}
	while(p){
		int j = p->j;
		if( (d[j]!=-1) && (d[j] == d[i]-1) && (p->cf > 0) ){
			dinicdfs(j, depth+1, p);
		}
		if(cfp[depth] == 0) return;
		p = p->next;
	}
	//exhausted, prune this node
	d[i] = -1;
	return;
}

int dinicrun(){
	int i,j;
	struct edge *p;
	int found = 0;
	int deltac;
	numiter++;
	head = tail = 0;
	queue[tail++] = dst;
	for(i=0;i<n;i++){
		d[i] = -1; 
	}

	d[dst] = 0;

	while(head!=tail){
		j = queue[head++];
		p = adjr[j];
		while(p) if((p->cf>0) && (d[p->i]==-1)){
			i = p->i;
			d[i] = d[j]+1;
			queue[tail++] = i;
			if(i == src)
				found = 1;
			p = p->rnext;
		}else{
			p = p->rnext;
		}
		if(found) break;
	}
	if(!found){
		return 0;
	}
	dinicdfs(src, 0, NULL);
	return 1;
}

int dinic(){
	int f;
	struct edge *p;
	while(f = dinicrun()){
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
	struct timeval start,finish;
	int flow;
	init();
	readdata();
	gettimeofday(&start,NULL);
	flow = dinic();
	gettimeofday(&finish,NULL);
	printf("%d\n",flow);
	printf("%ld\n",(finish.tv_sec-start.tv_sec) * 1000000 + finish.tv_usec - start.tv_usec);
	printf("%d\n",numaug);
	printf("%d\n",numiter);
	return 0;
}


