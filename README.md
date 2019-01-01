AVR C++ RC5 remote control decoder library
==========================================

This is a C++ library for decoding infrared remote control commands encoded
with the Philips RC5 protocol.  It is based on the article
"An Efficient Algorithm for Decoding RC5 Remote Control Signals"
by Guy Carpenter, Oct 2001.

For more information see http://clearwater.com.au/code/rc5.

This library supports the extended RC5 protocol which uses the second
stop bit S2 as an extension to the command value.

See also http://www.sbprojects.com/knowledge/ir/rc5.php

This is a fork of the original Arduino library version, which can be found here: https://github.com/guyc/RC5
I removed the Arduino dependency to enable the usage with pure avr-g++ and avr-libc. Also, I did some other slight changes on the class interface.

TODO:
* add new/valid C++ example
* maybe create some callback interfaces/logic
