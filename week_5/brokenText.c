#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gap_buffer {
  char *buffer;
  unsigned long gap_start;
  unsigned long gap_end;
  unsigned long buffer_size;
} gap_buffer_t;

gap_buffer_t *create_gap_buffer();
void print_gap_buffer(const gap_buffer_t *gb);
void move_cursor_to_start(gap_buffer_t *gb);
void move_cursor_to_end(gap_buffer_t *gb);
void insert_char(gap_buffer_t *gb, char c);
void grow_gap_buffer(gap_buffer_t *gb);
void free_gap_buffer(gap_buffer_t *gb);

int main() {
  gap_buffer_t *gb = create_gap_buffer();
  char c;
  while ((c = getchar()) != '\n') {
    switch (c) {
    case '<':
      move_cursor_to_start(gb);
      break;
    case '>':
      move_cursor_to_end(gb);
      break;
    default:
      insert_char(gb, c);
      break;
    }
  }

  print_gap_buffer(gb);
  free_gap_buffer(gb);
  return 0;
}

gap_buffer_t *create_gap_buffer() {
  gap_buffer_t *gb = (gap_buffer_t *)malloc(sizeof(gap_buffer_t));
  gb->buffer = NULL;
  gb->gap_start = 0;
  gb->gap_end = 0;
  gb->buffer_size = 0;
  return gb;
}

void print_gap_buffer(const gap_buffer_t *gb) {
  for (unsigned long i = 0; i < gb->gap_start; i++)
    putchar(gb->buffer[i]);
  for (unsigned long i = gb->gap_end; i < gb->buffer_size; i++)
    putchar(gb->buffer[i]);
  putchar('\n');
}

void move_cursor_to_start(gap_buffer_t *gb) {
  unsigned long gap_size = gb->gap_end - gb->gap_start;
  memmove(&gb->buffer[gap_size], &gb->buffer[0], gb->gap_start * sizeof(char));
  gb->gap_start = 0;
  gb->gap_end = gap_size;
}

void move_cursor_to_end(gap_buffer_t *gb) {
  unsigned long gap_size = gb->gap_end - gb->gap_start;
  memmove(&gb->buffer[gb->gap_start], &gb->buffer[gb->gap_end],
          (gb->buffer_size - gb->gap_end) * sizeof(char));
  gb->gap_start = gb->buffer_size - gap_size;
  gb->gap_end = gb->buffer_size;
}

void insert_char(gap_buffer_t *gb, char c) {
  if (gb->gap_start == gb->gap_end) {
    grow_gap_buffer(gb);
  }
  gb->buffer[gb->gap_start] = c;
  gb->gap_start++;
}

void grow_gap_buffer(gap_buffer_t *gb) {
  if (gb->buffer_size == 0) {
    gb->buffer = (char *)calloc(1, sizeof(char));
    gb->gap_end = 1;
    gb->buffer_size = 1;
    return;
  }

  unsigned long new_size = gb->buffer_size * 2;
  char *new_buffer = (char *)calloc(new_size, sizeof(char));

  memcpy(new_buffer, gb->buffer, gb->gap_start * sizeof(char));
  memcpy(&new_buffer[new_size - (gb->buffer_size - gb->gap_end)],
         &gb->buffer[gb->gap_end],
         (gb->buffer_size - gb->gap_end) * sizeof(char));

  gb->gap_end = new_size - (gb->buffer_size - gb->gap_end);
  gb->buffer_size = new_size;
  free(gb->buffer);
  gb->buffer = new_buffer;
}

void free_gap_buffer(gap_buffer_t *gb) {
  free(gb->buffer);
  free(gb);
}
