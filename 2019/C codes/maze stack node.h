#define SIZE 16    //Maze of 16 x 16

#define TRUE 1       
#define FALSE 0

int counter=0;

int State;
int LastState;


// Referance Constants
#define MAP_IJ this_maze->mapp[i][j]
#define MAP this_maze->mapp

#define FLOODVAL this_node->floodval
#define ROW this_node->row
#define COL this_node->column
#define VISITED this_node->visited
#define LEFT this_node->left
#define RIGHT this_node->right
#define UP this_node->up
#define DOWN this_node->down

#define STACKSIZE 256
int top;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//STRUCTURE DEFINITIONS

typedef struct Node { 

 
  short floodval;
  short row;
  short column;
  short visited;

  //pointers to neighbouring node
  struct Node * left;
  struct Node * right;
  struct Node * up;
  struct Node * down;
  
} Node;


typedef struct Maze {

  Node * mapp [SIZE][SIZE];  

} Maze;

typedef struct Stack {

  short top;
  Node * the_stack [STACKSIZE]; 

} Stack;

// Node Functions
Node * new_Node (const short i, const short j);
void delete_Node (Node ** npp);
void set_wall (Node * this_node, const short dir);
void set_value (Node * this_node, const short value);
void set_visited (Node * this_node);
void visit_Node (Maze * this_maze, Stack * this_stack, short i, short j, short & flag, short * dir);


// Maze Functions
Maze * new_Maze ();
void delete_Maze (Maze ** mpp);


// Stack Functions
Stack * new_Stack();
void delete_Stack (Stack ** spp);
int is_empty_Stack (Stack * this_stack);
void push (Stack * this_stack, Node * this_node);
void pop (Stack * this_stack, Node ** temp);
