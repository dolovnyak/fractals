NAME = fractol

#-g -fsanitize=address

FLAGS = -O3 -Wall -Werror -Wextra

FRAMEWORKS = -framework OpenGL -framework OpenCL -framework AppKit

SRC = fractol.c

SRC_MANDEL2D = mandel2d.c \
			   mandel2d_pow5.c \
			   mandel2d_initialization.c

SRC_MANDELFDF = mandelfdf.c \
				mandelfdf_initialization.c \

SRC_MANDEL3D = mandel3d.c \

SRC_JULIA2D = julia2d.c \
			  julia2d_pow5.c \
			  julia2d_initialization.c \
			  julia2d_events.c

SRC_JULIAFDF = juliafdf.c \
			   juliafdf_events.c \
			   juliafdf_initialization.c

SRC_JULIA3D = julia3d.c \

SRC_SHIP2D = burning_ship2d.c \
			 burning_ship2d_pow5.c \
			 burning_ship2d_initialization.c

SRC_NEWTON = newton_pow3.c \
			 newton_pow5.c \
			 newton_initialization.c

SRC_DICK = fractal_dick.c \
		   fractal_dick_initialization.c

SRC_RT = render_safety.c \
		 render_fast.c \
		 ray_trace_initialization.c \
		 create_objects.c \
		 create_lights.c \
		 render_keyboard_events.c \
		 get_objects_from_points.c

SRC_COMMON = common_events_for_2d.c \
			 common_events_for_fdf.c \
			 exit_event.c \
			 initialization_cl.c \
			 initialization_mlx.c \
			 utilits_for_initialization_cl.c

UTILITS = color.c \
		  math_vec1.c \
		  math_vec2.c \
		  math_complex1.c \
		  math_complex2.c

INCLUDES = -I ./includes -I ./minilibx_macos

LIBFT = ./libft/libft.a

LIBMLX = -L ./minilibx_macos -lmlx

DIR_O = objs

DIR_S = srcs

OBJS = $(addprefix $(DIR_O)/,$(SRC:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_MANDEL2D:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_MANDELFDF:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_MANDEL3D:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_JULIA2D:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_JULIAFDF:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_JULIA3D:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_SHIP2D:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_NEWTON:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_DICK:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_COMMON:.c=.o)) \
	$(addprefix $(DIR_O)/,$(UTILITS:.c=.o)) \
	$(addprefix $(DIR_O)/,$(SRC_RT:.c=.o)) 

all: make_libs $(NAME)

$(NAME): $(DIR_O) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT) $(LIBMLX) $(FRAMEWORKS) -o $(NAME)

$(DIR_O):
	mkdir -p $(DIR_O)

$(DIR_O)/%.o: $(DIR_S)/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/mandel2d/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/mandelfdf/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/mandel3d/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/julia2d/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/juliafdf/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/julia3d/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/burning_ship2d/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/newton/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/fractal_dick/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/ray_trace_render/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/common/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

$(DIR_O)/%.o: $(DIR_S)/utilits/%.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<

make_libs:
	@echo "\x1b[35;01mCompilation Libraries\x1b[32;01m"
	@make -C ./libft
	@make -C ./minilibx_macos

clean:
	@echo "\x1b[36;01mDeliting .o files\x1b[31;01m"
	@/bin/rm -rf $(DIR_O)
	@make clean --directory ./libft
	@make -C ./minilibx_macos/ clean

fclean: clean
	@echo "\x1b[36;01mDeliting execute file\x1b[31;01m"
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft
	@make -C ./minilibx_macos/ clean

re: fclean all
