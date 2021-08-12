#include "Visualizer.hpp"

void Visualizer::initWindow() {
    videoMode.height = screenHeight;
    videoMode.width = screenWidth;
    window.create(videoMode, "Algorithm Visualizer");
    window.setFramerateLimit(60);
    start = false;
    reset = false;
}

void Visualizer::initRectangle() {
    rectangle.setFillColor(Color(255, 255, 255));
    rectangle.setOutlineThickness(-0.5);
    rectangle.setOutlineColor(Color(0, 0, 0));
}

void Visualizer::initBar() {
    rectangle.setFillColor(Color::White);
    for (int i = 0; i < barCount; i++) {
        bars[i].height = rand() % screenHeight + 1;
        bars[i].position = i * barWidth; 
    }
}

Visualizer::Visualizer() {
    initWindow();
    initRectangle();
    initBar();

}

const bool Visualizer::running() const {
    return window.isOpen();
}

void Visualizer::pollEvents() {
    while (window.pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::B) {
                    start = true;
                    reset = false;
                    bubbleSort();
                    rectangle.setFillColor(Color::Green);
                }
                if (event.key.code == Keyboard::I) {
                    start = true;
                    reset = false;
                    insertionSort();
                    rectangle.setFillColor(Color::Green);
                }
                if (event.key.code == Keyboard::Q) {
                    start = true;
                    reset = false;
                    quickSort(0, barCount - 1);
                    rectangle.setFillColor(Color::Green);
                }
                if (event.key.code == Keyboard::M) {
                    start = true;
                    reset = false;
                    mergeSort(0, barCount - 1);
                    rectangle.setFillColor(Color::Green);
                }
                break;
		}
    }
}

void Visualizer::resetEvent() {
    while (window.pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::R) {
                    reset = true;
                    start = false;
                    initBar();
                }
		}
    }
}

void Visualizer::swap(int& i, int& j) {
    int temp = i;
    i = j;
    j = temp;
}

void Visualizer::bubbleSort() {
    bool swapped;
    do {
        if (!running() || reset) return;
        swapped = false;
        for (int i = 0; i < barCount - 1; i++) {
            if (bars[i].height > bars[i + 1].height) {
                swap(bars[i].height, bars[i + 1].height);
                Render();
                swapped = true;
            }
        }
    } while (swapped);
}

void Visualizer::insertionSort() {
    int i = 0;
    int j;
    while (i < barCount - 1) {
        if (!running() || reset) return;
        j = i;
        while (j >= 0 && bars[j].height > bars[j + 1].height)
        {
            swap(bars[j].height, bars[j + 1].height);
            Render();
            j--;
        }
        i++;
    }
}

void Visualizer::merge(int begin, int mid, int end) {
    int i, j, k;
    int nBegin = mid - begin + 1;
    int nEnd = end - mid;

    int arrBegin[nBegin];
    int arrEnd[nEnd];
    for(i = 0; i < nBegin; i++) arrBegin[i] = bars[begin + i].height;

    for(j = 0; j < nEnd; j++) arrEnd[j] = bars[mid + 1 + j].height;

    i = 0;
    j = 0;
    k = begin;

   while(i < nBegin && j < nEnd) {
        if(arrBegin[i] <= arrEnd[j]) {
            bars[k].height = arrBegin[i];
            i++;
        } else {
            bars[k].height = arrEnd[j];
            j++;
        }
        Render();
        k++;
    }

    while(i < nBegin) {
        bars[k].height = arrBegin[i];
        Render();
        i++;
        k++;
    }

    while(j < nEnd) {
        bars[k].height = arrEnd[j];
        Render();
        j++;
        k++;
    }
}

void Visualizer::mergeSort(int begin, int end) {
    if (begin < end) {
        if (!running() || reset) return;
        int mid = begin + (end - begin) / 2;
//        Render();
        mergeSort(begin, mid);
//        Render();
        mergeSort(mid + 1, end);
//        Render();
        merge(begin, mid, end);
    }
}

int Visualizer::partition(int lo,int hi) {
    int pivot = bars[hi].height;
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (bars[j].height < pivot) {
            i++;
            swap(bars[i].height, bars[j].height);
            Render();
        }
    }
    swap(bars[i + 1].height, bars[hi].height);
    Render();
    return i + 1;
}

void Visualizer::quickSort(int lo, int hi) {
//    if (lo >= 0 && hi >= 0) {
        if (lo < hi) {
            if (!running() || reset) return;
            int pi = partition(lo, hi);
//            Render();
            quickSort(lo, pi - 1);
//            Render();
            quickSort(pi + 1, hi);
//            Render();
        }
//    }
}

void Visualizer::Update() {
    for (int i = 0; i < barCount; i++) {
        rectangle.setSize(Vector2f((float)barWidth, float(bars[i].height)));
        rectangle.setPosition(bars[i].position, screenHeight - bars[i].height);
        window.draw(rectangle);
    }
}

void Visualizer::Render() {
    window.clear();
    
    (!start) ? pollEvents() : resetEvent();
    Update();

    window.display();
}