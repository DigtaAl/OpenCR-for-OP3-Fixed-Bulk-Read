/*
 *  dxl_hw.cpp
 *
 *  dynamixel hardware
 *
 *  Created on: 2016. 10. 21.
 *      Author: Baram
 */

#include "dxl_hw.h"

/* For debug */
uint32_t tx_led_count, rx_led_count;

/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_begin
     WORK    :
---------------------------------------------------------------------------*/
uint32_t dxl_hw_begin(uint8_t baud)
{
  uint32_t Baudrate = 0;

  pinMode( DXL_LED_RX, OUTPUT);
  pinMode( DXL_LED_TX, OUTPUT);

  pinMode( BDPIN_DXL_PWR_EN, OUTPUT );
  Baudrate = 2000000;       // 57,600 BPS
  DXL_PORT.begin(Baudrate);
  dxl_hw_tx_disable();
  dxl_hw_power_enable();

  return Baudrate;
}


/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_tx_enable
     WORK    :
---------------------------------------------------------------------------*/
void dxl_hw_tx_enable(void)
{
  drv_dxl_tx_enable(TRUE);
}


/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_tx_disable
     WORK    :
---------------------------------------------------------------------------*/
void dxl_hw_tx_disable(void)
{
  drv_dxl_tx_enable(FALSE);
}

/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_power_enable
     WORK    :
---------------------------------------------------------------------------*/
void dxl_hw_power_enable(void)
{
  pinMode( BDPIN_DXL_PWR_EN, OUTPUT );
  digitalWrite(BDPIN_DXL_PWR_EN, HIGH);
}


/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_power_enable
     WORK    :
---------------------------------------------------------------------------*/
void dxl_hw_power_disable(void)
{
  digitalWrite(BDPIN_DXL_PWR_EN, LOW);
}

/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_write
     WORK    :
---------------------------------------------------------------------------*/
void dxl_hw_write(uint8_t value)
{
  DXL_PORT.write(value);
}


/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_read
     WORK    :
---------------------------------------------------------------------------*/
uint8_t dxl_hw_read(void)
{
  rx_led_count = 3;
  //uint8_t data = DXL_PORT.read();
  return DXL_PORT.read();
}


/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_write
     WORK    :
---------------------------------------------------------------------------*/
void dxl_hw_write(uint8_t *p_data, uint32_t length)
{
  uint32_t i;


   dxl_hw_tx_enable();

  for (i=0; i<length; i++)
  {
    DXL_PORT.write(p_data[i]);
  }
  DXL_PORT.flush();
  
  tx_led_count = 3;

   dxl_hw_tx_disable();
}


/*---------------------------------------------------------------------------
     TITLE   : dxl_hw_available
     WORK    :
---------------------------------------------------------------------------*/
uint32_t dxl_hw_available(void)
{
  return DXL_PORT.available();
}
