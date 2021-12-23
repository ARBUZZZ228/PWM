const int RED_LED = 11;
const int GREEN_LED = 10;
const int BLUE_LED = 9;
const int BUTTON = 2; 
 
class ButtonLED
{
  private:
    bool lastButton_;
    bool currentButton_;
    int currState_;

    bool debounce(bool lastState)
    {
      bool currentState = digitalRead(BUTTON);
      if (lastState != currentState);
      {
        delay(10);
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
      int brightness = 0;
      analogWrite(GREEN_LED, 0);
      analogWrite(BLUE_LED, 10);
      
      while (brightness < 256) 
      {
        if (millis() % 50 == 0)
        {
          analogWrite(RED_LED, brightness);
          brightness++;
        }
      }

      while (brightness >= 0)
      {
        if (millis() % 50 == 0)
        {
          analogWrite(RED_LED, brightness);
          brightness--;
        }
      }
    }

    void pwmLemon()
    {
      int brightness = 0;
      analogWrite(RED_LED, 0);
      analogWrite(BLUE_LED, 20);
      
      while (brightness < 256)
      {
        if (millis() % 50 == 0)
        {
          analogWrite(GREEN_LED, brightness);
          brightness++;
        }
      }
      
      while (brightness >= 0)
      {
        if (millis() % 50 == 0)
        {
          analogWrite(GREEN_LED, brightness);
          brightness--;
        }
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
