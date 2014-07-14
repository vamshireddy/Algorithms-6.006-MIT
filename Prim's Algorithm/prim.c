#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#define NODES 500
#define POSITIVE_MAX 99999

typedef struct node
{
	int name;
	int weight;
	struct node* next;
}node;

typedef struct graph_node
{
	int name;
	int visited;
	struct node* list;
}graph_node;

void add_edge(int start,int w,int end,graph_node g[])
{
	//printf("Adding %d %d with %d\n",start,end,w);
	node* new_node = (node*)malloc(sizeof(node));
	new_node->name = end;
	new_node->weight = w;
	new_node->next = NULL;
	node* temp = g[start].list;
	if(temp==NULL)
	{
		g[start].list = new_node;
	}
	else
	{
		new_node->next = g[start].list;
		g[start].list = new_node;
	}
}


void initGraph(graph_node g[])
{
	/*
	 * Write code for taking the input from file and populating the graph
	 */
	 
	 FILE* fp = NULL;
	 fp = fopen("edges.txt","r");
	 
	 if( fp == NULL )
	 {
		 perror("Error");
	 }
	 char * line = NULL;
     size_t len = 0;
     int read;
     
     read = getline(&line, &len, fp);
     
	 while ((read = getline(&line, &len, fp)) != -1)
	 {
		   int x,y,w;
           sscanf(line,"%d %d %d",&x,&y,&w);
           add_edge(x,w,y,g);
           add_edge(y,w,x,g);
     }
    /* 
     add_edge(1,1,2,g);
     add_edge(1,3,3,g);
     add_edge(2,1,1,g);
     add_edge(2,2,3,g);
     add_edge(2,5,4,g);
     add_edge(3,3,1,g);
     add_edge(3,2,2,g);
     add_edge(3,1,4,g);
     add_edge(4,1,3,g);
     add_edge(4,5,2,g);
	*/
}

int prim(graph_node g[],int start)
{
	long long weight_of_tree = 0;
	/*
	 * Set X which has all the visited vertices
	 */
	int vertex_list[NODES];
	int vertex_count=0;
	
	g[start].visited = 1;
	vertex_list[vertex_count++] = start;

	while(vertex_count<NODES)
	{
		int min = POSITIVE_MAX;
		int min_vertex;
		
		/*
		 * Search for the Min edge in the crossing edges originating from the set X which is vertex_list here.
		 */
		int i;
		for(i=0;i<vertex_count;i++)
		{
			node* temp = g[vertex_list[i]].list;
			while(temp)
			{
				if(g[temp->name].visited==0 && temp->weight < min)
				{
					min = temp->weight;
					min_vertex = temp->name;
				}
				temp = temp->next;
			}
		}
		/*
		 * If no edge is found, Error
		 */
		if(min == POSITIVE_MAX)
		{
			/*
			 *	Disconnected conponent's exist. Exiting.
			 */
			printf("Error in graph structure!\nExiting\n");
			return;
		}
		/*
		 * Make the new edge visited and add it to the set X, update the spanning tree cost
		 */
		 printf("Min is %d\n",min);
		g[min_vertex].visited = 1;
		weight_of_tree += min;
		vertex_list[vertex_count++] = min_vertex;
	}
	return weight_of_tree;
}

void printGraph(graph_node g[])
{
	int i;
	for(i=1;i<=NODES;i++)
	{
		printf("\t%d ----> ",g[i].name);
		node* temp = g[i].list;
		while(temp)
		{
			printf("%d( %d )",temp->name,temp->weight);
			temp = temp->next;
		}
		printf("\n");
	}
}

int main()
{
	graph_node g[NODES+1];
	
	/* Neglect the 0th index */
	int i;
	g[0].list = NULL;
	g[0].visited = -1;
	for(i=1;i<=NODES;i++)
	{
		g[i].list = NULL;
		g[i].name = i;
		g[i].visited = 0;
	}
	initGraph(g);
	assert(g[0].list == NULL && g[0].visited == -1 );
	printf("The MST weight is %d\n",prim(g,1));
	//printGraph(g);
}
