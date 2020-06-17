//imageio header file

extern unsigned char * load(const char *filename, int &width, int &height);
extern void save(const char * filename, const unsigned char * image, int width, int height, const char * type, int quality); 
