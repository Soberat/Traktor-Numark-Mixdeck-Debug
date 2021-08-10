#include <Control_Surface.h>

#define displayOnlyUnknown false

USBMIDI_Interface midi;

Timer<millis> second = 1000;

int spaceCounter = 0;
int titleIndex = 0;
bool titleIncoming = false;
bool titleDiscovered = false;

int tempoOverflows = 0;
int minutes = 0;
int seconds = 0;
float tempo = 0.0;
int tempoSign = 1;
int bpmOverflows = 0;
int bpmRaw = 0;
//Tempo formula -> tempoSign*(tempoOverflows*128 + tempoSign*tempo)/10.0


char title[128] = {};

bool channelMessageCallback(ChannelMessage cm) {

      int header = cm.header & 0xF0;
    
      switch (header) {
        case 0x90:  //Mackie Control Universal message
            switch (cm.data1) {
                case 0x31:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Cue output " << cm.data2 << ")" << endl;
                    break;
                case 0x32:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Pause output " << cm.data2 << ")" << endl;
                    break;
                case 0x33:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Play output " << cm.data2 << ")" << endl;
                    break;
                case 0x3b:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Key Lock output " << cm.data2 << ")" << endl;
                    break;
                case 0x3c:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Zero Pitch output " << cm.data2 << ")" << endl;
                    break;
                case 0x40:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Scratch output " << cm.data2 << ")" << endl;
                    break;
                case 0x34:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Loop In output " << cm.data2 << ")" << endl;
                    break;
                case 0x35:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Loop Out output " << cm.data2 << ")" << endl;
                    break;
                case 0x36:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Reloop output " << cm.data2 << ")" << endl;
                    break;
                case 0x37:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Hot Cue 1 output " << cm.data2 << ")" << endl;
                    break;
                case 0x38:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Hot Cue 2 output " << cm.data2 << ")" << endl;
                    break;
                case 0x39:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Hot Cue 3 output " << cm.data2 << ")" << endl;
                    break;
                case 0x3a:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Rec output " << cm.data2 << ")" << endl;
                    break;
                case 0x3e:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Effect OnOff output " << cm.data2 << ")" << endl;
                    break;
                case 0x3f:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:LED:Search output " << cm.data2 << ")" << endl;
                    break;
                case 0x43:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Display:Card output " << cm.data2 << ")" << endl;
                    break;
                case 0x44:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Display:CD output " << cm.data2 << ")" << endl;
                    break;
                case 0x45:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Display:HD output " << cm.data2 << ")" << endl;
                    break;
                case 0x47:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t(" <<  MCU::getMCUNameFromNoteNumber(cm.data1)  << ")" << endl;
                    titleDiscovered = false;
                    titleIncoming = false;
                    spaceCounter = 0;
                    titleIndex = 0;
                    memset(title, 0, sizeof(title));
                case 0x48:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Display:MP3 output " << cm.data2 << ")" << endl;
                    break;
                case 0x4b:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Cue output " << cm.data2 << ")" << endl;
                    break;
                case 0x4c:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Pause output " << cm.data2 << ")" << endl;
                    break;
                case 0x4d:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Play output " << cm.data2 << ")" << endl;
                    break;
                case 0x4f:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(Traktor:Key Lock output " << cm.data2 << ")" << endl;
                    break;
                default:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t(" <<  MCU::getMCUNameFromNoteNumber(cm.data1)  << ")" << endl;
                    break;
            }
            break;
        case 0xB0:  //Deck data message
            switch (cm.data1) {
                case 32:
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(LED:Shift output " << cm.data2 << ")" << endl;
                    break;
                case 33:    // LED.Pitch Range output
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(LED:Pitch Range output " << cm.data2 << ")" << endl;
                    break;
                case 36:      //unknown
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\t\t\t\t\t(UNKNOWN)" << endl;
                    break;            
                case 37:
                    //if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(SEGMENT " << cm.data2 << "/60)" << endl;
                    break;
                case 39:
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\t\t\t\t\t(UNKNOWN)" << endl;
                    break;
                case 41:      //minutes data
                    minutes = cm.data2;//if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(MINUTE " << cm.data2 << ")" << endl; 
                    break;
                case 42:      //seconds data
                    seconds = cm.data2;//if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(SECOND " << cm.data2 << ")" << endl;
                    break;
                case 43:      //Milliseconds/10
                    //if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(MILLISECONDS: " << cm.data2*10 << ")" << endl;
                    break;
                case 44:      //tempo scale
                    if(!displayOnlyUnknown) {
                      bpmOverflows = cm.data2;
                      //Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t(BPM OVERFLOWS " << cm.data2 << ")" << endl;
                    }
                    break;
                case 45:      //tempo overflows
                    //if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t(TEMPO OVERFLOWS " << cm.data2 << ")" << endl;
                    if(cm.data2 > 100) {
                      tempoOverflows = 128 - cm.data2;
                      tempoSign = -1;
                    } else {
                      tempoOverflows = cm.data2;
                      tempoSign = 1;
                    }
                    break;
                case 46:      //jog wheel related
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "jog" << endl;
                    break;
                case 47:      //unknown
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\t\t\t\t\t(UNKNOWN)" << endl;
                    break;
                case 48:      //unknown
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\t\t\t\t\t(UNKNOWN)" << endl;
                    break;
                case 49:      //unknown
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\t\t\t\t\t(UNKNOWN)" << endl;
                    break;
                case 50:      //BPM is zero
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(BPM IS " << (cm.data2 ? "NONZERO" : "ZERO") << ")" << endl;
                    break;
                case 51:      //play status
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(PLAY " << (cm.data2 == 1 ? "ON" : "OFF") << ")" << endl;
                    break;
                case 52:      //unknown
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\t\t\t\t\t(UNKNOWN)" << endl;
                    break;
                case 53:      //BPM is zero
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(BPM IS " << (cm.data2 == 0 ? "ZERO" : "NONZERO") << ")" << endl;
                    break;
                case 54:      //unknown
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\t\t\t\t\t(UNKNOWN)" << endl;
                    break;
                case 55:      //tempo is doubled 
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(TEMPO IS " << (cm.data2 == 0 ? "DOUBLED" : "LESS THAN DOUBLE") << ")" << endl;
                    break;
                case 56:      //tempo is not standard
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(TEMPO CHANGED " << (cm.data2 == 0 ? "FALSE" : "TRUE") << ")" << endl;
                    break;
                case 57:      //jog wheel LEDs control. 1 - jog touch on, 2-8 - other
                    //if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(JOG WHEEL STATUS " << cm.data2 << ")" << endl;
                    break;
                case 71:      ///unknown
                    if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\t\t\t\t\t(UNKNOWN)" << endl;
                    break;
                case 76:      //tempo unknown
                    if(!displayOnlyUnknown){
                        bpmRaw = cm.data2;
                        //Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t(BPM RAW)" << endl; 
                    }
                    break;
                case 77:      //tempo bend percentage
                    //if(!displayOnlyUnknown) Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t(TEMPO BEND " << cm.data2/10.0 << ")" << endl;
                    tempo = cm.data2;
                    break;               
                default:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t\t\tNEW!!!!!!!! " << endl;
                    break;
            
            }
            break;
        case 0x80:
            switch (cm.data1) {
                case 49:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Cue output " << cm.data2 << ")" << endl;
                    break;
                case 50:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Pause output " << cm.data2 << ")" << endl;
                    break;
                case 51:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Play output " << cm.data2 << ")" << endl;
                    break;
                case 52:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Loop In output " << cm.data2 << ")" << endl;
                    break;
                case 53:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Loop Out output " << cm.data2 << ")" << endl;
                    break;
                case 54:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Reloop output " << cm.data2 << ")" << endl;
                    break;
                case 55:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Hot Cue 1 output " << cm.data2 << ")" << endl;
                    break;
                case 56:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Hot Cue 2 output " << cm.data2 << ")" << endl;
                    break;
                case 57:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Hot Cue 3 output " << cm.data2 << ")" << endl;
                    break;
                case 58:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Rec output " << cm.data2 << ")" << endl;
                    break;
                case 59:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Key Lock output " << cm.data2 << ")" << endl;
                    break;
                case 60:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Zero Pitch output " << cm.data2 << ")" << endl;
                    break;
                case 62:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Effect OnOff output " << cm.data2 << ")" << endl;
                    break;
                case 63:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Search output " << cm.data2 << ")" << endl;
                    break;
                case 64:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:LED:Scratch output " << cm.data2 << ")" << endl;
                    break;
                case 67:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Display:Card output " << cm.data2 << ")" << endl;
                    break;
                case 68:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Display:CD output " << cm.data2 << ")" << endl;
                    break;
                case 69:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Display:HD output " << cm.data2 << ")" << endl;
                    break;
                case 72:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Display:MP3 output " << cm.data2 << ")" << endl;
                    break;
                case 75:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Cue output " << cm.data2 << ")" << endl;
                    break;
                case 76:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Pause output " << cm.data2 << ")" << endl;
                    break;
                case 77:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Play output " << cm.data2 << ")" << endl;
                    break;
                case 78:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(STOP)" << endl;
                    break;
                case 79:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << cm.data2 << dec << "\t\t\t(Traktor:Key Lock output " << cm.data2 << ")" << endl;
                    break;
                case 80:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << "\t\t\t(STOP)" << endl;
                    break;
                default:
                    Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << endl;
                    break;
            }
            break;
        default:    //Other messages
            Serial << hex << cm.header << dec << ' ' << cm.data1 << ' ' << cm.data2 << dec << endl;
            break;
        
      }
             
      return false; // Return true to indicate that handling is done,
                    // and Control_Surface shouldn't handle it anymore.
                    // If you want Control_Surface to handle it as well,
                  // return false.

}
 
bool sysExMessageCallback(SysExMessage se) {
    
    if (se.data[0] == 0xF0 && se.data[se.length-1] == 0xF7) {
        if (titleDiscovered) return false;
        Serial << F("Title: ") << hex;
  
        if (spaceCounter == 3) {
            titleIncoming = true;
            spaceCounter = 0;
        }
  
        if (titleIncoming) {
            if (se.data[se.length-2] == 0x20) spaceCounter++;
            else spaceCounter = 0;
            
            if (spaceCounter == 3) {
                titleIncoming = false;
                titleIndex = 0;
                Serial << dec << F("FINISHED TITLE: ") << title << endl;
                titleDiscovered = true;
                spaceCounter = 0;
                return false;
            }
            
            char c = char(se.data[se.length-2]);
            title[titleIndex] = c;
            titleIndex++;
            Serial << dec << c << endl;
            return false;
        }
        
        if (se.data[se.length-2] == 0x20) spaceCounter++;
        else spaceCounter = 0;
  
        
        for (size_t i = 9; i < se.length-1; ++i) Serial << char(se.data[i]) << ' ';
        Serial << dec << endl;
        return false;
    }

    Serial << F("SysEx: ") << hex;
    for (size_t i = 1; i < se.length; ++i)
      Serial << char(se.data[i]) << ' ';
    Serial << dec << F("on cable ") << se.getCable().getRaw() << endl;
    return false;
}
 


void setup() {
    Serial.begin(1000000);
    Control_Surface.begin();
    Control_Surface.setMIDIInputCallbacks(channelMessageCallback,   
                                          sysExMessageCallback,     
                                          nullptr,
                                          nullptr); 
    second.beginNextPeriod();
}

void loop() {
    Control_Surface.loop();
    if (second) {
        Serial << dec << "BPM " << (bpmOverflows*128 + bpmRaw)/10.0 << endl;
        Serial << dec << "Time: " << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << endl;
        Serial << dec << "Tempo d: " << tempoSign*(tempoOverflows*128 + tempoSign*tempo)/10.0 << endl;
    }
}
