/** 
 *  @file ADsensors.h
 *  @brief Interface for A/D sensors.
 *  @author Madzivire Chikwanda
 *  @date 22 April 2015
 *
 *  Methods for reading sensor values. The A/D module has to be initialized by calling
 *  init() , defined in init.h, before methods defined in this file can be called.
 */


#define sensorOn(sensorRead)  ((sensorRead) < (0x20) ? (1) : (0))   // check on sensor

/**
 *  @brief Gets front sensor reading.
 *  @param void
 *  @return unsigned short
 *
 *  Front sensor reading is returned as an unsigned short type.
 */
unsigned short readFrontSensor (void)
{
   return (unsigned short) ATD1DR0L;
}

/**
 *  @brief Gets right wheel sensor reading.
 *  @param void
 *  @return unsigned short
 *
 *  Sensor reading is returned as an unsigned short type.
 */
unsigned short readRightWheel (void)
{
   return (unsigned short) ATD1DR6L;
}

/**
 *  @brief Gets right wall sensor reading.
 *  @param void
 *  @return unsigned short
 *
 *  Sensor reading is returned as an unsigned short type.
 */
unsigned short readRightWall (void)
{
   return (unsigned short) ATD1DR4L;
}

/**
 *  @brief Gets right alignment sensor reading.
 *  @param void
 *  @return unsigned short
 *
 *  Sensor reading is returned as an unsigned short type.
 */
unsigned short readRightAlign (void)
{
   return (unsigned short) ATD1DR3L;
}

/**
 *  @brief Gets left wheel sensor reading.
 *  @param void
 *  @return unsigned short
 *
 *  Sensor reading is returned as an unsigned short type.
 */
unsigned short readLeftWheel (void)
{
   return (unsigned short) ATD1DR5L;
}

/**
 *  @brief Gets left wall sensor reading.
 *  @param void
 *  @return unsigned short
 *
 *  Sensor reading is returned as an unsigned short type.
 */
unsigned short readLeftWall (void)
{
   return (unsigned short) ATD1DR2L;
}

/**
 *  @brief Gets left alignment sensor reading.
 *  @param void
 *  @return unsigned short
 *
 *  Sensor reading is returned as an unsigned short type.
 */
unsigned short readLeftAlign (void)
{
   return (unsigned short) ATD1DR1L; 
}

void showSensors(void)
{
   printf("                   FRONT SENSOR==%x\n\r",ATD1DR0L);
   printf("RIGHT WHEEL SENSOR==%02x   RIGHT WALL SENSOR==%02x\n\r",readRightWheel(),readRightWall());
   printf("LEFT WHEEL SENSOR==%02x    LEFT WALL SENSOR==%02x\n\r",readLeftWheel(),readLeftWall());
   printf("L ALIGNMENT SENSOR==%02x   R ALIGNMENT SENSOR==%02x\n\r",readLeftAlign(),readRightAlign());
}                                                       
