/**
 * @file linked_list_graph.c
 * 
 * @brief 
 *  Structs and functions for linked list graphs.
 * 
 * @implements
 *  linked_list_graph.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-21
 */
#include <stdlib.h>
#include "comp_funcs.h"
#include "linked_list_queue.h"
#include "doubly_linked_list.h"
#include "linked_list_graph.h"

/**
 * LOCAL FUNTION DECLARATIONS
 *
 * These function aren't defined outside of this source file and are not intended to be acessed directly.
*/
static void free_graph_vertex(void *vertex);
static void linked_graph_reset_vertices(void *vertex);
static int linked_graph_breath_traverse_internal_func(GRAPH_VERTEX_T *vertex, 
    int max_lvl, void (*func)(void*));

LINKED_GRAPH_T *linked_graph_create()
{
    return doubly_list_create();
}

void linked_graph_clear(LINKED_GRAPH_T **graph, void (*free_data)(void*))
{
    DOUBLY_NODE_T *curr_node = (*graph)->head;
    while(curr_node != NULL)
    {
        DOUBLY_NODE_T *prev = curr_node;
        curr_node = curr_node->next;
        if(free_data != NULL)
        {
            free_data(((GRAPH_VERTEX_T*) prev->data)->data);
        }
        free_graph_vertex(prev->data);
        free(prev);
    }
    free(*graph);
    *graph = NULL;
}

GRAPH_LIST_NODE_T *linked_graph_add(LINKED_GRAPH_T *graph, void *data)
{
    GRAPH_VERTEX_T *new_vertex = calloc(1, sizeof(GRAPH_VERTEX_T));
    if(new_vertex == NULL)
    {
        return NULL;
    }
    GRAPH_LIST_NODE_T *new_node = doubly_list_add_head(graph, new_vertex);
    if(new_node == NULL)
    {
        free(new_vertex);
        return NULL;
    }
    new_vertex->data = data;
    return new_node;
}

int linked_graph_remove(
    LINKED_GRAPH_T *graph, 
    GRAPH_LIST_NODE_T *vertex_node, 
    void (*free_data)(void*))
{
    if(vertex_node == NULL)
    {
        return 0;
    }
    GRAPH_VERTEX_T *vertex = vertex_node->data;
    if(free_data != NULL)
    {
        free_data(vertex->data);
    }

    // remove references
    DOUBLY_NODE_T *ref_node = vertex->ref_list.head;
    while(ref_node != NULL)
    {
        DOUBLY_NODE_T *vertex_ref = doubly_list_find(
            &((GRAPH_VERTEX_T*) ref_node->data)->adj_list, vertex, comp_ptr);
        doubly_list_remove(
            &((GRAPH_VERTEX_T*) ref_node->data)->adj_list, vertex_ref, NULL);
        ref_node = ref_node->next;
    }
    doubly_list_remove(graph, vertex_node, free_graph_vertex);
    return 1;
}

int linked_graph_connect(GRAPH_VERTEX_T *start, GRAPH_VERTEX_T *end)
{
    DOUBLY_NODE_T *new_node = doubly_list_add_head(&start->adj_list, end);
    if(new_node == NULL)
    {
        return 0;
    }
    if(doubly_list_add_head(&end->ref_list, start) == NULL)
    {
        doubly_list_remove(&start->adj_list, new_node, NULL);
        return 0;
    }
    return 1;
}

int linked_graph_disconnect(GRAPH_VERTEX_T *start, GRAPH_VERTEX_T *end)
{
    DOUBLY_NODE_T *connection = doubly_list_find(
        &start->adj_list, end, comp_ptr);
    DOUBLY_NODE_T *reference = doubly_list_find(
        &end->ref_list, start, comp_ptr);
    if(connection == NULL || reference == NULL)
    {
        return 0;
    }
    doubly_list_remove(&start->adj_list, connection, NULL);
    doubly_list_remove(&end->ref_list, reference, NULL);
    return 1;
}

GRAPH_LIST_NODE_T *linked_graph_find_node(
    LINKED_GRAPH_T *graph, 
    const void *key, 
    int (*comp_func)(const void*, const void*))
{
    DOUBLY_NODE_T *curr_node = graph->head;
    while(curr_node != NULL 
        && comp_func(((GRAPH_VERTEX_T*) curr_node->data)->data, key) != 0)
    {
        curr_node = curr_node->next;
    }
    return curr_node;
}

int linked_graph_is_connected(GRAPH_VERTEX_T *start, GRAPH_VERTEX_T *end)
{
    DOUBLY_NODE_T *connection = doubly_list_find(
        &start->adj_list, end, comp_ptr);
    if(connection == NULL)
    {
        return 0;
    }
    return 1;
}

void linked_graph_traverse_all(LINKED_GRAPH_T *graph, void (*func)(void*))
{
    GRAPH_LIST_NODE_T *curr_node = graph->head;
    while(curr_node != NULL)
    {
        func(((GRAPH_VERTEX_T*) curr_node->data)->data);
        curr_node = curr_node->next;
    }
}

void linked_graph_traverse_adj(GRAPH_VERTEX_T *vertex, void (*func)(void*))
{
    GRAPH_LIST_NODE_T *curr_node = vertex->adj_list.head;
    while(curr_node != NULL)
    {
        func(((GRAPH_VERTEX_T*) curr_node->data)->data);
        curr_node = curr_node->next;
    }
}

int linked_graph_breath_traverse(
    LINKED_GRAPH_T *graph,  GRAPH_VERTEX_T *start, 
    int max_lvl,            void (*func)(void*))
{
    int result = linked_graph_breath_traverse_internal_func(start, max_lvl, func);
    doubly_list_traverse(graph, linked_graph_reset_vertices);
    return result;
}

static int linked_graph_breath_traverse_internal_func(
    GRAPH_VERTEX_T *vertex, int max_lvl, void (*func)(void*))
{
    int curr_lvl = 0;
    if(max_lvl < 0)
    {
        curr_lvl = max_lvl;
    }
    LINKED_QUEUE_T *queue = linked_queue_create();
    if(queue == NULL)
    {
        return 0;
    }
    if(linked_queue_enqueue(queue, vertex) == 0)
    {
        linked_queue_clear(&queue, NULL);
        return 0;
    }
    vertex->lvl = curr_lvl;
    GRAPH_VERTEX_T *curr_vertex;
    while((curr_vertex = linked_queue_dequeue(queue)) != NULL)
    {
        if(curr_vertex->state == 0)
        {
            func(curr_vertex->data);
        }
        if(curr_vertex->state != 1)
        {
            GRAPH_LIST_NODE_T *curr_node = curr_vertex->adj_list.head; 
            if(max_lvl >= 0)
            {
                curr_lvl = curr_vertex->lvl + 1;
            }
            while(curr_node != NULL && curr_lvl <= max_lvl)
            {
                ((GRAPH_VERTEX_T*) curr_node->data)->lvl = curr_lvl;
                if(linked_queue_enqueue(queue, curr_node->data) == 0)
                {
                    linked_queue_clear(&queue, NULL);
                    return 0;
                }
                curr_node = curr_node->next;
            }
        }
        curr_vertex->state = 1;
    }
    return 1;
}

void linked_graph_set_adj_state(GRAPH_VERTEX_T *vertex, unsigned char state)
{
    GRAPH_LIST_NODE_T *curr_node = vertex->adj_list.head;
    while(curr_node != NULL)
    {
        ((GRAPH_VERTEX_T*) curr_node->data)->state = state;
        curr_node = curr_node->next;
    }
}

static void linked_graph_reset_vertices(void *vertex)
{
    ((GRAPH_VERTEX_T*) vertex)->state = 0;
    ((GRAPH_VERTEX_T*) vertex)->lvl = 0;
}

static void free_graph_vertex(void *vertex)
{
    doubly_list_remove_all(&((GRAPH_VERTEX_T*) vertex)->adj_list, NULL);
    doubly_list_remove_all(&((GRAPH_VERTEX_T*) vertex)->ref_list, NULL);
    free(vertex);
    vertex = NULL;
}