# cloudcharger

a battery charger running on an Arduino relying on AWS to keep track of every Battery.
Using standard components like the famous tp4056 boards and Ina2019 just connected with the minimum amount of external components to be 
controlled by an Arduino Mega.
The aim is to have a high throughput 18650 charger array which is so simple to build that anyone can do it on a Breadboard and a handfull of
components.
To make it a little more interesting FreeRTOS is used as sceduler.
