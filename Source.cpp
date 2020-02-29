#include<stdio.h> 
#include<stdbool.h> 

// csucsok szama
#define V 7
//szinek szama
#define M 3

int ertekadasok = 0;

void printSolution(int color[]);

//backtracking: v csucs kaphatja-e a c szint?
bool isSafe(int v, bool graph[V][V], int color[], int c)
{
	for (int i = 0; i < V; i++)
		if (graph[v][i] && c == color[i])
			return false;
	return true;
}

//backtracking
bool graphColoring_backtracking(bool graph[V][V], int color[], int v)
{
	//minden csucsnak van szine
	if (v == V)
		return true;

	//v csucsnak sorra adjuk a szineket
	for (int c = 1; c <= M; c++)
	{
		ertekadasok++;
		//a c szin megfelel-e
		if (isSafe(v, graph, color, c))
		{
			color[v] = c;

			//kovetkezo csucs
			if (graphColoring_backtracking(graph, color, v + 1) == true)
				return true;

			//a valasztott szin nem vezet megoldashoz, viszalep
			color[v] = 0;
		}
	}

	//nincs megfelelo szin
	return false;
}

//forward checking: visszalepeskor visszakerulnek a kitorolt szinek
void putBackColor(int t[], int c) {
	for (int i = 0; i < M; i++) {
		if (t[i] == 0) {
			t[i] = c;
			return;
		}
	}
}

// forward checking: toroljuk a szomszedok lehetseges szinei kozul, amit a v-nek valasztottunk
bool deleteInconsistentValues(bool graph[V][V], int v, int c, int forward_check_list[V][M]) {
	for (int i = 0; i < V; i++) {
		if (graph[v][i]) {
			for (int j = 0; j < M; j++) {
				if (c == forward_check_list[i][j]) {
					forward_check_list[i][j] = 0;
					bool kilep = true;
					for (int k = 0; k < M; k++) {
						if (forward_check_list[i][k] != 0) {
							kilep = false;
							break;
						}
					}
					if (kilep) {
						return false;
					}
				}
			}
		}
	}
	return true;
}


// backtracking + forward checking
bool graphColoring_forwardChecking(bool graph[V][V], int color[], int v, int forward_check_list[V][M])
{
	//minden csucsnak van szine
	if (v == V)
		return true;

	for (int k = 0; k < M; k++) {
		if (forward_check_list[v][k] == 0)
			continue;
		int c = forward_check_list[v][k];
		ertekadasok++;
		//a c szin megfelel-e
		if (isSafe(v, graph, color, c))
		{
			color[v] = c;
			if (deleteInconsistentValues(graph, v, c, forward_check_list) == true) {
				if (graphColoring_forwardChecking(graph, color, v + 1, forward_check_list) == true) {
					return true;
				}
				color[v] = 0;
				for (int i = 0; i < V; i++) {
					if (graph[v][i]) { // ha szomszedos
						putBackColor(forward_check_list[i], c); //visszatesszuk a szomszedok lehetseges szinei koze
					}
				}
			}
		}
	}

	//nincs megfelelo szin
	return false;
}

bool removeValuesIfArcIsInconsistent(int x, int y, int arc_consistency_list[V][M]) {
	for (int i = 0; i < M; i++) {
		if (arc_consistency_list[x][i] == 0)//kihagyni
			continue;
		bool consistent = false;
		for (int j = 0; j < M; j++) {
			if (arc_consistency_list[y][j] != 0 && arc_consistency_list[y][j] != arc_consistency_list[x][i]) {
				consistent = true;
				break;
			}
		}
		if (!consistent) {
			arc_consistency_list[x][i] == 0;
			bool kilep = true;
			for (int k = 0; k < M; k++) {
				if (arc_consistency_list[x][k] != 0) {
					kilep = false;
					break;
				}
			}
			if (kilep) {
				return false;
			}
		}
	}
	return true;
}

// backtracking + ac-3
bool backtrack_ac3(bool graph[V][V], int color[], int v, int arc_consistency_list[V][M]) {
	//minden csucsnak van szine
	if (v == V)
		return true;

	//v csucsnak sorra adjuk a szineket
	for (int k = 1; k <= M; k++)
	{
		if (arc_consistency_list[v][k] == 0)
			continue;
		int c = arc_consistency_list[v][k];
		ertekadasok++;
		//a c szin megfelel-e
		if (isSafe(v, graph, color, c))
		{
			color[v] = c;

			//kovetkezo csucs
			if (backtrack_ac3(graph, color, v + 1, arc_consistency_list) == true)
				return true;

			//a valasztott szin nem vezet megoldashoz, viszalep
			color[v] = 0;
		}
	}

	//nincs megfelelo szin
	return false;
}

bool graphColoring_ac3(bool graph[V][V], int color[], int arc_consistency_list[V][M])
{
	int queue[V*V][2]; // iranyitott elek
	int n = 0; //elek szama
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (graph[i][j]) {
				queue[n][0] = i;
				queue[n][1] = j;
				n++;
			}
		}
	}
	int i = 0; //aktualis el
	while (i < n) {//amig van el
		if (!removeValuesIfArcIsInconsistent(queue[i][0], queue[i][1], arc_consistency_list)) {
			return false;
		}
		i++;
	}
	backtrack_ac3(graph, color, 0, arc_consistency_list);
}

//terkepszinezes problema megoldasa 3 algoritmussal
void graphColoring(bool graph[V][V])
{
	//szin tomb inicialaizalasa
	int color[V];
	for (int i = 0; i < V; i++)
		color[i] = 0;

	// nyers backtracking
	if (graphColoring_backtracking(graph, color, 0) == false)
	{
		printf("nyers backtracking: nincs megoldas\n");
	}
	else {
		printf("nyers backtracking:\n");
		printSolution(color);
	}

	//taroljuk a csucsok lehetseges szineit, 
	//inicializaljuk mindenik csucsot mindenik szinnel
	int forward_check_list[V][3];
	int arc_consistency_list[V][3];
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < 3; j++) {
			forward_check_list[i][j] = j + 1;
			arc_consistency_list[i][j] = j + 1;
		}
	}

	//szin tomb inicializalasa
	for (int i = 0; i < V; i++)
		color[i] = 0;

	//backtracking + forward checking
	if (graphColoring_forwardChecking(graph, color, 0, forward_check_list) == false) {
		printf("backtracking + forward checking: nincs megoldas\n");
	}
	else {
		// Print the solution
		printf("backtracking + forward checking:\n");
		printSolution(color);;
	}

	//szin tomb inicializalasa
	for (int i = 0; i < V; i++)
		color[i] = 0;

	//backtracking + ac3
	if (graphColoring_ac3(graph, color, arc_consistency_list) == false) {
		printf("backtracking + ac3: nincs megoldas\n");
	}
	else {
		// Print the solution
		printf("backtracking + ac3:\n");
		printSolution(color);;
	}
}

void printSolution(int color[])
{
	for (int i = 0; i < V; i++)
		printf(" %d ", i+1);
	printf("\t -> csucsok\n");
	for (int i = 0; i < V; i++)
		printf(" %d ", color[i]);
	printf("\t -> szinek\n");
	printf("ertekadasok szama: %d\n\n", ertekadasok);
	ertekadasok = 0;
}


int main()
{
	bool graph[V][V] = {
		{0, 1, 1, 0, 0, 0, 0},
		{1, 0, 1, 1, 0, 0, 0},
		{1, 1, 0, 1, 1, 1, 0},
		{0, 1, 1, 0, 1, 0, 0},
		{0, 0, 1, 1, 0, 1, 0},
		{0, 0, 1, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0}
	};
	
	graphColoring(graph);

	//varjon entert
	char c;
	c = getchar();
	return 0;
}