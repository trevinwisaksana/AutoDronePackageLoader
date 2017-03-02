

char commandBuffer[8];
byte index = 0;

/* Scan is a method that takes two different values
 * in the serial monitor. The first value will be
 * used to set the servo that will be controlled,
 * the second would be the angle.
 */
bool scan(int * pFirst, int * pSecond)
{
   bool ended = false;
   int scanIndex = 0;
   // While there is an input in the Serial Monitor
   while(Serial.available() > 0)
   {  
      // Takes less than 8 characters 
      if(index < 8)
      {   
         // Serial reads the input
         char letter = Serial.read();
         // Checks for space or a newline
         if(letter != '\n' && letter != '\r')
         {
            commandBuffer[index++] = letter;
            commandBuffer[index] = '\0';
         }
         else
         {
             // Converts the Serial value read into an integer
             *pFirst  = decToInt(&scanIndex);
             *pSecond = decToInt(&scanIndex);
             Serial.print("Servo = ");
             Serial.print(*pFirst, DEC);
             Serial.print(" Angle = ");
             Serial.println(*pSecond, DEC);
             ended = true;
             index = 0;
         }
      }
   }

   return ended;
}

// Convert ASCII "0" to "9999" into an integer, -1 is value if no valid number is found, advances **pText
int decToInt(unsigned int * index) {
  char letter;
  int returnValue;
  int count;

  returnValue = 0;
  letter = commandBuffer[*index];

  // If the letter is between 0 and 9
  if (('0' <= letter) && ('9' >= letter) )
  { 
    for (count = 0; count < 4; count++)
    {
      if (('0' <= letter) && ('9' >= letter) )
      {
        returnValue = returnValue * 10;
        returnValue += letter - '0';
        (*index)++;
        letter = commandBuffer[*index];
      }
      else
        break;
    }
  }
  else
  { 
    // No valid value found
    returnValue = -1;
    goto exit;
  }
  
  if ((' ' == letter) || (':' == letter) )  // if the scanner hits a space, colon advance index and exit successfully
     (*index)++;

exit:
  return (returnValue);
}

