# WeatherAPI
Uses a Weather API for Cambridge, MA to bring the user four current pieces of info.
Uses Pythona and C++.

User can choose to have the device display either the current temperature, time, date, or visibility, with the press of a single button.

Scrolls so that the newest info is on the top and everything get shifted downwards.

Hardware: Esp32, tft screen 1.8", button

I used a finite state machine in order to keep track of the number of times the button was pressed(which worked really well). I used my python file code to control what info was returned to the arduino code (because coding in C is officially the worst). I went with different colors for the different options on the start screen display because I thought it would be easier to read and look nice. I enjoyed using cyan colored font. I also utilized postman which proved to be somewhat helpful in the debugging process. 
