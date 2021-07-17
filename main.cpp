#include "Play.h"

int main() {
    initgraph(950, 750);
    Play play;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        play.initialize();
        play.setMode();
        play.run();
    }
#pragma clang diagnostic pop
}
