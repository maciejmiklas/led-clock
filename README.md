[![Click me to play video :)](/doc/img/youtube.jpg)](https://www.youtube.com/watch/xcpKJU7HzQs)
This is a weather station with forecast for three days, it also includes clock with local time and date.

The whole project is based on Arduino, NodeMCU provides access to the Internet over WiFi. The display is built from single LEDs. Since they can be really bright it adopts illumination based on light conditions.
<img src="/doc/img/ledclockarch.png" width="640px"/>

Let's start from the beginning ;)

I've found those 8x8 LED modules:

<img src="/doc/img/led8x8.jpg" width="320px"/>

so I've decided to combine few to build a display. In my case there are 3 lines, each consists of 8 modules, 24 it total, this give us 1532 single LEDs! 

To drive single module I've chosen MAX72xx, I also wanted to improve my soldering skills, so I've decided to go for 24 PIN DIP chips and solder them to prototype boards:

<img src="/doc/img/cables.jpg" width="640px"/>

Well that worked out pretty well when it comes to those skills, but I would recommend to use LED modules combined with MAX Chip, this will save you at least few hours, not mentioning time spent afterwards when single cable gets loose ;) Such combo-module has only 3 wires instead of 16.

So we have hardware part for our display: 24 led modules with drivers. Now it's time to light them up! I've decided to go for Arduino Mega, because it has two serial ports, so it's easier to debug things (one port will be used for communication with EPS8266). You could also use Uno, in this case you would have to daisy chain MAX chips and change addressing in software. I've used separate line for each Max chip, but Uno just does not have enough digital output pins.

I was looking for API that will join all led modules into one canvas, so that you can print spites on it without bothering with transitions between LED modules. I did not find anything that would make me happy so I've decided to implement  [one by myself](https://github.com/maciejmiklas/LEDDisplay).  It provides not only simple canvas, but fonts and few animations. Basically everything that will be needed to display time and weather.

So ... we have a display and API to control it. Now we need to get date and weather. Arduino does not support Internet connectivity and it definitely does not have enough resources to process incoming data. So I've decided to use NodeMCU. With few Lua scripts I was able to implement [simple API](https://github.com/maciejmiklas/NodeMCUUtils) that is accessible over serial port. Arduino connects over it with NodeMCU, obtains time, date, weather and displays it.

In order to provide date NodeMCU connects with NTP server and receives UTC time, afterwards it calculates local date from it. I could use one of Internet services to grab the local date, but I was looking for solution that will remain stable for long time. Those services can change their API or just go off-line, but NTP protocol will remain unchanged. In worst case you will have to change server name. Current implementation supports also failover trough many different servers, so probably you will not have to bother with it soon ;)

Getting the weather was a bit tricky, because I had to find API that will return response small enough so it could be parsed by NodeMCU. I've decided to use yahoo weather. They provide nice REST API with small and simple response. Hopefully they will keep interfaces stable for long time.....

# Putting things together
First you have to build the display as described in this project: https://github.com/maciejmiklas/LEDDisplay . You can use the same pin numbers on Mega, so that you will not have to alter software.

After the display is ready, you should connect ESP8266 and photo-resistor. Schematic below contains all hardware elements together:

<img src="/doc/img/LED_Clock_schem.png" width="640px"/>

# Software for Arduino Mega
This project (LEDClock) contains main software part,  you have to compile it and upload to Arduino. Compilation requires SPI module and two other libraries: https://github.com/maciejmiklas/LEDDisplay and https://github.com/maciejmiklas/LEDDisplay

In [this blog post](http://maciej-miklas.blogspot.com/2017/03/weather-station-based-on-arduino-and.html#sloeber) you will find instrucitons howto compile it using Sloeber.

# Software for NodeMCU/ESP8266
In order to provide weather and time to Arduino you will have to clone this project: https://github.com/maciejmiklas/NodeMCUUtils , modify few scripts and upload those afterwards into NodeMCU. Here are the steps:

1. Compile firmware for NodeMCU so that it has all required modules. [Here](http://maciej-miklas.blogspot.com/2016/08/installing-nodemcu-v15-on-eps8266-esp.html) you will find instructions on it, and those are required modules: file, gpio, net, node, tmr, uart, wifi and cjson.

2. Clone project containing Lua scripts: https://github.com/maciejmiklas/NodeMCUUtils

3. Edit *serialAPIClock.lua* and set UTC offset for your location. This will be required to calculate local date from UTC time. For most European countries it's already set to correct value. For US you will have to replace *require "dateformatEurope"* with *require "dateformatAmerica"* and rename all method calls from *setEuropeTime* to *setAmericaTime*

3. Edit *yahooWeather.lua* and provide city and country that you would like to have weather for.

4. Create new file called: *credentials.lua* and specify login data for WiFi connection, it's just one line, for example: 
```lua
cred = {ssid = 'openwifi', password = '123456789'}
```

5. Upload all Lua scirpts from main project's folder into NodeMCU:
* credentials.lua
* dateformat.lua
* dateformatAmerica.lua
* dateformatEurope.lua
* ntp.lua
* ntpClock.lua
* serialAPI.lua
* serialAPIClock.lua
* serialAPIYahooWeather.lua
* wlan.lua
* yahooWeather.lua
6. Now for the final touch we need the init-file that will be executed right after NodeMCU boots up. In our case we are using the only Serial Port in order to expose weather and clock API. This also means, that once our API is registered, it's impossible to execute standard NodeMCU commands, like file upload. For this reason init-script has two seconds delay, during this time you can still upload files, or just remove current *init.lua* file. 

Init-files are there: *NodeMCUUtils/init/serialInit*
* init.lua
* serialInit.lua

# Matching LIB versions
* [LED Display](https://github.com/maciejmiklas/LEDDisplay/releases/tag/v1.1.0)
* [Arduino Logger](https://github.com/maciejmiklas/ArdLog/releases/tag/v1.1.0)
* [NodeMCU weather and clock](https://github.com/maciejmiklas/NodeMCUUtils/releases/tag/v1.4.0)





