
#include <xc.h>
#include "mcc_generated_files/system/system.h"
#include "application.h"
#include "string.h"

#define CIRCUMFERENCE         0.0188f  // Circumference (Wheel radius is 3cm= 0.003 meters) = 2*pi*r 
#define KMPH_TO_METERS        0.277f   // Converting KMPH to Metres 
#define NUMBER                6

#define MIN_SPEED             (100)
#define AVERGE_SPEED          (150)
#define MAX_SPEED             (600)
#define ZERO_SPEED            (0)

typedef enum
{
    INIT_STATE,
    WAIT_FOR_SWITCH_PRESS,
    MINIMUM_SPEED,
    AVERAGE_SPEED,
    MAXIMUM_SPEED,    
    MOTOR_OFF,
}speed_t;

typedef enum
{
    KEY_NO_ACTION,
    KEY_PRESSED,
    KEY_RELEASED,
}buttonstate_t;


volatile uint16_t rpm;
volatile uint16_t counter;
volatile uint8_t timerFlag;
volatile uint8_t pulsesCount;

static volatile speed_t applicationCurrentState = INIT_STATE;
static volatile speed_t applicationPreviousState;
static volatile buttonstate_t buttonState = KEY_NO_ACTION;

void SendString(uint8_t *data);

void my_reverse(uint8_t str[], uint16_t  len);
uint8_t* my_itoa(uint16_t num, uint8_t str[], uint16_t base1);


/*******************************************************************************
 * void ControlWheelSpeed(void)
 *
 * API to control the speed of the wheel with the following switch press events :
 * First switch press = minimum speed, 
 * Second switch press = average speed and 
 * Third switch press = maximum speed
 * Fourth switch press = turns OFF the wheel rotation
 * @param void 
 * @return void
 ******************************************************************************/
void ControlWheelSpeed(void)
{
    switch (applicationCurrentState)
        {
            case INIT_STATE:
                applicationCurrentState  += 1;
                applicationPreviousState = applicationCurrentState;
                break;
            case WAIT_FOR_SWITCH_PRESS:
                if(buttonState == KEY_PRESSED)
                    {
                        buttonState  = KEY_RELEASED;
                        applicationCurrentState = applicationPreviousState + 1;
                    }
                break;
            case MINIMUM_SPEED:
                EN_SetHigh();
                PWM3_LoadDutyValue(MIN_SPEED); 
                LED_TOGGLE();
                applicationPreviousState = applicationCurrentState;
                applicationCurrentState = WAIT_FOR_SWITCH_PRESS;
                break;
            case AVERAGE_SPEED:
                applicationPreviousState = applicationCurrentState;
                PWM3_LoadDutyValue(AVERGE_SPEED); 
                LED_TOGGLE();
                applicationCurrentState = WAIT_FOR_SWITCH_PRESS;
                break;
            case MAXIMUM_SPEED:
                applicationPreviousState = applicationCurrentState;
                PWM3_LoadDutyValue(MAX_SPEED); 
                LED_TOGGLE();
                applicationCurrentState = WAIT_FOR_SWITCH_PRESS;
                break;
            case MOTOR_OFF:
                LED_TOGGLE();
                EN_SetLow();
                PWM3_LoadDutyValue(ZERO_SPEED); 
                applicationCurrentState = WAIT_FOR_SWITCH_PRESS;
                applicationPreviousState = 0;
                applicationCurrentState = 0;
                break;
            default:
                break;
        }
}

/*******************************************************************************
 * void SpeedDistanceCalculation(void)
 *
 * API to calculate the Speed and Distance using the formula
 * Speed = Circumference x RPM
 * Distance = Speed x Time 
 * @param void 
 * @return void
 ******************************************************************************/
void SpeedDistanceCalculation(void)
{
    volatile uint16_t speedValue = 0;
    volatile uint16_t distanceValue = 0;
    static volatile uint16_t decSpeed = 0;
    static volatile uint16_t decDistance = 0;

    static volatile uint16_t distanceSum = 0;
    volatile float distance = 0;
    volatile float speedToMetres = 0;
    volatile float speedInKmph = 0;
    
    uint8_t baseValue = 10;
    uint8_t string[12];
    uint8_t* trasmitBuffer;
    
    if(timerFlag)
    {   
    rpm = (counter * NUMBER);
    speedInKmph = ((CIRCUMFERENCE * rpm) * 60); 
    
    speedValue = (uint16_t) (speedInKmph / 1000);
    decSpeed = ((uint16_t)(speedInKmph) % 1000);

    speedToMetres = (speedInKmph * KMPH_TO_METERS);
    distance = (speedToMetres * 10);
    
    distanceSum = distanceSum + (uint16_t)distance;
    distanceValue = (distanceSum / 100);
    decDistance = (distanceSum % 100);

    trasmitBuffer = my_itoa(speedValue ,string, baseValue);
      SendString((uint8_t*)"Speed is ");
      SendString(trasmitBuffer);
      SendString((uint8_t*)".");
      
    trasmitBuffer = my_itoa(decSpeed , string, baseValue);  
      SendString(trasmitBuffer);
      SendString((uint8_t*)"Kmph \n");
     
    
    trasmitBuffer = my_itoa(distanceValue , string, baseValue);
      SendString((uint8_t*)"Distance is ");
      SendString(trasmitBuffer);
      SendString((uint8_t*)".");
      
    trasmitBuffer = my_itoa(decDistance, string, baseValue);
      SendString(trasmitBuffer);
      SendString((uint8_t*)" meters \n");
    
    timerFlag = 0;
    counter = 0;
    
    }
   
    
}

/*******************************************************************************
 * void SwitchPressInterrupt_Handler(void)
 *
 * Interrupt Handler to detect the switch press event 
 * @param void 
 * @return void
 ******************************************************************************/
void SwitchPressInterrupt_Handler(void)
{
    
    buttonState = KEY_PRESSED;
    __delay_ms(100);
    Timer0_Start();
   
}

/*******************************************************************************
 * void CCPInterrupt_Handler(void)
 *
 * Interrupt Handler to capture the pulses generated by the bi hall click due to 
 * magnetic field
 * @param void 
 * @return void
 ******************************************************************************/
void CCPInterrupt_Handler(uint16_t dummy)
{
    pulsesCount++;
}

/*******************************************************************************
 * void TimerInterrupt_Handler(void)
 *
 * Interrupt Handler to generate 10 secs delay
 * @param void 
 * @return void
 ******************************************************************************/
void TimerInterrupt_Handler(void)
{    
    timerFlag = 1; 
    counter = pulsesCount;
    pulsesCount = 0;
}

/*******************************************************************************
 * void SendString(uint8_t *data)
 *
 * Function used to transmit the data on Data Visualizer
 * @param void 
 * @return void
 ******************************************************************************/
void SendString(uint8_t *data)
{
	uint8_t i = 0;
	for (i = 0; data[i] != '\0'; i++) 
    {
		// sending the data through EUSART2 peripheral
        while(0 == PIR1bits.TX1IF)
        {

        }
        EUSART1_Write(data[i]);
		
	}
}

/*******************************************************************************
 * void my_reverse(uint8_t str[], uint16_t len)
 *
 * Function to reverse a string
 * @param void 
 * @return void
 ******************************************************************************/
void my_reverse(uint8_t str[], uint16_t len)
{
    uint16_t  start, end;
    uint8_t temp;
    for(start=0, end=len-1; start < end; start++, end--) {
        temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
    }
}

/*******************************************************************************
 * uint8_t* my_itoa(uint16_t num, uint8_t str[], uint16_t base1)
 *
 * Function to convert integer to ASCII character
 * 
 * @param num, str, base1
 * @return (uint8_t) str
 ******************************************************************************/
uint8_t* my_itoa(uint16_t num, uint8_t str[], uint16_t baseNumber)
{
    uint16_t i = 0;
    uint16_t rem;
    uint8_t buffer = 0;
   
    /* A zero is same "0" string in all base */
    if (num == 0) {
        str[i] = '0';
        str[i + 1] = '\0';
        return str;
    }
  
    while (num != 0) {
        rem = num % baseNumber;
        buffer = (uint8_t)rem;
        str[i++] = (uint8_t)(buffer > 9)? (buffer-10) + 'A' : buffer + '0';
        num = num/baseNumber;
    }
  
    str[i] = '\0';
    my_reverse(str, i);
  
    return str;
}

