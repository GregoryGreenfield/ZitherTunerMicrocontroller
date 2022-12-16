# ZitherTunerMicrocontroller
My third year university project was to design and create an automatic zither (stringed instrument) tuner. The PCB microcontroller picks up the frequency of the string using a zero-cross detection (ZCD) algorithm whenever the string is plucked, and tightens or slackens the tension in the string to change the frequency to 46.25Hz, known in musical notation as F#1/Gb1. A stepper motor was used to change the tension of the string.

- I designed and fabricated the PCB board that hosted the microcontroller and the drive board for the stepper motor. The Zither produces a series of frequencies on top of the fundamental frequency. Only the fundamental frequency is required, so I had to filter out the unwanted overtones/harmonics and then amplify the remaining signal before it arrived at the microcontroller.
- I designed the Zither instrument and how the tuner would attach to it
- I programmed the PIC microcontroller, which converted the require change in frequency into the correct change in string tension by driving a stepper motor.
