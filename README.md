# Alarm-with-DSI1307

Now you can set the time using 4 buttons and Arduino will sleep until that time. You can simulate the project with Proteus. I attached it for your easiness.

There will be 4 buttons in the system,
1. ok/mode
2. up
3.down
4.cancel

mode button can change the mode. There is a two different mode for setup time and alarm.

Example Change the time:

ok -> set hours ->ok -> set Min -> ok (time set)

Example set Alarm:

Ok -> Ok -> ok -> cancel -> set hours -> ok -> set Mn -> ok.

** cancel button will cancel any mode into default time mode.
**There are many possibilities to make this fully foolproof. 
SO CAREFUL WITH,
*YOU CAN SET TIME IN THE NEXT HOURS. (DO NOT SET PASSED TIME AS An ALARM)
*THERE IS NO BACK BUTTON IN THE SYSTEM.
*ALARM WILL WRITE ON THE EEPROM SO BAD USAGE MAY LEAD TO RESET THE MEMORY. (BAD ALARM SETUP)
