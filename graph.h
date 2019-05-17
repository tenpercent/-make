#ifndef GRAPH_H
#define GRAPH_H

struct node;
struct dag;
struct payload;

struct node {
    struct node *parent;
    int nchildren;
    struct node *children;
    struct payload *payload;
};

struct payload {
    int (*callback)(char*);
};

#endif
