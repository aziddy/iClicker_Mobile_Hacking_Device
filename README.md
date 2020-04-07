# iClicker_Mobile_Hacking_Device

The actual libraries and reverse engineering of the iClicker Protocol is done by wizard97
https://github.com/wizard97/iSkipper

So I made a small portable device to see answers 
<br>

<p align="center" style="vertical-align: top; position: relative" >
  <img style="vertical-align:top" src="https://github.com/aziddy/iClicker_Mobile_Hacking_Device/blob/master/media/jiff.gif?raw=true" width="700"/>
</p>



<br>

<p align="center" style="vertical-align: top; position: relative" >
  <img style="vertical-align:top" src="https://github.com/aziddy/iClicker_Mobile_Hacking_Device/blob/master/front.jpg?raw=true" width="300"/>
  <img style="vertical-align:top" src="https://github.com/aziddy/iClicker_Mobile_Hacking_Device/blob/master/screen.jpg?raw=true" width="300"/>
  <img style="vertical-align: top; position: relative" src="https://github.com/aziddy/iClicker_Mobile_Hacking_Device/blob/master/back_battery.jpg?raw=true" width="400"/>
    <img style="vertical-align:top" src="https://github.com/aziddy/iClicker_Mobile_Hacking_Device/blob/master/00100dPORTRAIT_00100_BURST20200204102705053_COVER.jpg?raw=true" width="400"/>
</p>

<br>

## Component List

* DPDT Rocker Switch 
<a href="https://www.creatroninc.com/product/dpdt-rocker-switch/?search_query=switch&results=305">Link</a>
* Adafruit Feather M0 RFM69 PACKET RADIO - 868 OR 915 MHZ **GET THE M0 VERSION** <a href="https://elmwoodelectronics.ca/products/adafruit-feather-m0-rfm69-packet-radio-868-or-915-mhz">Link</a>
* Protoboard
* Some random battery bank I bought from Dollarama
* OLED Display 128x64 Pixel I2C, 0.96 inch, SSD1306 

<br>

## Libraries

All the libs required are in https://github.com/wizard97/iSkipper
<br>
<br>

## Wiring
<br>
<p align="center" style="vertical-align: top; position: relative" >

  <img style="vertical-align: top; position: relative" src="https://github.com/aziddy/iClicker_Mobile_Hacking_Device/blob/master/circuit.PNG?raw=true" width="700"/>

</p>

<br>
<br>

# RAM Considerations
**32u4** Version of the Feather only has *2.5Kb* of RAM. While the **M0** Version has *32Kb*. But my dumbass didn't see this untill I bought the **32u4** Version. So I had to edit my program abit so it wont shit itself.
<br>
<br>

The screen is 128x64. But the entire program would fuck up unless I lower the amount of RAM allocated for the display
```c
#define MALLOC_SCREEN_WIDTH 128
#define MALLOC_SCREEN_HEIGHT 40
```
<br>

```c
#define MAX_BUFFERED_PACKETS 10
```



<br>



