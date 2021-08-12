#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const unsigned int screenHeight = 600;
const unsigned int screenWidth = 800;
const unsigned int barWidth = 5;

const int barCount = screenWidth / barWidth;

class Bar {
    public:
        int position;
        int height;
};

class Visualizer {
    private:
        RenderWindow window;
        VideoMode videoMode;
        Event event;

        RectangleShape rectangle;
        Bar bars[barCount];

        bool start;
        bool reset;
        
        void initWindow();
        void initRectangle();
        void initBar();
    public:
        Visualizer();
//        virtual ~Visualizer();

        const bool running() const;

        void pollEvents();
        void resetEvent();

        void swap(int&, int&);

        void bubbleSort();
        void insertionSort();
        void merge(int, int, int);
        void mergeSort(int, int);
        int partition(int, int);
        void quickSort(int, int);

        void Render();
        void Update();
};