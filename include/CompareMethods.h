/* 
 * File:   CompareMethods.h
 * Author: tsa
 *
 * Created on 21 septembre 2012, 17:39
 */

#ifndef COMPAREMETHODS_H
#define	COMPAREMETHODS_H

bool ltMethod(double a, double b)
{
   bool res = false;
   
   if (a < b)
   {
       res = true;
   }
   return res;
}

bool leMethod(double a, double b)
{
   bool res = false;
   
   if (a <= b)
   {
       res = true;
   }
   return res;   
}

bool eqMethod(double a, double b)
{
   bool res = false;
   
   if (a = b)
   {
       res = true;
   }
   return res;   
}

bool neMethod(double a, double b)
{
   bool res = false;
   
   if (a != b)
   {
       res = true;
   }
   return res;  
}

bool geMethod(double a, double b)
{
   bool res = false;
   
   if (a >= b)
   {
       res = true;
   }
   return res;    
}

bool gtMethod(double a, double b)
{
   bool res = false;
   
   if (a > b)
   {
       res = true;
   }
   return res;    
}

#endif	/* COMPAREMETHODS_H */

