const int RED_LED = 11;
const int GREEN_LED = 10;
const int BLUE_LED = 9;
const int BUTTON = 2; 

class ButtonLED
{
  private:
    bool lastButton_;
    bool currentButton_;
    bool ledOn_;
    int currState_;

    bool debounce(bool lastState)
    {
      bool currentState = digitalRead(BUTTON);
      if (lastState != currentState);
      {
        delay(20);
      }
      return digitalRead(BUTTON);
    }

    void changeState()
    {
      currentButton_ = debounce(lastButton_);
      if (!lastButton_ && currentButton_)
      {
        if (currState_ < 2)
        {
          currState_ += 1;
        }
        else
        {
          currState_ = 0;
        }
      }
      lastButton_ = currentButton_;
    }
    
    void pwmPink()
    {
      for (short int i = 0; i < 128; i++)
      {
        analogWrite(RED_LED, i);
        analogWrite(GREEN_LED, 0);
        analogWrite(BLUE_LED, 10);
        delay(20);
      }
      for (short int i = 127; i >= 0; i--)
      {
        analogWrite(RED_LED, i);
        analogWrite(GREEN_LED, 0);
        analogWrite(BLUE_LED, 10);
        delay(20);
      }
    }

    void pwmLemon()
    {
      for (short int i = 0; i < 128; i++)
      {
        analogWrite(RED_LED, 0);
        analogWrite(GREEN_LED, i);
        analogWrite(BLUE_LED, 20);
        delay(20);
      }
      for (short int i = 127; i >= 0; i--)
      {
        analogWrite(RED_LED, 0);
        analogWrite(GREEN_LED, i);
        analogWrite(BLUE_LED, 20);
        delay(20);
      }
    }

    void turnOff()
    {
      digitalWrite(RED_LED, 0);
      digitalWrite(GREEN_LED, 0);
      digitalWrite(BLUE_LED, 0);
    }

  public:
    ButtonLED()
    {
      lastButton_ = 0;
      currentButton_ = 0;
      ledOn_ = 0;
      currState_ = 0;
    }
    
    void light()
    {
      changeState();
      switch(currState_)
      {
        case 0:
        {
          turnOff();
          break;
        }
        case 1:
        {
          pwmPink();
          break;
        }
        case 2:
        {
          pwmLemon();
          break;
        }
      }
    }
};

void setup() {
  pinMode (RED_LED, OUTPUT);
  pinMode (GREEN_LED, OUTPUT);
  pinMode (BLUE_LED, OUTPUT);
  pinMode (BUTTON, INPUT);
}

ButtonLED buttonLed;

void loop() {
  buttonLed.light();
}
