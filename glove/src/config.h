#ifndef CONFIG_H_
#define CONFIG_H_

class Config {
public:
  Config(bool debug = false) : debug(debug) {};

  bool debug = false;
};

#endif
