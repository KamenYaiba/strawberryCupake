This mod eliminates all calls to delay(), requiring users to implement their own non-blocking timing techniques (e.g., using millis() or micros()).

Additionally, this mod is highly optimized for speed, meaning:

No safety checks – The code assumes users have brains and will pass valid parameters to functions.
Maximum performance – Error handling has been removed to reduce overhead.