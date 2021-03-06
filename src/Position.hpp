#include <Adafruit_SSD1306.h>

/** Abstraction of the position of the robot relative to the black line its following
 *  Useful for getting an "x" value which is defined as having the black line at x = 0
 *  Left side is + and right is -
 * 
 *  @author Lukas
 */
class Position {

    int last_state;
    int last_state_length;
    int current_index;

    void addToHistory(int x);

    public:
        int left_sens;
        int right_sens;
        int x;
        int no_change; //Stores how long there has been no change for
        bool r, l;
        int rr, rl;
        int last;

        Position(int left_sensor, int right_sensor);
        Position();

        void setSensors(int left_sensor, int right_sensor);
        int read();
        void showLR(Adafruit_SSD1306 display);
        int getXValue();
        int getDerivative();

        //~Position();

        int getNoChange();
        void reset();
};