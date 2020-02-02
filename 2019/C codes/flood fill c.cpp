#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HEIGHT 100
#define MAX_WIDTH  100
#define wall '#'
#define path_cell '.'

typedef struct {
    char type;
    int reachable;
    int visited;
} mazecells_t;

typedef struct {
    int height;
    int width;
    mazecells_t M[MAX_HEIGHT][MAX_WIDTH];
} m_t;

void readmaze(m_t *maze);
void print(m_t *m);
void print_reachable(m_t *m);

int main(void) {
    m_t MAZE;

    readmaze(&MAZE);
    print(&MAZE);
    puts("");
    print_reachable(&MAZE);

    return 0;
}

void readmaze(m_t *maze) {
    int row=0, col=0;
    char ch;
    FILE *fp = stdin;//fopen("map.txt", "r");
    while(EOF != fscanf(fp, "%c", &ch)){
        if(ch == wall || ch == path_cell){
            maze->M[row][col].type = ch;
            maze->M[row][col].reachable = 0;
            maze->M[row][col].visited = 0;
            ++col;
        } else if(ch == '\n'){
            maze->width = col;
            col = 0;
            ++row;
        }
    }
    if(col != 0)
        ++row;
    //fclose(fp);
    maze->height = row;
}

void print(m_t *m){
    for(int r = 0; r < m->height; ++r){
        for(int c = 0; c < m->width; ++c){
            putchar(m->M[r][c].type);
        }
        putchar('\n');
    }
}

typedef enum dir {
    UP, RIGHT, DOWN, LEFT, FORWARD
} DIR;

typedef struct pos {
    int r, c;
    DIR dir;
} Pos;

typedef struct node {
    Pos pos;
    struct node *next;
} Node;

typedef struct queque {
    Node *head, *tail;
} Queque;

Queque *new_queque(void){
    Queque *q = malloc(sizeof(*q));
    q->head = q->tail = NULL;
    return q;
}

void enque(Queque *q, Pos pos){
    Node *node = malloc(sizeof(*node));
    node->pos = pos;
    node->next = NULL;
    if(q->head == NULL){
        q->head = q->tail = node;
    } else {
        q->tail = q->tail->next = node;
    }
}

Pos deque(Queque *q){
    Pos pos = q->head->pos;
    Node *temp = q->head;
    if((q->head = q->head->next)==NULL)
        q->tail = NULL;
    free(temp);
    return pos;
}

bool isEmpty_que(Queque *q){
    return q->head == NULL;
}

Pos dxdy(DIR curr, DIR next){
    Pos d = { 0, 0, 0};
    switch(curr){
    case UP:
        switch(next){
        case LEFT:
            d.c -= 1;
            break;
        case FORWARD:
            d.r -= 1;
            break;
        case RIGHT:
            d.c += 1;
            break;
        }
        break;
    case RIGHT:
        switch(next){
        case LEFT:
            d.r -= 1;
            break;
        case FORWARD:
            d.c += 1;
            break;
        case RIGHT:
            d.r += 1;
            break;
        }
        break;
    case DOWN:
        switch(next){
        case LEFT:
            d.c += 1;
            break;
        case FORWARD:
            d.r += 1;
            break;
        case RIGHT:
            d.c -= 1;
            break;
        }
        break;
    case LEFT:
        switch(next){
        case LEFT:
            d.r += 1;
            break;
        case FORWARD:
            d.c -= 1;
            break;
        case RIGHT:
            d.r -= 1;
            break;
        }
        break;
    }
    return d;
}

Pos next_pos(Pos pos, DIR dir){
    Pos dxy = dxdy(pos.dir, dir);
    switch(dir){
    case RIGHT:
        pos.dir = (pos.dir + 1) % 4;
        break;
    case LEFT:
        if((pos.dir = (pos.dir - 1)) < 0)
            pos.dir += 4;
        break;
    case FORWARD:
        break;
    }
    pos.r += dxy.r;
    pos.c += dxy.c;
    return pos;
}
static inline bool isValid(m_t *m, Pos pos){
    if(pos.r < 0 || pos.r >= m->height || pos.c < 0 || pos.c >= m->width || m->M[pos.r][pos.c].type == wall)
        return false;
    return true;
}
static inline bool isValidAndUnvisit(m_t *m, Pos pos){
    return isValid(m, pos) && !m->M[pos.r][pos.c].reachable;
}

void print_reachable(m_t *m){
    int i;
    for(i = 0; i < m->width; ++i)
        if(m->M[0][i].type == path_cell)
            break;
    Pos pos = { 0, i, DOWN};
    Queque *q = new_queque();
    enque(q, pos);
    while(!isEmpty_que(q)){
        pos = deque(q);
        if(!m->M[pos.r][pos.c].reachable){
            m->M[pos.r][pos.c].reachable = 1;

            Pos next = next_pos(pos, LEFT);
            if(isValidAndUnvisit(m, next))
                enque(q, next);
             next = next_pos(pos, FORWARD);
            if(isValidAndUnvisit(m, next))
                enque(q, next);
             next = next_pos(pos, RIGHT);
            if(isValidAndUnvisit(m, next))
                enque(q, next);
        }
    }
    free(q);
    for(int r = 0; r < m->height; ++r){
        for(int c = 0; c < m->width; ++c){
            if(m->M[r][c].reachable)
                putchar('+');
            else if(m->M[r][c].type == path_cell)
                putchar('-');
            else
                putchar(m->M[r][c].type);
        }
        putchar('\n');
    }
}
