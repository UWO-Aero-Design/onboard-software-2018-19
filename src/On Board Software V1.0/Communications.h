#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H

class Communications{
  private:

  public:
  	Communications();
  	virtual void recv() = 0;
  	virtual void send() = 0;
};

#endif // SENSORS_H
