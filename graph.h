#include <stdio.h>

#define WIDTH 200
#define HEIGHT 60

#define I2X(i)    (i % (WIDTH + 1))
#define I2Y(i)    (i / (WIDTH + 1))
#define XY2I(x,y) (y * (WIDTH + 1) + x)
#define B2I(x,y)  XY2I(x/2,y/4)
#define BX(x)     (x%2)
#define BY(y)     (y%4)
#define BCP(x,y)  braille[(BY(y)*2+BX(x))]

#define VBAR    0x2502
#define HBAR    0x2500
#define CENTER  0x253C

#ifdef logging
#define log(s)    printf("%s\n", #s);fflush(stdout);
#else
#define log(s) ;
#endif


#ifdef DELTA
#define COMP(a,b) ((a)-(b))*((a)-(b)) < DELTA
#else
#define COMP(a,b) (int)(a)==(int)(b)
#endif

static unsigned int braille[8] = {0x1, 0x8, 0x2, 0x10, 0x4, 0x20, 0x40, 0x80};

#define Bb 0x2800

#define GRAPH(Y, X) { \
	int size = (WIDTH + 1) * HEIGHT; \
	unsigned int str[size + 1]; \
	for (int i = 0; i < size; str[i++] = Bb); \
	log(initialized) \
	for (int i = WIDTH / 2; i < size; i += WIDTH + 1) { \
		str[i] = VBAR; \
	} \
	log(vertical axis) \
	for (int i = (HEIGHT / 2) * (WIDTH + 1); i < (HEIGHT / 2) * (WIDTH + 1) + WIDTH; i++) { \
		str[i] = HBAR; \
	} \
	log(horizontal axis) \
	for (int i = WIDTH; i < size; i += WIDTH + 1) { \
		str[i] = '\n'; \
	} \
	log(newlines) \
	str[XY2I(WIDTH/2,HEIGHT/2)] = CENTER; \
	log(center) \
	unsigned maxY = 0; \
	unsigned minY = -1; \
	for (int xf = 0; xf < WIDTH*2; xf++) { \
		int x = xf - WIDTH; \
		int xs = xf; \
		for (unsigned int yf = 0; yf < HEIGHT*4; yf++) { \
			int y = HEIGHT*2 - yf + 1; \
			int ys = yf; \
			int i = B2I(xs,ys); \
			unsigned int base = str[i]; \
			if (COMP(X,Y)) { \
				base = base < Bb ? Bb : str[i]; \
				base += BCP(xs,ys); \
			} \
			maxY = y > maxY ? y : maxY; \
			minY = y < minY ? y : minY; \
			log(assigning) \
			str[i] = base; \
			log(assigned) \
		} \
	} \
	printf("max: %u min: %u\n", maxY, minY); \
	log(graphed) \
	str[size] = 0; \
	printf("%ls", str); \
}
