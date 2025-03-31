#include "queue.h"
#include "tile_game.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdbool.h>

struct queue {
    struct linked_list list;
};

// Initialize the queue
struct queue *create_queue() {
    struct queue *q = malloc(sizeof(struct queue));
    if (!q) return NULL;
    q->list.head = NULL;
    q->list.tail = NULL;
    return q;
}

// Enqueue a game state (converted to an integer)
void enqueue(struct queue *q, struct game_state state) {
    uint64_t serialized_state = serialize(state);
    insert_at_tail(&q->list, serialized_state);
}

// Dequeue a game state (converted back from an integer)
struct game_state dequeue(struct queue *q) {
    if (!q->list.head) return (struct game_state){0}; // Empty queue
    uint64_t serialized_state = remove_from_head(&q->list);
    return deserialize(serialized_state);
}

// Check if the queue is empty
bool is_empty(struct queue *q) {
    return q->list.head == NULL;
}

// Free the queue
void free_queue(struct queue *q) {
    free_list(&q->list);
    free(q);
}

// BFS to find the shortest path to solve the Tiles game
int number_of_moves(struct game_state start) {
    struct queue *q = create_queue();
    if (!q) return -1; // Memory allocation failure

    enqueue(q, start);

    // A simple visited hash table to track seen game states
    bool visited[1000000] = {0};  // Adjust size based on expected unique states
    visited[serialize(start) % 1000000] = true;

    while (!is_empty(q)) {
        struct game_state current = dequeue(q);

        // If solved, return the move count
        if (is_solved(current)) {
            int result = current.num_steps;
            free_queue(q);
            return result;
        }

        // Generate possible next states (up, down, left, right)
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
