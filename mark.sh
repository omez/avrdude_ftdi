#!/usr/bin/env bash

cp bin/Debug/avrdude_ftdi /usr/local/bin/avrdude_ftdi
chown root /usr/local/bin/avrdude_ftdi
chmod ug+s /usr/local/bin/avrdude_ftdi
chmod +x /usr/local/bin/avrdude_ftdi