#ifndef MUXMANAGER
#define MUXMANAGER

// abstraction to make communication with the multiplexer clean
class MuxManager {
  private:
    int activeChannel;
    enum ioMode{write, read};
    int writeEnablePin;
    int ioPin;
    void setChannel(int channel);
    void init(ioMode mode);
    void setMode(ioMode mode);

  public:
    int (&dataPins) [4];
    MuxManager(int (&datapins)[4], int writeEnablePin, int ioPin );
    int readPin(int channel);
    void writePin(int channel, int data);
    // shorthands for read and write because of lazyness is skill
    int r(int channel);
    void w(int channel, int data);
    
};
 
#endif 
