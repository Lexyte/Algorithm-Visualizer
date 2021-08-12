#include "Visualizer.hpp"

int main() {
    srand(time(NULL));

    Visualizer Visualize;

    while (Visualize.running())
    {
//      Visualize.Update();

        Visualize.Render();
    }
    return 0;
}