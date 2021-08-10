# Traktor-Numark-Mixdeck-Debug
 This repo contains my decoding of the MIDI messages between Traktor Pro and Numark Mixdeck

## Available data
- Song timer (minutes, seconds and milliseconds)
- BPM
- Tempo
- Title - artist
- and more!
 
## Usage
Flash the .ino file to [Control-Surface](https://github.com/tttapa/Control-Surface) compatible board. Then, in Traktor go to settings, Controller Manager, and add both Deck A and Deck B from Numark->Mixdeck. Set their outports as your board, and set their respective device targets like this:

![](https://i.imgur.com/CCHvgnJ.png)
![](https://i.imgur.com/NOcctTD.png)

Then load and play a song in a deck to see the output in the serial monitor. You might want to adjust the output depending on what information you're interested in.

