
// ========================================================================================================================
#include "project.h"
#include <stdio.h>
#include <stdlib.h>

void display_num(double value);
void draw_7Seg(int number,int dp);
CY_ISR(seg7_ISR);
CY_ISR(Receive_Ultra);

void print_uart(int num);
double current_second();
void BuzzerSound(double duration);
void BuzzerRuntime(double duration);
void seg_runtime(double value);
int clear_7_seg();

void EEPROM_writeDouble(uint16 address, double value);
double EEPROM_readDouble(uint16 address);
void writeDoubleArrayToEEPROM(uint16 startAddress, double* array, uint16 arraySize);
void readDoubleArrayFromEEPROM(uint16 startAddress, double* array, uint16 arraySize);
void EEPROM_writeInt(uint16 address, int value);
int EEPROM_readInt(uint16 address) ;

void mode_0(void);
void mode_1(void);
void mode_2(void);
void mode_3(void);

void MetricLedOn(void);
void ImperialLedOn(void);
void SingleButtonWait(void);
void DoubleButtonWait(void);

float find_median(float arr[], int size);
int compare_qsort(const void *a, const void *b);

double ultra_avg();
double ultra_reading();

void runtime();
void EEPROM_writeInt(uint16 address, int value);




// ========================================================================================================================
double counter = 0;

int time_passed_step=0;
double previous_buzz= 0;

double buzz_duration=0;
double seg_num =0;



int mode = 0;
int group_num = 0;
char cm_or_inch;

double distance=0;



int main(void)
{
    // Enable interrupts
    CyGlobalIntEnable; 
    
    // 7 Segment display setup
    isr_7Seg_ClearPending(); 
    isr_7Seg_StartEx(seg7_ISR);  
    
    //  Ultrasonic transmitter setup
    isr_6_ClearPending(); 
    Timer_1_SetInterruptMode(3);
    isr_6_StartEx(Receive_Ultra);  
    
    // Ultrasonic receiver setup
    PGA_1_Start();
    Opamp_1_Start();
    Comp_1_Start();
    VDAC8_1_Start();
    Count7_1_Start(); 
    
    // Global clock timer 
    Timer_2_SetInterruptMode(3);
    Timer_2_Start();
    
    // Setup EEPROM
    EEPROM_Start(); 
    
    // Setup UART
    UART_1_Start();
    UART_1_PutString("Start UART");
    CyDelay(5);
    UART_1_WriteTxData(0x20);   
    CyDelay(5);
    
    double setup_previous_time =current_second();
    while((current_second()-setup_previous_time)<=4)
    {
        if((int)(current_second()-setup_previous_time) ==0) display_num(-5);
        if((int)(current_second()-setup_previous_time) ==1) display_num(-6);
        if((int)(current_second()-setup_previous_time) ==2) display_num(-7);
        if((int)(current_second()-setup_previous_time) ==3) display_num(-8);
        runtime();
    }
    
    // EEPROM Write startup
    //
    // Place your initialization/startup code here (e.g. MyInst_Start())
    //int teamNumber = 200;
    //EEPROM_writeInt(0, teamNumber);
    //int nextAddress = sizeof(int);
    //char measurementSystem = 'c';
    //EEPROM_WriteByte((uint8)measurementSystem, nextAddress);
    //nextAddress += sizeof(char);
    //double calibration[55] = {0.0};
    //writeDoubleArrayToEEPROM(nextAddress, calibration, 55);
    //
    
    //int eprom_read = EEPROM_ReadByte(0x00);
    //int eprom_write =eprom_read+1;
    //EEPROM_WriteByte(eprom_write,0x0000);
    
    
    //int eprom_num = EEPROM_ReadByte(55*sizeof(double)+sizeof(char));
    
    group_num = EEPROM_ReadByte(0);
    cm_or_inch = EEPROM_ReadByte(sizeof(int));
    
    
    double previous_second = current_second();
    for(;;)
    {
    
        
        //UART_1_WriteTxData(0x20);    
        //print_uart(mode);
        
        if (mode==0)
        {
            UART_1_PutString("Mode 0\n");
            CyDelay(5);
            
            EEPROM_WriteByte((uint8)cm_or_inch, sizeof(int));
            mode_0();
        
        }
        if (mode==1)
        {
            UART_1_PutString("Mode 1\n");
            CyDelay(5);
            
            mode_1();
        }
        if (mode==2)
        {
           UART_1_PutString("Mode 2\n");
           CyDelay(5);
        
           // TODO problem with EEPROM write
           EEPROM_writeInt(0, group_num);
           mode_2();
        }
        if (mode==3)
        {
            
            UART_1_PutString("Mode 3\n");
            CyDelay(5);
            
            mode_3();
        }
        CyDelay(5);
        //mode_0();
        
        
        //if(Button_S5_Select_State_Read()==0)
        //{
        //   clear_7_seg();
        //   display_num(ultra_avg());
        //}
        
        
        //display_num( current_second());
        //display_num( 0);
        //if (cm_or_inch =='c') display_num(-1);
        //if (cm_or_inch =='i') display_num(-2);
        
        //display_num( eprom_num);
        //display_num(Button_S5_Select_State_Read()*1000+ Button_S2_Left_Read()*100+Button_S4_Right_Read()*10);
        //display_num(-3);
        //BuzzerRuntime(0.2);
        runtime();
        
        
    }
    
}

// ========================================================================================================================
//sleep mode
void mode_0(void)
{
    double previous_second_decimal=current_second();
    while (mode == 0) {
        
        //UART_1_PutString("1");
        //CyDelay(5);
        
        //flash decimal point 1 second on, off
        double time_diff = current_second()-previous_second_decimal;
            
        if (time_diff<=1)                               display_num(-3); //display decimal
        else if ((time_diff > 1)  && (time_diff <= 2))  display_num(-4); //display blank
        else previous_second_decimal = current_second();
        
      
        //check if either button is pressed
        if ((Button_S5_Select_State_Read() == 0) || (Button_S2_Left_State_Read() == 0))
        {
            
            //wait 0.2 seconds to delay check
            double check_second = current_second();
            while ((current_second() - check_second )<0.2)  runtime();
            
            
            
            //if both buttons pressed, wait 1 seconds to go to mode 1
            if ((Button_S5_Select_State_Read() == 0) && (Button_S2_Left_State_Read() == 0))
            {
                BuzzerSound(0.2);
                check_second = current_second();        
                while ((Button_S5_Select_State_Read() == 0) && (Button_S2_Left_State_Read() == 0))
                {
                    runtime();
                    if (current_second()-check_second==1)
                    {
                        
                        UART_1_PutString("Enter Mode 1\n");
                        CyDelay(5);
                        mode = 1;
                        break;
                    }
                }  
            }
            
            //if instead just button 1 is pressed, go to mode 3
            else if ((Button_S5_Select_State_Read() == 0) && (Button_S2_Left_State_Read() == 1))
            {
                mode =3;
            }
        }
        runtime();
        
        
        
    }
}

//program mode
void mode_1(void)
{
    double previous_second=0;
    while (mode == 1) {
       
        runtime();
        //flash group number
        double time_diff = current_second()-previous_second;
        if (time_diff<=1)
        {
           display_num(group_num); // group_num
            //display_num(200); // group_num
        }
        else if ((time_diff>1) && (time_diff<=1.5))
        {
            display_num(-4); // Blank
        }
        else
        {
            previous_second = current_second();
        }
       
       
        // Check to go to mode 2
        if (Button_S4_Right_State_Read() == 0) // Assuming active low buttons
        {
            SingleButtonWait();
            BuzzerSound(0.2);
            mode = 2;
        }
        //check to increment number
        if (Button_S5_Select_State_Read() == 0)
        {
            SingleButtonWait();
            BuzzerSound(0.2);
            group_num ++;
        }
        //check to decrement number
        if (Button_S2_Left_State_Read() == 0)
        {
            SingleButtonWait();
            BuzzerSound(0.2);
            group_num --;
        }
    }
}

//system change mode
void mode_2(void)
{
    while (mode == 2)
    {
        runtime();
        
        // Display cm or inch
        if (cm_or_inch =='c') display_num(-1);
        if (cm_or_inch =='i') display_num(-2);
        
        //check to go to mode 0
        if (Button_S4_Right_State_Read() == 0)
        {
            SingleButtonWait();
            BuzzerSound(0.2);
            mode = 0;
        }
        //Set system to metric (centimeters)
        if (Button_S5_Select_State_Read() == 0)
        {
            SingleButtonWait();
            BuzzerSound(0.2);
            MetricLedOn();
            
            cm_or_inch = 'c'; // set system to use cm
        }
        //Set system to imperial (inches)
        if (Button_S2_Left_State_Read() == 0)
        {
            SingleButtonWait();
            BuzzerSound(0.2);
            ImperialLedOn();
            
            cm_or_inch = 'i'; // set system to use inch
            
           
        }
    }
    
    EEPROM_WriteByte(cm_or_inch,sizeof(int));

}

 //ultrasonic reading and display mode
void mode_3(void)
{
   
    int flag_read = 1;
    double previous_second;
    while (mode == 3)
    {
        //check if first time entering loop
        if (flag_read == 1)
        {
            
            BuzzerSound(0.2);
            distance = ultra_avg();
            
            previous_second= current_second();
            
            clear_7_seg();
            flag_read = 0;
            
            // output distance in cm currently
            
            // convert to inch if needed
            
            if (cm_or_inch =='i') distance = distance/2.54;
        }
       
        display_num(distance);
        runtime();
       
        //check if loop has gone for over 2 seconds
        if (current_second()-previous_second >=2)
        {
            //if button pressed, reset whole loop from start. else go to mode 0
            if (Button_S5_Select_State_Read() == 0)
            {
                clear_7_seg();
                BuzzerSound(0.2);
                flag_read=1;
            }
            else
            {
                mode = 0;
            }
        }
       
    }
   
}




void MetricLedOn(void)
{
    // TODO enable metric LED back again
    LED2_Yellow_Write(0);
    LED3_Green_Write(1);
}

void ImperialLedOn(void)
{
    LED3_Green_Write(0);
    LED2_Yellow_Write(1);

}

void SingleButtonWait(void)
{
    while (Button_S4_Right_State_Read()==0 || Button_S5_Select_State_Read()==0 || Button_S2_Left_State_Read()==0)
    {
        runtime();
    }
}

void DoubleButtonWait(void)
{
    while (Button_S5_Select_State_Read() == 0 && Button_S2_Left_State_Read() == 0)
    {
        runtime();
    }
}

// ========================================================================================================================
/* System timer*/
void runtime()
{
    BuzzerRuntime(buzz_duration);
    seg_runtime(seg_num);
    
    if (cm_or_inch =='i')ImperialLedOn();
    else  MetricLedOn();
    
    /*if(mode==0) LED1_Red_Write(1);
    if(mode==1) LED2_Yellow_Write(1);
    if(mode==2) LED3_Green_Write(1);
    if(mode==3) 
    {
        LED2_Yellow_Write(1);
        LED3_Green_Write(1);
    }*/
    
}

double current_second()
{
    double time = (double)(Timer_2_ReadPeriod()-Timer_2_ReadCounter());
    time = time/1000;
    
    return time;
}
// ========================================================================================================================
/* EEPROM */

void EEPROM_writeInt(uint16 address, int value) {
    uint8* ptr = (uint8*) &value;  // Convert int to byte array
    for (uint8 i = 0; i < sizeof(int); i++) {
        EEPROM_WriteByte(ptr[i], address + i);
    }
}

/*
void EEPROM_writeDouble(uint16 address, double value) {
    uint8 ptr = (uint8)(void*)&value;  // Convert double to byte array
    for (uint8 i = 0; i < sizeof(double); i++) {
        EEPROM_WriteByte(ptr[i], address + i);
    }
}

double EEPROM_readDouble(uint16 address) {
    double value = 0.0;
    uint8 ptr = (uint8)(void*)&value;
    for (uint8 i = 0; i < sizeof(double); i++) {
        ptr[i] = EEPROM_ReadByte(address + i);
    }
    return value;
}

void writeDoubleArrayToEEPROM(uint16 startAddress, double* array, uint16 arraySize) {
    for (uint16 i = 0; i < arraySize; i++) {
        EEPROM_writeDouble(startAddress + i * sizeof(double), array[i]);
    }
}

void readDoubleArrayFromEEPROM(uint16 startAddress, double* array, uint16 arraySize) {
    for (uint16 i = 0; i < arraySize; i++) {
        array[i] = EEPROM_readDouble(startAddress + i * sizeof(double));
    }
}

void EEPROM_writeInt(uint16 address, int value) {
    uint8 ptr = (uint8)(void*)&value;  // Convert int to byte array
    for (uint8 i = 0; i < sizeof(int); i++) {
        EEPROM_WriteByte(ptr[i], address + i);
    }
}

int EEPROM_readInt(uint16 address) {
    int value = 0;
    uint8 ptr = (uint8)(void*)&value;
    for (uint8 i = 0; i < sizeof(int); i++) {
        ptr[i] = EEPROM_ReadByte(address + i);
    }
    return value;
}*/

// ========================================================================================================================
/* UART communications */

uint8 value_text[16];
void print_uart(int num)
{ 
    int num_digits = 0;
    int temp = num;
    
    // Count the number of digits (optional for pre-allocation)
    while (temp != 0) {
        temp /= 10;
        num_digits++;
    }

    for (int i = num_digits-1; i >= 0; --i) {
        value_text[i] = num % 10;
        num /= 10;
    }
    
    for (int i = 0; i < num_digits; ++i) {
        UART_1_WriteTxData(value_text[i]+0x30); //display number
        CyDelay(5);
    }
    
}

// ========================================================================================================================
/* Buzzer */
void BuzzerSound(double duration)
{
    previous_buzz = current_second();
    buzz_duration= duration;
}
void BuzzerRuntime(double duration)
{
    double buzz_time_diff = current_second()-previous_buzz;
    
    if(buzz_time_diff<duration) Buzzer_Write(0);  // Turn on buzzer
    else Buzzer_Write(1); // Turn off buzzer
}



// ========================================================================================================================
/* Ultrasinic launch function*/

int waiting_ultra = 0;

double ultra_avg(){
 
    //UART_1_PutString("1");
    //CyDelay(5);
    float vals[10] = {0,0,0,0,0,0,0,0,0,0};
    float count_median[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double predicted_dist;
    double actual_dist;
    
    //UART_1_PutString("2");
    //CyDelay(5);
    for(int x = 0; x< 20 ; x++)
    {
        
        //runtime();
        //UART_1_PutString("3");
        //CyDelay(5);
        for (int i = 0; i < 10; i++) 
        {    
        BuzzerRuntime(buzz_duration);
            
        //UART_1_PutString("4");
        //CyDelay(5);
        vals[i] = ultra_reading();
        }
        
        //UART_1_PutString("5");
        //CyDelay(5);
        count_median[x] = find_median(vals, 10);
    }
            
    predicted_dist = find_median(count_median, 20);
    
    // Linear fitting using eeprom values
    float a1 = 0.798;
    float a0 = -0.789;
    actual_dist = a1* predicted_dist + a0;
    return actual_dist;
}

double ultra_reading()
{
    isr_6_ClearPending();
    isr_6_StartEx(Receive_Ultra);  
    
    // Send pulse
    Control_Reg_1_Write(1); // Reset counter to do more pulses
    CyDelayUs(150);
    Control_Reg_1_Write(0);
    
    Timer_1_Start();        // Start receiver timer
    waiting_ultra =1;
    
    // Wait for response
    // TODO: may need to write blocking code to obtain ultrasonic values
    double previous_ultra_second=current_second();
    double time_diff = current_second()-previous_ultra_second;
    
    
    //while(waiting_ultra==1 && (current_second()-previous_ultra_second)<1){
    //    runtime();
    //}
    CyDelay(10);

    double value =  (double)time_passed_step/10000; //in ms
    distance = (34*value)/2;
    
    return distance;
}
void send_ultra_pulse()
{
    Control_Reg_1_Write(1); // Reset counter to do more pulses
    CyDelayUs(150);
    Control_Reg_1_Write(0);
    
    Timer_1_Start();        // Start receiver timer
    
    waiting_ultra =1;
}

uint8 InterruptCnt;
CY_ISR(Receive_Ultra)  // Ultrasonic Receiver
{
    Timer_1_Stop();
    time_passed_step = Timer_1_ReadPeriod()-Timer_1_ReadCounter() ;
    waiting_ultra =0;
    
    //print_uart(time_passed_step);
}

// Compare two values for quick sort
int compare_qsort(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

// Find the median of a given array
float find_median(float arr[], int size) 
{
    double median;
    qsort(arr, size, sizeof(int), compare_qsort); // Sort the array

    // Check if the size of the array is odd or even
    if (size % 2 == 0) 
    {
        median = (arr[(size/2)-2] + arr[(size/2)-1] + arr[size/2] + arr[(size/2)+1] + arr[(size/2)+2]) / 5.0;
    }
    else
    {
//        median = (arr[(size - 1) / 2] + arr[size / 2]) / 2.0;
        median = (arr[((size-1)/2)-2] + arr[((size-1)/2)-1] + arr[(size-1)/2] + arr[(size+1)/2]+ arr[((size+1)/2)+1] + arr[((size+1)/2)+2]) / 6.0;
    }
    return median;
}
// ========================================================================================================================
/* Mid Level 7 Segment display code*/

//Global variable
int run_7_Seg = 0;

// Interrupt routine for displaying each sections
CY_ISR(seg7_ISR) 
{
    run_7_Seg = 1;
}

double old_dis_val=0;

int D[4]= {0,0,0,0};
int dp[4]={0,0,0,0};
unsigned long count = 0;

void display_num(double value)
{
    seg_num = value;
}
void seg_runtime(double value){
      
    if (run_7_Seg==0) return; // Ignore the rest of the code when interrupt is not triggered
    
    for (int i = 0; i < 4; ++i) dp[i] = 0; // Reset all 0 
    if(value>0)
    {
    
        //////////////// Code after this would only run once per interrupt////////////////
        // Only update the value when it gets a new value (for consistency and save computation for pooling loop)
        if((value != old_dis_val)){ 
            // Convert double to d1,d2,d3,d4,dp_pos
            int dp_pos = 0;
            
            if (value>=1){ // For values above 1
            while(value<1000){
                value=value*10;
                 dp_pos+=1;
            }
                    
            // Extract integer and decimal parts
            int digits = (int)value;
                    
            D[0] = (int)(digits/1000)%10;
            D[1] = (int)(digits/100)%10;
            D[2] = (int)(digits/10)%10;
            D[3] = (int)(digits/1) %10;
            }
            else { //For below 1, fix decimal point to always show 4 significant figure (eg. 0.900, 0.805, 0.010)
            dp_pos=3;
            int digits = (int) (value*1000);
                    
            D[0] = (int)(digits/1000)%10;
            D[1] = (int)(digits/100)%10;
            D[2] = (int)(digits/10)%10;
            D[3] = (int)(digits/1) %10;
            }
            
        ////////////////////////////////////////////
        // fill each segments of the display
        for (int i = 0; i < 4; ++i) dp[i] = 0; // Reset all 0 
            dp[dp_pos]=1;
                
            old_dis_val = value;
        }
            
    }
    else if(value==0)
    {
        D[0] = 0; 
        D[1] = 0;
        D[2] = 0; 
        D[3] = 0; 
        dp[0]=1;
    }
    
    else if(value== -1) //Show cm icon
    {
        D[0] = 15; //C
        D[1] = 16; //E
        D[2] = 18; //N
        D[3] = 17; //t
    }
    else if(value== -2) //Show inch icon
    {
        D[0] = 13; //i 
        D[1] = 12; //n 
        D[2] = 11; //c
        D[3] = 14; //h
        
    }
    else if(value== -3) // Dot
    {
        D[0] = 10; //space
        D[1] = 10; //space
        D[2] = 10; //space
        D[3] = 10; //space
        dp[1]=1;
    }
    else if(value== -4) // Nothing
    {
        D[0] = 10; //space
        D[1] = 10; //space
        D[2] = 10; //space
        D[3] = 10; //space
        
    }
    else // reserve for startup
    {
        D[0] = 10; //space
        D[1] = 10; //space
        D[2] = 10; //space
        D[3] = 10; //space
        
        if(value ==-5) D[0] = 8; 
        if(value ==-6) D[1] = 8; 
        if(value ==-7) D[2] = 8; 
        if(value ==-8) D[3] = 8; 
    }
    
        
    
    
    // Loop through each display each time we run 7_seg display function
    count++;
    count = count %4; //limit count between 0 to 3
        
    // Turn off all sections
    Dis_D1_Write(1);
    Dis_D2_Write(1);
    Dis_D3_Write(1);
    Dis_D4_Write(1);
        
    // Update to show a specific value
    draw_7Seg(D[count],dp[3-count]);
        
    // Only show on specified section
    if     (count==0)Dis_D1_Write(0);
    else if(count==1)Dis_D2_Write(0);
    else if(count==2)Dis_D3_Write(0);
    else if(count==3)Dis_D4_Write(0);
    
    run_7_Seg =0;
    
}

int clear_7_seg()
{
    // Turn off all sections
    Dis_D1_Write(1);
    Dis_D2_Write(1);
    Dis_D3_Write(1);
    Dis_D4_Write(1);
}

// ========================================================================================================================
/* Low level 7 segment display conversion code*/
// Lookup table for 0 to 9
const char charLookup[][8] = {
  "1111110", // 0
  "0110000", // 1
  "1101101", // 2
  "1111001", // 3
  "0110011", // 4
  "1011011", // 5
  "1011111", // 6
  "1110000", // 7
  "1111111", // 8
  "1111011", // 9
  "0000000", // Space - 10
  "0001101", // c -11
  "0010101", // n -12
  "0010000", // i -13
  "0010111", // h -14
  "1001110", // big C -15
  "1001111", // big E -16
  "0001111", // t -17
  "1110110", // big N -18
};

// update pins to show a specific number and turn on the decimal point if required
int segmentPattern_array[7];  // Array to store the converted 1s and 0s (7 elements for 7 segments)
void draw_7Seg(int number,int dp)
{
    const char* segmentPattern = charLookup[number];
    
    // Convert string to integer
    for (int i = 0; i < 7; i++) {
        segmentPattern_array[i] = segmentPattern[i]-'0';
    }
    
    Dis_A_Write(!segmentPattern_array[0]);
    Dis_B_Write(!segmentPattern_array[1]);
    Dis_C_Write(!segmentPattern_array[2]);
    Dis_D_Write(!segmentPattern_array[3]);
    Dis_E_Write(!segmentPattern_array[4]);
    Dis_F_Write(!segmentPattern_array[5]);
    Dis_G_Write(!segmentPattern_array[6]);
    Dis_DP_Write(!dp);
}
// ========================================================================================================================



/* [] END OF FILE */
