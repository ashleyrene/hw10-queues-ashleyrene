#include "queue.h"
#include "tile_game.h"

struct queue {
    struct list_node *head;
    struct list_node *tail;
};

// Initialize the queue
struct queue *create_queue() {
    struct queue *q = malloc(sizeof(struct queue));
    if (!q) return NULL;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

// Enqueue a game state (converted to an integer)
void enqueue(struct queue *q, struct game_state state) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (!node) return;
    node->value = serialize(state);
    node->next = NULL;

    if (q->tail) {
        q->tail->next = node;
    } else {
        q->head = node;
    }
    q->tail = node;
}

// Dequeue a game state (converted back from an integer)
struct game_state dequeue(struct queue *q) {
    if (!q->head) return (struct game_state){0}; // Empty queue
    
    struct list_node *temp = q->head;
    uint64_t serialized_state = temp->value;
    q->head = q->head->next;
    
    if (!q->head) q->tail = NULL;

    free(temp);
    return deserialize(serialized_state);
}

// Check if the queue is empty
bool is_empty(struct queue *q) {
    return q->head == NULL;
}

// Free the queue
void free_queue(struct queue *q) {
    while (!is_empty(q)) {
        dequeue(q); // Remove each node
    }
    free(q);
}

// BFS to find the shortest path to solve the Tiles game
int number_of_moves(struct game_state start) {
    struct queue *q = create_queue();
    if (!q) return -1; // Memory allocation failure

    enqueue(q, start);

    bool visited[1000000] = {0};  // Adjust size based on expected unique states
    visited[serialize(start) % 1000000] = true;

    while (!is_empty(q)) {
        struct game_state current = dequeue(q);

        if (is_solved(current)) {
            int result = current.num_steps;
            free_queue(q);
            return result;
        }

        struct game_state next_states[4];
        int num_next_states = get_next_states(current, next_states);

        for (int i = 0; i < num_next_states; i++) {
            uint64_t serialized = serialize(next_states[i]);

            if (!visited[serialized % 1000000]) {
                visited[serialized % 1000000] = true;
                enqueue(q, next_states[i]);
            }
        }
    }

    free_queue(q);
    return -1; // No solution found
}

