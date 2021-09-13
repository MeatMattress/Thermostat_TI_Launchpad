## Prototype thermostat on the TI_Launchpad3220s

Application that senses ambient air temperature and toggles an LED based on user's desired temperature, to simulate turning a heater on/off.

## Peripherals & Assignments

This application utilizes the UART, I2C, internal Timer, an LED, and the Launchpad user buttons (GPIO)

* `UART` - Outputs formatted data in the form: <`Ambient Air Temperature`, `User's Desired Temperature`, `LED State`, `Ticks Elapsed`>
* `I2C` - Protocol that reads temperature from the on-board temperature sensor
* `Timer` - Utilized as a task-scheduler much like a typical Operating System, in order to minimize processing power and electricity usage
* `CONFIG_GPIO_BUTTON_0` - P04, LaunchPad User Button SW2 (Left) | Lowers desired temperature
* `CONFIG_GPIO_BUTTON_1` - P15, LaunchPad User Button SW3 (Right) | Raises desired temperature
* `CONFIG_GPIO_LED_1` - P64, LaunchPad LED D10 (Red) | Toggled if `Ambient Air Temperature` < `User's Desired Temperature`

## Journal / reflection assignment below (This was an AWESOME school project)
&emsp; Task scheduling is a core concept of Operating Systems, and is the heart of efficient embedded systems design. In this project, I designed a task-scheduler in C that checks certain peripherals on different intervals, updating it's state-machine every corresponding tick. I think I designed the task scheduler and the state-machine very well in this project, as it is well-organized and understandable within the main loop, and the tick functions are commented well.
<br>
&emsp; I think I could improve on the design by outputting to something other than a regular UART terminal instance. For example, I might be able to output it to a window on-screen, or utilize the WI-FI to send the data to a Node server to update a web-page with the information. There are several ways to integrate embedded systems into the IOT and I love to see it happen. These types of improvements will come soon with other projects I'm currently working on. I'm going big: Artificial Intelligence and object recognition, servo motors, Discord, and overclocked high-powered lasers. Keep an eye on my Github.
<br>
&emsp; This project was well-maintained, readable, and adaptable in that the initializations, global variables, tick functions, etc. had their own spots to live, and the task scheduler itself is scalable to tens of thousands of tasks with the same efficiency. Code was commented well and explained each function concisely.
<br>
&emsp; Just want to say a big <b>thank-you</b> to professor Pettit for hosting this class and guiding my expansion of knowledge.
