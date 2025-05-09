#include &lt;stdio.h&gt;
int num_edges =1;
int par[10];
int G[10][10];
int findparent(int);
int Union(int, int);
int findparent(int i){
while(i!=par[i]){
i=par[i];
}
return i;
}
int Union(int i, int j){
if (i!=j){
par[j]=i;
return 1;
}
return 0;
}
int main (){
int min = 99;
int n, i , j, minW =0;
int choice;
printf(&quot;Choose graph input method:\n1. Adjacency Matrix\n2. Adjacency List\n&quot;);
scanf(&quot;%d&quot;, &amp;choice);
printf(&quot;Enter the number of vertices: \n&quot;);
scanf(&quot;%d&quot;, &amp;n);
for (i = 0; i &lt; n; i++) {
par[i] = i;
}
if (choice == 1){
printf(&quot;Enter the adjacency matrix: \n&quot;);
for (i=0; i&lt;n; i++){
for (j=0; j&lt;n; j++){
scanf(&quot;%d&quot;, &amp;G[i][j]);
}

}
}
else if (choice == 2){
int edges, u, v, w;
printf(&quot;Enter the number of edges: \n&quot;);
scanf(&quot;%d&quot;, &amp;edges);
for (i=0;i&lt;n;i++){
for (j=0;j&lt;n;j++){
G[i][j]=99;
}
}
printf(&quot;Enter edges in format: u v weight\n&quot;);
for (i=0; i&lt;edges; i++){
scanf(&quot;%d%d%d&quot;, &amp;u, &amp;v, &amp;w);
G[u][v] = w;
G[v][u] = w;
}
}
else{
printf(&quot;Invalid choice!\n&quot;);
return 0;
}
int u, v, a, b;
while (num_edges &lt; n){
for (i=0, min = 99; i&lt;n; i++){
for (j=0; j&lt;n; j++){
if (G[i][j] &lt; min){
min = G[i][j];
a = u = i;
b = v = j;
}
}
}
u = findparent(u);
v = findparent(v);
if(Union(u,v)){
minW += min;
printf(&quot;%d Edge :- %d - %d -&gt; %d\n&quot;, num_edges, a, b, min);
num_edges++;
}
G[a][b]=G[b][a] = 99;
}
printf(&quot;MST weight: %d\n&quot;, minW);
return 0;
}
