enum Material {
    Sand,
    Water
};

class Canvas {
    private:
        unsigned char *data = nullptr;
    public:
        Canvas(unsigned short width, unsigned short height);
        ~Canvas();

        void update();
        void setPixel(unsigned short x, unsigned short y);
        Material getPixel(unsigned short x, unsigned short y);
};