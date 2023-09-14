// #include <stdbool.h> // for bool identifiers (true/false)
// #define TRUE 1
// #define FALSE 0
#include <stdio.h>  // for printf
#include <stdlib.h> // for exit
#include <string.h> // for string comparison

// define InputBuffer struct
typedef struct {
  char *buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

// create instance of InputBuffer and return it's address
InputBuffer *new_input_buffer() {
  InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

// print prompt to user
void print_prompt() { printf("db > "); }

void read_input(InputBuffer *input_buffer) {
  // read data from stdin and return the number of bytes read
  // getline allocates a buffer at this point
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  // if doesn't read anything
  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer) {
  // TODO: why should i free the buffer field manullay, even already free the
  // struct?
  free(input_buffer->buffer);
  free(input_buffer);
}

// make REPL
int main(int argc, char *argv[]) {
  InputBuffer *input_buffer = new_input_buffer();

  // repLoop
  // while (TRUE)
  for (;;) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'. \n", input_buffer->buffer);
    }
  }
}
