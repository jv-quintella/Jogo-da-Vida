
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

INCLUDES = -Icontroller/jogo \
           -Imodel/jogo \
           -Imodel/struct \
           -Iview/jogo \
           -Iview/menu \
           -Iview/utilidades

SRC = JVIDA_HJRV_main.c \
      controller/jogo/JVIDA_HJRV_controller_jogo.c \
      model/jogo/JVIDA_HJRV_model_jogo.c \
      view/jogo/JVIDA_HJRV_view_jogo.c \
      view/menu/JVIDA_HJRV_view_menu.c \
      view/utilidades/JVIDA_HJRV_view_utilidades.c

TARGET = jogo_da_vida

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
