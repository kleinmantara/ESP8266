/*
 * Copyright (C) 2018 kleinMantara <code@kleinmantara.de>
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

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <Pushover.h>

/***************************************************************************
Util methods

define the folling things:
const String VERSION = "1";
****************************************************************************/

extern "C" {
#include "user_interface.h"
}

void sendMessage(String text) {
  String title = String(host);
  title.concat(F(" ["));
  title.concat(VERSION);
  title.concat(F("]"));

  log(F("SEND"), text);
  Pushover po = Pushover("token", "user");
  po.setTitle(title);
  po.setMessage(text);
  po.setSound(F("none"));
  po.setUrl("http://" + WiFi.localIP().toString() +"/");
  po.setUrlTitle(F("Web-Admin"));
  po.send();
}

String getReadableBytes(unsigned int bytes) {
  float kB = bytes / 1024;
  float mB = kB / 1024;
  return String(mB) + "mB / " + kB + "kB /" + String(bytes) + "B";
}


String getNow() {
  String message = String("");
  message.concat(appendZeros(hour()));
  message.concat(F(":"));
  message.concat(appendZeros(minute()));
  message.concat(F(":"));
  message.concat(appendZeros(second()));
  message.concat(F(" "));
  message.concat(appendZeros(day()));
  message.concat(F("."));
  message.concat(appendZeros(month()));
  message.concat(F("."));
  message.concat(year());
  return message;
}

String appendZeros(byte value) {
  if (value < 10) {
    String s("0");
    s.concat(value);
    return s;
  }
  return String(value);
}
