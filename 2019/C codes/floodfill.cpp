#include "Arduino.h"
#include "floodfill.h"



floofill::floodfill(){

}


//FLOOD FILL ALGORITHM FUNCTIONS

// function for obtaining this_node's smallest neighbor's floodval 
short floodfill::get_smallest_neighbor (Node * this_node) {

  short smallestneighbor = LARGEVAL;

  if (UP != NULL && (UP->down != NULL) && (UP->floodval) < smallestneighbor)
    smallestneighbor = UP->floodval;

  if (RIGHT != NULL && (RIGHT->left != NULL) && (RIGHT->floodval) < smallestneighbor)
    smallestneighbor = RIGHT->floodval; 

  if (LEFT != NULL && (LEFT->right != NULL) && (LEFT->floodval) < smallestneighbor)
    smallestneighbor = LEFT->floodval;

  if (DOWN != NULL && (DOWN->up != NULL) && (DOWN->floodval) < smallestneighbor)
    smallestneighbor = DOWN->floodval;

  return smallestneighbor;
}

// function for obtaining this nodes's smallest neighbor's direction 
short floodfill::get_smallest_neighbor_dir (Node * this_node) 
{

  short smallestval;    
  smallestval = get_smallest_neighbor(this_node);

      //returning a direction means that path is reachable
      if ((UP != NULL) && (UP->floodval == smallestval) && (UP->visited == FALSE))
       return NORTH;
      else if ((RIGHT != NULL) && (RIGHT->floodval == smallestval) && (RIGHT->visited == FALSE))
        return EAST;
      else if ((LEFT != NULL) && (LEFT->floodval == smallestval) && (LEFT->visited == FALSE))
        return WEST;
      else if ((DOWN != NULL) && (DOWN->floodval == smallestval) && (DOWN->visited == FALSE))
        return SOUTH;

    if ((UP != NULL) && (UP->floodval == smallestval))
       return NORTH;
      else if ((RIGHT != NULL) && (RIGHT->floodval == smallestval))
        return EAST;
      else if ((LEFT != NULL) && (LEFT->floodval) == smallestval)
        return WEST;
      else //if ((DOWN != NULL) && (DOWN->floodval == smallestval))
        return SOUTH;

}

// function for modified flood_fill 
short floodfill::floodval_check(Node * this_node) {
  if (get_smallest_neighbor (this_node) + 1 == this_node->floodval)
    return TRUE;
  else
  return FALSE;
}

//Floodfill Update Function
void floodfill::update_floodval (Node * this_node) 
{ 
  this_node->floodval = get_smallest_neighbor (this_node) + 1;
}

// pushes the open neighboring cells of this node to the stack 
void floodfill::push_open_neighbors (Node * this_node, Stack * this_stack) 
{

  if (UP != NULL && UP->down != NULL) 
    push (this_stack, UP);
    
  if (LEFT != NULL && LEFT->right != NULL) 
    push (this_stack, LEFT);

  if (RIGHT != NULL && RIGHT->left != NULL) 
    push (this_stack, RIGHT);

  if (DOWN != NULL && DOWN->up != NULL) 
    push (this_stack, DOWN);

}

// main function for propagating the flood values  

void floodfill::propagate_floodvalue(Node * this_node, Stack * this_stack){

    Node * temp;
    short check;  
    
    push_open_neighbors(this_node, this_stack);
    while(!is_empty_Stack(this_stack)) {
      check = floodval_check(this_stack->the_stack[top]);
      if (!check) 
  {
    update_floodval(this_stack->the_stack[top]);
    propagate_floodvalue(this_stack->the_stack[top],this_stack);
  } 
      else
      {
        pop (this_stack, &temp);
      }
 }    
}

void floodfill::flooding_fill (Node * this_node, Stack * this_stack, short & reflood_flag) {

  short check;  
  
  if (!reflood_flag) 
    if (ROW == SIZE / 2 || ROW == SIZE / 2 - 1) 
        if (COL == SIZE / 2 || COL == SIZE / 2 - 1) 
        {
          reflood_flag = TRUE;
          return;
        }
  
   check = floodval_check (this_node);

  if (!check) 
  {
    update_floodval(this_node); 
    push (this_stack, this_node);
    propagate_floodvalue(this_node,this_stack);
  } 
}

//TRAVELLED PATH RUN ALGORITHM

//Storing only required elements
void floodfill::store_path(Node * this_node, Stack * this_stack)
{
  if(ROW==0 && COL==0)
     push(this_stack,this_node);
  else if(FLOODVAL== this_stack->the_stack[top]->floodval - 1)
     push (this_stack,this_node);
}

//Final path to run from start to destination
void floodfill::path_to_travel(Stack * this_stack1 , Stack * this_stack2)
{
 Node * temp;
 while(!is_empty_Stack(this_stack1)) 
 {
  push (this_stack2, this_stack1->the_stack[top]);
  pop (this_stack1, &temp);  
 }
}

void floodfill::follow_the_travelled_path(Maze * this_maze, Stack * this_stack, short * i, short * j, short * dir)
{
  Node * this_node;
  Node * temp;
  short face_dir;
  face_dir = (*dir);
  while(!is_empty_Stack(this_stack))
  {
    this_node = this_maze->mapp[(*i)][(*j)];
  int prev_i, prev_j;
  prev_i=ROW;
  prev_j=COL;
  
  pop (this_stack, &temp);
  if (this_stack->the_stack[top]->row == prev_i + 1)
  {
    motor_turn_dir(face_dir , NORTH);
    (*i) = (*i) + 1;
    *dir = NORTH;
  }
  else if(this_stack->the_stack[top]->column == prev_j + 1)
  {
    motor_turn_dir(face_dir , EAST);
    (*j) = (*j) + 1;
    *dir = EAST;
  }
  else if(this_stack->the_stack[top]->column == prev_j - 1)
  {
    motor_turn_dir(face_dir , WEST);
    (*j) = (*j) - 1;
    *dir = WEST;

  }
  else if(this_stack->the_stack[top]->row == prev_i - 1)
  {
    motor_turn_dir(face_dir , SOUTH);
    (*i) = (*i) - 1;
    *dir = SOUTH;
  }

    counter=0;
    
    analogWrite(enR,255);
    analogWrite(enL,255);
    digitalWrite(Rf,HIGH);
    digitalWrite(Rb,LOW);
    digitalWrite(Lf, HIGH);
    digitalWrite(Lb, LOW);

    
    State=digitalRead(pin);
   if(State!=LastState)
   {
      counter++;
   }
   LastState=State;

   if(counter==7)
   {
    
    digitalWrite(Rf,LOW);
    digitalWrite(Rb,LOW);
    digitalWrite(Lf,LOW);
    digitalWrite(Lb,LOW);

    delay(1000); 
   } 

  }

}
floodfill flfill = floodfill();

}

