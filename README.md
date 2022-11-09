[![Click me to play video :)](/doc/img/youtube.jpg)](https://www.youtube.com/watch/xcpKJU7HzQs)

[This video shows a boxed version with the latest improvements](https://www.youtube.com/watch?v=c8wJdQJHX8o)

It is a weather station with a three-day forecast, current temperature, and a clock with local time and date.

The project is based on Arduino, NodeMCU provides access to the Internet over WiFi. 
The display is built from single LEDs. Since they can be bright, it adopts illumination based on light conditions.
<img src="/doc/img/ledclockarch.png" width="640px"/>

Let's start from the beginning ;)

I've found those 8x8 LED modules:

<img src="/doc/img/led8x8.jpg" width="320px"/>

so I've decided to combine a few to build a display. In my case, there are three lines, each consisting of 8 modules, 24 in total; this gives us 1532 single LEDs! 

To drive a single module, I've chosen MAX72xx. I also wanted to improve my soldering skills, so I've decided to go for 24 PIN DIP chips and solder them to prototype boards:

<img src="/doc/img/cables.jpg" width="640px"/>

That worked out well regarding those skills, but I recommend using LED modules combined with MAX Chip. It will save you at least a few hours, not to mention the time spent afterward when a single cable gets loose ;) Such a combo module has only three wires instead of 16.

So we have a hardware part for our display: 24 led modules with drivers. Now it's time to light them up! I've decided to go for Arduino Mega because it has two serial ports, so it's easier to debug things (one port will be used for communication with EPS8266). You could also use Uno. In this case, you would have to daisy chain MAX chips and change the addressing in the software because Uno does not have enough output pins.

I was looking for an API that will join all led modules into one canvas so that you can print spites without bothering with transitions between LED modules. I did not find anything that would make me happy, so I've decided to implement  [one by myself](https://github.com/maciejmiklas/LEDDisplay). It provides a simple canvas with fonts and a few animations, which is everything necessary to display time and weather.

We have a display and API to control it. Now we need to get the date and weather. Arduino does not support Internet connectivity, and it does not have enough resources to process incoming data. So I've decided to use NodeMCU. With a few Lua scripts, I could implement [simple API](https://github.com/maciejmiklas/NodeMCUUtils) that is accessible over a serial port. Arduino connects over it with NodeMCU, obtains time, date, and weather, and displays it.

To provide a date, the NodeMCU connects with the NTP server and receives time in UTC. Afterward, it calculates the local date from it. I could use one of the Internet services to grab the local time, but I was looking for a solution that would remain stable for a long time. Those services can change their API or go offline, but the NTP protocol is solid. In the worse case, you will have to change a server name. The current implementation also supports failover through many different servers, so you will probably not have to bother with it soon ;)

Getting the weather was tricky because I had to find an API that would return a response small enough so NodeMCU could parse it. I've decided to use yahoo weather. They provide a nice REST API with a small and straightforward response. Hopefully, they will keep interfaces stable for a long time.

# Putting things together
First, you must build the display described in this project: https://github.com/maciejmiklas/LEDDisplay . You can use the same PINs on Mega so that you will not have to alter the software.

After the display is ready, you should connect ESP8266 and the photo-resistor. The Schematic below contains all hardware elements together:

<img src="/doc/img/LED_Clock_schem.png" width="640px"/>

# Software for Arduino Mega
This project (LEDClock) contains the main software part,  you have to compile it and upload it to Arduino. Compilation requires an SPI module and two other libraries: https://github.com/maciejmiklas/LEDDisplay and https://github.com/maciejmiklas/ArdLog

You will find in [this blog post](http://maciej-miklas.blogspot.com/2017/03/weather-station-based-on-arduino-and.html#sloeber) instrucitons on howto compile it using Sloeber.

# Software for NodeMCU/ESP32
To provide weather and time to Arduino, you will have to clone this project: https://github.com/maciejmiklas/NodeMCUUtils , modify a few scripts, and upload those afterward into NodeMCU. Here are the steps:

1. Compile firmware for NodeMCU/ESP32 so that it has all required modules: file, mqtt, gpio, net, node, tmr, uart, WiFi, sjson. Theres is also already a precomipled version in the repo.

2. Edit *serial_api_clock.lua* and set UTC to offset for your location. It will be required to calculate local time from UTC. For most European countries, it's already set to the correct value. For US you will have to replace *require "date_format_europe"* with *require "date_format_america"* in _*init.lua_

3. Register at [Open Weather](https://openweathermap.org) to get the application id. You will have to provide it in the next step.

4. Create a new file called: *credentials.lua* and specify login data for WiFi connection. It's just one line, for example: 
```lua
cred = {ssid = 'openwifi', password = '123456789'}
owe.appid = 'your app id'
```

6. Upload all Lua scripts from _/src_ and _/scr/init_ into NodeMCU.


# Matching LIB versions
* [LED Clock](https://github.com/maciejmiklas/LEDClock) - v1.x.x
* [LED Display](https://github.com/maciejmiklas/LEDDisplay) - v2.x.x
* [Arduino Logger](https://github.com/maciejmiklas/ArdLog) - v2.x.x
* [NodeMCU weather and clock](https://github.com/maciejmiklas/NodeMCUUtils) - v2.x.x
Replace x with the latest version, they are all compatible.