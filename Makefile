CC = gcc
CFLAGS = -Wall -Wextra -g
SRCS = tema1.c add_incident.c check_units_availability.c dispatch.c select_task.c show_interventions.c undo_last_dispatch.c show_incident.c show_unit.c solved_incident.c
OBJS = $(SRCS:.c=.o)
TARGET = tema1

.PHONY: build run clean

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
