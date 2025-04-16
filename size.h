#pragma once
class Size {
private:
	unsigned int width;
	unsigned int height;
public:
	Size(unsigned int w = 0, unsigned int h = 0) : width{ w }, height{ h } {};
};