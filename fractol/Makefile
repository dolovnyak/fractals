NAME = fractol

#-g -fsanitize=address

FLAGS = -c -O3 -Wall -Werror -Wextra 

MLXFLAGS = -lmlx -framework OpenGL -framework OpenCL -framework AppKit -O3 -Wall -Werror -Wextra

SRC = fractol.c \
	  initialization.c \
	  initialization_cl.c

SRC_MANDEL2D = mandel2d.c \
			   mandel2d_initialization.c \
			   mandel2d_mouse_events.c \
			   mandel2d_keyboard_events.c

SRC_MANDELFDF = mandelfdf.c \
			   mandelfdf_initialization.c \
			   mandelfdf_mouse_events.c \
			   mandelfdf_keyboard_events.c

UTILITS = color.c \
		  math_vec.c

INCLUDES = $(addprefix -I, ./includes)

LIB = libft/libft.a

DIR_O = objs

DIR_S = srcs

OBJS = $(addprefix $(DIR_O)/,$(SRC:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_MANDEL2D:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_MANDELFDF:.c=.o)) \
	$(addprefix $(DIR_O)/,$(UTILITS:.c=.o))

all: $(LIB) $(NAME)

$(LIB):
	@echo "\x1b[35;01mCompilation Lib and binary\x1b[32;01m"
	@make -C ./libft

$(NAME): $(DIR_O) $(OBJS)
	gcc -I /usr/local/include $(OBJS) $(LIB) -L /usr/local/lib/ $(MLXFLAGS) -o $(NAME)

$(DIR_O):
	mkdir -p $(DIR_O)

$(DIR_O)/%.o: $(DIR_S)/%.c
	gcc $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/mandel2d/%.c
	gcc $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/mandelfdf/%.c
	gcc $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/utilits/%.c
	gcc $(FLAGS) $(INCLUDES) -o $@ $<

clean:
	@echo "\x1b[36;01mDeliting .o files\x1b[31;01m"
	@/bin/rm -rf $(DIR_O)
	@make clean --directory ./libft

fclean: clean
	@echo "\x1b[36;01mDeliting execute file\x1b[31;01m"
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft

re: fclean all
