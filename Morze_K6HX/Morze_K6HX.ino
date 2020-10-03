//
// Simple Arduino Morse Beacon
// Written by Mark VandeWettering K6HX
// Email: <a href="mailto:k6hx@arrl.net">k6hx@arrl.net</a>
// 
// This code is so trivial that I'm releasing it completely without 
// restrictions.  If you find it useful, it would be nice if you dropped
// me an email, maybe plugged my blog @ <a data-cke-saved-href="<a href="http://brainwagon.org" rel="nofollow">http://brainwagon.org</a>" href="<a href="http://brainwagon.org" rel="nofollow">http://brainwagon.org</a>" rel="nofollow"><a href="http://brainwagon.org" rel="nofollow">http://brainwagon.org</a></a> or included
// a brief acknowledgement in whatever derivative you create, but that's
// just a courtesy.  Feel free to do whatever.
//

#define ATtiny

struct t_mtab { char c, pat; } ;

struct t_mtab morsetab[] = {
  {'.', 106},
  {',', 115},
  {'?', 76},
  {'/', 41},
  {'A', 6},
  {'B', 17},
  {'C', 21},
  {'D', 9},
  {'E', 2},
  {'F', 20},
  {'G', 11},
  {'H', 16},
  {'I', 4},
  {'J', 30},
  {'K', 13},
  {'L', 18},
  {'M', 7},
  {'N', 5},
  {'O', 15},
  {'P', 22},
  {'Q', 27},
  {'R', 10},
  {'S', 8},
  {'T', 3},
  {'U', 12},
  {'V', 24},
  {'W', 14},
  {'X', 25},
  {'Y', 29},
  {'Z', 19},
  {'1', 62},
  {'2', 60},
  {'3', 56},
  {'4', 48},
  {'5', 32},
  {'6', 33},
  {'7', 35},
  {'8', 39},
  {'9', 47},
  {'0', 63}
} ;

#define N_MORSE  (sizeof(morsetab)/sizeof(morsetab[0]))

#define SPEED  (12)
#define DOTLEN  (1200/SPEED)
#define DASHLEN  (3*(1200/SPEED))

#ifdef ATtiny
int LEDpin = 3 ;
#else
int LEDpin = 13 ;
#endif


void
dash()
{
  digitalWrite(LEDpin, HIGH) ;
  delay(DASHLEN);
  digitalWrite(LEDpin, LOW) ;
  delay(DOTLEN) ;
}

void
dit()
{
  digitalWrite(LEDpin, HIGH) ;
  delay(DOTLEN);
  digitalWrite(LEDpin, LOW) ;
  delay(DOTLEN);
}

void
send(char c)
{
  int i ;
  if (c == ' ') {

#ifndef ATtiny
   Serial.print(c) ;
#endif
 
    delay(7*DOTLEN) ;
    return ;
  }
  for (i=0; i<N_MORSE; i++) {
    if (morsetab[i].c == c) {
      unsigned char p = morsetab[i].pat ;
#ifndef ATtiny
Serial.print(morsetab[i].c) ;
#endif

      while (p != 1) {
          if (p & 1)
            dash() ;
          else
            dit() ;
          p = p / 2 ;
      }
      delay(2*DOTLEN) ;
      return ;
    }
  }
  /* if we drop off the end, then we send a space */
#ifndef ATtiny
Serial.print("?") ;
#endif
 
}

void
sendmsg(char *str)
{
  while (*str)
    send(*str++) ;
#ifndef ATtiny
Serial.println("");
#endif
}

void setup() {
  pinMode(LEDpin, OUTPUT) ;
/* */ 
#ifndef ATtiny
  Serial.begin(9600) ;
  Serial.println("Simple Arduino Morse Beacon v0.0") ;
  Serial.println("Written by Mark VandeWettering <k6hx@arrl.net>") ;
  Serial.println("Check out my blog @ http://brainwagon.org") ;
  Serial.println("") ;
#endif
/* */
}

void loop() {
  sendmsg("CQ CQ UA6EM/B UA6EM/B LN14AF K") ;
  delay(5000) ;
}
