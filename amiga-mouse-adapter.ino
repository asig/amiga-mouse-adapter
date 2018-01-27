/*
 * Convert Amiga joystick movements to mouse movements.
 * 
 * Copyright (c) 2017 Andreas Signer <asigner@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#define LED 13

// Input pins
#define P_IN_UP    2 // Orange
#define P_IN_DOWN  3 // Blue
#define P_IN_LEFT  4 // Brown
#define P_IN_RIGHT 5 // Grey
#define P_IN_FIRE  6 // Yellow

// Output pins
#define P_OUT_V_PULSE  12 // Orange
#define P_OUT_H_PULSE  11 // Blue
#define P_OUT_VQ_PULSE 10 // Brown
#define P_OUT_HQ_PULSE  9 // Grey
#define P_OUT_LMB       8 // Yellow

#define UP    0x01
#define DOWN  0x02
#define LEFT  0x04
#define RIGHT 0x08
#define FIRE  0x10

// #define DEBUG

void setup() {
  pinMode(LED, OUTPUT);

  pinMode(P_IN_UP,    INPUT_PULLUP);
  pinMode(P_IN_DOWN,  INPUT_PULLUP);
  pinMode(P_IN_LEFT,  INPUT_PULLUP);
  pinMode(P_IN_RIGHT, INPUT_PULLUP);
  pinMode(P_IN_FIRE,  INPUT_PULLUP);

  pinMode(P_OUT_V_PULSE,  OUTPUT);
  pinMode(P_OUT_H_PULSE,  OUTPUT);
  pinMode(P_OUT_VQ_PULSE, OUTPUT);
  pinMode(P_OUT_HQ_PULSE, OUTPUT);
  pinMode(P_OUT_LMB,      OUTPUT);

#ifdef DEBUG
  Serial.begin(9600);
#endif  
}

void loop() {
  int val = 0;
  if (digitalRead(P_IN_UP) == 0) val |= UP;
  if (digitalRead(P_IN_DOWN) == 0) val |= DOWN;
  if (digitalRead(P_IN_LEFT) == 0) val |= LEFT;
  if (digitalRead(P_IN_RIGHT) == 0) val |= RIGHT;
  if (digitalRead(P_IN_FIRE) == 0) val |= FIRE;

#ifdef DEBUG
    Serial.println(val);
#endif    
  
  digitalWrite(LED, (val & FIRE) > 0);  

  /*
   * From "Amiga Intern", page 258:
   * 
   * Right/Down: H/V:     ______        ___
   *                     |      |      |
   *                     |      |      |
   *                     |      |______|
   * 
   *             HQ/VQ:      ______
   *                        |      |      |
   *                        |      |      |
   *                     ___|      |______|
   *         
   *         
   * Left/Up:    H/V:        ______        ___
   *                        |      |      |
   *                        |      |      |
   *                     ___|      |______|
   * 
   *             HQ/VQ:   ______        ______
   *                     |      |      |
   *                     |      |      |
   *                     |      |______|
   *         
   */   
  int h[4] = {0,0,0,0};
  int hq[4] = {0,0,0,0};
  int v[4] = {0,0,0,0};
  int vq[4] = {0,0,0,0};

  if (val & UP) {
#ifdef DEBUG
    Serial.println("=== UP ===");
#endif    
    v[0]  = 1; v[1]  = 0; v[2]  = 0; v[3]  = 1;
    vq[0] = 0; vq[1] = 0; vq[2] = 1; vq[3] = 1;
  } else if (val & DOWN) {
#ifdef DEBUG
    Serial.println("=== DOWN ===");
#endif    
    v[0]  = 0; v[1]  = 0; v[2]  = 1; v[3]  = 1;
    vq[0] = 1; vq[1] = 0; vq[2] = 0; vq[3] = 1;
  }
  if (val & LEFT) {
#ifdef DEBUG
    Serial.println("=== LEFT ===");
#endif    
    h[0]  = 1; h[1]  = 0; h[2]  = 0; h[3]  = 1;
    hq[0] = 0; hq[1] = 0; hq[2] = 1; hq[3] = 1;
  } else if (val & RIGHT) {
#ifdef DEBUG
    Serial.println("=== RIGHT ===");
#endif    
    h[0]  = 0; h[1]  = 0; h[2]  = 1; h[3]  = 1;
    hq[0] = 1; hq[1] = 0; hq[2] = 0; hq[3] = 1;
  }

#ifdef DEBUG
  for (int i = 0; i < 4; i++) {
    Serial.print("h["); Serial.print(i); Serial.print("] = "); Serial.print(h[i]);
    Serial.print("; hq["); Serial.print(i); Serial.print("] = "); Serial.print(hq[i]);
    Serial.print("; v["); Serial.print(i); Serial.print("] = "); Serial.print(v[i]);    
    Serial.print("; vq["); Serial.print(i); Serial.print("] = "); Serial.print(vq[i]);
    Serial.println();
  }
#endif

  digitalWrite(P_OUT_LMB, (val & FIRE) == 0);
  for(int i = 0; i < 4; i++) {
    digitalWrite(P_OUT_V_PULSE, v[i]);
    digitalWrite(P_OUT_VQ_PULSE, vq[i]);
    digitalWrite(P_OUT_H_PULSE, h[i]);
    digitalWrite(P_OUT_HQ_PULSE, hq[i]);
    delay(5);
  }
}
