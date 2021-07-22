#include <Adafruit_SSD1306.h>

#define HISTORY_LEN 1000

class Position {

    int history [HISTORY_LEN];
    int current_index;

    void addToHistory(int x);

    public:
        int left_sens;
        int right_sens;
        int x;
        int no_change; //Stores how long there has been no change for
        bool r;
        bool l;
        int last;

        Position(int left_sensor, int right_sensor);
        Position();

        void setSensors(int left_sensor, int right_sensor);
        int read();
        void showLR(Adafruit_SSD1306 display);
        int getXValue();
        int getDerivative();

        //~Position();
};