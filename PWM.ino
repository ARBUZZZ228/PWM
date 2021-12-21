const int LED = 11;
const int BUTTON = 2;

bool lastButton, currentButton, ledOn;
class ButtonLED
{
  private:
    bool lastButton_;
    bool currentButton_;
    bool ledOn_;
  
  public:
    ButtonLED()
    {
      lastButton_ = 0;
      currentButton_ = 0;
      ledOn_ = 0;
    }
  
    bool debounce(bool last_state_)
    {
      bool current_state_ = digitalRead(BUTTON);
      if (last_state_ != current_state_);
      {
        delay(10);
      }
      return digitalRead(BUTTON);
    }

    void checkState()
    {
      currentButton_ = debounce(lastButton_);
      if (!lastButton_ && currentButton_)
      {
        ledOn_ = !ledOn_;
      }
      lastButton_ = currentButton_;
    }

    void pwm()
    {
      if (ledOn_)
      {
        for (int i = 0; i < 256; i++)
        {
          analogWrite(LED, i);
          delay(10);
        }
        for (int i = 255; i >= 0; i--)
        {
          analogWrite(LED, i);
          delay(10);
        }
      }
      else
      {
        digitalWrite(LED, 0);
      }
    }
};

void setup() {
  pinMode (LED, OUTPUT);
  pinMode (BUTTON, INPUT);
}

ButtonLED buttonLed;

void loop() {
  buttonLed.checkState();
  buttonLed.pwm();
}
