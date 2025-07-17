#include <cs50.h>
#include <stdio.h>
int main(void)
{
    long x = get_long("Could you please provide your credit card number?");
    printf("Thank you!\n");
    int sum = 0;
    long temp = x;
    int position = 0;
    while (temp > 0)
    {
          int digit = temp % 10;

        if (position % 2 == 0)
        {
            sum += digit;
        }
        else
 {
            int doubled = digit * 2;
            if (doubled > 9)
            {
               sum += (doubled / 10) + (doubled % 10);
            }
            else
            {
               sum += doubled;
            }
       }

       temp /= 10;
position++;
   }

    if (sum % 10 != 0)
     {
printf("INVALID\n");
     return 0;
 }

    long start = x;
 while (start >= 100)
    {
    start = start / 10;
    }
     int length = 0;
     for (long temp = x; temp > 0; temp /= 10)
      {
length++;
     }
 if (length == 15 && (start == 34 || start == 37))
     {
 printf("AMEX\n");
     }
else if (length == 16 && (start >= 51 && start <= 55))
    {
printf("MASTERCARD\n");
     }
else if (length == 13 || length == 16 && (start / 10 == 4 || start == 4))
     {
 printf("VISA\n");
     }
     else
{
 printf("INVALID\n");
      return 0;
}
}
