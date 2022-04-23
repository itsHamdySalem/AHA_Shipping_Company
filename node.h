#ifndef NODE_H
#define NODE_H
template <typename ItemType>
struct node
{
    ItemType data;
    node *next;
    int priority;
};
#endif
