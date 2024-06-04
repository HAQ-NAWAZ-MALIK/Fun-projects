# Snake Game

This is a classic Snake game implemented in Python using the `turtle` library. The objective of the game is to control the snake and eat as much food as possible without colliding with the walls or the snake's own body.

## How to Play

1. Run the `Snake game.py` script.
2. Use the arrow keys on your keyboard to control the snake's movement.
  - Up Arrow: Move the snake up
  - Right Arrow: Move the snake right
  - Down Arrow: Move the snake down
  - Left Arrow: Move the snake left
3. The game starts with the snake in the center of the window, and a red food item is randomly placed within the window boundaries.
4. The snake will automatically move in the direction specified by the arrow keys.
5. Eating the food item will increase the length of the snake.
6. The game ends if the snake collides with the window edges or its own body.
7. The game will reset automatically upon collision.

## Features

- Simple and clean graphics using the `turtle` library.
- Smooth snake movement with a configurable delay between each move.
- Random food item placement within the window boundaries.
- Screen wrapping, allowing the snake to wrap around the edges of the window.
- Keyboard input handling for controlling the snake's movement.
- Collision detection with window edges and the snake's body.
- Game reset upon collision.

## Requirements

- Python 3.x
- `turtle` library (built-in with Python)

## Configuration

You can adjust the game settings by modifying the constants at the top of the `Snake game.py` file:

- `WIDTH`: The width of the game window in pixels.
- `HEIGHT`: The height of the game window in pixels.
- `FOOD_SIZE`: The size of the food item.
- `DELAY`: The delay (in milliseconds) between each move of the snake.

## License

This project is licensed under the [MIT License](LICENSE).
