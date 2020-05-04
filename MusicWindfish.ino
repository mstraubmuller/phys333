// this is the start of a music player
void setup() {
  //Serial.begin(9600);
  pinMode(10, OUTPUT);

  // playing TLoZ Link's Awakening "Marin's Ballad of the Wind Fish"
  // adapted from https://musescore.com/user/15639516/scores/5457374, originally composed by Minako Hamano (濱野 美奈子)
  // piano keys (by int), could also be notes[33]
  int notes[] = {39, 40, 42, 0,
                 39, 40, 42, 0,
                 40, 39, 36, 38, 39, 0,
                 39, 40, 41, 0,
                 38, 41, 44, 0,
                 43, 42, 43
                };
  // note duration, in 8th notes
  int duration[] = {1, 1, 5, 1,
                    1, 1, 5, 1,
                    1, 1, 1, 3, 5, 6,
                    1, 1, 5, 1,
                    1, 1, 5, 1,
                    1, 1, 5
                   };
  //Serial.println(sizeof(duration));
  //Serial.println(sizeof(duration[0]));
  //Serial.println(sizeof(duration) / sizeof(duration[0]));
  int i;
  // @ 191.5bpm, there are 8x8th notes per measure
  // 313 ms per beat
  int ms_per_16th = 4*31;
  for (i = 0; i < 25; i++) {
    play_note(ms_per_16th * duration[i], get_period(notes[i]), 10);
    delay(50); // things sound better when you throw a 50ms delay in between notes.
  }

  //Serial.println("\n\n");
}

void loop() {
  
}

int play_note(int duration_ms, int tone_period_us, int out_pin) {
  unsigned int t0;
  t0 = millis();
  if (tone_period_us > 0) {
    while ((millis() - t0) < duration_ms) {
      digitalWrite(out_pin, HIGH);
      delayMicroseconds(tone_period_us / 2);
      digitalWrite(out_pin, LOW);
      delayMicroseconds(tone_period_us / 2);
    }
  }
  else {
    // this is the case that the note is a rest
    // b/c tone_period_us is negative
    digitalWrite(out_pin, LOW);
    delay(duration_ms);
  }
  return;
}



int get_period(int note) { //rewritten to use switch statement rather than else if else if else if spam; much smaller this way
  int Tus;
  /* Piano keys are indexed by number, 1 to 88.
      Key 1 is the highest
      Middle C is 40
     using the convention that note 0 is a rest.
     indicated with negative period
     source: https://en.wikipedia.org/wiki/Piano_key_frequencies
  */
  switch (note) { //lowest note 36, highest note 44
    case 36:
      Tus = 4816;
      break;
    case 37:
      Tus = 4545;
      break;
    case 38:
      Tus = 4290;
      break;
    case 39:
      Tus = 4050;
      break;
    case 40:
      Tus = 3822;
      break;
    case 41:
      Tus = 3608;
      break;
    case 42:
      Tus = 3405;
      break;
    case 43:
      Tus = 3214;
      break;
    case 44:
      Tus = 3034;
      break;
    default:
      Tus = -1;
  } 
  return Tus;
}                                                    
