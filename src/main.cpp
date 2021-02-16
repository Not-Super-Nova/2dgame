#include <simple2d.h>

void log(char str[]) {
	printf("%s\n", str);
}

void render() {
	S2D_DrawCircle(320, 240, 64, 64, 1, 1, 1, 1);
}

void on_key(S2D_Event e) {
	switch (e.type)
	{
		case S2D_KEY_DOWN:
			printf("Key %X down\n", e.key);
			break;
		case S2D_KEY_HELD:
			printf("Key %X held\n", e.key);
			break;
		case S2D_KEY_UP:
			printf("Key %X up\n", e.key);
			break;
	}
}

int main() {
	S2D_Window *window = S2D_CreateWindow(
"Hello Triangle", 640, 480, NULL, render, 0
	);
	window -> on_key = on_key;
	S2D_Show(window);
	return 0;
}
