bool raw_state = 1;
bool previous_state = 1;
bool button_state = 1;
uint8_t debounce_counter = 0;

#define DEBOUNCE_MAX 100
#define DEBOUNCE_MIN 0

void IRAM_ATTR D15_ISR()
{
    raw_state = digitalRead(15);
}

void debounce_update()
{
    if (!raw_state)
    {
        if (debounce_counter < DEBOUNCE_MAX)
        {
            debounce_counter++;            
        }
        else
        {
          button_state = true;
        }
    }
    else
    {
        if (debounce_counter > DEBOUNCE_MIN)
        {
            debounce_counter--;            
        }
        else
        {
          button_state = false;
        }
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(15, INPUT_PULLUP);
    attachInterrupt(15, D15_ISR, CHANGE);
}

void loop()
{
    debounce_update();
    if (button_state != previous_state)
    {
        previous_state = button_state;
        Serial.println(button_state ? "Released" : "Pressed");
    }
}
