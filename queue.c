#include "queue.h"
#include "tile_game.h"

// Enqueue a game state to the queue
void enqueue(struct queue *q, struct game_state state) {
    // Serialize the game state before enqueueing
    size_t serialized_state = serialize(state);
    insert_at_tail(&q->data, serialized_state); // Insert serialized state at the tail of the list
}

// Dequeue a game state from the queue
struct game_state dequeue(struct queue *q) {
    // Remove the serialized state from the head of the list
    size_t serialized_state = remove_from_head(&q->data);
    
    // Deserialize the state back into a game_state structure
    return deserialize(serialized_state);
}

// Return the number of moves from the given game state
int number_of_moves(struct game_state start) {
    return start.num_steps; // Simply return the number of moves already recorded in the game state
}
