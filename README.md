# Good People Use Less Power (GPU LP)
## By Jared Nussbaum

* I made an I/O device that someone can use for cryptocurrency mining (in my case Etherium). You can visualize the GPU temperature,
and while mining, the Hashrate. You can also switch off and on mining the cryptocurrency. This is allow headless
mining (avoiding monitor power use)


* The microcontroller only needs to be started once and shouldn’t need to be restarted.


* If the python script is not already running, run it on the laptop. The output of the script is the Serial message
being sent to the microcontroller.


* The initial state is “not mining”. In order to start mining, press the button closest to the microcontroller and wait
for it to initialize.


* In order to stop mining, hit the button farther from the microcontroller. 


* PLEASE STOP MINING BEFORE YOU LEAVE THE PROJECT!


* I learned a lot about two-way serial communication, including buffers, and about parsing information from processes’
stdout and stderr streams that I read the temperature and hash rate information from. I also utilized interrupt buttons and it was neat to find a practical use for them. Although the end product is not visually stunning, it is a practical project that incorporates topics I learned in class.


