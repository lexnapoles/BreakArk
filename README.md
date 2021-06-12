# BreakArk
Breakout clone built with C++11, SDL and SDL_net. It was the university's final project.

- Client-server architecture with an authoritative server. Client sends inputs, the server runs the game and sends results to the client.
- Multiple levels that can be loaded from files.
- Realistic collision detection and movement of the ball that weren't affected by the CPU slowing or speeding up with the Runge–Kutta method.
- State machine defines the different game states.

