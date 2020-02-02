#ifndef floodfill_h
#define floodfill_h


class floodfill
{
  public:
    floodfill();
    void SETUP();
    // Floodfill algorithm Functions
short get_smallest_neighbor (Node * this_node);
short get_smallest_neighbor_dir (Node * this_node);
short floodval_check(Node * this_node) ;
void update_floodval (Node * this_node);
void push_open_neighbors (Node * this_node, Stack * this_stack);
void propagate_floodvalue(Node * this_node, Stack * this_stack);
void flooding_fill (Node * this_node, Stack * this_stack,  short & reflood_flag);

//Travelled Path Run
void store_path(Node * this_node, Stack * this_stack);
void path_to_travel(Stack * this_stack1 , Stack * this_stack2);
void follow_the_travelled_path(Maze * this_maze, Stack * this_stack, short * i, short * j, short *dir);

};

extern floodfill flfill;

#endif
