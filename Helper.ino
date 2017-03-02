char commandBuffer[8];
byte index = 0;

bool scan(int * pFirst, int * pSecond)
{
   bool ended = false;
   int scanIndex = 0;
   while(Serial.available() > 0)
   {
      if(index < 8)
      {
         char letter = Serial.read();
         if(letter != '\n' && letter != '\r')
         {
            commandBuffer[index++] = letter;
            commandBuffer[index] = '\0';
         }
         else
         {
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

//---------------------------------------------------------------------
// Convert ASCII "0" to "9999" into an integer, -1 is value if no valid number is found, advances **pText
int decToInt(unsigned int * index) {
  char letter;
  int returnValue;
  int count;

  returnValue = 0;
  letter = commandBuffer[*index];
  
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
    returnValue = -1;
    goto exit;
  }
  
  if ((' ' == letter) || (':' == letter) )  // if the scanner hits a space, colon advance index and exit successfully
     (*index)++;

exit:
  return (returnValue);
}

