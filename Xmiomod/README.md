This mod eliminates all calls to delay(), requiring users to implement their own non-blocking timing techniques (e.g., using millis() or micros()).

Additionally, this mod is highly optimized for speed, meaning:
No safety checks – The code assumes users have brains and will pass valid arguments to functions.
No classes - The mod avoids using classes to keep the code simple and efficient, reducing the memory footprint.
